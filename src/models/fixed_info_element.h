#pragma once

#include "label_element.h"
#include <QFont>
#include <QColor>

namespace LabelDesigner {

/**
 * @brief Fixed information element
 * Represents static text content on the label
 */
class FixedInfoElement : public LabelElement {
public:
    FixedInfoElement();
    explicit FixedInfoElement(const QString& name);

    ElementType getType() const override {
        return ElementType::FixedInfo;
    }

    /**
     * @brief Get fixed text content
     */
    const QString& getText() const { return m_text; }

    /**
     * @brief Set fixed text content
     */
    void setText(const QString& text) { m_text = text; }

    /**
     * @brief Get text font
     */
    const QFont& getFont() const { return m_font; }

    /**
     * @brief Set text font
     */
    void setFont(const QFont& font) { m_font = font; }

    /**
     * @brief Get text color
     */
    const QColor& getColor() const { return m_color; }

    /**
     * @brief Set text color
     */
    void setColor(const QColor& color) { m_color = color; }

    /**
     * @brief Get text alignment
     */
    int getAlignment() const { return m_alignment; }

    /**
     * @brief Set text alignment
     */
    void setAlignment(int alignment) { m_alignment = alignment; }

    std::map<QString, QVariant> getProperties() const override;
    void setProperty(const QString& key, const QVariant& value) override;
    QString toJson() const override;
    void fromJson(const QString& json) override;
    std::unique_ptr<LabelElement> clone() const override;

private:
    QString m_text;
    QFont m_font;
    QColor m_color;
    int m_alignment;
};

} // namespace LabelDesigner
