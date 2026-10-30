"""Build the audited, hash-pinned Xenon toolchain without sudo or upstream script execution.

Downloads must already be present in --downloads. Clone libxenon separately and
checkout the locked commit. Prefer a Linux filesystem for --work (e.g. /tmp).
No optional graphics/filesystem libraries or moving Git branches are downloaded.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import time

HERE = Path(__file__).resolve().parent

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--sdk', type=Path, required=True)
    p.add_argument('--downloads', type=Path, required=True)
    p.add_argument('--work', type=Path, required=True)
    p.add_argument('--prefix', type=Path, required=True)
    p.add_argument('--jobs', type=int, default=4)
    a = p.parse_args()
    sdk, work, prefix = a.sdk.resolve(), a.work.resolve(), a.prefix.resolve()
    lock = json.loads((HERE/'toolchain-lock.json').read_text())
    if subprocess.check_output(['git','rev-parse','HEAD'], cwd=sdk, text=True).strip() != lock['libxenon_commit']:
        raise SystemExit('SDK commit does not match toolchain-lock.json')
    subprocess.run(['git','diff','--exit-code','HEAD','--','toolchain','devkitxenon','libxenon'],cwd=sdk,check=True)
    for command in ('gcc','g++','make','bison','flex','makeinfo','patch','tar'):
        if not shutil.which(command):
            raise SystemExit('Missing host dependency: '+command)
    work.mkdir(parents=True, exist_ok=True)
    prefix.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, DEVKITXENON=str(prefix), PATH=str(prefix/'bin')+':'+os.environ['PATH'],
               CC='gcc', CXX='g++', CXXFLAGS='-O2 -std=gnu++11', CFLAGS='-O2 -fcommon')
    # Record actual commands/results immediately, even when a stage fails.
    evidence = work/'stages.json'
    stages = json.loads(evidence.read_text()) if evidence.exists() else []
    def run(label, command, cwd):
        logfile = work/(label+'.log')
        start = time.time()
        print(label, flush=True)
        with logfile.open('w') as log:
            rc = subprocess.call([str(v) for v in command], cwd=cwd, env=env, stdout=log, stderr=subprocess.STDOUT)
        stages.append(dict(stage=label,command=[str(v) for v in command],cwd=str(cwd),returncode=rc,
                           seconds=round(time.time()-start,2),log=str(logfile),
                           environment={key:env[key] for key in ('DEVKITXENON','CC','CXX','CFLAGS','CXXFLAGS')}))
        evidence.write_text(json.dumps(stages, indent=2))
        if rc:
            print(logfile.read_text()[-6000:], flush=True)
            raise SystemExit(rc)
    for source in lock['sources']:
        archive = a.downloads/Path(source['url']).name
        patch = sdk/'toolchain'/(source['name']+'.diff')
        for path, expected in ((archive, source['sha256']), (patch, source['patch_sha256'])):
            if hashlib.sha256(path.read_bytes()).hexdigest() != expected:
                raise SystemExit('Hash mismatch: '+str(path))
        if not (work/source['name']/'.patched').exists():
            if (work/source['name']).exists():
                raise SystemExit('Unmarked source directory exists; inspect it before retrying')
            run('extract-'+source['name'], ['tar','xf',archive.resolve()], work)
            run('patch-'+source['name'], ['patch','--batch','--fuzz=0','-p0','-i',patch], work)
            (work/source['name']/'.patched').touch()
    def build(label, source, options, targets):
        directory = work/label
        directory.mkdir(exist_ok=True)
        if (directory/'.installed').exists():
            print(label+' already installed', flush=True)
            return
        if not (directory/'Makefile').exists():
            run(label+'-configure', [work/source/'configure','--target=xenon','--prefix='+str(prefix)]+options, directory)
        for target in targets:
            run(label+'-'+target, ['make','-j'+str(a.jobs),target], directory)
        (directory/'.installed').touch()
    build('binutils', 'binutils-2.32', ['--enable-multilib','--disable-nls','--disable-werror'], ['all','install'])
    base = ['--with-cpu=cell','--enable-altivec','--with-newlib','--disable-nls','--disable-shared',
            '--disable-decimal-float','--disable-libssp','--disable-libquadmath','--disable-libsanitizer']
    build('gcc-bootstrap','gcc-9.2.0',base+['--enable-languages=c','--without-headers'],['all-gcc','install-gcc'])
    build('newlib','newlib-3.1.0',['--enable-multilib','--disable-nls','--enable-newlib-io-long-long',
          '--enable-newlib-io-long-double','CFLAGS_FOR_TARGET=-DHAVE_BLKSIZE -O2 -fcommon'],['all','install'])
    build('gcc-final','gcc-9.2.0',base+['--enable-languages=c,c++','--enable-cxx-flags=-G0',
          '--disable-libatomic','--disable-threads','--disable-libgomp','--disable-libitm',
          '--disable-libstdcxx-time','--disable-initfini-array','--disable-linux-futex'],['all','install'])
    sdk_build = sdk/'libxenon/ports/xenon'
    run('libxenon-build',['make','-j'+str(a.jobs),'libxenon.a'],sdk_build)
    run('libxenon-install',['make','install'],sdk_build)
    run('compiler-version',[prefix/'bin/xenon-gcc','--version'],work)
    print('Installed: '+str(prefix),flush=True)

if __name__ == '__main__':
    main()
