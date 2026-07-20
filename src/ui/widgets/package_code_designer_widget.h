#pragma once

#include <QWidget>

class QListWidget;
class QSpinBox;
class QPushButton;

namespace LabelDesigner {

/**
 * @brief Package code designer widget
 * Provides UI for designing package codes with counters
 */
class PackageCodeDesignerWidget : public QWidget {
    Q_OBJECT

public:
    explicit PackageCodeDesignerWidget(QWidget* parent = nullptr);
    ~PackageCodeDesignerWidget();

private slots:
    void onAddCounter();
    void onDeleteCounter();
    void onResetCounter();
    void onResetAllCounters();

private:
    void createUI();
    void setupConnections();

    QListWidget* m_counterList;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;
    QPushButton* m_resetButton;
    QPushButton* m_resetAllButton;
};

} // namespace LabelDesigner
