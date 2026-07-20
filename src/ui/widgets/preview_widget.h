#pragma once

#include <QWidget>

namespace LabelDesigner {
class LabelManager;
class JsonParser;

class PreviewWidget : public QWidget {
    Q_OBJECT

public:
    explicit PreviewWidget(LabelManager* manager, JsonParser* parser, QWidget* parent = nullptr);
    ~PreviewWidget();

    void updatePreview();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void createUI();
    LabelManager* m_labelManager;
    JsonParser* m_jsonParser;
    QLabel* m_previewLabel;
};

} // namespace LabelDesigner
