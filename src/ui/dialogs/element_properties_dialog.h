#pragma once

#include <QDialog>
#include <memory>

namespace LabelDesigner {

class LabelElement;
class FixedInfoElement;
class BindingInfoElement;
class JsonParser;

class ElementPropertiesDialog : public QDialog {
    Q_OBJECT
public:
    explicit ElementPropertiesDialog(std::shared_ptr<LabelElement> element, JsonParser* parser, QWidget* parent = nullptr);
    ~ElementPropertiesDialog();

private slots:
    void onLoadJsonClicked();
    void onApply();

private:
    struct Impl;
    Impl* m;
};

} // namespace LabelDesigner
