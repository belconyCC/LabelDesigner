#include "preview_widget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

namespace LabelDesigner {

PreviewWidget::PreviewWidget(QWidget* parent)
    : QWidget(parent) {
    createUI();
}

PreviewWidget::~PreviewWidget() {
}

void PreviewWidget::createUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QLabel* titleLabel = new QLabel("Preview");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);
    
    m_previewLabel = new QLabel();
    m_previewLabel->setStyleSheet("background-color: white; border: 1px solid black;");
    m_previewLabel->setMinimumHeight(300);
    m_previewLabel->setAlignment(Qt::AlignCenter);
    m_previewLabel->setText("Label preview will be displayed here");
    mainLayout->addWidget(m_previewLabel);
    
    setLayout(mainLayout);
}

void PreviewWidget::updatePreview() {
    // TODO: Render label preview
}

void PreviewWidget::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);
    // TODO: Custom painting for preview
}

} // namespace LabelDesigner
