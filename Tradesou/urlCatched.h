#ifndef URLCATCHED_H
#define URLCATCHED_H

#include <QUrl>
#include <QStringList>
#include <QTreeWidgetItem>
#include <QTime>

class UrlCatched : public QUrl
{
    private:
        //QUrl url;
        bool scanned;
        bool canBeUrlRewriting;
        bool isUrlRewriting;
        QTreeWidgetItem *item;
    public:
        UrlCatched(const QString &u,bool ur=false);
        UrlCatched(const UrlCatched &u);
        ~UrlCatched();
        QUrl &getUrl();
        bool isInList(const QUrl &url);
        bool UrlRewriting();
        bool isUrlRewrited();
        void isUrlRewrited(bool ur);
        void addToList();
        void setItem(QTreeWidgetItem * i);
        QTreeWidgetItem *getItem();

        static QList<UrlCatched*> *allUrl;
};


#endif // URLCATCHED_H
