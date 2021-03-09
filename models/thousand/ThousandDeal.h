//
// Created by Oleg Evseev on 08.03.2021.
//

#ifndef THOUSANDDEAL_H
#define THOUSANDDEAL_H


#include "../Deal.h"
#include "ThousandState.h"

class ThousandDeal : public Deal
{
public:
    ThousandDeal();

    [[nodiscard]] int getPlayerCount() const override;
    void playCard(Card card) override;
};


#endif //THOUSANDDEAL_H
