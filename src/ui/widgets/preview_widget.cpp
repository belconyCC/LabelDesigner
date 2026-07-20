#include "preview_widget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include "../../core/label_info/label_manager.h"
#include "../../models/fixed_info_element.h"
#include "../../models/image_element.h"
#include "../../utils/barcode_generator.h"
#include "../../utils/qrcode_generator.h"

namespace LabelDesigner {

PreviewWidget::PreviewWidget(LabelManager* manager, QWidget* parent)
    : QWidget(parent), m_labelManager(manager) {
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
    if (!m_labelManager) return;
    // Create a pixmap and render elements onto it
    int w = 600;
    int h = 400;
    QPixmap pixmap(w, h);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    const auto& elems = m_labelManager->getElements();
    for (const auto& e : elems) {
        switch (e->getType()) {
        case LabelElement::ElementType::FixedInfo: {
            FixedInfoElement* f = dynamic_cast<FixedInfoElement*>(e.get());
            if (!f) break;
            painter.setPen(QPen(f->getColor()));
            QFont font = f->getFont();
            painter.setFont(font);
            QRect r = f->getRect().isNull() ? QRect(10, 10, 200, 30) : f->getRect();
            painter.drawText(r, f->getAlignment(), f->getText());
            break;
        }
        case LabelElement::ElementType::Image: {
            ImageElement* img = dynamic_cast<ImageElement*>(e.get());
            if (!img) break;
            QPixmap pm = img->getPixmap();
            if (!pm.isNull()) {
                QRect r = img->getRect().isNull() ? QRect(10, 50, pm.width(), pm.height()) : img->getRect();
                painter.drawPixmap(r, pm);
            }
            break;
        }
        case LabelElement::ElementType::Barcode: {
            // Use BarcodeGenerator placeholder
            // For now render content as text
            QRect r = e->getRect().isNull() ? QRect(10, 100, 200, 50) : e->getRect();
            painter.setPen(Qt::black);
            painter.drawRect(r);
            painter.drawText(r, Qt::AlignCenter, "[Barcode]");
            break;
        }
        case LabelElement::ElementType::QRCode: {
            QRect r = e->getRect().isNull() ? QRect(220, 100, 120, 120) : e->getRect();
            painter.setPen(Qt::black);
            painter.drawRect(r);
            painter.drawText(r, Qt::AlignCenter, "[QR]");
            break;
        }
        case LabelElement::ElementType::BindingInfo: {
            // Show bound path text for preview
            QLabel dummy;
            QRect r = e->getRect().isNull() ? QRect(10, 180, 300, 30) : e->getRect();
            // We can't evaluate JSON here; just show the path
            BindingInfoElement* b = dynamic_cast<BindingInfoElement*>(e.get());
            if (!b) break;
            painter.setPen(Qt::black);
            painter.drawText(r, Qt::AlignLeft | Qt::AlignVCenter, QString("Bind: %1").arg(b->getJsonPath()));
            break;
        }
        default:
            break;
        }
    }
    painter.end();
    
    m_previewLabel->setPixmap(pixmap.scaled(m_previewLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void PreviewWidget::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);
}

} // namespace LabelDesigner
