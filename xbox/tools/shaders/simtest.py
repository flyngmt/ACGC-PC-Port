"""Compile each variant with xsc, run it on the Xenos CPU simulator, compare with a Python TEV reference."""
import math, os, random, re, subprocess, sys
from pathlib import Path
# Usage: simtest.py <work dir from compile_variants.sh>; needs XSDK_DIR, and spirv-dis on PATH or in SPIRV_DIS.
B = Path(sys.argv[1])
SPIRV_DIS = os.environ.get('SPIRV_DIS', 'spirv-dis')
sys.path.insert(0, str(Path(os.environ['XSDK_DIR'])/'xenos-toolchain'))
import xsc.spirv as spirv
import xsc.lower as L
import xdis.simulate as sim
from xasm.program import RegisterBudget

MOD = ((15,8,10,15),(7,4,5,7),(0,0,0,0),(1,1,0,0),0)
ADD = ((0,8,10,15),(0,4,5,7),(0,0,0,0),(1,1,0,0),1)
KON = ((15,0,14,15),(7,0,6,7),(0,1,0,0),(1,1,0,0),0)
K = {
 'v1_tex_modulate': dict(st=[MOD],tex=(1,0,0)),
 'v2_lit_fog_alpha': dict(st=[MOD,KON],tex=(1,0,0),light=(1,1,0,1),l1=(1,1,0x0F),alpha=(4,0,7),fog=1),
 'v3_3stage_8light': dict(st=[MOD,ADD,KON],tex=(1,1,1),light=(1,1,1,1),l1=(1,1,0xFF),alpha=(4,1,1),fog=1,
                          ksel=[(12,16),(16,20),(1,28)]),
 'v4_indirect': dict(st=[MOD,ADD],tex=(1,1,0),light=(1,1,0,1),l1=(1,1,1),fog=1,
                     ind=[(0,1,3,0),(0,1,3,0)],wrap=[(0,0,0),(3,3,1)]),
}
LOC = dict(fog=0, prev=2, r0=3, r1=4, r2=5, chan=6, lpos=8, lcol=16, k=24, refs=28, m0=33, m1=36)

def clamp(x): return min(max(x, 0.0), 1.0)
def tex(slot, u, v):
    return [0.5+0.5*math.sin(3.1*u+1.7*v*(c+1)+(slot or 0)*2.3+c) for c in range(4)]
def konst_c(sel, kc):
    if sel <= 7: return [(8-sel)/8.0]*3
    if sel <= 11: return [0.0]*3
    if sel <= 15: return kc[sel-12][:3]
    return [kc[(sel-16) & 3][(sel-16) >> 2]]*3
def konst_a(sel, kc):
    if sel <= 7: return (8-sel)/8.0
    if sel <= 15: return 0.0
    return kc[(sel-16) & 3][(sel-16) >> 2]
def arg_c(i, P, T, R, r0, r1, r2, k):
    return {0:P[:3],1:[P[3]]*3,2:r0[:3],3:[r0[3]]*3,4:r1[:3],5:[r1[3]]*3,6:r2[:3],7:[r2[3]]*3,8:T[:3],9:[T[3]]*3,
            10:R[:3],11:[R[3]]*3,12:[1.0]*3,13:[.5]*3,14:k}.get(i,[0.0]*3)
def arg_a(i, P, T, R, r0, r1, r2, k):
    return {0:P[3],1:r0[3],2:r1[3],3:r2[3],4:T[3],5:R[3],6:k}.get(i,0.0)
def mix(a, b, c): return a*(1-c)+b*c

def reference(k, I, U, bind):
    st = k['st']; n = len(st)
    tc = [I['tc0'], I['tc1']]
    stc = []; prev_off = [0.0, 0.0]
    for s in range(n):
        base = tc[st[s][4]]; c = list(base)
        ind = k.get('ind');
        if ind and ind[s][1]:
            w = k['wrap'][s]; I0 = tex(bind['ind0'], tc[0][0], tc[0][1])[:3]
            b = list(I0); bias = ind[s][2]
            for a in range(3):
                if bias & (1 << a): b[a] -= .5
            idx = ind[s][1]-1
            off = [sum(x*y for x, y in zip(U['m0'][idx], b)), sum(x*y for x, y in zip(U['m1'][idx], b))]
            if w[2]: off = [off[0]+prev_off[0], off[1]+prev_off[1]]
            wc = list(c)
            for a in range(2):
                if 1 <= w[a] <= 5:
                    size = float(1 << (9-w[a])); v = c[a]*256.0
                    wc[a] = (v - size*math.floor(v/size))/256.0
            c = [wc[0]+off[0], wc[1]+off[1]]
            prev_off = [c[0]-base[0], c[1]-base[1]]
        stc.append(c)
    T = [tex(bind['t%d' % s], *stc[s]) if k['tex'][s] else [1.0]*4 for s in range(n)]
    light = k.get('light', (0,0,0,1)); l1 = k.get('l1', (0,0,0))
    ch = U['chan']; col = I['col']
    mat = col[:3] if light[1] else ch[0][:3]; amb = col[:3] if light[2] else ch[1][:3]
    if light[0]:
        acc = list(amb)
        for i in range(8):
            if l1[2] & (1 << i):
                p = U['lpos'][i]; ln = math.sqrt(sum(x*x for x in p)); L_ = [x/ln for x in p]
                d = clamp(sum(a*b for a, b in zip(I['nrm'], L_)))
                acc = [a + d*c for a, c in zip(acc, U['lcol'][i])]
        rgb = [m*clamp(a) for m, a in zip(mat, acc)]
    else:
        rgb = list(mat)
    mA = col[3] if l1[1] else ch[0][3]
    ras = rgb + [mA*ch[1][3] if l1[0] else mA]
    P, r0, r1, r2 = list(U['prev']), list(U['r0']), list(U['r1']), list(U['r2'])
    for s in range(n):
        ci, ai, bsc, out, _ = st[s]
        ks = k.get('ksel', [(12,16)]*3)[s]
        kc, ka = konst_c(ks[0], U['k']), konst_a(ks[1], U['k'])
        ca = [arg_c(i, P, T[s], ras, r0, r1, r2, kc) for i in ci]
        aa = [arg_a(i, P, T[s], ras, r0, r1, r2, ka) for i in ai]
        res = [ca[3][c] + mix(ca[0][c], ca[1][c], ca[2][c]) for c in range(3)]
        al = aa[3] + mix(aa[0], aa[1], aa[2])
        scale = [1, 2, 4, .5]
        res = [(v + [0, .5, -.5][bsc[0]])*scale[bsc[1]] for v in res]
        al = (al + [0, .5, -.5][bsc[2]])*scale[bsc[3]]
        if out[0]: res = [clamp(v) for v in res]
        if out[1]: al = clamp(al)
        P = res + [al]
    ctl = k.get('alpha', (7,0,7)); killed = False
    if ctl[0] != 7 or ctl[2] != 7:
        def t(c, ref): return {1: P[3] < ref, 4: P[3] > ref, 7: True}[c]
        p0, p1 = t(ctl[0], U['refs'][0]/255.0), t(ctl[2], U['refs'][1]/255.0)
        killed = not ((p0 and p1) if ctl[1] == 0 else (p0 or p1))
    c = list(P)
    if k.get('fog'):
        d = max(U['fog'][2]-U['fog'][1], 1e-6); f = clamp((I['fog']-U['fog'][1])/d)
        c = [mix(c[i], U['fogc'][i], f) for i in range(3)] + [c[3]]
    return c, killed

def rv(r, n=4): return [r.random() for _ in range(n)]

def bindings(spv):
    text = subprocess.run([SPIRV_DIS, str(spv)], capture_output=True, text=True).stdout
    d = {m[1]: int(m[2]) for m in re.finditer(r'OpDecorate %(u_\w+) Binding (\d+)', text)}
    order = {b: i for i, b in enumerate(sorted(d.values()))}   # fetch constants count from tf0 in binding order
    return {'t0': order.get(d.get('u_texture0')), 't1': order.get(d.get('u_texture1')), 't2': order.get(d.get('u_texture2')), 'ind0': order.get(d.get('u_ind_tex0'))}

def constants(U, manifest):
    c = {}
    c[0] = U['fog']; c[1] = U['fogc']
    for i, n in enumerate(('prev', 'r0', 'r1', 'r2')): c[2+i] = U[n]
    for i in range(2): c[6+i] = U['chan'][i]
    for i in range(8): c[8+i] = U['lpos'][i]+[0.0]; c[16+i] = U['lcol'][i]+[0.0]
    for i in range(4): c[24+i] = U['k'][i]
    c[28] = U['refs']+[0.0, 0.0]
    for i in range(3): c[33+i] = U['m0'][i]+[0.0]; c[36+i] = U['m1'][i]+[0.0]
    for e in manifest:
        if isinstance(e[0], int): c[e[0]] = list(e[1])
    return c

fails = 0
for name, k in K.items():
    spv = B/'v'/(name+'.f.spv')
    for opt in (False, True):
        try:
            blob, man = L.lower_ex(spirv.Module.parse(spv.read_bytes()), RegisterBudget(pixel=16, vertex=112), opt)
        except Exception as e:
            print(f'{name:20} opt={opt!s:5} COMPILE: {str(e)[:80]}'); continue
        bind = bindings(spv); r = random.Random(1234)
        bad = kills = 0; worst = 0.0; first = None; N = 2000
        for t in range(N):
            I = dict(col=rv(r), tc0=rv(r, 2), tc1=rv(r, 2), nrm=[x*2-1 for x in rv(r, 3)], fog=r.random())
            U = dict(fog=[0.0, r.random()*.4, .5+r.random()*.5, 0.0], fogc=rv(r), prev=rv(r), r0=rv(r), r1=rv(r), r2=rv(r),
                     chan=[rv(r), rv(r)], lpos=[[x+.1 for x in rv(r, 3)] for _ in range(8)], lcol=[rv(r, 3) for _ in range(8)],
                     k=[rv(r) for _ in range(4)], refs=[float(r.randrange(256)), float(r.randrange(256))],
                     m0=[[x-.5 for x in rv(r, 3)] for _ in range(3)], m1=[[x-.5 for x in rv(r, 3)] for _ in range(3)])
            want, wk = reference(k, I, U, bind)
            regs = {0: I['col'], 1: I['tc0']+[0.0, 0.0], 2: I['tc1']+[0.0, 0.0], 3: I['nrm']+[0.0], 4: [I['fog']]*4}
            res = sim.run(blob, regs, constants(U, man), texture_fetch=lambda s, c: tex(s, c[0], c[1]))
            kills += wk
            if bool(res.killed) != wk:
                bad += 1; first = first or ('kill', wk, res.killed); continue
            if wk: continue
            got = next(v for e, v in res.exports.items() if 'oC0' in str(e) or e == 0)
            err = max(abs(a-b) for a, b in zip(got, want))
            worst = max(worst, err)
            if err > 1e-3:
                bad += 1; first = first or (t, [round(x, 4) for x in got], [round(x, 4) for x in want])
        fails += bad
        print(f'{name:20} opt={opt!s:5} {N} runs, mismatches={bad}, kills={kills}, worst_err={worst:.2e}' + (f' first={first}' if first else ''))
print('TOTAL MISMATCHES', fails)
sys.exit(1 if fails else 0)
