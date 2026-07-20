#pragma once

#include <QMainWindow>
#include <QString>
#include <memory>

namespace LabelDesigner {

class LabelManager;
class LayoutEngine;
class CounterManager;
class LabelEditorWidget;
class LayoutDesignerWidget;
class PackageCodeDesignerWidget;
class PreviewWidget;
class FileManager;

/**
 * @brief Main application window
 * Provides menu bar, toolbar, and central widget management
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onNewProject();
    void onOpenProject();
    void onSaveProject();
    void onSaveProjectAs();
    void onExportJson();
    void onImportJson();
    void onExit();
    void onAbout();
    void onAboutQt();

private:
    void createMenuBar();
    void createToolBar();
    void createCentralWidget();
    void setupConnections();
    bool maybeSave();

    std::unique_ptr<LabelManager> m_labelManager;
    std::unique_ptr<LayoutEngine> m_layoutEngine;
    std::unique_ptr<CounterManager> m_counterManager;
    std::unique_ptr<FileManager> m_fileManager;

    // UI Components
    LabelEditorWidget* m_labelEditorWidget;
    LayoutDesignerWidget* m_layoutDesignerWidget;
    PackageCodeDesignerWidget* m_packageCodeDesignerWidget;
    PreviewWidget* m_previewWidget;

    QString m_currentFilePath;
    bool m_isModified;
};

} // namespace LabelDesigner
