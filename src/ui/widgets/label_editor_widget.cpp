#include "label_editor_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>

namespace LabelDesigner {

LabelEditorWidget::LabelEditorWidget(QWidget* parent)
    : QWidget(parent) {
    createUI();
    setupConnections();
}

LabelEditorWidget::~LabelEditorWidget() {
}

void LabelEditorWidget::createUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel* titleLabel = new QLabel("Label Elements");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);
    
    // Element list
    m_elementList = new QListWidget();
    m_elementList->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(m_elementList);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    m_addButton = new QPushButton("Add Element");
    m_editButton = new QPushButton("Edit");
    m_deleteButton = new QPushButton("Delete");
    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_editButton);
    buttonLayout->addWidget(m_deleteButton);
    mainLayout->addLayout(buttonLayout);
    
    setLayout(mainLayout);
}

void LabelEditorWidget::setupConnections() {
    connect(m_addButton, &QPushButton::clicked, this, &LabelEditorWidget::onAddElement);
    connect(m_deleteButton, &QPushButton::clicked, this, &LabelEditorWidget::onDeleteElement);
    connect(m_editButton, &QPushButton::clicked, this, &LabelEditorWidget::onEditElement);
    connect(m_elementList, &QListWidget::itemSelectionChanged, this, &LabelEditorWidget::onElementSelected);
}

void LabelEditorWidget::onAddElement() {
    // TODO: Show dialog to select element type and add to list
}

void LabelEditorWidget::onDeleteElement() {
    if (m_elementList->currentRow() >= 0) {
        delete m_elementList->takeItem(m_elementList->currentRow());
    }
}

void LabelEditorWidget::onElementSelected() {
    m_editButton->setEnabled(m_elementList->currentRow() >= 0);
    m_deleteButton->setEnabled(m_elementList->currentRow() >= 0);
}

void LabelEditorWidget::onEditElement() {
    if (m_elementList->currentRow() >= 0) {
        // TODO: Show dialog to edit selected element
    }
}

} // namespace LabelDesigner
