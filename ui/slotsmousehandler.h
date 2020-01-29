//
// Created by Dmitry Khrykin on 2019-07-10.
//

#ifndef STRATEGR_SLOTSMOUSEHANDLER_H
#define STRATEGR_SLOTSMOUSEHANDLER_H

#include <QMouseEvent>
#include <QFrame>
#include "strategy.h"
#include "cursorprovider.h"
#include "colorprovider.h"
#include "sessionsmainwidget.h"
#include "mousehandler.h"
#include "slotswidget.h"

class SessionWidget;
class QPropertyAnimation;

class SlotsMouseHandler :
        public QFrame,
        public CursorProvider,
        public ColorProvider {
public:
    explicit SlotsMouseHandler(SlotsWidget *slotsWidget);

    void reset();
private:
    static const auto stretchZoneHeight = 3;

    struct StretchZonePosition;

    enum class Operation {
        Drag,
        StretchTop,
        StretchBottom,
        DragSelect,
        OpenActivities
    };

    enum class MouseZone {
        DragZone,
        TopStretchZone,
        BottomStretchZone,
    };

    enum class Direction {
        Up,
        Down
    };

    SlotsWidget *slotsWidget;

    stg::mousehandler handler{slotsWidget->strategy,
                              [this]() {
                                  return slotsWidget->_slotHeight;
                              },
                              [this]() {
                                  return stg::rect(slotsWidget->slotsLayout->contentsRect());
                              }};

    std::optional<Operation> operation = std::nullopt;
    std::optional<Direction> direction = std::nullopt;

    std::optional<MouseZone> currentMouseZone = std::nullopt;

    int currentSlotIndex = -1;
    int clickedSessionIndex = -1;

    int previousMouseTop = 0;
    int handleSlotIndex = -1;

    std::optional<int> resizeBoundarySlotIndex = std::nullopt;

    bool mousePressHappened = false;
    bool isPerformingAutoscroll = false;

    QPropertyAnimation *autoscrollAnimation = nullptr;

    SessionWidget *sessionWidgetAtIndex(int sessionIndex);
    SessionWidget *sessionWidgetAtSlotIndex(int timeSlotIndex);

    stg::strategy &strategy();
    int slotHeight();

    int firstSlotTopOffset();

    template<class Event>
    int relativeTop(Event *event) {
        return event->pos().y() - firstSlotTopOffset();
    }

    template<class Event>
    int slotIndexForEvent(Event *event) {
        return relativeTop(event) / slotHeight();
    }

    bool hasSelection();
    void selectSlotAtIndex(int slotIndex);
    void fillSelection(int fromIndex, int toIndex);

    void selectSessionAtSlotIndex(int slotIndex);
    void selectSessionsAtIndices(const std::vector<int> &sessionIndices);
    void selectStetchingSessions(int sourceIndex);
    void setSelectedForSessionIndex(int sessionIndex, bool isSelected);
    void deselectAllSessions();

    void updateCursor(stg::mousehandler::cursor new_cursor);
    SlotsMouseHandler::MouseZone determineMouseZone(const QMouseEvent *event, int slotIndex);

    std::optional<Operation> determineOperationForMouseZone(MouseZone mouseZone);
    std::optional<Direction> determineDirection(const QMouseEvent *event);

    int sessionIndexForSlotIndex(int slotIndex);

    void handleDragOperation(QMouseEvent *event);
    void handleMouseHover(const QMouseEvent *event);
    void handleStretchOperation(QMouseEvent *event);
    void handleLeftButtonPress(const QMouseEvent *event);
    void handleResizeDirectionChange(const std::optional<Direction> &previousDirection);

    bool checkForDirectionChange(const QMouseEvent *event);

    int getMouseTopDelta(int currentMouseTop, int previousMouseTop);

    bool isSlotIndexSelected(int slotIndex);

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void initDragSelectedOperation();

    QScrollArea *slotBoardScrollArea() const;
    QScrollBar *verticalScrollBar() const;
    void handleAutoScroll(const QMouseEvent *event);
    void resetAutoscrollAnimation();

    friend std::ostream &operator<<(std::ostream &os, Direction direction);
};


struct SlotsMouseHandler::StretchZonePosition {
    explicit StretchZonePosition(int top = 0) : _top(top) {}

    int top() {
        return _top;
    }

    int bottom() {
        return top() + stretchZoneHeight;
    }

private:
    int _top = 0;
};


#endif //STRATEGR_SLOTSMOUSEHANDLER_H
