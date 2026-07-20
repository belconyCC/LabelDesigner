#include "counter_manager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

namespace LabelDesigner {

CounterManager::CounterManager() {
}

CounterManager::~CounterManager() {
    clear();
}

void CounterManager::createCounter(const QString& counterId, const QString& bindingKey,
                                  int minVal, int maxVal,
                                  int digits, bool zeroPadding) {
    CounterInfo info;
    info.bindingKey = bindingKey;
    info.currentValue = minVal;
    info.minValue = minVal;
    info.maxValue = maxVal;
    info.displayDigits = digits;
    info.autoZeroPadding = zeroPadding;
    
    m_counters[counterId] = info;
}

const CounterInfo* CounterManager::getCounter(const QString& counterId) const {
    auto it = m_counters.find(counterId);
    if (it != m_counters.end()) {
        return &it->second;
    }
    return nullptr;
}

bool CounterManager::incrementCounter(const QString& counterId) {
    auto it = m_counters.find(counterId);
    if (it == m_counters.end()) return false;
    
    CounterInfo& info = it->second;
    if (info.currentValue < info.maxValue) {
        info.currentValue++;
        return true;
    }
    return false;
}

bool CounterManager::decrementCounter(const QString& counterId) {
    auto it = m_counters.find(counterId);
    if (it == m_counters.end()) return false;
    
    CounterInfo& info = it->second;
    if (info.currentValue > info.minValue) {
        info.currentValue--;
        return true;
    }
    return false;
}

void CounterManager::resetCounter(const QString& counterId) {
    auto it = m_counters.find(counterId);
    if (it != m_counters.end()) {
        it->second.currentValue = it->second.minValue;
    }
}

void CounterManager::resetCountersByBindingKey(const QString& bindingKey) {
    for (auto& pair : m_counters) {
        if (pair.second.bindingKey == bindingKey) {
            pair.second.currentValue = pair.second.minValue;
        }
    }
}

QString CounterManager::getFormattedValue(const QString& counterId) const {
    const CounterInfo* info = getCounter(counterId);
    if (!info) return "";
    
    QString result = QString::number(info->currentValue);
    if (info->autoZeroPadding) {
        result = result.rightJustified(info->displayDigits, '0');
    }
    return result;
}

std::vector<QString> CounterManager::getAllCounterIds() const {
    std::vector<QString> ids;
    for (const auto& pair : m_counters) {
        ids.push_back(pair.first);
    }
    return ids;
}

bool CounterManager::removeCounter(const QString& counterId) {
    return m_counters.erase(counterId) > 0;
}

void CounterManager::clear() {
    m_counters.clear();
}

QString CounterManager::toJson() const {
    QJsonObject root;
    QJsonArray countersArray;
    
    for (const auto& pair : m_counters) {
        QJsonObject counterObj;
        counterObj["id"] = pair.first;
        counterObj["binding_key"] = pair.second.bindingKey;
        counterObj["current_value"] = pair.second.currentValue;
        counterObj["min_value"] = pair.second.minValue;
        counterObj["max_value"] = pair.second.maxValue;
        counterObj["display_digits"] = pair.second.displayDigits;
        counterObj["auto_zero_padding"] = pair.second.autoZeroPadding;
        countersArray.append(counterObj);
    }
    root["counters"] = countersArray;

    QJsonDocument doc(root);
    return QString::fromUtf8(doc.toJson());
}

void CounterManager::fromJson(const QString& json) {
    clear();
    
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isObject()) return;
    
    QJsonObject root = doc.object();
    QJsonArray countersArray = root["counters"].toArray();
    
    for (const auto& counterValue : countersArray) {
        QJsonObject counterObj = counterValue.toObject();
        QString counterId = counterObj["id"].toString();
        QString bindingKey = counterObj["binding_key"].toString();
        int minVal = counterObj["min_value"].toInt();
        int maxVal = counterObj["max_value"].toInt();
        int digits = counterObj["display_digits"].toInt();
        bool zeroPadding = counterObj["auto_zero_padding"].toBool();
        
        createCounter(counterId, bindingKey, minVal, maxVal, digits, zeroPadding);
        
        // Set current value
        auto it = m_counters.find(counterId);
        if (it != m_counters.end()) {
            it->second.currentValue = counterObj["current_value"].toInt();
        }
    }
}

} // namespace LabelDesigner
