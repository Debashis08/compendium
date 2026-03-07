#include <QtQuickTest>
#include <QQmlEngine>
#include <QQmlContext>
#include <QDebug>

// Force "BASIC" style
// This struct ensures we set the style to "Basic" before the QGuiApplication
// in main() is even created. This fixes the "geometry=0,0" and customization errors.
struct StyleConfig
{
    StyleConfig()
    {
        qputenv("QT_QUICK_CONTROLS_STYLE", "Basic");
    }
};
static StyleConfig styleConfig;

// Test Setup Class
class Setup : public QObject
{
    Q_OBJECT
public:
    Setup() {}

public slots:
    void qmlEngineAvailable(QQmlEngine *engine)
    {
        // Set Import Path so 'import App.Ui' works
        engine->addImportPath("qrc:/qt/qml");
    }
};

// Main Entry Point
QUICK_TEST_MAIN_WITH_SETUP(tst_ui, Setup)
#include "TestSetup.moc"
