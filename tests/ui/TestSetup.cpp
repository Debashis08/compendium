#include <QtQuickTest>
#include <QQmlEngine>
#include <QQmlContext>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QStringList>

#include "../../src/core/ServiceProvider.h"
#include "../../src/core/interfaces/IWorkspaceService.h"

// Dummy Service for UI Tests
class DummyWorkspaceService : public IWorkspaceService
{
public:
    QString getWorkspacePath() const override { return "C:/Test/Workspace"; }
    QString getWorkspaceName() const override { return "TestWorkspace"; }
    void setWorkspacePath(const QString& path) override {}
    bool hasValidWorkspace() const override { return false; }
};

// Force "BASIC" style
struct StyleConfig
{
    StyleConfig() { qputenv("QT_QUICK_CONTROLS_STYLE", "Basic"); }
};
static StyleConfig styleConfig;

// struct EnvConfig
// {
//     EnvConfig() {
//         // Force the fallback styling
//         qputenv("QT_QUICK_CONTROLS_STYLE", "Basic");

//         // CRITICAL FIX: Forces Qt to render headlessly into a memory buffer.
//         // This prevents the instant exit code 1 crash on GitHub Actions servers.
//         qputenv("QT_QPA_PLATFORM", "offscreen");
//     }
// };
// static EnvConfig envConfig;

class Setup : public QObject
{
    Q_OBJECT
public:
    Setup()
    {
#ifdef Q_OS_WIN
        QString currentPath = qgetenv("PATH");
        QString buildDir = QString::fromUtf8(APP_BUILD_DIR);

        // CATCH-ALL: Tell Windows where every single DLL could possibly be hiding
        QStringList dllPaths = {
            QDir(buildDir).absoluteFilePath("src/ui"),
            QDir(buildDir).absoluteFilePath("src/backend"),
            QDir(buildDir).absoluteFilePath("src/core"),
            QDir(buildDir).absoluteFilePath("qml/App/Ui"),
            QDir(buildDir).absoluteFilePath(".qt/qml/App/Ui")
        };

        QString newPath = dllPaths.join(";") + ";" + currentPath;
        newPath.replace("/", "\\");
        qputenv("PATH", newPath.toLocal8Bit());
#endif
        ServiceProvider::instance().setWorkspaceService(&_dummyService);
    }

    ~Setup()
    {
        ServiceProvider::instance().setWorkspaceService(nullptr);
    }

public slots:
    void qmlEngineAvailable(QQmlEngine *engine)
    {
        engine->addImportPath("qrc:/qt/qml");

        QString buildDir = QString::fromUtf8(APP_BUILD_DIR);

        // CATCH-ALL: Tell the QML Engine where every single qmldir could possibly be hiding
        engine->addImportPath(buildDir);
        engine->addImportPath(QDir(buildDir).absoluteFilePath("src/ui"));
        engine->addImportPath(QDir(buildDir).absoluteFilePath("qml"));
        engine->addImportPath(QDir(buildDir).absoluteFilePath(".qt/qml"));
    }

private:
    DummyWorkspaceService _dummyService;
};

QUICK_TEST_MAIN_WITH_SETUP(UiTests, Setup)
#include "TestSetup.moc"