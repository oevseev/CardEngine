//
// Created by Oleg Evseev on 25.02.2021.
//

#include "ThousandSolver.h"

#include <unordered_map>

std::unordered_map<ThousandState, int> dp;

int solve(ThousandState s, int alpha, int beta)
{
    if (dp.contains(s)) {
        return dp[s];
    }

    auto transitions = s.transitions();
    if (transitions.empty()) {
        dp[s] = 0;
        return dp[s];
    }

    if (s.currentPlayer == 1) {
        dp[s] = 0;
        for (const auto &t : transitions) {
            dp[s] = std::max(dp[s], solve(t.first, alpha, beta) + t.second);
            alpha = std::max(alpha, dp[s]);
            if (alpha >= beta) {
                break;
            }
        }
    }
    else {
        dp[s] = INT_MAX;
        for (const auto &t : s.transitions()) {
            dp[s] = std::min(dp[s], solve(t.first, alpha, beta) + t.second);
            beta = std::min(beta, dp[s]);
            if (beta <= alpha) {
                break;
            }
        }
    }

    return dp[s];
}
