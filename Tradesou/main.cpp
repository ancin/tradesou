#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    MainWindow w;

    QPixmap pixmap(":/images/tradesou-logo.png");//need a logo!!
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();
    app.processEvents();
    splash->showMessage("Loading data...");
    app.processEvents();
    //
   /// w.setStyleSheet(QString("background-color:##F0FFFF"));

    app.processEvents();

    delete splash;
    w.resize(QSize(900,500));
    w.show();


    return app.exec();
}
