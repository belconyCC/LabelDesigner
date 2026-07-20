#pragma once

#include <QString>
#include <QRect>
#include <memory>
#include <map>

namespace LabelDesigner {

/**
 * @brief Base class for all label elements
 * Provides common interface for different element types
 */
class LabelElement {
public:
    enum class ElementType {
        FixedInfo,
        BindingInfo,
        TimeInfo,
        Barcode,
        QRCode,
        Image,
        Custom
    };

    virtual ~LabelElement() = default;

    /**
     * @brief Get element type
     */
    virtual ElementType getType() const = 0;

    /**
     * @brief Get element ID
     */
    const QString& getId() const { return m_id; }

    /**
     * @brief Get element name
     */
    const QString& getName() const { return m_name; }

    /**
     * @brief Set element name
     */
    void setName(const QString& name) { m_name = name; }

    /**
     * @brief Get element position and size
     */
    const QRect& getRect() const { return m_rect; }

    /**
     * @brief Set element position and size
     */
    void setRect(const QRect& rect) { m_rect = rect; }

    /**
     * @brief Get element properties
     */
    virtual std::map<QString, QVariant> getProperties() const = 0;

    /**
     * @brief Set element property
     */
    virtual void setProperty(const QString& key, const QVariant& value) = 0;

    /**
     * @brief Serialize element to JSON
     */
    virtual QString toJson() const = 0;

    /**
     * @brief Deserialize element from JSON
     */
    virtual void fromJson(const QString& json) = 0;

    /**
     * @brief Clone element
     */
    virtual std::unique_ptr<LabelElement> clone() const = 0;

protected:
    QString m_id;
    QString m_name;
    QRect m_rect;

    /**
     * @brief Generate unique ID
     */
    void generateId();
};

using LabelElementPtr = std::shared_ptr<LabelElement>;
using LabelElementUPtr = std::unique_ptr<LabelElement>;

} // namespace LabelDesigner
