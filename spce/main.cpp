#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "corecontroller.h"
#include "uicontroller.h"
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLocale::setDefault(QLocale::English);
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
