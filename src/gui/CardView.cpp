//
// Created by Oleg Evseev on 07.03.2021.
//

#include "CardView.h"

#include <QApplication>
#include <QBitmap>
#include <QDrag>
#include <QHBoxLayout>
#include <QMimeData>
#include <QPainter>

QHash<int, QPixmap> CardView::cardPixmaps{};

CardView::CardView(QWidget *parent) : QWidget(parent)
{
    // setAcceptDrops(true);
}

void CardView::setEstimate(Card card, int estimate)
{
    for (auto &entry : cardEntries) {
        if (entry.card == card) {
            entry.estimate = estimate;
        }
    }
    repaint();
}

void CardView::clearEstimates()
{
    for (auto &entry : cardEntries) {
        entry.estimate = -1;
    }
    repaint();
}

void CardView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-1000card") && event->source() != this) {
        event->acceptProposedAction();
    }
    else {
        event->ignore();
    }
}

void CardView::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-1000card") && event->source() != this) {
        event->acceptProposedAction();
    }
    else {
        event->ignore();
    }
}

void CardView::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-1000card")) {
        QByteArray itemData = event->mimeData()->data("application/x-1000card");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        int id;
        dataStream >> id;
        emit cardDropped(id);

        event->acceptProposedAction();
    }
    else {
        event->ignore();
    }
}

void CardView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint currentPos = event->pos();
    if ((lastClickPos - currentPos).manhattanLength() >= QApplication::startDragDistance()) {
        startDrag(currentPos);
    }
}

void CardView::mousePressEvent(QMouseEvent *event)
{
    lastClickPos = event->pos();
}

void CardView::mouseReleaseEvent(QMouseEvent *event)
{
    // Should not interfere with drag & drop, should it?
    emit cardClicked(getCardEntryAt(lastClickPos).card);
}

void CardView::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setPen(QPen(QColorConstants::Blue));
    painter.setFont(QFont("Arial", 8));

    for (const auto &entry : cardEntries) {
        if (!entry.visible) {
            continue;
        }
        QPixmap pixmap = getCardPixmap(entry.card);
        painter.drawPixmap(entry.position, pixmap);
        if (entry.estimate != -1) {
            QRect rect(entry.position.x() + 1, entry.position.y() + 30, 20, 20);
            painter.drawText(rect, QString("%1").arg(entry.estimate));
        }
    }
}

QSize CardView::minimumSizeHint() const
{
    int maxWidth = 0, maxHeight = 0;

    for (auto entry : cardEntries) {
        QPixmap pixmap = getCardPixmap(entry.card);
        QRect rect(entry.position, pixmap.size());
        QPoint point = rect.bottomRight();

        maxWidth = std::max(maxWidth, point.x());
        maxHeight = std::max(maxHeight, point.y());
    }

    return QSize(maxWidth, maxHeight);
}

QSize CardView::sizeHint() const
{
    return minimumSizeHint();
}

void CardView::hideCard(Card card)
{
    setCardVisibility(card, false);
}

void CardView::showCard(Card card)
{
    setCardVisibility(card, true);
}

QPixmap CardView::getCardPixmap(Card card)
{
    int id = card.getId();

    // TODO: More beautiful way to reuse card pixmaps
    if (!cardPixmaps.contains(id)) {
        // TODO: Use resources instead of file path
        auto fileName = QString("resources/images/cards/Bitmap%1.bmp").arg(id);
        QPixmap pixmap(fileName);

        // TODO: Preload mask
        pixmap.setMask(pixmap.createHeuristicMask());

        cardPixmaps[id] = pixmap;
    }
    return cardPixmaps[id];
}

CardView::Entry CardView::getCardEntryAt(QPoint point) const
{
    for (auto it = cardEntries.crbegin(); it != cardEntries.crend(); ++it) {
        if (!it->visible) {
            continue;
        }
        QPixmap cardPixmap = getCardPixmap(it->card);
        QRect rect(it->position, cardPixmap.size());
        if (rect.contains(point)) {
            return *it;
        }
    }
    return CardView::Entry{};
}

void CardView::setCardVisibility(Card card, bool visible)
{
    for (auto &entry : cardEntries) {
        if (entry.card == card) {
            entry.visible = visible;
            repaint();
            return;
        }
    }
}

void CardView::startDrag(const QPoint &currentPos)
{
    auto entry = getCardEntryAt(lastClickPos);
    int id = entry.card.getId();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << id;

    auto *mimeData = new QMimeData;
    mimeData->setData("application/x-1000card", itemData);

    auto *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(getCardPixmap(entry.card));
    drag->setHotSpot(currentPos - entry.position);

    hideCard(entry.card);
    if (drag->exec() == Qt::MoveAction) {
        emit cardDragged(entry.card);
    }
    else {
        showCard(entry.card);
    }
}
