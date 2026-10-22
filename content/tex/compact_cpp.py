"""Pack printed C++ whitespace without changing source files or code tokens."""
import re,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[2]/'docs/usage'))
from cppstyle import tokens,signature

def separate_blocks(source):
    """Keep a closing block separate from the next declaration/statement."""
    ts=[t for t in tokens(source) if t[0]!='space']
    edits=[]
    directive=False;protected=set();at=0
    for line in source.splitlines(keepends=True):
        directive=directive or line.lstrip().startswith('#')
        if directive:protected.add(at)
        directive=directive and line.rstrip().endswith('\\')
        at+=len(line)
    for i,t in enumerate(ts):
        if t[3]!='}':continue
        j=i+1
        if j<len(ts) and ts[j][3]==';':j+=1
        if j>=len(ts):continue
        next_token=ts[j]
        if next_token[0]!='identifier' or next_token[3] in ('else','catch','while'):continue
        end=ts[j-1][2];start=next_token[1]
        if '\n' in source[end:start] or source[end:start].strip():continue
        line_start=source.rfind('\n',0,t[1])+1
        if line_start in protected:continue
        indent=re.match(r'[ \t]*',source[line_start:]).group()
        edits.append((end,start,'\n'+indent))
    for a,b,replacement in reversed(edits):source=source[:a]+replacement+source[b:]
    return source

def compact_listing(source,width=62):
    original=source
    source=separate_blocks(source)
    lines=source.splitlines();locked=set();comments=set()
    offsets=[];at=0
    for i,line in enumerate(lines):offsets.append(at);at+=len(line)+1
    import bisect
    for kind,a,b,text in tokens(source):
        first=bisect.bisect_right(offsets,a)-1
        last=bisect.bisect_right(offsets,max(a,b-1))-1
        if kind in ('literal','comment') and first!=last:
            locked.update(range(first,last+1))
        if kind=='comment' and text.startswith('//'):comments.add(first)
    continuation=False
    for i,line in enumerate(lines):
        directive=continuation or line.lstrip().startswith('#')
        if directive:locked.add(i)
        continuation=directive and line.rstrip().endswith('\\')
    out=[]
    controls=re.compile(r'^(?:for|while|if|switch|case|default|else|do|try|catch)\b|^[A-Za-z_]\w*\s*:(?!:)')
    for i,line in enumerate(lines):
        if not line.strip() and i not in locked:continue
        text=line.rstrip();stripped=text.lstrip()
        if out and i not in locked and not out[-1][1] and not out[-1][2] and not stripped.startswith('//'):
            previous=out[-1][0].rstrip()
            close=stripped in ('}', '};') and '}' not in previous
            opening=(previous.endswith('{') and '{' not in stripped
                     and not controls.match(stripped))
            statement=(previous.endswith(';') and not previous.endswith('};')
                       and not previous.lstrip().startswith('}')
                       and not controls.match(previous.lstrip())
                       and not controls.match(stripped) and '{' not in stripped)
            alternative=previous.endswith('}') and stripped.startswith(('else','catch'))
            joined=previous+' '+stripped
            if (close or opening or statement or alternative) and len(joined.expandtabs(2))<=width:
                out[-1]=(joined,False,i in comments);continue
        out.append((text,i in locked,i in comments))
    result='\n'.join(s for s,_,_ in out)
    assert signature(original)==signature(result),'Printed packing changed C++ tokens'
    return result
