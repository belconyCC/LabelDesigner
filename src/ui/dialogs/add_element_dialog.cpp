#include "add_element_dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QFileDialog>
#include <QGroupBox>
#include "src/utils/json_parser.h"
#include <QMessageBox>

namespace LabelDesigner {

struct AddElementDialog::Impl {
    QComboBox* m_typeCombo = nullptr;
    QLineEdit* m_nameEdit = nullptr;

    // Fixed
    QLineEdit* m_fixedText = nullptr;

    // Binding
    QComboBox* m_bindingPaths = nullptr;
    QPushButton* m_loadJsonBtn = nullptr;
    JsonParser m_jsonParser;
};

AddElementDialog::AddElementDialog(QWidget* parent)
    : QDialog(parent), m(new Impl()) {
    setWindowTitle("Add Element");
    setModal(true);
    resize(400, 200);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Type and name
    QHBoxLayout* typeLayout = new QHBoxLayout();
    typeLayout->addWidget(new QLabel("Type:"));
    m->m_typeCombo = new QComboBox();
    m->m_typeCombo->addItem("Fixed Info");
    m->m_typeCombo->addItem("Binding Info");
    m->m_typeCombo->addItem("Time Info");
    m->m_typeCombo->addItem("Barcode");
    m->m_typeCombo->addItem("QRCode");
    m->m_typeCombo->addItem("Image");
    typeLayout->addWidget(m->m_typeCombo);

    typeLayout->addWidget(new QLabel("Name:"));
    m->m_nameEdit = new QLineEdit();
    typeLayout->addWidget(m->m_nameEdit);

    mainLayout->addLayout(typeLayout);

    // Stacked area for type-specific options
    // Fixed info group
    QGroupBox* fixedGroup = new QGroupBox("Fixed Info Options");
    QHBoxLayout* fixedLayout = new QHBoxLayout();
    fixedLayout->addWidget(new QLabel("Text:"));
    m->m_fixedText = new QLineEdit();
    fixedLayout->addWidget(m->m_fixedText);
    fixedGroup->setLayout(fixedLayout);
    mainLayout->addWidget(fixedGroup);

    // Binding info group
    QGroupBox* bindGroup = new QGroupBox("Binding Info Options");
    QHBoxLayout* bindLayout = new QHBoxLayout();
    m->m_bindingPaths = new QComboBox();
    m->m_bindingPaths->setEditable(false);
    bindLayout->addWidget(new QLabel("JSON Path:"));
    bindLayout->addWidget(m->m_bindingPaths);
    m->m_loadJsonBtn = new QPushButton("Load JSON...");
    bindLayout->addWidget(m->m_loadJsonBtn);
    bindGroup->setLayout(bindLayout);
    mainLayout->addWidget(bindGroup);

    // Initially only show fixed group
    fixedGroup->setVisible(true);
    bindGroup->setVisible(false);

    connect(m->m_typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &AddElementDialog::onTypeChanged);
    connect(m->m_loadJsonBtn, &QPushButton::clicked, this, &AddElementDialog::onLoadJsonClicked);

    // Buttons
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    QPushButton* ok = new QPushButton("OK");
    QPushButton* cancel = new QPushButton("Cancel");
    btnLayout->addWidget(ok);
    btnLayout->addWidget(cancel);
    mainLayout->addLayout(btnLayout);

    connect(ok, &QPushButton::clicked, this, &AddElementDialog::accept);
    connect(cancel, &QPushButton::clicked, this, &AddElementDialog::reject);
}

AddElementDialog::~AddElementDialog() {
    delete m;
}

void AddElementDialog::onTypeChanged(int index) {
    // index 0 = Fixed, 1 = Binding
    QGroupBox* fixedGroup = qobject_cast<QGroupBox*>(this->layout()->itemAt(1)->widget());
    QGroupBox* bindGroup = qobject_cast<QGroupBox*>(this->layout()->itemAt(2)->widget());
    if (!fixedGroup || !bindGroup) return;
    if (index == 0) {
        fixedGroup->setVisible(true);
        bindGroup->setVisible(false);
    } else if (index == 1) {
        fixedGroup->setVisible(false);
        bindGroup->setVisible(true);
    } else {
        fixedGroup->setVisible(false);
        bindGroup->setVisible(false);
    }
}

void AddElementDialog::onLoadJsonClicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open JSON File", "", "JSON Files (*.json);;All Files (*)");
    if (filePath.isEmpty()) return;
    if (!m->m_jsonParser.loadJsonFile(filePath)) {
        // show error
        QMessageBox::critical(this, "Error", QString("Failed to load JSON: %1").arg(m->m_jsonParser.getLastError()));
        return;
    }
    // Populate binding paths (recursively)
    m->m_bindingPaths->clear();
    auto paths = m->m_jsonParser.getAllPaths(3);
    for (const auto& p : paths) {
        m->m_bindingPaths->addItem(p);
    }
}

AddElementDialog::ElementType AddElementDialog::selectedType() const {
    int idx = m->m_typeCombo->currentIndex();
    switch (idx) {
    case 0: return ElementType::FixedInfo;
    case 1: return ElementType::BindingInfo;
    case 2: return ElementType::TimeInfo;
    case 3: return ElementType::Barcode;
    case 4: return ElementType::QRCode;
    case 5: return ElementType::Image;
    default: return ElementType::FixedInfo;
    }
}

QString AddElementDialog::elementName() const {
    return m->m_nameEdit->text();
}

QString AddElementDialog::fixedText() const {
    return m->m_fixedText->text();
}

QString AddElementDialog::bindingJsonPath() const {
    return m->m_bindingPaths->currentText();
}

} // namespace LabelDesigner
