#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QUdpSocket>
#include <QSettings>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButtonPowerOnAll_clicked();
    void on_pushButtonPowerOffAll_clicked();
    void on_pushButtonStatReq_clicked();
    void handleUdpReadyRead();

private:
    Ui::Dialog *ui;
    QUdpSocket *s;
    void handlePushPon(int);
    void handlePushPoff(int);

    QSettings settings;


};

#endif // DIALOG_H
