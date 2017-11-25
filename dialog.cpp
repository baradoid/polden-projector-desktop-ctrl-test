#include "dialog.h"
#include "ui_dialog.h"
#include <QUdpSocket>
#include <QNetworkDatagram>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    settings("murinets", "projector-ctrl-test")
{
    ui->setupUi(this);
    s = new QUdpSocket(this);
    if(s->bind(QHostAddress::LocalHost, 8053) == false){
        qDebug("bind fail");
    }
    connect(s, SIGNAL(readyRead()), this, SLOT(handleUdpReadyRead()));

    QString destIp = settings.value("destIp", QString("localhost")).toString();
    int destPort = settings.value("destPort", 8052).toInt();
    int locPort = settings.value("locPort", 8053).toInt();

    ui->lineEditDestIp->setText(destIp);
    ui->lineEditDestPort->setText(QString("%1").arg(destPort));
    ui->lineEditLocPort->setText(QString("%1").arg(locPort));

    connect(ui->pushButtonPon1, &QPushButton::clicked, [this](){handlePushPon(0);});
    connect(ui->pushButtonPon2, &QPushButton::clicked, [this](){handlePushPon(1);});
    connect(ui->pushButtonPon3, &QPushButton::clicked, [this](){handlePushPon(2);});
    connect(ui->pushButtonPon4, &QPushButton::clicked, [this](){handlePushPon(3);});
    connect(ui->pushButtonPon5, &QPushButton::clicked, [this](){handlePushPon(4);});

    connect(ui->pushButtonPoff1, &QPushButton::clicked, [this](){handlePushPoff(0);});
    connect(ui->pushButtonPoff2, &QPushButton::clicked, [this](){handlePushPoff(1);});
    connect(ui->pushButtonPoff3, &QPushButton::clicked, [this](){handlePushPoff(2);});
    connect(ui->pushButtonPoff4, &QPushButton::clicked, [this](){handlePushPoff(3);});
    connect(ui->pushButtonPoff5, &QPushButton::clicked, [this](){handlePushPoff(4);});


    destIp = settings.value("sonoffDestIp", QString("127.0.0.1")).toString();
    destPort = settings.value("destPort", 8053).toInt();
    ui->lineEditSonoffDestIp->setText(destIp);
    ui->lineEditSonoffDestPort->setText(QString("%1").arg(destPort));

    connect(ui->pushButtonDev1On, &QPushButton::clicked,
        [this](){
        QString devId = ui->lineEditDeviceId1->text();
        turnReleSonOff(devId, 0, true);
        });

    connect(ui->pushButtonDev1Off, &QPushButton::clicked,
        [this](){
        QString devId = ui->lineEditDeviceId1->text();
        turnReleSonOff(devId, 0, false);
        });
}

Dialog::~Dialog()
{
    settings.setValue("destIp", ui->lineEditDestIp->text());
    settings.setValue("destPort", ui->lineEditDestPort->text().toInt());
    settings.setValue("locPort", ui->lineEditLocPort->text().toInt());
    delete ui;
}

void Dialog::on_pushButtonPowerOnAll_clicked()
{                
    QString destIp = ui->lineEditDestIp->text();
    int destPort = ui->lineEditDestPort->text().toInt();
    QString msg("pon_all");
    if(s->writeDatagram(msg.toLatin1(), QHostAddress(destIp), destPort) == -1)
        qDebug() << "sendErr";
}

void Dialog::on_pushButtonPowerOffAll_clicked()
{
    QString destIp = ui->lineEditDestIp->text();
    int destPort = ui->lineEditDestPort->text().toInt();
    QString msg("poff_all");
    if(s->writeDatagram(msg.toLatin1(), QHostAddress(destIp), destPort) == -1)
        qDebug() << "sendErr";
}

void Dialog::on_pushButtonStatReq_clicked()
{ 
    QString destIp = ui->lineEditDestIp->text();
    int destPort = ui->lineEditDestPort->text().toInt();
    QString msg("stat?");
    if(s->writeDatagram(msg.toLatin1(), QHostAddress(destIp), destPort) == -1)
        qDebug() << "sendErr";
}

void Dialog::handleUdpReadyRead()
{
    while (s->hasPendingDatagrams()) {
        QNetworkDatagram datagram = s->receiveDatagram();
        QString msg(datagram.data());
        ui->lineEditStat->setText(msg);
        qDebug() << qPrintable(msg);
    }
}
void Dialog::handlePushPon(int id)
{   
    QString destIp = ui->lineEditDestIp->text();
    int destPort = ui->lineEditDestPort->text().toInt();
    QString msg = QString("pon_%1").arg(id);
    if(s->writeDatagram(msg.toLatin1(), QHostAddress(destIp), destPort) == -1)
        qDebug() << "sendErr";
}

void Dialog::handlePushPoff(int id)
{
    QString destIp = ui->lineEditDestIp->text();
    int destPort = ui->lineEditDestPort->text().toInt();
    QString msg = QString("poff_%1").arg(id);
    if(s->writeDatagram(msg.toLatin1(), QHostAddress(destIp), destPort) == -1)
        qDebug() << "sendErr";
}


void Dialog::turnReleSonOff(QString devId, int releId, bool ena)
{

}
