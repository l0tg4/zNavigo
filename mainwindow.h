#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWebKitWidgets>
#include <QtWidgets>

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

public:
    FenPrincipale();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    QWidget *createTabWebPage(QString url = "");
    QWebView *actualPage();

private slots:
    void previous();
    void next();
    void home();
    void stop();
    void refresh();

    void about();
    void newTab();
    void closeTab();
    void loadPage();
    void changeTab(int index);
    void changeTitle(const QString & fullTitle);
    void changeUrl(const QUrl & url);

    void startLoad();
    void progressLoad(int pourcentage);
    void finishLoad(bool ok);

private:
    QTabWidget *tabs;

    QAction *actionNewTab;
    QAction *actionCloseTab;
    QAction *actionQuit;
    QAction *actionAbout;
    QAction *actionPrevious;
    QAction *actionNext;
    QAction *actionStop;
    QAction *actionRefresh;
    QAction *actionHome;
    QAction *actionGo;

    QLineEdit *fieldAdress;
    QProgressBar *progress;

};

#endif // MAINWINDOW_H
