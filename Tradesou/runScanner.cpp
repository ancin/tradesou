#include "runScanner.h"

#include "mainWindow.h"

runScanner *runScanner::_runScanner;

runScanner::runScanner(QWidget* parent,QString *url) : QWidget(parent) {
//    setupUi(this);
    _runScanner=this;
    this->resize(this->maximumSize().width(),this->maximumSize().height());

   // connect(tr_result, SIGNAL(itemClicked(QTreeWidgetItem *,int)), this, SLOT(urlItemClicked(QTreeWidgetItem *)));
   // connect(tr_result, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(urlItemClicked(QTreeWidgetItem *)));
   // if(url!=NULL)
        //tx_url->setText(url->trimmed());
}

void runScanner::urlItemClicked(QTreeWidgetItem * item)
{
    //qDebug()<< "SIMPLETEST"+item->text(2)+"\n";
   // cout<<">>> URL item clicked..."<<endl;
}
void runScanner::on_bt_url_clicked(){
   // QUrl url(tx_url->text());
   // Crawler *s=new Crawler(url,tr_result);
}
void runScanner::setLog(QString line)
{
       // _runScanner->log->insertPlainText("("+QTime::currentTime().toString()+") "+line);
}
void runScanner::setPage(QUrl &url)
{
    //Useless now ...
    //MainWindow::getWebView()->setPage(url);
        //_runScanner->webView->load(url);
}

