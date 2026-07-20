#pragma once

#include <QDialog>
#include <QString>

namespace LabelDesigner {

class JsonParser;

class AddElementDialog : public QDialog {
    Q_OBJECT
public:
    enum class ElementType {
        FixedInfo,
        BindingInfo,
        TimeInfo,
        Barcode,
        QRCode,
        Image
    };

    explicit AddElementDialog(QWidget* parent = nullptr);
    // Accept an optional shared JsonParser pointer. If provided, the dialog will use it for loading JSON and enumerating paths.
    explicit AddElementDialog(JsonParser* sharedParser, QWidget* parent = nullptr);
    ~AddElementDialog();

    ElementType selectedType() const;
    QString elementName() const;

    // For FixedInfo
    QString fixedText() const;

    // For BindingInfo
    QString bindingJsonPath() const;

private slots:
    void onTypeChanged(int index);
    void onLoadJsonClicked();

private:
    struct Impl;
    Impl* m;
};

} // namespace LabelDesigner
