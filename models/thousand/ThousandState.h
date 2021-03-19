//
// Created by Oleg Evseev on 08.03.2021.
//

#ifndef THOUSANDSTATE_H
#define THOUSANDSTATE_H

#include <cstddef>

#include <boost/functional/hash.hpp>

#include "../State.h"
#include "../Card.h"

// TODO: Remember marriage declarer

struct ThousandState : public State
{
    Suit trump = Suit::NONE;

    ThousandState();

    bool operator==(const ThousandState &rhs) const;
    bool operator!=(const ThousandState &rhs) const;

    [[nodiscard]] std::size_t hash() const override;
};

#endif //THOUSANDSTATE_H
