#pragma once

#include <QString>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>
#include <map>
#include <vector>

namespace LabelDesigner {

/**
 * @brief JSON parser for data binding
 * Supports JSONPath-like syntax for accessing nested objects
 */
class JsonParser {
public:
    JsonParser();
    ~JsonParser();

    /**
     * @brief Load JSON from string
     */
    bool loadJson(const QString& jsonStr);

    /**
     * @brief Load JSON from file
     */
    bool loadJsonFile(const QString& filePath);

    /**
     * @brief Get value by JSONPath
     * Examples: "$.name", "$.user.profile.age", "$[0].id"
     */
    QVariant getValue(const QString& jsonPath, const QVariant& defaultValue = QVariant());

    /**
     * @brief Get string value
     */
    QString getString(const QString& jsonPath, const QString& defaultValue = "");

    /**
     * @brief Get integer value
     */
    int getInteger(const QString& jsonPath, int defaultValue = 0);

    /**
     * @brief Get array by JSONPath
     */
    QJsonArray getArray(const QString& jsonPath);

    /**
     * @brief Check if path exists
     */
    bool pathExists(const QString& jsonPath) const;

    /**
     * @brief Get all keys at root level
     */
    std::vector<QString> getRootKeys() const;

    /**
     * @brief Get last error message
     */
    const QString& getLastError() const { return m_lastError; }

private:
    QJsonObject m_root;
    QString m_lastError;

    /**
     * @brief Parse JSONPath and navigate to target
     */
    QVariant navigatePath(const QString& jsonPath);

    /**
     * @brief Split JSONPath into segments
     */
    std::vector<QString> parseJsonPath(const QString& jsonPath) const;
};

} // namespace LabelDesigner
