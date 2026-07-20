#pragma once

#include <QWidget>

class QListWidget;
class QPushButton;

namespace LabelDesigner {

/**
 * @brief Label editor widget
 * Provides UI for editing label elements
 */
class LabelEditorWidget : public QWidget {
    Q_OBJECT

public:
    explicit LabelEditorWidget(QWidget* parent = nullptr);
    ~LabelEditorWidget();

private slots:
    void onAddElement();
    void onDeleteElement();
    void onElementSelected();
    void onEditElement();

private:
    void createUI();
    void setupConnections();

    QListWidget* m_elementList;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;
    QPushButton* m_editButton;
};

} // namespace LabelDesigner
