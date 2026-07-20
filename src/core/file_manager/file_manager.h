#pragma once

#include "src/core/label_info/label_manager.h"
#include <QString>
#include <memory>

namespace LabelDesigner {

/**
 * @brief File manager for project persistence
 * Handles reading and writing project files
 */
class FileManager {
public:
    FileManager();
    ~FileManager();

    /**
     * @brief Save project to .ldf file
     * @param filePath Path to save file
     * @param projectName Project name
     * @param labelManager Label manager with elements
     * @return true if save successful
     */
    bool saveProject(const QString& filePath, const QString& projectName,
                     const LabelManager& labelManager);

    /**
     * @brief Load project from .ldf file
     * @param filePath Path to load file
     * @param projectName Output parameter for project name
     * @param labelManager Label manager to populate
     * @return true if load successful
     */
    bool loadProject(const QString& filePath, QString& projectName,
                     LabelManager& labelManager);

    /**
     * @brief Export to JSON format
     */
    bool exportToJson(const QString& filePath,
                      const QString& projectName,
                      const LabelManager& labelManager);

    /**
     * @brief Import from JSON format
     */
    bool importFromJson(const QString& filePath,
                        QString& projectName,
                        LabelManager& labelManager);

    /**
     * @brief Get last error message
     */
    const QString& getLastError() const { return m_lastError; }

private:
    QString m_lastError;
};

} // namespace LabelDesigner
