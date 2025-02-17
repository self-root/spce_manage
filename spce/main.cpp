#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    spce_core::DatabaseManager::init();
    spce_core::DatabaseManager *instance = spce_core::DatabaseManager::instance();
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("spce", "Main");

    return app.exec();
}
