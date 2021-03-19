//
// Created by Oleg Evseev on 10.03.2021.
//

#include "PreferansDeal.h"

const int PREFERANS_PLAYER_COUNT = 3;

PreferansDeal::PreferansDeal(Suit trump) : DealImpl<PreferansState>(), trump(trump)
{}

int PreferansDeal::getPlayerCount() const
{
    return PREFERANS_PLAYER_COUNT;
}

Suit PreferansDeal::getTrump() const
{
    return trump;
}

void PreferansDeal::setTrump(Suit newTrump)
{
    trump = newTrump;
}

std::pair<int, std::vector<PreferansState>> PreferansDeal::evaluateState(Solver &solver, const PreferansState &state) const
{
    return solver.evaluate(*this, state);
}

std::pair<PreferansState, int> PreferansDeal::playCard(const PreferansState &state, Card card, int player) const
{
    // TODO: Implement card play
    throw std::runtime_error("not implemented");
}
