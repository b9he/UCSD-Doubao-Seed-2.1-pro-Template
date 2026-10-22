/**
 * Author: Chengxi Meng
 * Source: First Draft Template.pdf, page 18
 * Description: Fixed-seed mt19937 and usage fragments. Paste inside a function
 * after declaring v, L, R and mod. Draws use inclusive [L,R]; mod must be positive.
 * The modulo draw can be biased. Use mt19937\_64 for 64-bit draws.
 * Usage:
 * vec<int>v={1, 2, 3};int L=1, R=10, mod=7;
 * // Paste fragment here.
 * cout<<rand_val; // in [1,10]
 * for(int x:v)cout<<x<<' '; // shuffled permutation
 * Time: O(N) shuffle; expected O(1) per draw; O(1) extra space.
 * Status: Layout preview; original implementation retained
 */
#pragma once
mt19937 rng(810975); shuffle(v.begin(), v.end(), rng);
int rand_val=uniform_int_distribution<int>(L, R)(rng);
int simple_rand=rng()%mod;
