#include <QtTest>
#include "../../src/core/file_manager/file_manager.h"
#include "../../src/core/label_info/label_manager.h"
#include "../../src/models/fixed_info_element.h"

using namespace LabelDesigner;

class TestFileManager : public QObject {
    Q_OBJECT

private slots:
    void testSaveLoadRoundTrip() {
        FileManager fm;
        LabelManager mgr;
        auto e = std::make_shared<FixedInfoElement>("Title");
        e->setText("HelloFile");
        mgr.addElement(e);
        QString tmpFile = QDir::temp().filePath("test_project.ldf");
        QString bindingJson = "{ \"product\": { \"name\": \"Test\" } }";
        bool ok = fm.saveProject(tmpFile, "TestProject", mgr, bindingJson);
        QVERIFY(ok);
        LabelManager mgr2;
        QString projectName;
        QString outBinding;
        ok = fm.loadProject(tmpFile, projectName, mgr2, &outBinding);
        QVERIFY(ok);
        QCOMPARE(projectName, QString("TestProject"));
        QCOMPARE((int)mgr2.getElementCount(), 1);
        QVERIFY(!outBinding.isEmpty());
    }
};

QTEST_MAIN(TestFileManager)
#include "test_filemanager.moc"
