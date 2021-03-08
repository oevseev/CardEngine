//
// Created by Oleg Evseev on 26.02.2021.
//

#include "HandView.h"

#include <QBitmap>
#include <QDrag>
#include <QHBoxLayout>
#include <QMimeData>
#include <QPainter>

HandView::HandView(QWidget *parent) : CardView(parent)
{
}

void HandView::addCard(Card card)
{
    for (const auto &entries : cardEntries) {
        if (entries.card == card) {
            return;
        }
    }
    cardEntries.append(Entry(card));
    recalculatePositions();
}

void HandView::removeCard(Card card)
{
    for (int i = 0; i < cardEntries.size(); i++) {
        if (cardEntries.at(i).card == card) {
            cardEntries.remove(i);
            break;
        }
    }
    recalculatePositions();
}

void HandView::setCards(QVector<Card> cards)
{
    cardEntries.clear();
    for (auto card : cards) {
        cardEntries.append(Entry(card));
    }
    recalculatePositions();
}

void HandView::recalculatePositions()
{
    // TODO: Group by suit
    // TODO: Sort by specified rank
    // TODO: Vertical alignments
    for (int i = 0; i < cardEntries.size(); i++) {
        cardEntries[i].position = QPoint(i * 15, 0);
    }
    repaint();
    updateGeometry();
}