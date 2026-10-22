"""Compact operator spacing while preserving C++ preprocessing tokens."""
import re
PUNCTS=sorted('''%:%: <=> >>= <<= ->* ... :: ++ -- -> .* << >> <= >= == != && || += -= *= /= %= ^= &= |= ## <: :> <% %> %:'''.split(),key=len,reverse=True)
OPERATORS=set('+-=*/%&|^!~<>?:.')|set(PUNCTS)-{'...', '##', '<:', ':>', '<%', '%>', '%:', '%:%:'}|{'and','or','xor','not','bitand','bitor','compl','and_eq','or_eq','xor_eq','not_eq'}
IDENT=re.compile(r'[A-Za-z_][A-Za-z_0-9]*')
NUMBER=re.compile(r'(?:[0-9]|\.[0-9])(?:[A-Za-z_0-9\x27.]|(?<=[eEpP])[+-])*')
def tokens(s):
 out=[];i=0
 while i<len(s):
  start=i
  if s[i].isspace():
   i+=1
   while i<len(s) and s[i].isspace():i+=1
   kind='space'
  elif s.startswith('//',i):
   end=s.find('\n',i);i=len(s) if end<0 else end;kind='comment'
  elif s.startswith('/*',i):
   end=s.find('*/',i+2);assert end>=0,'Unclosed block comment';i=end+2;kind='comment'
  else:
   raw=re.match(r'(?:u8|u|U|L)?R"([^\s()\\]{0,16})\(',s[i:])
   quoted=re.match(r'(?:u8|u|U|L)?(["\x27])',s[i:])
   if raw:
    end=s.find(')'+raw[1]+'"',i+raw.end());assert end>=0,'Unclosed raw literal'
    i=end+len(raw[1])+2;kind='literal'
   elif quoted:
    quote=quoted[1];i+=quoted.end()
    while i<len(s):
     if s[i]=='\\':i+=2;continue
     if s[i]==quote:i+=1;break
     i+=1
    kind='literal'
   else:
    number=NUMBER.match(s,i);ident=IDENT.match(s,i)
    if number:i=number.end();kind='number'
    elif ident:i=ident.end();kind='identifier'
    else:
     op=next((p for p in PUNCTS if s.startswith(p,i)),None)
     i+=len(op) if op else 1;kind='punct'
  out.append((kind,start,i,s[start:i]))
 return out

def signature(s):return [(k,t) for k,a,b,t in tokens(s) if k not in ('space','comment')]
def can_join(a,b):
 try:return signature(a[3]+b[3])==[(a[0],a[3]),(b[0],b[3])]
 except AssertionError:return False
def compact_cpp(s):
 ts=[t for t in tokens(s) if t[0]!='space']
 if not ts:return s
 out=[s[:ts[0][1]],ts[0][3]]
 for a,b in zip(ts,ts[1:]):
  gap=s[a[2]:b[1]]
  if '\n' not in gap and '\r' not in gap and a[0]!='comment' and b[0]!='comment':
   prefix=s[s.rfind('\n',0,a[2])+1:a[2]]
   macro_boundary=bool(re.match(r'^\s*#\s*define\s+[A-Za-z_]\w*$',prefix))
   if a[3]==',':gap=' '
   elif b[3]==',':gap=''
   elif (a[3] in OPERATORS or b[3] in OPERATORS) and not macro_boundary and can_join(a,b):gap=''
  out.extend((gap,b[3]))
 out.append(s[ts[-1][2]:]);result=''.join(out)
 assert signature(s)==signature(result),'Formatting changed C++ tokens'
 assert s.count('\n')==result.count('\n'),'Formatting changed line count'
 return result
