//
// Created by Oleg Evseev on 07.03.2021.
//

#ifndef CARDVIEW_H
#define CARDVIEW_H

#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QWidget>

#include "../models/Card.h"

class CardView : public QWidget
{
    Q_OBJECT

public:
    explicit CardView(QWidget *parent = nullptr);

    // TODO: Maybe it's better to move it to the model layer
    void setEstimate(Card card, int estimate);
    void clearEstimates();

signals:
    void cardClicked(Card card);
    void cardDragged(Card card);
    void cardDropped(Card card);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    [[nodiscard]] QSize minimumSizeHint() const override;
    [[nodiscard]] QSize sizeHint() const override;

    void hideCard(Card card);
    void showCard(Card card);

    struct Entry
    {
        Card card;
        QPoint position;
        bool visible;
        int estimate;

        explicit Entry(Card card = Card{}, QPoint position = QPoint{}, bool visible = true, int estimate = -1)
            : card(card), position(position), visible(visible), estimate(estimate)
        {}
    };

    QVector<Entry> cardEntries{};

private:
    [[nodiscard]] static QPixmap getCardPixmap(Card card);
    [[nodiscard]] Entry getCardEntryAt(QPoint point) const;
    void setCardVisibility(Card card, bool hidden);
    void startDrag(const QPoint &pos);

    static QHash<int, QPixmap> cardPixmaps;
    QPoint lastClickPos;
};

#endif //CARDVIEW_H
