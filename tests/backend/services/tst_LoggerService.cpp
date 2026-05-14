#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <utility>
#include <QThread>

// Include the class we are testing
#include "../../src/backend/services/LoggerService.h"

class LoggerServiceTest : public ::testing::Test {
protected:
    QtMessageHandler originalHandler = nullptr;
    QString logDirPath;

    void SetUp() override {
        // 1. Save the original Qt Message Handler so we can restore it later
        originalHandler = qInstallMessageHandler(nullptr);
        qInstallMessageHandler(originalHandler);

        // 2. Determine where the LoggerService will create its files
        logDirPath = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("logs");

        // 3. Start with a completely clean slate
        QDir dir(logDirPath);
        if (dir.exists()) {
            dir.removeRecursively();
        }
    }

    void TearDown() override {
        // 1. Force the logger to close its file handles
        LoggerService::cleanup();

        // 2. Restore the original Qt Message Handler so other tests aren't affected
        qInstallMessageHandler(originalHandler);

        // 3. Clean up the generated log files from the hard drive
        QDir dir(logDirPath);
        if (dir.exists()) {
            dir.removeRecursively();
        }
    }
};

// Unit tests.
TEST_F(LoggerServiceTest, InitializesSuccessfullyAndCreatesLogFile) {
    // Act
    LoggerService::initialize();

    // Assert 1: The 'logs' directory was created
    QDir dir(logDirPath);
    EXPECT_TRUE(dir.exists());

    // Assert 2: A log file for today was created
    QStringList logs = dir.entryList(QStringList() << "log_*.txt", QDir::Files);
    EXPECT_EQ(logs.size(), 1);

    // Assert 3: The file contains the session start banner
    QFile logFile(dir.absoluteFilePath(logs.first()));
    ASSERT_TRUE(logFile.open(QIODevice::ReadOnly | QIODevice::Text));
    QString content = logFile.readAll();
    EXPECT_TRUE(content.contains("session start"));

    logFile.close();
}

TEST_F(LoggerServiceTest, InterceptsAndWritesQtLogMessages) {
    // Arrange
    LoggerService::initialize();

    // Act: Emit standard Qt log messages
    qInfo() << "Enterprise Initialization Complete";
    qWarning() << "Disk space running low";

    // Close the file so we can safely read it
    LoggerService::cleanup();

    // Assert: Read the file and verify the messages were captured and formatted
    QDir dir(logDirPath);
    QStringList logs = dir.entryList(QStringList() << "log_*.txt", QDir::Files);
    ASSERT_EQ(logs.size(), 1);

    QFile logFile(dir.absoluteFilePath(logs.first()));
    ASSERT_TRUE(logFile.open(QIODevice::ReadOnly | QIODevice::Text));
    QString content = logFile.readAll();

    // Verify our specific messages exist
    EXPECT_TRUE(content.contains("Enterprise Initialization Complete"));
    EXPECT_TRUE(content.contains("Disk space running low"));

    // Verify the formatting injected the correct level tags
    EXPECT_TRUE(content.contains("[INFO ]"));
    EXPECT_TRUE(content.contains("[WARN ]"));

    logFile.close();
}

TEST_F(LoggerServiceTest, EnforcesMaximumLogFileLimit) {
    QDir dir(logDirPath);
    dir.mkpath(".");

    // 1. ADAPTIVE MATH: Count how many files currently exist (including stubborn ghost files!)
    int ghostFilesCount = dir.entryList(QStringList() << "log_*.txt", QDir::Files).size();

    // 2. Create just enough dummy files so the total equals exactly 12
    int filesToCreate = 12 - ghostFilesCount;

    for (int i = 1; i <= filesToCreate; ++i) {
        QString dummyName = dir.absoluteFilePath(QString("log_2000-01-%1.txt").arg(i, 2, 10, QChar('0')));
        QFile dummy(dummyName);

        ASSERT_TRUE(dummy.open(QIODevice::WriteOnly));
        (void)dummy.write("dummy data");
        dummy.close();
    }

    // Pre-Assert: We successfully adapted to the environment to hit exactly 12 files
    EXPECT_EQ(dir.entryList(QStringList() << "log_*.txt", QDir::Files).size(), 12);

    // Act: Initializing triggers the cleanOldLogs() method
    LoggerService::initialize();

    // Assert: Total expected files = 11
    // (Cleaner trims 12 down to 10, then initialize() creates 1 new file for today = 11)
    EXPECT_EQ(dir.entryList(QStringList() << "log_*.txt", QDir::Files).size(), 11);
}