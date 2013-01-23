#include "crawler.h"
#include <QDebug>
#include "urlCatched.h"
#include "formCatched.h"


bool Crawler::isCrawlerRunning=false;
int Crawler::currentUrlCrawled=0;

Crawler::~Crawler(){
    http->abort();
    delete http;
    delete tr_result;
    delete root;
    delete cookie_tr;
}

Crawler::Crawler(QUrl &url,QTreeWidget *tr) : QWidget() {
    http=new QHttp(this);

    connect(http,SIGNAL(done(bool)),this,SLOT(getPage()));
    QSettings settings;
    if(settings.value("network/useproxy").toBool())
    {
        http->setProxy(
                    settings.value("network/cra_host").toString(),
                    settings.value("network/cra_port").toInt(),
                    settings.value("network/cra_name").toString(),
                    settings.value("network/cra_pass").toString()
                    );
    }

    //the request ...
    QHttpRequestHeader header;
    header.setValue("User-agent",settings.value("crawler/user-agent","Firefox 3").toString());
    header.setValue("Host",url.host());
    header.setRequest("GET",url.path());
    http->setHost(url.host(),url.port(80));
    http->request(header);
    tr_result=tr;
    startUrl=url;
    ///ÁÙÊ±×¢ÊÍµô
    root=new QTreeWidgetItem(tr_result,QStringList(url.host()));
    tr_result->addTopLevelItem(root);
    //runScanner::setPage(url);
    additionnalInfo=false;
    //here display content of cookie
    cookie_tr=new QTreeWidgetItem(tr_result,QStringList("Cookie"));
    tr_result->addTopLevelItem(cookie_tr);

    //here display content of forms
     form_tr=new QTreeWidgetItem(tr_result,QStringList("Formulaires"));
    tr_result->addTopLevelItem(form_tr);
}

void Crawler::CrawlWholeUrl() {
    if(!isCrawlerRunning&&currentUrlCrawled<UrlCatched::allUrl->count())
    {//as for the moment we only want 1 thread to download the page
        http->setHost(
                    UrlCatched::allUrl->at(currentUrlCrawled)->getUrl().host(),
                    UrlCatched::allUrl->at(currentUrlCrawled)->getUrl().port(80)
                    );
        QHttpRequestHeader header;
        QSettings settings;
        header.setValue("User-agent",settings.value("crawler/user-agent","Firefox 3").toString());
        header.setValue("Host",UrlCatched::allUrl->at(currentUrlCrawled)->getUrl().host());
        /***
         *ÁÙÊ±É¾³ý
        for(int i=0;i<cookie_list.count();i++)
        {
            header.setValue("Cookie",cookie_list.at(i));
        }
        ***/
        header.setRequest("GET",UrlCatched::allUrl->at(currentUrlCrawled)->getUrl().path());
        http->request(header);
        isCrawlerRunning=true;
        currentUrlCrawled++;
    }else if(!isCrawlerRunning&&currentUrlCrawled==UrlCatched::allUrl->count())
    {
        QString end = "Scan ended we can launch attack now :D\n***************************\n";
        //runScanner::setLog(end);///ÁÙÊ±É¾³ý
        //issuesExecuter::launchAttack(0);//GET///ÁÙÊ±É¾³ý
        qDebug()<<">>>>"<<end<<endl;
    }
}

void Crawler::getPage() {
    isCrawlerRunning=true;
    QSettings settings;
    QStringList content_scan=settings.value("crawler/content-type","text/html;text/plain").toString().split(";");

    //here we fetch more information about the currently scanned page
    if(currentUrlCrawled>0)
    {
        QTreeWidgetItem* currentUrl= UrlCatched::allUrl->at(currentUrlCrawled-1)->getItem();
        UrlCatched *curUrl=UrlCatched::allUrl->at(currentUrlCrawled-1);
        if(currentUrl)
        {
            //currentUrl->setText(1,QString::number(http->lastResponse().statusCode()));
            if(
                    curUrl->UrlRewriting() &&
                    (
                        http->lastResponse().statusCode() == 301||
                        http->lastResponse().statusCode() == 302||
                        http->lastResponse().statusCode() == 404
                        )
                    )
            {
                curUrl->isUrlRewrited(true);
                //UR means URL Rewriting
                currentUrl->setText(1,"UR:"+QString::number(http->lastResponse().statusCode()));
            }
            else
                currentUrl->setText(1,QString::number(http->lastResponse().statusCode()));
            currentUrl->setText(2,http->lastResponse().contentType());
            //currentUrl->setText(3,QString::number(http->lastResponse().contentLength()));
        }
    }
    if(content_scan.contains(http->lastResponse().contentType()))
    {
        pageWeb=QString(http->readAll());

        /*ADDITIONNAL INFORMATION*/
        if(!additionnalInfo)
        {
            additionnalInfo=true;
            //ÁÙÊ±×¢ÊÍµô

            QTreeWidgetItem *addInfo=new QTreeWidgetItem(tr_result,QStringList("Server Information"));
            tr_result->addTopLevelItem(addInfo);
            if(http->lastResponse().hasKey("Server"))
                addInfo->addChild(new QTreeWidgetItem(addInfo,QStringList(http->lastResponse().value("Server"))));
            if(http->lastResponse().hasKey("X-Powered-By"))
                addInfo->addChild(new QTreeWidgetItem(addInfo,QStringList(http->lastResponse().value("X-Powered-By"))));

        }

        /*COOKIE*/


        //LOG MESSAGE
        //TODO: add status message : statusBar ? tooltip??
        QString statusMessage ="Found ";
        QString currentUrl = startUrl.toString();
        if(currentUrlCrawled>0)
            currentUrl = UrlCatched::allUrl->at(currentUrlCrawled-1)->getUrl().scheme()+"://"+
                    UrlCatched::allUrl->at(currentUrlCrawled-1)->getUrl().host()+
                    UrlCatched::allUrl->at(currentUrlCrawled-1)->getUrl().path();

        //PARSING PAGE CURRENT
        if(settings.value("crawler/crawl_type","html").toString()=="xml")
            statusMessage += QString::number(crawlerXml(pageWeb));
        else
            statusMessage += QString::number(crawlerHtml(pageWeb,currentUrl));
        statusMessage +=" links via html parsing";
        if(currentUrlCrawled>0)
            statusMessage +=" on page : " + UrlCatched::allUrl->at(currentUrlCrawled-1)->getUrl().toString();
        statusMessage += "\n";
        //runScanner::setLog(statusMessage);
       qDebug()<<">>>>crawler:"<<statusMessage<<endl;

    }
    //REINIT VAR
    isCrawlerRunning=false;
    CrawlWholeUrl();//launch next scan
}

int Crawler::crawlerHtml(QString &pageWeb,QString &url)/*"dirty mode"*/ {

    int nbUrlAdded=0;
    QString nhost=QString(startUrl.host());

    /*FORM PART*/
    QRegExp form("<form[^>]*>.*</form>");
    form.setMinimal(true);
    int formPos=0;
    while((formPos = form.indexIn(pageWeb, formPos)) != -1)
    {//here we got a form
        QString formContent=form.capturedTexts().takeFirst();
        formPos += form.matchedLength();

        FormCatched *formC=new FormCatched(formContent,url);
        if(FormCatched::isInList(formC) == false)
        {
            formC->addToList();
            formC->addItem(form_tr);
        }

    }

    /*LINK PART*/
    QRegExp rx("<a[^>]+>[^<]+</a>");
    QRegExp ra("href=['\"]?[^>'\"]+"); /*('[^']+|\"[^\"]+|[^>]+)")*/;
    //because we can write : href='url'|href="url"|href=url
    QRegExp hl(QString("^https?://")+nhost+QString(".*"));
    //can't use startUrl.scheme() because a website can make a link to a crypted website
    QRegExp dl("^/");
    QRegExp al("^http");

    int pos=0;
    QStringList tmp;
    QString tmpUrl="";
    while((pos = rx.indexIn(pageWeb, pos)) != -1)
    {//here we got a <a .*>.*</a>
        QString qs=rx.capturedTexts().takeFirst();
        pos += rx.matchedLength();
        if((ra.indexIn(qs, 0) !=-1))
        {//here we got the href=....
            QString ls=ra.capturedTexts().takeFirst();
            ls.replace(QRegExp("(href=|'|\")"),"");
            qDebug()<<"Link found : "<<ls;
            if(hl.indexIn(ls,0)!=-1)
                tmpUrl=ls;
            else if(dl.indexIn(ls,0)!=-1)
                tmpUrl=startUrl.scheme()+"://"+nhost+"/"+startUrl.path()+"/"+ls;
            else if(al.indexIn(ls,0)==-1)
                tmpUrl=url+"/"+ls;

            QRegExp removeDblSlashes = QRegExp("([^:]?)/+");
            tmpUrl.replace(removeDblSlashes,"\\1/");
            /*else
                {external links ... useful?
                  tr_result->addTopLevelItem(new QTreeWidgetItem(tr_result,QStringList(ql)));
                            }*/
            qDebug()<<"Url : "<<tmpUrl<<" Sur la page : "<<url;
            nbUrlAdded++;
            if(tmpUrl!="")
                addUrl(tmpUrl);
            tmpUrl="";
        }//if ra
    }//while
    return nbUrlAdded;
}

int Crawler::crawlerXml(QString &pageWeb) {

    QDomDocument web;
    web.setContent(pageWeb);
    QDomNodeList nodel= web.elementsByTagName("a");
    int nbUrlAdded=0;
    for(int i=0;i<nodel.count();i++)
    {
        if(nodel.at(i).hasAttributes())
            for(int j=0;j<nodel.at(i).attributes().count();j++)
            {
                if(nodel.at(i).attributes().item(j).nodeName()=="href")
                {
                    QString url=nodel.at(i).attributes().item(j).nodeValue();
                    qDebug()<<">>>>Catch : "<<url;
                    QString finalUrl;
                    if(url.startsWith(startUrl.scheme()+"://"+startUrl.host()))
                        finalUrl=url;
                    else if(url.startsWith("./"))
                    {
                        url.remove(0,2);
                        QString fullPath=startUrl.path();
                        if(currentUrlCrawled>0)
                            fullPath=UrlCatched::allUrl->at(currentUrlCrawled)->getUrl().path();
                        int lastSPos=fullPath.lastIndexOf("/");
                        fullPath.remove(lastSPos,fullPath.length()-lastSPos);
                        if(fullPath.length()>0)
                            fullPath.append("/");
                        finalUrl=startUrl.scheme()+"://"+startUrl.host()+"/"+fullPath+url;
                    }
                    else if(url.startsWith("/"))
                        finalUrl=startUrl.scheme()+"://"+startUrl.host()+url;
                    else
                    {
                        if(url.startsWith("http://")||url.startsWith("https://"))
                            break;
                        finalUrl=startUrl.scheme()+"://"+startUrl.host()+startUrl.path()+url;
                    }
                    if(finalUrl.length()>0)
                    {
                        addUrl(finalUrl);
                        nbUrlAdded++;
                    }
                    qDebug()<<"Url : "<<finalUrl;
                }
            }
    }
    return nbUrlAdded;
}


QTreeWidgetItem* Crawler::recursiveAdd(QTreeWidgetItem *item,QString &toFind,int prof) {
    if(prof<0)//we seek the same profondeur
        return NULL;
    if(item->text(0)==toFind&&prof>=0)
        return item;//we got it!!
    prof=prof-1;
    for(int i=0;i<item->childCount();i++)
    {
        QTreeWidgetItem *tmp= recursiveAdd(item->child(i),toFind,prof);
        if(tmp!=NULL)
            return tmp;
    }
    return NULL;
}

void Crawler::addUrl(QString &url) {
    UrlCatched *urlc=new UrlCatched(url);
    QString fullUrl="http:/";//here a small hack ^^

    /*FIX: problem when scanning a specific directory on a domain*/
    QRegExp hl(QString("^https?://")+startUrl.host()+startUrl.path()+QString(".*"));
    /*FIX: problem with links that contains # or javascript:...*/
    QRegExp script(QString(".*(#|javascript:|mailto:).*"));
    /*END OF FIX*/

    if(!urlc->isInList(url))
    {/*add the current url to the list ...*/
        //urlc->addToList();
        QString tmpUrl=url;
        tmpUrl.replace(QRegExp("^http://"),"");
        QStringList folder =  tmpUrl.split("/");
        QTreeWidgetItem *lastItem=root;
        int nbProf=0;
        while(folder.count()>0)
        {
            QString f=folder.takeFirst();
            if(!f.isEmpty())//do not display ""
            {
                //here we add the hierarchy of the url
                QTreeWidgetItem *tmp;
                tmp = recursiveAdd(lastItem,f,nbProf);
                if(tmp!=NULL)
                    lastItem=tmp;
                else
                {
                    tmp = new QTreeWidgetItem(lastItem,QStringList(f));
                    lastItem->addChild(tmp);
                    lastItem=tmp;
                }
                nbProf++;
                fullUrl+="/"+f;
                UrlCatched * urlTmpFolder=new UrlCatched(fullUrl,false);
                //here we can find if the website is using URL REWRITING or PATH_INFO or NOT :p
                if(!urlTmpFolder->isInList(fullUrl) && hl.indexIn(fullUrl,0)!=-1 && script.indexIn(fullUrl,0)==-1)
                {
                    urlTmpFolder->addToList();
                    urlTmpFolder->setItem(lastItem);
                }
            }
        }
        urlc->setItem(lastItem);
        //to get an access to the object ...
    }
}
