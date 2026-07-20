#pragma once

#include "label_element.h"
#include <vector>
#include <memory>
#include <QString>
#include <map>

namespace LabelDesigner {

class LayoutCell;
using LayoutCellPtr = std::shared_ptr<LayoutCell>;

/**
 * @brief Label manager for managing all label elements
 * Provides factory methods and element management
 */
class LabelManager {
public:
    LabelManager();
    ~LabelManager();

    /**
     * @brief Add element to manager
     */
    void addElement(LabelElementPtr element);

    /**
     * @brief Remove element by ID
     */
    bool removeElement(const QString& elementId);

    /**
     * @brief Get element by ID
     */
    LabelElementPtr getElement(const QString& elementId) const;

    /**
     * @brief Get all elements
     */
    const std::vector<LabelElementPtr>& getElements() const { return m_elements; }

    /**
     * @brief Get elements by type
     */
    std::vector<LabelElementPtr> getElementsByType(LabelElement::ElementType type) const;

    /**
     * @brief Clear all elements
     */
    void clear();

    /**
     * @brief Get element count
     */
    size_t getElementCount() const { return m_elements.size(); }

    /**
     * @brief Serialize all elements to JSON
     */
    QString toJson() const;

    /**
     * @brief Deserialize elements from JSON
     */
    void fromJson(const QString& json);

protected:
    std::vector<LabelElementPtr> m_elements;
    std::map<QString, size_t> m_elementIndex;  // id -> index mapping
};

} // namespace LabelDesigner
