#pragma once

#include <QString>
#include <vector>
#include <memory>
#include <map>

namespace LabelDesigner {

struct CounterInfo {
    QString bindingKey;     // Binding key for grouping
    int currentValue;
    int minValue;
    int maxValue;
    int displayDigits;      // Number of digits to display
    bool autoZeroPadding;   // Whether to pad with zeros
};

/**
 * @brief Counter manager for package code
 * Manages counter information and operations
 */
class CounterManager {
public:
    CounterManager();
    ~CounterManager();

    /**
     * @brief Create a new counter
     */
    void createCounter(const QString& counterId, const QString& bindingKey,
                      int minVal = 0, int maxVal = 9999,
                      int digits = 4, bool zeroPadding = true);

    /**
     * @brief Get counter info
     */
    const CounterInfo* getCounter(const QString& counterId) const;

    /**
     * @brief Increment counter
     */
    bool incrementCounter(const QString& counterId);

    /**
     * @brief Decrement counter
     */
    bool decrementCounter(const QString& counterId);

    /**
     * @brief Reset counter to minimum value
     */
    void resetCounter(const QString& counterId);

    /**
     * @brief Reset all counters with specific binding key
     */
    void resetCountersByBindingKey(const QString& bindingKey);

    /**
     * @brief Get formatted counter value as string
     */
    QString getFormattedValue(const QString& counterId) const;

    /**
     * @brief Get all counter IDs
     */
    std::vector<QString> getAllCounterIds() const;

    /**
     * @brief Remove counter
     */
    bool removeCounter(const QString& counterId);

    /**
     * @brief Clear all counters
     */
    void clear();

    /**
     * @brief Save counters to JSON
     */
    QString toJson() const;

    /**
     * @brief Load counters from JSON
     */
    void fromJson(const QString& json);

private:
    std::map<QString, CounterInfo> m_counters;
};

} // namespace LabelDesigner
