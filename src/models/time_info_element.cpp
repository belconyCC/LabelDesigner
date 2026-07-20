#include "time_info_element.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

namespace LabelDesigner {

TimeInfoElement::TimeInfoElement()
    : m_timeFormat(TimeFormat::DateTime),
      m_timeOffset(0),
      m_alignment(Qt::AlignLeft | Qt::AlignVCenter) {
    generateId();
    setName("Time Info");
}

TimeInfoElement::TimeInfoElement(const QString& name)
    : m_timeFormat(TimeFormat::DateTime),
      m_timeOffset(0),
      m_alignment(Qt::AlignLeft | Qt::AlignVCenter) {
    generateId();
    setName(name);
}

QString TimeInfoElement::getFormattedTime() const {
    QDateTime dt = QDateTime::currentDateTime().addSecs(m_timeOffset);
    
    switch (m_timeFormat) {
    case TimeFormat::Year:
        return dt.toString("yyyy");
    case TimeFormat::YearMonth:
        return dt.toString("yyyy-MM");
    case TimeFormat::Date:
        return dt.toString("yyyy-MM-dd");
    case TimeFormat::DateTime:
        return dt.toString("yyyy-MM-dd HH:mm:ss");
    case TimeFormat::Time:
        return dt.toString("HH:mm:ss");
    case TimeFormat::DateTimeMs:
        return dt.toString("yyyy-MM-dd HH:mm:ss.zzz");
    case TimeFormat::Week: {
        int weekNum = dt.date().weekNumber();
        return QString("%1").arg(weekNum, 2, 10, QChar('0'));
    }
    case TimeFormat::Custom:
        return dt.toString(m_customFormat);
    default:
        return dt.toString("yyyy-MM-dd HH:mm:ss");
    }
}

std::map<QString, QVariant> TimeInfoElement::getProperties() const {
    std::map<QString, QVariant> props;
    props["id"] = m_id;
    props["name"] = m_name;
    props["time_format"] = static_cast<int>(m_timeFormat);
    props["custom_format"] = m_customFormat;
    props["time_offset"] = m_timeOffset;
    props["font_family"] = m_font.family();
    props["font_size"] = m_font.pointSize();
    props["color"] = m_color.name();
    props["alignment"] = m_alignment;
    return props;
}

void TimeInfoElement::setProperty(const QString& key, const QVariant& value) {
    if (key == "time_format") {
        m_timeFormat = static_cast<TimeFormat>(value.toInt());
    } else if (key == "custom_format") {
        m_customFormat = value.toString();
    } else if (key == "time_offset") {
        m_timeOffset = value.toInt();
    } else if (key == "font_family") {
        m_font.setFamily(value.toString());
    } else if (key == "font_size") {
        m_font.setPointSize(value.toInt());
    } else if (key == "color") {
        m_color = QColor(value.toString());
    } else if (key == "alignment") {
        m_alignment = value.toInt();
    }
}

QString TimeInfoElement::toJson() const {
    QJsonObject obj;
    obj["id"] = m_id;
    obj["name"] = m_name;
    obj["type"] = "TimeInfo";
    obj["time_format"] = static_cast<int>(m_timeFormat);
    obj["custom_format"] = m_customFormat;
    obj["time_offset"] = m_timeOffset;
    obj["rect_x"] = m_rect.x();
    obj["rect_y"] = m_rect.y();
    obj["rect_width"] = m_rect.width();
    obj["rect_height"] = m_rect.height();
    
    QJsonObject font;
    font["family"] = m_font.family();
    font["size"] = m_font.pointSize();
    font["bold"] = m_font.bold();
    font["italic"] = m_font.italic();
    obj["font"] = font;
    
    obj["color"] = m_color.name();
    obj["alignment"] = m_alignment;

    QJsonDocument doc(obj);
    return QString::fromUtf8(doc.toJson());
}

void TimeInfoElement::fromJson(const QString& json) {
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isObject()) return;
    
    QJsonObject obj = doc.object();
    m_id = obj["id"].toString();
    m_name = obj["name"].toString();
    m_timeFormat = static_cast<TimeFormat>(obj["time_format"].toInt());
    m_customFormat = obj["custom_format"].toString();
    m_timeOffset = obj["time_offset"].toInt();
    
    m_rect = QRect(
        obj["rect_x"].toInt(),
        obj["rect_y"].toInt(),
        obj["rect_width"].toInt(),
        obj["rect_height"].toInt()
    );
    
    QJsonObject fontObj = obj["font"].toObject();
    m_font.setFamily(fontObj["family"].toString());
    m_font.setPointSize(fontObj["size"].toInt());
    m_font.setBold(fontObj["bold"].toBool());
    m_font.setItalic(fontObj["italic"].toBool());
    
    m_color = QColor(obj["color"].toString());
    m_alignment = obj["alignment"].toInt();
}

std::unique_ptr<LabelElement> TimeInfoElement::clone() const {
    auto clone = std::make_unique<TimeInfoElement>();
    clone->m_id = m_id;
    clone->m_name = m_name;
    clone->m_timeFormat = m_timeFormat;
    clone->m_customFormat = m_customFormat;
    clone->m_timeOffset = m_timeOffset;
    clone->m_rect = m_rect;
    clone->m_font = m_font;
    clone->m_color = m_color;
    clone->m_alignment = m_alignment;
    return clone;
}

} // namespace LabelDesigner
