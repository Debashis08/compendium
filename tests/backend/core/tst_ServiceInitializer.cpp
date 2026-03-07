#include <QtTest>
#include "core/ServiceInitializer.h"
#include "core/ServiceProvider.h"

class TestServiceInitializer : public QObject
{
    Q_OBJECT

private slots:
    void test_bootstrapping()
    {
        // Ensure Registry is initially empty (or reset it)
        ServiceProvider::instance().setAppController(nullptr);
        QVERIFY(ServiceProvider::instance().appController() == nullptr);

        // Run the Initializer
        ServiceInitializer init;
        init.initialize();

        // Verify the Registry is now populated
        QVERIFY(ServiceProvider::instance().appController() != nullptr);
    }
};

QTEST_MAIN(TestServiceInitializer)
#include "tst_ServiceInitializer.moc"
