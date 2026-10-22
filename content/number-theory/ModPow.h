/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description:
 * Usage:
 * ll result=modpow(2, 10);cout<<result; // 1024
 * Status: tested
 */
#pragma once

const ll mod=1000000007; // faster if const

ll modpow(ll b, ll e) {
	ll ans=1;
	for (; e; b=b*b%mod, e/=2)
		if (e&1) ans=ans*b%mod;
	return ans;
}
