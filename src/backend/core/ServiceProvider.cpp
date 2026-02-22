#include "ServiceProvider.h"

ServiceProvider& ServiceProvider::instance()
{
    static ServiceProvider _instance;
    return _instance;
}

ServiceProvider* ServiceProvider::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    Q_UNUSED(qmlEngine)
    Q_UNUSED(jsEngine)
    QJSEngine::setObjectOwnership(&instance(), QJSEngine::CppOwnership);
    return &instance();
}

void ServiceProvider::setCounterService(ICounterService* service)
{
    _counterService = service;
}

void ServiceProvider::setAppController(AppController* appController)
{
    this->_appController = appController;
}

ICounterService* ServiceProvider::counter() const
{
    return _counterService;
}

AppController* ServiceProvider::appController() const
{
    return this->_appController;
}
