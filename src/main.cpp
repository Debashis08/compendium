#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "core/ServiceInitializer.h"

int main(int argc, char *argv[])
{
    // Qt Quick Controls file.
    qputenv("QT_QUICK_CONTROLS_CONF", ":/compendium-qtquickcontrols2.conf");
    QGuiApplication app(argc, argv);

    // service initializer called to create all the requried services.
    ServiceInitializer initializer;
    initializer.initialize();

    QQmlApplicationEngine engine;
    engine.addImportPath(":/qt/qml");
    engine.loadFromModule("App.Ui", "Main");

    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    // Execute and run the application.
    return app.exec();
}
