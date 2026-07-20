#include "package_code_designer_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>

namespace LabelDesigner {

PackageCodeDesignerWidget::PackageCodeDesignerWidget(QWidget* parent)
    : QWidget(parent) {
    createUI();
    setupConnections();
}

PackageCodeDesignerWidget::~PackageCodeDesignerWidget() {
}

void PackageCodeDesignerWidget::createUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel* titleLabel = new QLabel("Package Code Counters");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);
    
    // Counter list
    m_counterList = new QListWidget();
    m_counterList->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(m_counterList);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    m_addButton = new QPushButton("Add Counter");
    m_deleteButton = new QPushButton("Delete");
    m_resetButton = new QPushButton("Reset");
    m_resetAllButton = new QPushButton("Reset All");
    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_deleteButton);
    buttonLayout->addWidget(m_resetButton);
    buttonLayout->addWidget(m_resetAllButton);
    mainLayout->addLayout(buttonLayout);
    
    setLayout(mainLayout);
}

void PackageCodeDesignerWidget::setupConnections() {
    connect(m_addButton, &QPushButton::clicked, this, &PackageCodeDesignerWidget::onAddCounter);
    connect(m_deleteButton, &QPushButton::clicked, this, &PackageCodeDesignerWidget::onDeleteCounter);
    connect(m_resetButton, &QPushButton::clicked, this, &PackageCodeDesignerWidget::onResetCounter);
    connect(m_resetAllButton, &QPushButton::clicked, this, &PackageCodeDesignerWidget::onResetAllCounters);
}

void PackageCodeDesignerWidget::onAddCounter() {
    // TODO: Show dialog to create new counter
}

void PackageCodeDesignerWidget::onDeleteCounter() {
    if (m_counterList->currentRow() >= 0) {
        delete m_counterList->takeItem(m_counterList->currentRow());
    }
}

void PackageCodeDesignerWidget::onResetCounter() {
    if (m_counterList->currentRow() >= 0) {
        // TODO: Reset selected counter
    }
}

void PackageCodeDesignerWidget::onResetAllCounters() {
    // TODO: Reset all counters
}

} // namespace LabelDesigner
