/**
 * Author: Gemini
 * Date: 2025-11-11
 * License: Unknown
 * Source: own work
 * Description: Runs until close to the time limit. Good for brute forcing solutions.
 * Keep \texttt{start} and \texttt{timeLimit} outside the loop and refresh \texttt{now} inside. Print the saved answer at the marked timeout location before \texttt{exit(0)}.
 * Usage:
 * int best=42;
 * cout<<best; // 42
 * Status: tested
 */
#pragma once

auto start=chrono::high_resolution_clock::now();
auto timeLimit=chrono::milliseconds(900); // <- set to close to time limit
auto now=chrono::high_resolution_clock::now();
if (now-start>=timeLimit) {
    // <- output answer answer
    exit(0);
}