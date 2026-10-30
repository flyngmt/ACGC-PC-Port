"""Generate specialized default.frag variants, mirroring pc_gx_tev.c's emit_const_block."""
import re, sys
from pathlib import Path

src = Path(sys.argv[1]).read_text()
out = Path(sys.argv[2]); out.mkdir(exist_ok=True)
FOLDED = ["u_num_tev_stages","u_tev_color_in","u_tev_alpha_in","u_tev_color_op","u_tev_alpha_op",
          "u_tev_tc_src","u_tev_bsc","u_tev_out","u_tev_swap","u_tev_ksel","u_tev_ind_cfg",
          "u_tev_ind_wrap","u_use_texture","u_lighting_cfg0","u_lighting_cfg1","u_swap_table",
          "u_alpha_ctrl","u_num_ind_stages","u_fog_enable"]

def strip(s):
    keep = []
    for l in s.split('\n'):
        if l.startswith('#version'): continue
        if l.strip().startswith('uniform') and any(re.search(r'\b%s\b' % n, l) for n in FOLDED): continue
        keep.append(l)
    body, block = [], []
    for l in keep:
        if l.strip().startswith('uniform') and 'sampler' not in l:
            block.append(re.sub(r'/\*.*', '', l.strip()[len('uniform'):]).strip().replace('ivec2 u_alpha_refs', 'vec2 u_alpha_refs'))
        else:
            body.append(l)
    return 'layout(std140) uniform Frag {\n' + '\n'.join(block) + '\n};\n' + '\n'.join(body)

def arr(t, n, vals):
    return "const %s %s[%d] = %s[%d](%s);\n" % (t, n, len(vals), t, len(vals), ",".join(vals))
def iv(t, seq): return [ "%s(%s)" % (t, ",".join(map(str, v))) for v in seq ]


def expand_loop(s, header, var, n, guard):
    """Replace `for (...) { body }` with n literal copies of body."""
    i = s.index(header); j = s.index('{', i); d = 0; k = j
    while True:
        if s[k] == '{': d += 1
        elif s[k] == '}':
            d -= 1
            if d == 0: break
        k += 1
    body = s[j+1:k]
    out = ''
    for v in range(n):
        out += ('if (%d < %s) {' % (v, guard) if guard else '{') + re.sub(r'\b%s\b' % var, str(v), body) + '}\n'
    return s[:i] + out + s[k+1:]

def unloop(s):
    h = 'for (int s = 0; s < u_num_tev_stages; s++) {'
    s = expand_loop(s, h, 's', 3, 'u_num_tev_stages')
    s = expand_loop(s, h, 's', 3, 'u_num_tev_stages')
    return expand_loop(s, 'for (int i = 0; i < 8; i++) {', 'i', 8, None)

def fix_output(s):
    a = s.index('fragColor = prev;')
    tail = s[a:].replace('fragColor', 'outc').replace('outc = prev;', 'vec4 outc = prev;', 1)
    e = tail.rindex('}')
    return s[:a] + tail[:e] + '    fragColor = outc;\n}\n'

IDENT = [(0,1,2,3)]*4
def key(stages, tex, light=(0,0,0,1), light1=(0,0,0), alpha=(7,0,7), fog=0, ind=None, wrap=None, nind=0, ksel=None):
    # stages: list of (cin, ain, bsc, out, tc)
    n = len(stages)
    st = stages + [((15,15,15,15),(7,7,7,7),(0,0,0,0),(1,1,0,0),0)]*(3-n)
    c = "const int u_num_tev_stages = %d;\n" % n
    c += arr("ivec4","u_tev_color_in",iv("ivec4",[s[0] for s in st]))
    c += arr("ivec4","u_tev_alpha_in",iv("ivec4",[s[1] for s in st]))
    c += arr("int","u_tev_color_op",["0"]*3) + arr("int","u_tev_alpha_op",["0"]*3)
    c += arr("int","u_tev_tc_src",[str(s[4]) for s in st])
    c += arr("ivec4","u_tev_bsc",iv("ivec4",[s[2] for s in st]))
    c += arr("ivec4","u_tev_out",iv("ivec4",[s[3] for s in st]))
    c += arr("ivec2","u_tev_swap",iv("ivec2",[(0,0)]*3))
    c += arr("ivec3","u_tev_ksel",iv("ivec3",[(k[0],k[1],i) for i,k in enumerate(ksel or [(12,16)]*3)]))
    c += arr("ivec4","u_tev_ind_cfg",iv("ivec4",ind or [(0,0,0,0)]*3))
    c += arr("ivec3","u_tev_ind_wrap",iv("ivec3",wrap or [(0,0,0)]*3))
    c += arr("int","u_use_texture",[str(t) for t in tex])
    c += "const ivec4 u_lighting_cfg0 = ivec4(%d,%d,%d,%d);\n" % light
    c += "const ivec4 u_lighting_cfg1 = ivec4(%d,%d,%d,0);\n" % light1
    c += arr("ivec4","u_swap_table",iv("ivec4",IDENT))
    c += "const ivec3 u_alpha_ctrl = ivec3(%d,%d,%d);\n" % alpha
    c += "const int u_num_ind_stages = %d;\n" % nind
    c += "const int u_fog_enable = %d;\n" % fog
    return c

MOD = ((15,8,10,15),(7,4,5,7),(0,0,0,0),(1,1,0,0),0)        # tex * ras
ADD = ((0,8,10,15),(0,4,5,7),(0,0,0,0),(1,1,0,0),1)         # lerp(prev, tex, ras)
KON = ((15,0,14,15),(7,0,6,7),(0,1,0,0),(1,1,0,0),0)        # prev * konst, x2

V = {
 'v1_tex_modulate': key([MOD],(1,0,0)),
 'v2_lit_fog_alpha': key([MOD,KON],(1,0,0),light=(1,1,0,1),light1=(1,1,0x0F),alpha=(4,0,7),fog=1),
 'v3_3stage_8light': key([MOD,ADD,KON],(1,1,1),light=(1,1,1,1),light1=(1,1,0xFF),alpha=(4,1,1),fog=1,
                         ksel=[(12,16),(16,20),(1,28)]),
 'v4_indirect': key([MOD,ADD],(1,1,0),light=(1,1,0,1),light1=(1,1,0x01),fog=1,nind=1,
                    ind=[(0,1,3,0),(0,1,3,0),(0,0,0,0)],wrap=[(0,0,0),(3,3,1),(0,0,0)]),
}
for name, c in V.items():
    (out/(name+'.frag')).write_text("#version 330 core\n" + c + fix_output(unloop(strip(src))))
(out/'uber.frag').write_text(src)
print(*V, 'uber')
