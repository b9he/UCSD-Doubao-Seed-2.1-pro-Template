/**
 * Author: Chengxi Meng
 * Source: First Draft Template.pdf, page 18
 * Description: Nonnegative base-1e9 integers with arithmetic, comparisons and streams.
 * Subtraction requires a >= b. Construct numeric zero as BigInt(0).
 * Scalar operands should not exceed 2e9; division/modulo require a positive divisor.
 * Usage:
 * BigInt a(string("1000000000000000000")), b(7);
 * BigInt c=a+b;cout<<c; // 1000000000000000007
 * cout<<(a-b<a); // 1
 * Time: O(D) add/subtract, O(D^2) multiply, O(D) space.
 * Status: Layout preview; original implementation retained
 */
#pragma once
struct BigInt { static const int BASE=1e9; vec<int>v;
	BigInt() {} BigInt(ll val) { if (val==0) v.push_back(0);
		while (val>0) { v.push_back(val%BASE); val/=BASE; } }
	BigInt(string s) {
		if (s.empty()||s=="0") { v.push_back(0); return; }
		for (int i=(int)s.length(); i>0; i-=9) {
			if (i<9) v.push_back(stoi(s.substr(0, i)));
			else v.push_back(stoi(s.substr(i-9, 9))); } trim(); }
	void trim() {
		while (v.size()>1&&v.back()==0) v.pop_back(); }
	bool operator<(const BigInt&b) const {
		if (v.size()!=b.v.size()) return v.size()<b.v.size();
		for (int i=(int)v.size()-1; i>=0; i--) {
			if (v[i]!=b.v[i]) return v[i]<b.v[i]; } return false;
	} bool operator>(const BigInt&b) const { return b<
*this; }
	bool operator<=(const BigInt&b) const { return!(b<
*this); } bool operator>=(const BigInt&b) const { return!
(*this<b); }
	bool operator==(const BigInt&b) const { return!
(*this<b)&&!(b<*this); }
	bool operator!=(const BigInt&b) const { return
(*this<b)||(b<*this); }
	BigInt operator+(const BigInt&b) const { BigInt res;
		int n=max(v.size(), b.v.size()); ll carry=0;
		for (int i=0; i<n||carry; i++) { ll sum=carry;
			if (i<v.size()) sum+=v[i];
			if (i<b.v.size()) sum+=b.v[i];
			res.v.push_back(sum%BASE); carry=sum/BASE; }
		res.trim(); return res; }
	BigInt operator-(const BigInt&b) const { BigInt res;
		ll borrow=0; for (int i=0; i<v.size(); i++) {
			ll diff=v[i]-borrow-(i<b.v.size()?b.v[i]:0);
			if (diff<0) { diff+=BASE; borrow=1; }
			else borrow=0; res.v.push_back(diff); } res.trim();
		return res; } BigInt operator*(const BigInt&b) const {
		if ((v.size()==1&&v[0]==0)||(b.v.size()==
1&&b.v[0]==0)) return BigInt(0); BigInt res;
		res.v.assign(v.size()+b.v.size(), 0);
		for (int i=0; i<v.size(); i++) { ll carry=0;
			for (int j=0; j<b.v.size()||carry; j++) {
				ll cur=res.v[i+j]+1LL*v[i]*
(j<b.v.size()?b.v[j]:0)+carry;
				res.v[i+j]=cur%BASE; carry=cur/BASE; } }
		res.trim(); return res; }
	BigInt operator*(const ll&b) const {
		if (b==0||(v.size()==1&&v[0]==0)) return
BigInt(0); BigInt res; ll carry=0;
		for (int i=0; i<v.size()||carry; i++) {
			ll cur=carry; if (i<v.size()) cur+=1LL*v[i]*b;
			res.v.push_back(cur%BASE); carry=cur/BASE; }
		res.trim(); return res; }
	BigInt operator/(const ll&b) const { BigInt res;
		res.v.assign(v.size(), 0); ll rem=0;
		for (int i=(int)v.size()-1; i>=0; i--) {
			rem=rem*BASE+v[i]; res.v[i]=rem/b; rem%=b; }
		res.trim(); return res; }
	ll operator%(const ll&b) const { ll rem=0;
		for (int i=(int)v.size()-1; i>=0; i--) {
			rem=(rem*BASE+v[i])%b; } return rem; }
	friend istream&operator>>(istream&is, BigInt&a) {
		string s; is>>s; a=BigInt(s); return is; }
	friend ostream&operator<<(ostream&os, const BigInt&a) {
		if (a.v.empty()) { os<<0; return os; } os<<a.v.back();
		for (int i=(int)a.v.size()-2; i>=0; i--) {
			os<<setfill('0')<<setw(9)<<a.v[i]; } return os; }
};
