#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "appcore.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    appcore appCore; // Создаём ядро приложения
    QQmlContext *context = engine.rootContext(); // Создаём корневой контекст


    /* Загружаем объект в контекст для установки соединения,
         * а также определяем имя, по которому будет происходить соединение
         * */
    context->setContextProperty("appCore", &appCore);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

