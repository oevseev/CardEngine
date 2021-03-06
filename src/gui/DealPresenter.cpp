//
// Created by Oleg Evseev on 07.03.2021.
//

#include "DealPresenter.h"

#include <utility>
#include <QMessageBox>

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

std::shared_ptr<Solver> DealPresenter::getSolver() const
{
    return solver;
}

void DealPresenter::setSolver(std::shared_ptr<Solver> newSolver)
{
    solver = std::move(newSolver);
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
    if (deal == nullptr || solver == nullptr) {
        return;
    }

    auto scores = deal->evaluatePossibleMoves(*solver);

    QVector<QPair<Card, int>> estimates;
    for (const auto &[card, score] : scores) {
        estimates.append(qMakePair(card, score));
    }

    emit estimatesUpdated(estimates);
}

void DealPresenter::playCard(Card card)
{
    if (deal == nullptr) {
        return;
    }
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
