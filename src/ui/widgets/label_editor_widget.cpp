#include "label_editor_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>
#include "../dialogs/add_element_dialog.h"
#include "../../models/fixed_info_element.h"
#include "../../models/binding_info_element.h"

namespace LabelDesigner {

LabelEditorWidget::LabelEditorWidget(LabelManager* manager, QWidget* parent)
    : QWidget(parent), m_labelManager(manager) {
    createUI();
    setupConnections();
    refreshElementList();
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

void LabelEditorWidget::refreshElementList() {
    m_elementList->clear();
    if (!m_labelManager) return;
    const auto& elems = m_labelManager->getElements();
    for (const auto& e : elems) {
        m_elementList->addItem(e->getName() + " (" + QString::number(static_cast<int>(e->getType())) + ")");
    }
}

void LabelEditorWidget::onAddElement() {
    AddElementDialog dlg(this);
    if (dlg.exec() != QDialog::Accepted) return;
    QString name = dlg.elementName();
    if (name.isEmpty()) name = "Element";
    switch (dlg.selectedType()) {
    case AddElementDialog::ElementType::FixedInfo: {
        auto elem = std::make_shared<FixedInfoElement>(name);
        elem->setText(dlg.fixedText());
        m_labelManager->addElement(elem);
        break;
    }
    case AddElementDialog::ElementType::BindingInfo: {
        auto elem = std::make_shared<BindingInfoElement>(name);
        elem->setJsonPath(dlg.bindingJsonPath());
        m_labelManager->addElement(elem);
        break;
    }
    default: {
        // For now, create generic fixed info for other types as placeholder
        auto elem = std::make_shared<FixedInfoElement>(name);
        elem->setText("(placeholder)");
        m_labelManager->addElement(elem);
        break;
    }
    }
    refreshElementList();
}

void LabelEditorWidget::onDeleteElement() {
    int row = m_elementList->currentRow();
    if (row >= 0) {
        const auto& elems = m_labelManager->getElements();
        if (row < static_cast<int>(elems.size())) {
            QString id = elems[row]->getId();
            m_labelManager->removeElement(id);
            refreshElementList();
        }
    }
}

void LabelEditorWidget::onElementSelected() {
    m_editButton->setEnabled(m_elementList->currentRow() >= 0);
    m_deleteButton->setEnabled(m_elementList->currentRow() >= 0);
}

void LabelEditorWidget::onEditElement() {
    int row = m_elementList->currentRow();
    if (row < 0) return;
    const auto& elems = m_labelManager->getElements();
    if (row >= static_cast<int>(elems.size())) return;
    auto e = elems[row];
    // For demo, only allow editing FixedInfo text and BindingInfo path
    if (e->getType() == LabelElement::ElementType::FixedInfo) {
        FixedInfoElement* f = dynamic_cast<FixedInfoElement*>(e.get());
        if (!f) return;
        bool ok;
        QString text = QInputDialog::getText(this, "Edit Fixed Text", "Text:", QLineEdit::Normal, f->getText(), &ok);
        if (ok) {
            f->setText(text);
            refreshElementList();
        }
    } else if (e->getType() == LabelElement::ElementType::BindingInfo) {
        BindingInfoElement* b = dynamic_cast<BindingInfoElement*>(e.get());
        if (!b) return;
        AddElementDialog dlg(this);
        dlg.exec();
        QString path = dlg.bindingJsonPath();
        if (!path.isEmpty()) {
            b->setJsonPath(path);
            refreshElementList();
        }
    } else {
        QMessageBox::information(this, "Edit", "Edit not implemented for this element type yet.");
    }
}

} // namespace LabelDesigner
