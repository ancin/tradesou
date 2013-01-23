#ifndef FORMCATCHED_H
#define FORMCATCHED_H

#include "runScanner.h"
class FormCatched /*: public QObject*/ {
        //Q_OBJECT
        private:
                QString method; //POST | GET
                QString url;    //POST | GET
                QList<QPair<QString,QString> > *input;//LIST OF INPUT <name,value>
                QTreeWidgetItem *item;
        public:
                FormCatched();
                FormCatched(const QString &f,const QString &url_page);
                ~FormCatched();

                QList<QPair<QString,QString> > *getInput();
                QString &getMethod();
                QString &getUrl();

                //bool isInList();
                static bool isInList(FormCatched *f);
                void addToList();
                void addItem(QTreeWidgetItem *lastItem);
                QTreeWidgetItem *getItem();

                static QList<FormCatched*> *allForm;
};


#endif // FORMCATCHED_H
