//
// Created by Oleg Evseev on 19.03.2021.
//

#include "AlphaBetaSolver.h"

#include "../models/preferans/PreferansDeal.h"
#include "../models/thousand/ThousandDeal.h"

std::pair<int, std::vector<PreferansState>> AlphaBetaSolver::evaluate(const PreferansDeal &deal, const PreferansState &state)
{
    // TODO: Reuse evaluation results
    score.clear();

    // TODO: Return best sequence of moves
    return {evaluateAlphaBeta(deal, state), std::vector<PreferansState>{}};
}

std::pair<int, std::vector<ThousandState>> AlphaBetaSolver::evaluate(const ThousandDeal &deal, const ThousandState &state)
{
    score.clear();
    return {evaluateAlphaBeta(deal, state), std::vector<ThousandState>{}};
}

template<typename DealT, typename StateT>
int AlphaBetaSolver::evaluateAlphaBeta(const DealT &deal, const StateT &state, int alpha, int beta)
{
    // TODO: Upper and lower possible bound pruning
    // TODO: Avoid possible under- and overflows

    if (score.contains(state)) {
        return score[state];
    }

    bool isMaximizingPlayer = state.currentPlayer == maximizingPlayer;

    int currentScore;
    if (isMaximizingPlayer) {
        currentScore = alpha;
    }
    else {
        currentScore = beta;
    }

    auto validMoves = deal.getValidMoves(state);
    if (validMoves.empty()) {
        currentScore = 0;
    }

    for (const auto &card : validMoves) {
        auto [newState, delta] = deal.playCard(state, card, maximizingPlayer);
        int newStateScore = evaluateAlphaBeta(deal, newState, alpha, beta);
        int newScore = newStateScore + delta;

        if (isMaximizingPlayer) {
            currentScore = std::max(currentScore, newScore);
            alpha = std::max(alpha, currentScore);
            if (alpha >= beta) {
                break;
            }
        }
        else {
            currentScore = std::min(currentScore, newScore);
            beta = std::min(beta, currentScore);
            if (beta <= alpha) {
                break;
            }
        }
    }

    score[state] = currentScore;
    return currentScore;
}
