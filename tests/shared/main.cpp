#include <QCoreApplication>
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    // 1. Spin up the Qt Event Loop (Required for QTimer and QStateMachine)
    QCoreApplication app(argc, argv);

    // 2. Initialize Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // 3. Run all the tests!
    return RUN_ALL_TESTS();
}