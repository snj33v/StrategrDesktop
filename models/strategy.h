#ifndef STRATEGY_H
#define STRATEGY_H

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "activity.h"
#include "activitylist.h"
#include "timeslotsstate.h"
#include "activitysessionslist.h"
#include "strategyhistory.h"
#include "notifiableonchange.h"

struct Strategy : public NotifiableOnChange {
public:
    struct Defaults {
        static constexpr auto timeSlotDuration = 15;
        static constexpr auto beginTime = 6 * 60;
        static constexpr auto numberOfTimeSlots = (22 - 6) * 60 / timeSlotDuration;
    };

    using Duration = TimeSlot::Duration;
    using Time = TimeSlot::Time;
    using TimeSlotIndex = TimeSlotsState::Index;
    using StateSize = TimeSlotsState::StateSize;

    static constexpr auto NoActivity = TimeSlot::NoActivity;

    const ActivityList &activities() const;
    const ActivitySessionsList &activitySessions() const;
    const TimeSlotsState &timeSlots() const;

    explicit Strategy(Time beginTime = Defaults::beginTime,
                      Duration timeSlotDuration = Defaults::timeSlotDuration,
                      StateSize numberOfTimeSlots = Defaults::numberOfTimeSlots);

    Strategy(const TimeSlotsState &timeSlots, const ActivityList &activities);

    Time beginTime() const;
    void setBeginTime(Time beginTime);

    Duration timeSlotDuration() const;
    void setTimeSlotDuration(Duration timeSlotDuration);

    StateSize numberOfTimeSlots() const;
    void setNumberOfTimeSlots(StateSize numberOfTimeSlots);

    Time endTime() const;

    void addActivity(const Activity &activity);

    void removeActivityAtIndex(ActivityIndex activityIndex);

    void editActivityAtIndex(ActivityIndex activityIndex,
                             const Activity &newActivity);

    void dragActivity(ActivityIndex fromIndex, ActivityIndex toIndex);

    void putActivityInTimeSlotsAtIndices(ActivityIndex activityIndex,
                                         const std::vector<TimeSlotIndex> &timeSlotIndices);

    void emptyTimeSlotsAtIndices(const std::vector<TimeSlotIndex> &timeSlotIndices);;

    void fillTimeSlots(TimeSlotIndex fromIndex, TimeSlotIndex tillIndex);

    void commitToHistory();
    void undo();
    void redo();

    // TODO
//    std::optional<ActivitySession *> currentSession() {
//
//    }
//
//    std::optional<ActivitySession *> nextSession() {
//
//    }

private:
    ActivityList _activities;
    TimeSlotsState _timeSlots;
    ActivitySessionsList _activitySessions;
    StrategyHistory history;

    void timeSlotsChanged();
    void setupTimeSlotsCallback();

    StrategyHistory::Entry makeHistoryEntry();
};

#endif // STRATEGY_H