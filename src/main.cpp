#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "core/ServiceInitializer.h"

int main(int argc, char *argv[])
{
    // Qt Quick Controls file.
    qputenv("QT_QUICK_CONTROLS_CONF", ":/compendium-qtquickcontrols2.conf");
    QGuiApplication app(argc, argv);

    // This tells QSettings exactly where to save settings data permanently.
    QCoreApplication::setOrganizationName("Compendium");
    QCoreApplication::setOrganizationDomain("Compendium.com");
    QCoreApplication::setApplicationName("compendium");
    // Set the default format as IniFormat to keep the settings in visible local path.
    QSettings::setDefaultFormat(QSettings::IniFormat);

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
