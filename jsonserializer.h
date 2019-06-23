#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "strategy.h"
#include <QByteArray>
#include <QJsonObject>

class JSONSerializer {
public:
  JSONSerializer(const Strategy &strategy);

  QByteArray write() const;
  static std::optional<Strategy> read(const QString &json);
  static QByteArray writeActivities(const std::vector<Activity> &activities);
  static std::optional<std::vector<Activity>>
  readActivities(const QString &json);

private:
  const Strategy &strategy;
  static QJsonObject activityToJson(const Activity &activity);
  static std::optional<std::vector<Activity>>
  readActivities(const QJsonArray &jsonArray);
};

namespace Keys {
const QString slotDuration = "slotDuration";
const QString startTime = "startTime";
const QString activities = "activities";
const QString numberOfSlots = "numberOfSlots";
const QString name = "name";
const QString color = "color";
const QString slotsKey = "slots";
}; // namespace Keys

#endif // JSONSERIALIZER_H