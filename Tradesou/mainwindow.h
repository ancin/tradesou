#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_searchBtn_clicked();

private:
    Ui::MainWindow *ui;

    void createHorizontalGroupBox();
    void createGridGroupBox();
    void createToolBars();
    void createActions();
    void createStatusBar();
    void createMenus();



    enum { NumGridRows = 3, NumButtons = 4 };
    QSystemTrayIcon* trayIcon;
    QMenuBar *menuBar;
    QGroupBox *horizontalGroupBox;
    QGroupBox *gridGroupBox;
    QGroupBox *formGroupBox;
    QTextEdit *smallEditor;
    QTextEdit *bigEditor;
    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QPushButton *buttons[NumButtons];
    QDialogButtonBox *buttonBox;
    //
    QTextEdit *output;


    QPushButton *searchBtn;
    QLineEdit * urlLnEdit;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    QAction *exitAction;

    //
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    //
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;

};

#endif // MAINWINDOW_H
