#include "mainwindow.h"

#include <QtWebKitWidgets>
#include <QtWidgets>

FenPrincipale::FenPrincipale()
{
    //génération des widgets de la fenêtre principale
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createTabWebPage();

    //génération des tabs et chargement de la page d'accueil
    tabs = new QTabWidget;
    tabs->addTab(createTabWebPage(tr("http://google.com")), tr("(New page)"));
    connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(changeTab(int)));
    setCentralWidget(tabs);

    //définition de quelques propriétés de la fenêtre
    setMinimumSize(500, 300);
    setWindowIcon(QIcon("images/znavigo"));
    setWindowTitle(tr("zNavigo"));
}

QWidget *FenPrincipale::createTabWebPage(QString url)
{
    QWidget *pageTab = new QWidget;
    QWebView *pageWeb = new QWebView;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(pageWeb);
    pageTab->setLayout(layout);

    if(url.isEmpty())
    {
        pageWeb->load(QUrl(tr("html/blank_page")));
    }
    else
    {
        if(url.left(7)  != "http://")
        {
            url = "http://" + url;
        }
        pageWeb->load(QUrl(url));
    }

    //gestion des signaux envoyés par la page web
    connect(pageWeb, SIGNAL(titleChanged(QString)), this, SLOT(changeTitle(QString)));
    connect(pageWeb, SIGNAL(urlChanged(QUrl)), this, SLOT(changeUrl(QUrl)));
    connect(pageWeb, SIGNAL(loadStarted()), this, SLOT(startLoad()));
    connect(pageWeb, SIGNAL(loadProgress(int)), this, SLOT(progressLoad(int)));
    connect(pageWeb, SIGNAL(loadFinished(bool)), this, SLOT(finishLoad(bool)));

    return pageTab;
}

void FenPrincipale::previous()
{
    actualPage()->back();
}

void FenPrincipale::next()
{
    actualPage()->forward();
}

void FenPrincipale::home()
{
    actualPage()->load(QUrl(tr("http://google.com")));
}

void FenPrincipale::stop()
{
    actualPage()->stop();
}

void FenPrincipale::refresh()
{
    actualPage()->reload();
}

void FenPrincipale::about()
{
    QMessageBox::information(this, tr("About"), tr("zNavigo est un projet réalisé..."));
}

void FenPrincipale::newTab()
{
    int indexNewTab = tabs->addTab(createTabWebPage(), tr("(New page)"));
    tabs->setCurrentIndex(indexNewTab);
    fieldAdress->setText("");
    fieldAdress->setFocus(Qt::OtherFocusReason);
}

void FenPrincipale::closeTab()
{
    //on ne doit pas fermer le dernier onglet
    if (tabs->count() > 1)
    {
        tabs->removeTab(tabs->currentIndex());
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("It takes at least one tab !"));
    }
}

void FenPrincipale::loadPage()
{
    QString url = fieldAdress->text();

    //on rajoute le "http://" s'il n'est pas déjà dans l'adresse
    if(url.left(7) != "http://")
    {
        url = "http://" + url;
        fieldAdress->setText(url);
    }

    actualPage()->load(QUrl(url));
}

void FenPrincipale::changeTab(int index)
{
    changeTitle(actualPage()->title());
    changeUrl(actualPage()->url());
}

void FenPrincipale::changeTitle(const QString & fullTitle)
{
    QString shortTitle = fullTitle;
    // On tronque le titre pour éviter des onglets trop larges
    if (fullTitle.size() > 40)
    {
        shortTitle = fullTitle.left(40) + "...";
    }

    setWindowTitle(shortTitle + " - " + tr("zNavigo"));
    tabs->setTabText(tabs->currentIndex(), shortTitle);
}

void FenPrincipale::changeUrl(const QUrl & url)
{
    if (url.toString() != tr("html/page_blanche.html"))
    {
        fieldAdress->setText(url.toString());
    }
}

void FenPrincipale::startLoad()
{
    progress->setVisible(true);
}

void FenPrincipale::progressLoad(int pourcentage)
{
    progress->setValue(pourcentage);
}

void FenPrincipale::finishLoad(bool ok)
{
    progress->setVisible(false);
    statusBar()->showMessage(tr("Prêt"), 2000);
}

QWebView *FenPrincipale::actualPage()
{
    return tabs->currentWidget()->findChild<QWebView *>();
}
