#include "dialog.h"
#include "ui_dialog.h"
#include <QUdpSocket>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonPowerOnAll_clicked()
{
    QString msg("pon_all\r\n");
    QUdpSocket s;
    if(s.writeDatagram(msg.toLatin1(), QHostAddress::LocalHost, 8052) == -1)
        qDebug() << "sendErr";
}

void Dialog::on_pushButtonPowerOffAll_clicked()
{
    QString msg("poff_all\r\n");
    QUdpSocket s;
    if(s.writeDatagram(msg.toLatin1(), QHostAddress::LocalHost, 8052) == -1)
        qDebug() << "sendErr";
}
