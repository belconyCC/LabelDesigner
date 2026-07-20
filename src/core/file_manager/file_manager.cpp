#include "file_manager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>

namespace LabelDesigner {

FileManager::FileManager() {
}

FileManager::~FileManager() {
}

bool FileManager::saveProject(const QString& filePath, const QString& projectName,
                              const LabelManager& labelManager) {
    QJsonObject root;
    root["project_name"] = projectName;
    root["version"] = "1.0";
    root["created_at"] = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    
    // Save elements
    QJsonDocument elementsDoc = QJsonDocument::fromJson(labelManager.toJson().toUtf8());
    if (elementsDoc.isObject()) {
        root["label_data"] = elementsDoc.object();
    }
    
    QJsonDocument doc(root);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        m_lastError = QString("Cannot open file for writing: %1").arg(filePath);
        return false;
    }
    
    file.write(doc.toJson());
    file.close();
    return true;
}

bool FileManager::loadProject(const QString& filePath, QString& projectName,
                              LabelManager& labelManager) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        m_lastError = QString("Cannot open file for reading: %1").arg(filePath);
        return false;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    
    if (!doc.isObject()) {
        m_lastError = "Invalid project file format";
        return false;
    }
    
    QJsonObject root = doc.object();
    projectName = root["project_name"].toString();
    
    // Load elements
    QJsonObject labelData = root["label_data"].toObject();
    QString labelDataJson = QString::fromUtf8(QJsonDocument(labelData).toJson());
    labelManager.fromJson(labelDataJson);
    
    return true;
}

bool FileManager::exportToJson(const QString& filePath,
                               const QString& projectName,
                               const LabelManager& labelManager) {
    QJsonObject root;
    root["project_name"] = projectName;
    root["version"] = "1.0";
    root["exported_at"] = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    
    // Export elements
    QJsonDocument elementsDoc = QJsonDocument::fromJson(labelManager.toJson().toUtf8());
    if (elementsDoc.isObject()) {
        root["elements"] = elementsDoc.object();
    }
    
    QJsonDocument doc(root);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        m_lastError = QString("Cannot open file for writing: %1").arg(filePath);
        return false;
    }
    
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

bool FileManager::importFromJson(const QString& filePath,
                                 QString& projectName,
                                 LabelManager& labelManager) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        m_lastError = QString("Cannot open file for reading: %1").arg(filePath);
        return false;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    
    if (!doc.isObject()) {
        m_lastError = "Invalid JSON file format";
        return false;
    }
    
    QJsonObject root = doc.object();
    projectName = root["project_name"].toString();
    
    // Import elements
    QJsonObject elementsObj = root["elements"].toObject();
    QString elementsJson = QString::fromUtf8(QJsonDocument(elementsObj).toJson());
    labelManager.fromJson(elementsJson);
    
    return true;
}

} // namespace LabelDesigner
