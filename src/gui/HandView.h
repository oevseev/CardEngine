//
// Created by Oleg Evseev on 26.02.2021.
//

#ifndef HANDVIEW_H
#define HANDVIEW_H

#include "../models/Card.h"
#include "CardView.h"

class HandView : public CardView
{
    Q_OBJECT

public:
    explicit HandView(QWidget *parent = nullptr);

public slots:
    void addCard(Card card);
    void removeCard(Card card);
    void setCards(QVector<Card> cards);

private:
    void recalculatePositions();
};

#endif //HANDVIEW_H
