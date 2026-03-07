#include <QtTest>
#include "core/ServiceProvider.h"

class TestServiceProvider : public QObject
{
    Q_OBJECT

private slots:
    void test_singleton_behavior()
    {
        // Verify multiple calls return the same memory address
        auto* instance1 = &ServiceProvider::instance();
        auto* instance2 = &ServiceProvider::instance();
        
        QCOMPARE(instance1, instance2);
    }
};

QTEST_MAIN(TestServiceProvider)
#include "tst_ServiceProvider.moc"
