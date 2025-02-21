#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "corecontroller.h"
#include "uicontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName("SPCE manage");
    QCoreApplication::setOrganizationName("iroot");
    QQmlApplicationEngine engine;
    spce_core::CoreController controller;
    UIController uiController;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("controller", &controller);
    context->setContextProperty("uicontroller", &uiController);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("spce", "Main");

    return app.exec();
}
