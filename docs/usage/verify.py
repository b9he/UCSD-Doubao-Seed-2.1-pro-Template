"""Compile/run documented examples; adapt only explicitly marked fragments."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor,as_completed
import runpy,subprocess,json,re,platform
ROOT=Path(__file__).resolve().parents[2]
M=runpy.run_path(str(ROOT/'docs/usage/catalog.py')); E=M['ENTRIES']
compact_cpp=M['compact_cpp']
B=ROOT/'build/usage';A=B/'adapt';A.mkdir(parents=True,exist_ok=True)
CXX='/opt/homebrew/bin/g++-14'
P=B/'preamble.h';P.write_text((ROOT/'examples/preamble.h').read_text())
subprocess.run([CXX,'-std=c++17','-O0','-x','c++-header',str(P),'-o',str(P)+'.gch'],check=True,capture_output=True)
paths={p.name:p for p in M['active_headers']()}
def adapted(name,text):
 p=A/name;p.write_text(text);return p

def replace_code(text,old,new):
 old=compact_cpp(old);new=compact_cpp(new)
 assert old in text,old
 return text.replace(old,new)

def prepare(name,e):
 p=paths[name];mode=e['mode'];setup=e['setup'];body=compact_cpp(e['example']);source=p
 if mode=='x86' and platform.machine() not in ('x86_64','AMD64'):
  return None,'x86 AVX2 example: interface reviewed; not executable on this ARM host.'
 if mode=='fragment':
  body='int n=3;std::istringstream input("1 2 3");cin.rdbuf(input.rdbuf());\n#include "'+str(p)+'"\n'
  source=None
 elif mode=='fragment-inverse':
  body=body.replace('// Paste fragment here.','#include "'+str(p)+'"');source=None
 elif mode=='fragment-random':
  body=body.replace('// Paste fragment here.','#include "'+str(p)+'"');source=None
 elif mode=='fragment-timer':
  body=body.replace('int best=42;','int best=42;\n#include "'+str(p)+'"');source=None
 elif mode=='adapt':
  t=p.read_text()
  for a,b in e['adapt'].items():t=replace_code(t,a,b)
  source=adapted(name,t)
 elif mode=='adapt-ntt':
  dep=(ROOT/'content/number-theory/ModPow.h').read_text()
  dep=re.sub(r'^const ll mod\s*=.*\n','',dep,flags=re.M)
  t=p.read_text().replace('#include "../number-theory/ModPow.h"','const ll mod=998244353;\n'+dep)
  t=replace_code(t,'const ll mod = (119 << 23) + 1, root = 62;','const ll root = 62;')
  source=adapted(name,t)
 elif mode=='adapt-sqrt':
  t=p.read_text().replace('#include "ModPow.h"','#include "content/number-theory/ModMulLL.h"')
  source=adapted(name,t)
 elif mode=='patch':
  t=(ROOT/'content/numerical/SolveLinear.h').read_text()
  t=replace_code(t,'rep(j,i+1,n) {','rep(j,0,n) if(j!=i) {')
  at=t.index('\tx.assign(m, 0);');end=t.index('\treturn rank;',at)
  t=t[:at]+'''\tx.assign(m, undefined);
 rep(i,0,rank) {
  rep(j,rank,m) if(fabs(A[i][j])>eps) goto fail;
  x[col[i]]=b[i]/A[i][i];
 fail:; }
'''+t[end:]
  setup+='\nconst double undefined=numeric_limits<double>::quiet_NaN();\n'
  source=adapted(name,t)
 elif mode=='adapt-dp':
  setup+='\nvec<vec<ll>> dp(4,vec<ll>(4));vec<pii> res(4);\n'
  body='rep(i,0,4)rep(k,0,4)dp[i][k]=(i-k)*(i-k);\n'+body
 lines=['#include "'+str(P)+'"',setup]
 if source:lines.append('#include "'+str(source)+'"')
 lines.append('int main(){\n'+body+'\n}\n')
 return '\n'.join(lines),''

def run(name):
 e=E[name];s,reason=prepare(name,e)
 if s is None:return name,dict(status='platform',reason=reason)
 p=B/(name+'.cpp');p.write_text(s);exe=B/(name+'.out')
 try:
  q=subprocess.run([CXX,'-std=c++17','-O0','-I'+str(ROOT),str(p),'-o',str(exe)],capture_output=True,text=True,timeout=60)
  if q.returncode:return name,dict(status='compile-fail',error=q.stderr[-6000:])
  inp='12 -5\n' if name=='FastInput.h' else ''
  r=subprocess.run([str(exe)],input=inp,capture_output=True,text=True,timeout=15)
  if r.returncode:return name,dict(status='run-fail',code=r.returncode,error=r.stderr[-2000:],output=r.stdout[:500])
  return name,dict(status='pass',output=r.stdout[:600],mode=e['mode'])
 except subprocess.TimeoutExpired as x:return name,dict(status='timeout',error=str(x))

results={}
with ThreadPoolExecutor(max_workers=4) as pool:
 for f in as_completed([pool.submit(run,n) for n in E]):
  n,r=f.result();results[n]=r
  if r['status'] not in ('pass','platform'):print(n,r['status'],r.get('error',''),flush=True)
(B/'results.json').write_text(json.dumps(results,indent=2)+'\n')
from collections import Counter
print(dict(Counter(r['status'] for r in results.values())))
for n in sorted(results):
 r=results[n]
 if r['status']=='pass':print(n,repr(r['output']))
