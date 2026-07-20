#include "json_parser.h"
#include <QJsonDocument>
#include <QFile>
#include <QStringList>
#include <QRegularExpression>

namespace LabelDesigner {

JsonParser::JsonParser() {
}

JsonParser::~JsonParser() {
}

bool JsonParser::loadJson(const QString& jsonStr) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
    if (!doc.isObject()) {
        m_lastError = "Invalid JSON format";
        return false;
    }
    m_root = doc.object();
    return true;
}

bool JsonParser::loadJsonFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        m_lastError = QString("Cannot open file: %1").arg(filePath);
        return false;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    
    if (!doc.isObject()) {
        m_lastError = "Invalid JSON format in file";
        return false;
    }
    
    m_root = doc.object();
    return true;
}

std::vector<QString> JsonParser::parseJsonPath(const QString& jsonPath) const {
    std::vector<QString> segments;
    QString path = jsonPath;
    
    // Remove leading $.
    if (path.startsWith("$.")) {
        path = path.mid(2);
    } else if (path.startsWith("$")) {
        path = path.mid(1);
    }
    
    // Split by dots
    QStringList parts = path.split('.', Qt::SkipEmptyParts);
    for (const auto& part : parts) {
        segments.push_back(part);
    }
    
    return segments;
}

QVariant JsonParser::navigatePath(const QString& jsonPath) {
    std::vector<QString> segments = parseJsonPath(jsonPath);
    
    QJsonValue current = m_root;
    for (size_t i = 0; i < segments.size(); ++i) {
        const QString& segment = segments[i];
        
        if (current.isObject()) {
            current = current.toObject()[segment];
        } else if (current.isArray()) {
            // Try to parse segment as array index
            bool ok;
            int index = segment.toInt(&ok);
            if (ok && index >= 0 && index < current.toArray().size()) {
                current = current.toArray()[index];
            } else {
                return QVariant();
            }
        } else {
            return QVariant();
        }
        
        if (current.isUndefined()) {
            return QVariant();
        }
    }
    
    return current.toVariant();
}

QVariant JsonParser::getValue(const QString& jsonPath, const QVariant& defaultValue) {
    QVariant result = navigatePath(jsonPath);
    return result.isNull() ? defaultValue : result;
}

QString JsonParser::getString(const QString& jsonPath, const QString& defaultValue) {
    QVariant value = getValue(jsonPath);
    return value.isNull() ? defaultValue : value.toString();
}

int JsonParser::getInteger(const QString& jsonPath, int defaultValue) {
    QVariant value = getValue(jsonPath);
    return value.isNull() ? defaultValue : value.toInt();
}

QJsonArray JsonParser::getArray(const QString& jsonPath) {
    QVariant value = navigatePath(jsonPath);
    if (value.canConvert<QJsonArray>()) {
        return value.value<QJsonArray>();
    }
    return QJsonArray();
}

bool JsonParser::pathExists(const QString& jsonPath) const {
    std::vector<QString> segments = parseJsonPath(jsonPath);
    
    QJsonValue current = m_root;
    for (const auto& segment : segments) {
        if (current.isObject()) {
            if (current.toObject().contains(segment)) {
                current = current.toObject()[segment];
            } else {
                return false;
            }
        } else if (current.isArray()) {
            bool ok;
            int index = segment.toInt(&ok);
            if (ok && index >= 0 && index < current.toArray().size()) {
                current = current.toArray()[index];
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    
    return true;
}

std::vector<QString> JsonParser::getRootKeys() const {
    std::vector<QString> keys;
    for (const auto& key : m_root.keys()) {
        keys.push_back(key);
    }
    return keys;
}

} // namespace LabelDesigner
