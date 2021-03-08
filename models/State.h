//
// Created by Oleg Evseev on 06.03.2021.
//

#ifndef STATE_H
#define STATE_H


#include <cstddef>
#include "Card.h"

enum class CardStatus {
    INACTIVE = 0, NOT_DEALT, IN_TALON, IN_HAND, IN_TRICK, PLAYED, DISCARDED
};

struct State {
    Suit trump = Suit::NONE;
    int currentPlayer = 0;
    int owner[NUM_CARDS + 1] = {0};
    CardStatus status[NUM_CARDS + 1] = {CardStatus::INACTIVE};
};


#endif //STATE_H
