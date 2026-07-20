#include "mainwindow.h"
#include "widgets/label_editor_widget.h"
#include "widgets/layout_designer_widget.h"
#include "widgets/package_code_designer_widget.h"
#include "widgets/preview_widget.h"
#include "src/core/label_info/label_manager.h"
#include "src/core/layout/layout_engine.h"
#include "src/core/package_code/counter_manager.h"
#include "src/core/file_manager/file_manager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>

namespace LabelDesigner {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_labelManager(std::make_unique<LabelManager>()),
      m_layoutEngine(std::make_unique<LayoutEngine>()),
      m_counterManager(std::make_unique<CounterManager>()),
      m_fileManager(std::make_unique<FileManager>()),
      m_isModified(false) {
    
    setWindowTitle("Label Designer - Industrial Label Design Tool");
    setWindowIcon(QIcon(":/images/app_icon.png"));
    setGeometry(100, 100, 1400, 900);

    createMenuBar();
    createToolBar();
    createCentralWidget();
    setupConnections();
}

MainWindow::~MainWindow() {
}

void MainWindow::createMenuBar() {
    QMenu* fileMenu = menuBar()->addMenu("&File");
    
    QAction* newAction = fileMenu->addAction("&New Project");
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, &QAction::triggered, this, &MainWindow::onNewProject);
    
    QAction* openAction = fileMenu->addAction("&Open Project");
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpenProject);
    
    fileMenu->addSeparator();
    
    QAction* saveAction = fileMenu->addAction("&Save Project");
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSaveProject);
    
    QAction* saveAsAction = fileMenu->addAction("Save Project &As...");
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::onSaveProjectAs);
    
    fileMenu->addSeparator();
    
    QAction* exportAction = fileMenu->addAction("&Export to JSON");
    connect(exportAction, &QAction::triggered, this, &MainWindow::onExportJson);
    
    QAction* importAction = fileMenu->addAction("&Import from JSON");
    connect(importAction, &QAction::triggered, this, &MainWindow::onImportJson);
    
    fileMenu->addSeparator();
    
    QAction* exitAction = fileMenu->addAction("E&xit");
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExit);
    
    QMenu* helpMenu = menuBar()->addMenu("&Help");
    QAction* aboutAction = helpMenu->addAction("&About");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
    
    QAction* aboutQtAction = helpMenu->addAction("About &Qt");
    connect(aboutQtAction, &QAction::triggered, this, &MainWindow::onAboutQt);
}

void MainWindow::createToolBar() {
    QToolBar* toolBar = addToolBar("Main Toolbar");
    toolBar->setObjectName("MainToolBar");
}

void MainWindow::createCentralWidget() {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Create left panel: Label Editor and Layout Designer
    QSplitter* leftSplitter = new QSplitter(Qt::Vertical);
    m_labelEditorWidget = new LabelEditorWidget();
    m_layoutDesignerWidget = new LayoutDesignerWidget();
    leftSplitter->addWidget(m_labelEditorWidget);
    leftSplitter->addWidget(m_layoutDesignerWidget);
    leftSplitter->setStretchFactor(0, 1);
    leftSplitter->setStretchFactor(1, 1);
    
    // Create right panel: Package Code Designer and Preview
    QSplitter* rightSplitter = new QSplitter(Qt::Vertical);
    m_packageCodeDesignerWidget = new PackageCodeDesignerWidget();
    m_previewWidget = new PreviewWidget();
    rightSplitter->addWidget(m_packageCodeDesignerWidget);
    rightSplitter->addWidget(m_previewWidget);
    rightSplitter->setStretchFactor(0, 1);
    rightSplitter->setStretchFactor(1, 2);
    
    // Create main splitter
    QSplitter* mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->addWidget(leftSplitter);
    mainSplitter->addWidget(rightSplitter);
    mainSplitter->setStretchFactor(0, 1);
    mainSplitter->setStretchFactor(1, 1);
    
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->addWidget(mainSplitter);
    layout->setContentsMargins(0, 0, 0, 0);
    centralWidget->setLayout(layout);
}

void MainWindow::setupConnections() {
    // Connect signals/slots for UI synchronization
}

bool MainWindow::maybeSave() {
    if (!m_isModified) return true;
    
    QMessageBox::StandardButton ret = QMessageBox::warning(
        this, "Unsaved Changes",
        "The project has been modified. Do you want to save your changes?",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    
    if (ret == QMessageBox::Save) {
        onSaveProject();
        return true;
    } else if (ret == QMessageBox::Cancel) {
        return false;
    }
    return true;
}

void MainWindow::onNewProject() {
    if (!maybeSave()) return;
    
    m_labelManager->clear();
    m_currentFilePath.clear();
    m_isModified = false;
    setWindowTitle("Label Designer - Untitled");
}

void MainWindow::onOpenProject() {
    if (!maybeSave()) return;
    
    QString filePath = QFileDialog::getOpenFileName(
        this, "Open Project", "",
        "Label Designer Files (*.ldf);;All Files (*)");
    
    if (filePath.isEmpty()) return;
    
    QString projectName;
    if (m_fileManager->loadProject(filePath, projectName, *m_labelManager)) {
        m_currentFilePath = filePath;
        m_isModified = false;
        setWindowTitle(QString("Label Designer - %1").arg(projectName));
    } else {
        QMessageBox::critical(this, "Error",
            QString("Failed to load project: %1").arg(m_fileManager->getLastError()));
    }
}

void MainWindow::onSaveProject() {
    if (m_currentFilePath.isEmpty()) {
        onSaveProjectAs();
    } else {
        QString projectName = QFileInfo(m_currentFilePath).baseName();
        if (m_fileManager->saveProject(m_currentFilePath, projectName, *m_labelManager)) {
            m_isModified = false;
            QMessageBox::information(this, "Success", "Project saved successfully!");
        } else {
            QMessageBox::critical(this, "Error",
                QString("Failed to save project: %1").arg(m_fileManager->getLastError()));
        }
    }
}

void MainWindow::onSaveProjectAs() {
    QString filePath = QFileDialog::getSaveFileName(
        this, "Save Project As", "",
        "Label Designer Files (*.ldf);;All Files (*)");
    
    if (filePath.isEmpty()) return;
    
    QString projectName = QFileInfo(filePath).baseName();
    if (m_fileManager->saveProject(filePath, projectName, *m_labelManager)) {
        m_currentFilePath = filePath;
        m_isModified = false;
        setWindowTitle(QString("Label Designer - %1").arg(projectName));
        QMessageBox::information(this, "Success", "Project saved successfully!");
    } else {
        QMessageBox::critical(this, "Error",
            QString("Failed to save project: %1").arg(m_fileManager->getLastError()));
    }
}

void MainWindow::onExportJson() {
    QString filePath = QFileDialog::getSaveFileName(
        this, "Export to JSON", "",
        "JSON Files (*.json);;All Files (*)");
    
    if (filePath.isEmpty()) return;
    
    QString projectName = QFileInfo(m_currentFilePath).baseName();
    if (m_fileManager->exportToJson(filePath, projectName, *m_labelManager)) {
        QMessageBox::information(this, "Success", "Project exported successfully!");
    }
}

void MainWindow::onImportJson() {
    QString filePath = QFileDialog::getOpenFileName(
        this, "Import from JSON", "",
        "JSON Files (*.json);;All Files (*)");
    
    if (filePath.isEmpty()) return;
    
    QString projectName;
    if (m_fileManager->importFromJson(filePath, projectName, *m_labelManager)) {
        m_isModified = false;
        setWindowTitle(QString("Label Designer - %1").arg(projectName));
        QMessageBox::information(this, "Success", "Project imported successfully!");
    }
}

void MainWindow::onExit() {
    if (maybeSave()) {
        qApp->quit();
    }
}

void MainWindow::onAbout() {
    QMessageBox::about(this, "About Label Designer",
        "Label Designer v1.0\n\n"
        "Professional Industrial Label Design Tool\n"
        "Supports complex label information, layout design, and package codes.");
}

void MainWindow::onAboutQt() {
    QMessageBox::aboutQt(this);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

} // namespace LabelDesigner
