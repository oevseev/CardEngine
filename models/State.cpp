//
// Created by Oleg Evseev on 06.03.2021.
//

#include "State.h"

bool State::operator==(const State &rhs) const
{
    if (leadSuit != rhs.leadSuit) {
        return false;
    }
    if (currentPlayer != rhs.currentPlayer) {
        return false;
    }
    for (int i = 1; i <= NUM_CARDS; i++) {
        if (status[i] != rhs.status[i] || owner[i] != rhs.owner[i]) {
            return false;
        }
    }
    return true;
}

bool State::operator!=(const State &rhs) const
{
    return !(rhs == *this);
}

std::size_t State::hash() const
{
    std::size_t result = 0;

    boost::hash_combine(result, leadSuit);
    boost::hash_combine(result, currentPlayer);
    for (int i = 1; i <= NUM_CARDS; i++) {
        boost::hash_combine(result, status[i]);
        boost::hash_combine(result, owner[i]);
    }

    return result;
}

std::size_t std::hash<State>::operator()(State const &s) const noexcept
{
    return s.hash();
}
