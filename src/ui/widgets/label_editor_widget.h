#pragma once

#include "../../core/label_info/label_manager.h"
#include <QWidget>
#include <QString>

namespace LabelDesigner {

class JsonParser;

class LabelEditorWidget : public QWidget {
    Q_OBJECT

public:
    explicit LabelEditorWidget(LabelManager* manager, JsonParser* parser, QWidget* parent = nullptr);
    ~LabelEditorWidget();

private slots:
    void onAddElement();
    void onDeleteElement();
    void onElementSelected();
    void onEditElement();

private:
    void createUI();
    void setupConnections();
    void refreshElementList();

    LabelManager* m_labelManager;
    JsonParser* m_jsonParser;
    QListWidget* m_elementList;
    QPushButton* m_addButton;
    QPushButton* m_deleteButton;
    QPushButton* m_editButton;
};

} // namespace LabelDesigner
