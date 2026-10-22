/**
 * Author: Chengxi Meng
 * Source: First Draft Template, page 22
 * Description: Splits valid UTF-8 into strings containing one Unicode code point each.
 * Combining marks remain separate; input bytes are not validated.
 * Usage:
 * auto parts=split_utf8("A\u4E2D\U0001F60A");
 * cout<<parts.size()<<' '<<parts[1].size(); // 3 3
 * Time: O(N) time and space for N input bytes.
 */
#pragma once
vec<string>split_utf8(const string&s) {
 vec<string>res;
 for(size_t i=0;i<s.length();) {
  int len=1;unsigned char c=s[i];
  if(c>=0xF0)len=4;
  else if(c>=0xE0)len=3;
  else if(c>=0xC0)len=2;
  res.push_back(s.substr(i, len));i+=len;
 }
 return res;
}
