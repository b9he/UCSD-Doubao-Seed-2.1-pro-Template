/**
 * Author: Gemini
 * Date: 2025-11-11
 * License: Unknown
 * Source: own work
 * Description: Random number generator. 
 * Usage: 
 * int x = distrib(rng);
 * Status: tested
 */
#pragma once


mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
uniform_int_distribution<> distrib(a, b); // [a, b]

