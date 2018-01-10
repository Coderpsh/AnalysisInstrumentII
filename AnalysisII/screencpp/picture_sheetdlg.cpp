#include "screeninclu/picture_sheetdlg.h"
#include "ui_picture_sheetdlg.h"

#include <QTime>
#include <QTimer>


picture_sheetDlg::picture_sheetDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::picture_sheetDlg)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(800,480);
    //时间计时器
//    QTimer *timer = new QTimer(this);
 //   connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
 //   timer->start(1000);
    ui->back->setFocusPolicy(Qt::NoFocus);

}

picture_sheetDlg::~picture_sheetDlg()
{
    delete ui;
}

//显示时间
void picture_sheetDlg::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}

void picture_sheetDlg::on_back_clicked()
{
    backMainWindow();
    this->hide();
}
