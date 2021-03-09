//
// Created by Oleg Evseev on 07.03.2021.
//

#include "DealPresenter.h"

#include <utility>
#include <QMessageBox>

#include "../solvers/ThousandSolver.h"

DealPresenter::DealPresenter(QObject *parent) : QObject(parent)
{}

std::shared_ptr<Deal> DealPresenter::getDeal() const
{
    return deal;
}

void DealPresenter::setDeal(std::shared_ptr<Deal> newDeal)
{
    deal = std::move(newDeal);
    updateAll();
}

void DealPresenter::nextState()
{
    if (deal == nullptr) {
        return;
    }
    deal->nextState();
    updateAll();
}

void DealPresenter::previousState()
{
    if (deal == nullptr) {
        return;
    }
    deal->previousState();
    updateAll();
}

void DealPresenter::evaluateCurrentState()
{
    if (deal == nullptr) {
        return;
    }

    // TODO: Support other state types
    ThousandState s(static_cast<ThousandState &>(deal->getCurrentState()));

    QVector<QPair<Card, int>> estimates;
    for (const auto &[state, card, score] : s.transitions()) {
        int estimate = solve(state);
        estimates.append(qMakePair(card, estimate));
    }

    emit estimatesUpdated(estimates);
}

void DealPresenter::playCard(Card card)
{
    // TODO: Played card validation
    deal->playCard(card);
    updateAll();
}

void DealPresenter::updateAll()
{
    emit playerCountChanged(deal->getPlayerCount());

    State state = deal->getCurrentState();
    for (int playerId = 1; playerId <= deal->getPlayerCount(); playerId++) {
        QVector<Card> cards{};
        for (int cardId = 1; cardId <= NUM_CARDS; cardId++) {
            if (state.status[cardId] != CardStatus::IN_HAND) {
                continue;
            }
            if (state.owner[cardId] == playerId) {
                cards.append(Card(cardId));
            }
        }
        emit handChanged(playerId, cards);
    }

    emit estimatesUpdated({});
}
