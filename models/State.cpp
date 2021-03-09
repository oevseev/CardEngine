//
// Created by Oleg Evseev on 06.03.2021.
//

#include "State.h"

bool State::operator==(const State &rhs) const
{
    if (trump != rhs.trump) {
        return false;
    }
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
