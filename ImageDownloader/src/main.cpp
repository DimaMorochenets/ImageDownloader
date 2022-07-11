#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>

#define APP_VERSION "1.0.0"
#define FULLSCREEN false
#define DEFAULT_WIDTH 1080
#define DEFAULT_HEIGTH 720

int main(int argc, char** argv)
{
    QCoreApplication::setApplicationVersion("1.0.0");
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":Images/logo.ico"));

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                        if(!obj && url == objUrl) QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("APP_VERSION", QString(APP_VERSION));
    engine.rootContext()->setContextProperty("FULLSCREEN", FULLSCREEN);
    engine.rootContext()->setContextProperty("WIDTH", DEFAULT_WIDTH);
    engine.rootContext()->setContextProperty("HEIGTH", DEFAULT_HEIGTH);

    engine.load(url);

    return app.exec();
}     