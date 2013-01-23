#include "formCatched.h"

QList<FormCatched*> *FormCatched::allForm=new QList<FormCatched*>();


FormCatched::FormCatched(const QString &f,const QString &url_page)
{
    //CATCH ACTION / METHOD
    QRegExp action("action=['\"]?[^>'\"]+");
    QRegExp method("method=['\"]?[^>'\"]+");
    QUrl urlTmp(url_page);
    if(action.indexIn(f)!=-1)
    {
        this->url=action.capturedTexts().takeFirst();
        this->url.replace(QRegExp("action=|'|\""),"");
        if(this->url.startsWith("/"))
        {//need to add the host
            this->url=urlTmp.scheme()+"://"+urlTmp.host()+this->url;
        }
        if(!this->url.startsWith("http://"))//here we will get a problem with https forms
        {//so we need to retrieve the path and add the url :
            int lastSlashe = urlTmp.path().lastIndexOf("/")+1;
            this->url=urlTmp.scheme()+"://"+urlTmp.host()+urlTmp.path().replace(lastSlashe,urlTmp.path().length()-lastSlashe,"")+this->url;
        }
    }

    if(method.indexIn(f)!=-1)
    {
        this->method=method.capturedTexts().takeFirst();
        this->method.replace(QRegExp("method=|'|\""),"");
    }

    //CATCH ALL INPUTS
    QRegExp rx("<(input|textarea)[^>]*>");
    QRegExp name("name=['\"]?(?:[^>'\"]+)");
    QRegExp value("value=['\"]?[^>'\"]+");
    input=new QList<QPair<QString,QString> >();

    int pos=0;
    while((pos = rx.indexIn(f, pos)) != -1)
    {//here we got a <input.*>
        QString qs=rx.capturedTexts().takeFirst();
        pos += rx.matchedLength();

        if(name.indexIn(qs)!=-1)
        {
            QString nameContent = name.capturedTexts().takeFirst();
            nameContent.replace(QRegExp("(name=|'|\")"),"");
            QString valueContent("");
            if(value.indexIn(qs)!=-1)
            {//value aren't usefull without name so ...
                valueContent = value.capturedTexts().takeFirst();
                valueContent.replace(QRegExp("(value=|'|\")"),"");
            }
            QPair<QString,QString> InputNamVal(nameContent,valueContent);
            input->push_back(InputNamVal);
        }
    }
}

FormCatched::~FormCatched()
{
    delete input;
    //delete item;
}




bool FormCatched::isInList(FormCatched *f)
{
    for(int i=0;i<FormCatched::allForm->size();i++)
    {
        //if action url and method are equals so it's the same forms ?? :s
        FormCatched* tmp = FormCatched::allForm->at(i);
        if(
                ( f->getUrl()           == tmp->getUrl()           ) &&
                ( f->getMethod()        == tmp->getMethod()        ) &&
                ( f->getInput()->size() == tmp->getInput()->size() )
                )
        {
            return true;
        }
    }
    return false;
}

//GETTERS
QList<QPair<QString,QString> > *FormCatched::getInput(){return this->input; }
QString &FormCatched::getMethod(){return this->method;}
QString &FormCatched::getUrl(){return this->url;}

void FormCatched::addToList(){FormCatched::allForm->append(this);}
void FormCatched::addItem(QTreeWidgetItem *lastItem)
{//add to the list
    QString formName = this->url+" ["+this->method.toUpper()+"]";
    item = new QTreeWidgetItem(lastItem,QStringList(formName));
    lastItem->addChild(item);
    QTreeWidgetItem *tmp;
    QStringList qstl;
    for(int i=0;i<this->getInput()->size();i++)
    {
        //QPair<QString,QString> tmpS = ;
        qstl = QStringList(this->getInput()->at(i).first);
        tmp = new QTreeWidgetItem(item,qstl);
    }
}


