#ifndef CRAWLER_H
#define CRAWLER_H

#include <QHttp>
#include <QUrl>
#include <QWidget>
#include <QTreeWidget>
#include <QSettings>
#include <QtXml>

class Crawler : public QWidget
{
    Q_OBJECT
public:
    Crawler(QUrl &url, QTreeWidget *tr);
    ~Crawler();
    void CrawlWholeUrl();
    void addUrl(QString &url);
    int crawlerXml(QString &pageWeb);
    int crawlerHtml(QString &pageWeb,QString &url);
    QTreeWidgetItem* recursiveAdd(QTreeWidgetItem *item,QString &toFind,int prof);

public slots:
    void getPage();
private:
    static bool isCrawlerRunning;
    static int currentUrlCrawled;
    QHttp *http;
    QUrl startUrl;
    QString pageWeb;
    QTreeWidget *tr_result;
    QTreeWidgetItem *root;

    /*COOKIE AND ADDITIONNAL INFORMATION*/
    bool additionnalInfo;
    QTreeWidgetItem *cookie_tr;
    QStringList cookie_list;
    /*FORMS*/
    QTreeWidgetItem *form_tr;


};
#endif // CRAWLER_H
