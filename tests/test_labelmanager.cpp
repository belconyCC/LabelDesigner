#include <QtTest>
#include "../../src/core/label_info/label_manager.h"
#include "../../src/models/fixed_info_element.h"

using namespace LabelDesigner;

class TestLabelManager : public QObject {
    Q_OBJECT

private slots:
    void testAddRemove() {
        LabelManager mgr;
        auto e = std::make_shared<FixedInfoElement>("Title");
        e->setText("Hello");
        mgr.addElement(e);
        QCOMPARE((int)mgr.getElementCount(), 1);
        QVERIFY(mgr.removeElement(e->getId()));
        QCOMPARE((int)mgr.getElementCount(), 0);
    }

    void testSerializeDeserialize() {
        LabelManager mgr;
        auto e = std::make_shared<FixedInfoElement>("Title");
        e->setText("Hello");
        mgr.addElement(e);
        QString json = mgr.toJson();
        LabelManager mgr2;
        mgr2.fromJson(json);
        QCOMPARE((int)mgr2.getElementCount(), 1);
        auto elems = mgr2.getElements();
        QCOMPARE(elems[0]->getName(), QString("Title"));
    }
};

QTEST_MAIN(TestLabelManager)
#include "test_labelmanager.moc"
