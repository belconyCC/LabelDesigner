#include <QtTest>
#include "../../src/core/package_code/counter_manager.h"

using namespace LabelDesigner;

class TestCounterManager : public QObject {
    Q_OBJECT

private slots:
    void testCreateIncrementReset() {
        CounterManager mgr;
        mgr.createCounter("c1", "grp1", 0, 100, 4, true);
        QVERIFY(mgr.getCounter("c1") != nullptr);
        QCOMPARE(mgr.getAllCounterIds().size(), (size_t)1);
        // increment
        bool ok = mgr.incrementCounter("c1");
        QVERIFY(ok);
        // formatted value should respect zero padding
        QString formatted = mgr.getFormattedValue("c1");
        QVERIFY(!formatted.isEmpty());
        // reset
        mgr.resetCounter("c1");
        const CounterInfo* info = mgr.getCounter("c1");
        QVERIFY(info != nullptr);
        QCOMPARE(info->currentValue, info->minValue);
    }
};

QTEST_MAIN(TestCounterManager)
#include "test_countermanager.moc"
