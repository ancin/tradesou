#include "urlCatched.h"
#include <QDebug>
QList<UrlCatched*> *UrlCatched::allUrl=new QList<UrlCatched*>();

UrlCatched::UrlCatched(const QString &u,bool ur) : QUrl(u) {/*url=QUrl(u);*/scanned=false;canBeUrlRewriting=ur;}

void UrlCatched::addToList() {
    allUrl->push_back(this);
    QString mesg="Adding Url : "+this->toString()+"\n";
    //runScanner::setLog(mesg);
    qDebug()<<">>>>"<<mesg<<endl;
}
QUrl &UrlCatched::getUrl() {return *this;}
UrlCatched::~UrlCatched() {delete item;}

bool UrlCatched::isInList(const QUrl &url) {
    for(int i=(allUrl->count()-1);i>0;i--)
    {
        if(url==allUrl->at(i)->getUrl())
            return true;//WTF NAAB!!! ret=true;
    }
    return false;
}

void UrlCatched::setItem(QTreeWidgetItem * i) {
    item=i;
}

QTreeWidgetItem *UrlCatched::getItem() {
    return item;
}

bool UrlCatched::UrlRewriting() {
    return canBeUrlRewriting;
}

void UrlCatched::isUrlRewrited(bool ur) {
    isUrlRewriting=ur;
}

bool UrlCatched::isUrlRewrited() {
    return isUrlRewriting;
}

