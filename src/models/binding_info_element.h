#pragma once

#include "label_element.h"
#include <QFont>
#include <QColor>

namespace LabelDesigner {

/**
 * @brief Binding information element
 * Represents dynamic information bound to JSON data
 */
class BindingInfoElement : public LabelElement {
public:
    BindingInfoElement();
    explicit BindingInfoElement(const QString& name);

    ElementType getType() const override {
        return ElementType::BindingInfo;
    }

    /**
     * @brief Get JSON path for data binding
     * e.g., "$.model", "$.product.name"
     */
    const QString& getJsonPath() const { return m_jsonPath; }

    /**
     * @brief Set JSON path for data binding
     */
    void setJsonPath(const QString& path) { m_jsonPath = path; }

    /**
     * @brief Get default value when binding fails
     */
    const QString& getDefaultValue() const { return m_defaultValue; }

    /**
     * @brief Set default value
     */
    void setDefaultValue(const QString& value) { m_defaultValue = value; }

    /**
     * @brief Get format string for value formatting
     */
    const QString& getFormatString() const { return m_formatString; }

    /**
     * @brief Set format string
     */
    void setFormatString(const QString& format) { m_formatString = format; }

    const QFont& getFont() const { return m_font; }
    void setFont(const QFont& font) { m_font = font; }

    const QColor& getColor() const { return m_color; }
    void setColor(const QColor& color) { m_color = color; }

    int getAlignment() const { return m_alignment; }
    void setAlignment(int alignment) { m_alignment = alignment; }

    std::map<QString, QVariant> getProperties() const override;
    void setProperty(const QString& key, const QVariant& value) override;
    QString toJson() const override;
    void fromJson(const QString& json) override;
    std::unique_ptr<LabelElement> clone() const override;

private:
    QString m_jsonPath;
    QString m_defaultValue;
    QString m_formatString;
    QFont m_font;
    QColor m_color;
    int m_alignment;
};

} // namespace LabelDesigner
