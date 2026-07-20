#include "layout_designer_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpinBox>
#include <QLabel>
#include <QGroupBox>

namespace LabelDesigner {

LayoutDesignerWidget::LayoutDesignerWidget(QWidget* parent)
    : QWidget(parent) {
    createUI();
    setupConnections();
}

LayoutDesignerWidget::~LayoutDesignerWidget() {
}

void LayoutDesignerWidget::createUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel* titleLabel = new QLabel("Layout Design");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);
    
    // Grid settings group
    QGroupBox* gridGroup = new QGroupBox("Grid Settings");
    QGridLayout* gridLayout = new QGridLayout();
    
    gridLayout->addWidget(new QLabel("Rows:"), 0, 0);
    m_rowsSpinBox = new QSpinBox();
    m_rowsSpinBox->setRange(1, 20);
    m_rowsSpinBox->setValue(4);
    gridLayout->addWidget(m_rowsSpinBox, 0, 1);
    
    gridLayout->addWidget(new QLabel("Columns:"), 1, 0);
    m_columnsSpinBox = new QSpinBox();
    m_columnsSpinBox->setRange(1, 20);
    m_columnsSpinBox->setValue(4);
    gridLayout->addWidget(m_columnsSpinBox, 1, 1);
    
    gridLayout->addWidget(new QLabel("Cell Width (px):"), 2, 0);
    m_cellWidthSpinBox = new QSpinBox();
    m_cellWidthSpinBox->setRange(10, 500);
    m_cellWidthSpinBox->setValue(100);
    gridLayout->addWidget(m_cellWidthSpinBox, 2, 1);
    
    gridLayout->addWidget(new QLabel("Cell Height (px):"), 3, 0);
    m_cellHeightSpinBox = new QSpinBox();
    m_cellHeightSpinBox->setRange(10, 500);
    m_cellHeightSpinBox->setValue(100);
    gridLayout->addWidget(m_cellHeightSpinBox, 3, 1);
    
    gridGroup->setLayout(gridLayout);
    mainLayout->addWidget(gridGroup);
    
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void LayoutDesignerWidget::setupConnections() {
    connect(m_rowsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &LayoutDesignerWidget::onRowsChanged);
    connect(m_columnsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &LayoutDesignerWidget::onColumnsChanged);
    connect(m_cellWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &LayoutDesignerWidget::onCellWidthChanged);
    connect(m_cellHeightSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &LayoutDesignerWidget::onCellHeightChanged);
}

void LayoutDesignerWidget::onRowsChanged(int rows) {
    // TODO: Update layout engine
}

void LayoutDesignerWidget::onColumnsChanged(int cols) {
    // TODO: Update layout engine
}

void LayoutDesignerWidget::onCellWidthChanged(int width) {
    // TODO: Update layout engine
}

void LayoutDesignerWidget::onCellHeightChanged(int height) {
    // TODO: Update layout engine
}

} // namespace LabelDesigner
