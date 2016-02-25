#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    binding();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    setWindowTitle(tr(APP_NAME) + " " + tr(APP_VER));
    qApp->setStyle("Fusion");
    QFile file(":/res/styles/main.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    qApp->setStyleSheet(styleSheet);
    QLocale().setDefault(QLocale(QLocale::English));
    //qDebug() << QLocale().name();
}

void MainWindow::binding()
{
    connect(&networkmanager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleNetworkData(QNetworkReply*)));
    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->toolButton, SIGNAL(clicked(bool)), this, SLOT(fuckoff()));
    connect(ui->toolButton_2, SIGNAL(clicked(bool)), this, SLOT(fuckoff2()));
    connect(ui->lineEdit_cj_id, SIGNAL(returnPressed()), this, SLOT(fuckoff()));
    connect(ui->lineEdit_cj_name, SIGNAL(returnPressed()), this, SLOT(fuckoff()));
    connect(ui->lineEdit_cj_keywords, SIGNAL(returnPressed()), this, SLOT(fuckoff()));
}

void MainWindow::fuckoff()
{
    QUrl u;
    u.setUrl(ADVERTISER_LOOKUP_URL);
    QUrlQuery q;
    q.addQueryItem("advertiser-ids", ui->lineEdit_cj_id->text());
    q.addQueryItem("advertiser-name", ui->lineEdit_cj_name->text());
    q.addQueryItem("records-per-page", RECORDS_PER_PAGE);
    q.addQueryItem("page-number", PAGE_NUMBER);
    q.addQueryItem("keywords", ui->lineEdit_cj_keywords->text());
    u.setQuery(q);
    QNetworkRequest request(u);
    request.setRawHeader("authorization", CJ_KEY);
    networkmanager.get(request);
    ui->progressBar->reset();
    ui->progressBar->setValue(20);
}

void MainWindow::fuckoff2()
{
}

void MainWindow::handleNetworkData(QNetworkReply *networkReply)
{
    ui->progressBar->setValue(60);
    if (!networkReply->error()) {
        ui->treeWidget_cj_result->clear();
        QByteArray response(networkReply->readAll());
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(response.data());
        if (result.status == pugi::status_ok) {
            pugi::xml_node advertisers = doc.child("cj-api").child("advertisers");
            for (pugi::xml_node_iterator it = advertisers.begin(); it != advertisers.end(); ++it) {

                // advertiser name
                QTreeWidgetItem *twi = new QTreeWidgetItem(ui->treeWidget_cj_result);
                twi->setIcon(0,QIcon(":/res/images/basket_shopping.png"));
                twi->setText(0, it->child("advertiser-name").text().as_string());

                // advertiser id
                QTreeWidgetItem *twi2 = new QTreeWidgetItem(twi);
                twi2->setIcon(0,QIcon(":/res/images/key_solid.png"));
                twi2->setText(0, it->child("advertiser-id").text().as_string());

                // account status
                QTreeWidgetItem *twi3 = new QTreeWidgetItem(twi);
                twi3->setIcon(0,QIcon(":/res/images/key_solid.png"));
                twi3->setText(0, it->child("account-status").text().as_string());
            }
        }
    }
    ui->progressBar->setValue(100);
    networkReply->deleteLater();
    ui->progressBar->reset();
}
