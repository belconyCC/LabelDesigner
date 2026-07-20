#include "element_properties_dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QComboBox>
#include <QMessageBox>
#include "../../models/fixed_info_element.h"
#include "../../models/binding_info_element.h"
#include "src/utils/json_parser.h"

namespace LabelDesigner {

struct ElementPropertiesDialog::Impl {
    std::shared_ptr<LabelElement> m_element;
    JsonParser* m_parser = nullptr;

    // Common
    QLineEdit* m_nameEdit = nullptr;

    // Fixed
    QLineEdit* m_fixedText = nullptr;

    // Binding
    QComboBox* m_bindingPaths = nullptr;
    QPushButton* m_loadJsonBtn = nullptr;
};

ElementPropertiesDialog::ElementPropertiesDialog(std::shared_ptr<LabelElement> element, JsonParser* parser, QWidget* parent)
    : QDialog(parent), m(new Impl()) {
    m->m_element = element;
    m->m_parser = parser;

    setWindowTitle("Edit Element Properties");
    resize(420, 220);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Name
    QHBoxLayout* nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("Name:"));
    m->m_nameEdit = new QLineEdit();
    if (element) m->m_nameEdit->setText(element->getName());
    nameLayout->addWidget(m->m_nameEdit);
    mainLayout->addLayout(nameLayout);

    // Type specific
    if (element && element->getType() == LabelElement::ElementType::FixedInfo) {
        FixedInfoElement* f = dynamic_cast<FixedInfoElement*>(element.get());
        QGroupBox* g = new QGroupBox("Fixed Info");
        QHBoxLayout* gl = new QHBoxLayout();
        gl->addWidget(new QLabel("Text:"));
        m->m_fixedText = new QLineEdit();
        if (f) m->m_fixedText->setText(f->getText());
        gl->addWidget(m->m_fixedText);
        g->setLayout(gl);
        mainLayout->addWidget(g);
    } else if (element && element->getType() == LabelElement::ElementType::BindingInfo) {
        BindingInfoElement* b = dynamic_cast<BindingInfoElement*>(element.get());
        QGroupBox* g = new QGroupBox("Binding Info");
        QHBoxLayout* gl = new QHBoxLayout();
        gl->addWidget(new QLabel("JSON Path:"));
        m->m_bindingPaths = new QComboBox();
        if (b) m->m_bindingPaths->addItem(b->getJsonPath());
        gl->addWidget(m->m_bindingPaths);
        m->m_loadJsonBtn = new QPushButton("Load JSON...");
        gl->addWidget(m->m_loadJsonBtn);
        g->setLayout(gl);
        mainLayout->addWidget(g);

        connect(m->m_loadJsonBtn, &QPushButton::clicked, this, &ElementPropertiesDialog::onLoadJsonClicked);
    }

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    QPushButton* apply = new QPushButton("Apply");
    QPushButton* cancel = new QPushButton("Cancel");
    btnLayout->addWidget(apply);
    btnLayout->addWidget(cancel);
    mainLayout->addLayout(btnLayout);

    connect(apply, &QPushButton::clicked, this, &ElementPropertiesDialog::onApply);
    connect(cancel, &QPushButton::clicked, this, &ElementPropertiesDialog::reject);
}

ElementPropertiesDialog::~ElementPropertiesDialog() {
    delete m;
}

void ElementPropertiesDialog::onLoadJsonClicked() {
    if (!m->m_parser) return;
    QString filePath = QFileDialog::getOpenFileName(this, "Open JSON File", "", "JSON Files (*.json);;All Files (*)");
    if (filePath.isEmpty()) return;
    if (!m->m_parser->loadJsonFile(filePath)) {
        QMessageBox::critical(this, "Error", QString("Failed to load JSON: %1").arg(m->m_parser->getLastError()));
        return;
    }
    m->m_bindingPaths->clear();
    auto paths = m->m_parser->getAllPaths(3);
    for (const auto& p : paths) m->m_bindingPaths->addItem(p);
}

void ElementPropertiesDialog::onApply() {
    if (!m->m_element) return;
    m->m_element->setName(m->m_nameEdit->text());
    if (m->m_element->getType() == LabelElement::ElementType::FixedInfo) {
        FixedInfoElement* f = dynamic_cast<FixedInfoElement*>(m->m_element.get());
        if (f && m->m_fixedText) f->setText(m->m_fixedText->text());
    } else if (m->m_element->getType() == LabelElement::ElementType::BindingInfo) {
        BindingInfoElement* b = dynamic_cast<BindingInfoElement*>(m->m_element.get());
        if (b && m->m_bindingPaths) b->setJsonPath(m->m_bindingPaths->currentText());
    }
    accept();
}

} // namespace LabelDesigner
