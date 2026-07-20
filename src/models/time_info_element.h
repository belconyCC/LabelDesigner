#pragma once

#include "label_element.h"
#include <QDateTime>
#include <QFont>
#include <QColor>

namespace LabelDesigner {

enum class TimeFormat {
    Year,           // yyyy
    YearMonth,      // yyyy-MM
    Date,           // yyyy-MM-dd
    DateTime,       // yyyy-MM-dd HH:mm:ss
    Time,           // HH:mm:ss
    DateTimeMs,     // yyyy-MM-dd HH:mm:ss.zzz
    Week,           // ww (week number)
    Custom          // custom format string
};

/**
 * @brief Time information element
 * Represents date/time information with various formats
 */
class TimeInfoElement : public LabelElement {
public:
    TimeInfoElement();
    explicit TimeInfoElement(const QString& name);

    ElementType getType() const override {
        return ElementType::TimeInfo;
    }

    /**
     * @brief Get time format
     */
    TimeFormat getTimeFormat() const { return m_timeFormat; }

    /**
     * @brief Set time format
     */
    void setTimeFormat(TimeFormat format) { m_timeFormat = format; }

    /**
     * @brief Get custom format string
     * Used when TimeFormat is Custom
     */
    const QString& getCustomFormat() const { return m_customFormat; }

    /**
     * @brief Set custom format string
     * e.g., "yyyy-MM-dd HH:mm"
     */
    void setCustomFormat(const QString& format) { m_customFormat = format; }

    /**
     * @brief Get time offset in seconds
     */
    int getTimeOffset() const { return m_timeOffset; }

    /**
     * @brief Set time offset (e.g., -3600 for 1 hour earlier)
     */
    void setTimeOffset(int seconds) { m_timeOffset = seconds; }

    const QFont& getFont() const { return m_font; }
    void setFont(const QFont& font) { m_font = font; }

    const QColor& getColor() const { return m_color; }
    void setColor(const QColor& color) { m_color = color; }

    int getAlignment() const { return m_alignment; }
    void setAlignment(int alignment) { m_alignment = alignment; }

    /**
     * @brief Get formatted time string
     */
    QString getFormattedTime() const;

    std::map<QString, QVariant> getProperties() const override;
    void setProperty(const QString& key, const QVariant& value) override;
    QString toJson() const override;
    void fromJson(const QString& json) override;
    std::unique_ptr<LabelElement> clone() const override;

private:
    TimeFormat m_timeFormat;
    QString m_customFormat;
    int m_timeOffset;  // in seconds
    QFont m_font;
    QColor m_color;
    int m_alignment;
};

} // namespace LabelDesigner
