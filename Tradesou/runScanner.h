#ifndef RUNSCANNER_H
#define RUNSCANNER_H

#include <QtGui>
#include <QWidget>
#include <QUrl>
#include "crawler.h"

class runScanner : public QWidget
{
    Q_OBJECT
    public:
                runScanner(QWidget* parent=0,QString* url=0);
                static void setLog(QString line);
                static void setPage(QUrl &url);
    private slots:
                void on_bt_url_clicked();
                void urlItemClicked(QTreeWidgetItem * item);
    private:
        static runScanner *_runScanner;
};

#endif // RUNSCANNER_H
