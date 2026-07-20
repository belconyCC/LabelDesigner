#include <QtTest>
#include "../../src/utils/json_parser.h"

using namespace LabelDesigner;

class TestJsonParser : public QObject {
    Q_OBJECT

private slots:
    void testLoadAndPaths() {
        JsonParser p;
        bool ok = p.loadJsonFile("examples/sample_label.json");
        QVERIFY(ok);
        auto paths = p.getAllPaths(3);
        QVERIFY(!paths.empty());
        bool hasProduct = false;
        for (const auto &s : paths) {
            if (s == "$.product") { hasProduct = true; break; }
        }
        QVERIFY(hasProduct);
    }

    void testGetValue() {
        JsonParser p;
        p.loadJsonFile("examples/sample_label.json");
        QVariant v = p.getValue("$.product.name");
        QVERIFY(v.isValid());
        QCOMPARE(v.toString(), QString("Industrial Widget"));
    }
};

QTEST_MAIN(TestJsonParser)
#include "test_jsonparser.moc"
