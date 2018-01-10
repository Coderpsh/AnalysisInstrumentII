#include "screeninclu/alamdlg4.h"
#include "ui_alamdlg4.h"

#include <QTime>
#include <QTimer>
#include<QMessageBox>

//add 6.14-5
extern fileoperate *files;


alamDlg4::alamDlg4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alamDlg4)
{
    ui->setupUi(this);
    //时间计时器
  //  QTimer *timer = new QTimer(this);
  //  connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
  //  timer->start(1000);
    keyboarddlg=new keyboardDlg;
     setWindowFlags(Qt::FramelessWindowHint);
     //add 6.14-1
     setFocusPolicy(Qt::NoFocus);

     ui->back->setFocusPolicy(Qt::NoFocus);
     ui->cancel->setFocusPolicy(Qt::NoFocus);
     ui->darkcurrenttoohighTip->setFocusPolicy(Qt::NoFocus);
     ui->darkcurrenttoolow->setFocusPolicy(Qt::NoFocus);
     ui->NullHigh_change->setFocusPolicy(Qt::NoFocus);
     ui->NullLow_change->setFocusPolicy(Qt::NoFocus);
     ui->ok->setFocusPolicy(Qt::NoFocus);
     ui->pageUp->setFocusPolicy(Qt::NoFocus);
     ui->spectralsaturationthresholdTip->setFocusPolicy(Qt::NoFocus);
     ui->temperaturedifferencelimitedrestartTip->setFocusPolicy(Qt::NoFocus);
     ui->Tlimit_change->setFocusPolicy(Qt::NoFocus);
     ui->TwoFSat_change->setFocusPolicy(Qt::NoFocus);

     //add 6.14-2
     ui->Tlimit_lineEdit->setFocusPolicy(Qt::NoFocus);
     ui->TwoFSat_lineEdit->setFocusPolicy(Qt::NoFocus);
     ui->NullHigh_lineEdit->setFocusPolicy(Qt::NoFocus);
     ui->NullLow_lineEdit->setFocusPolicy(Qt::NoFocus);

}

alamDlg4::~alamDlg4()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void alamDlg4::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}


void alamDlg4::backtothis()
{
    this->show();
    this->show_paras();
}

void alamDlg4::on_temperaturedifferencelimitedrestartTip_clicked()
{
    QMessageBox::information(this,"input"," 0:close  >0:degree centigrade");
}

void alamDlg4::on_spectralsaturationthresholdTip_clicked()
{
    QMessageBox::information(this,"input","input value");
}

void alamDlg4::on_darkcurrenttoolow_clicked()
{
     QMessageBox::information(this,"input","input value");
}

void alamDlg4::on_darkcurrenttoohighTip_clicked()
{
    QMessageBox::information(this,"input","input value");
}

void alamDlg4::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void alamDlg4::on_pageUp_clicked()
{
    up();
    this->hide();
}

void alamDlg4::on_Tlimit_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Tlimit_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();

    QObject::connect(ui->Tlimit_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_wait(QString)));

}

void alamDlg4::on_TwoFSat_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->TwoFSat_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->TwoFSat_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_TwoFSat(QString)));

}

void alamDlg4::on_NullHigh_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->NullHigh_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->NullHigh_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_NullHigh(QString)));

}

void alamDlg4::on_NullLow_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->NullLow_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->NullLow_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_NullLow(QString)));
}


void alamDlg4::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        waitstr = QString::number(AnaParas_Ch0->wait,'f',2);//bool,int,long
        ui->Tlimit_lineEdit->setText(waitstr);

        TwoFSatstr =  QString::number(AnaParas_Ch0->TwoFSat,'f',2);
        ui->TwoFSat_lineEdit->setText(TwoFSatstr);

        NullHighstr =  QString::number((int)AnaParas_Ch0->NullHigh,'f',2);
        ui->NullHigh_lineEdit->setText(NullHighstr);

        NullLowstr =  QString::number(AnaParas_Ch0->NullLow,'f',2);//float ,double
        ui->NullLow_lineEdit->setText(NullLowstr);

    }
    else
    {
        waitstr = QString::number(AnaParas_Ch1->wait,'f',2);//bool,int,long
        ui->Tlimit_lineEdit->setText(waitstr);

        TwoFSatstr =  QString::number(AnaParas_Ch1->TwoFSat,'f',2);
        ui->TwoFSat_lineEdit->setText(TwoFSatstr);

        NullHighstr =  QString::number((int)AnaParas_Ch1->NullHigh,'f',2);
        ui->NullHigh_lineEdit->setText(NullHighstr);

        NullLowstr =  QString::number(AnaParas_Ch1->NullLow,'f',2);//float ,double
        ui->NullLow_lineEdit->setText(NullLowstr);

    }

}

//add 6.14-4
void alamDlg4::range_limit_wait(QString)
{
    bool ok;
    float a = ui->Tlimit_lineEdit->text().toFloat(&ok);
    if(!((a>=0)))
    {
     on_temperaturedifferencelimitedrestartTip_clicked();

     ui->Tlimit_lineEdit->setText(waitstr);
    }
}
void alamDlg4::range_limit_TwoFSat(QString)
{
    bool ok;
    float a = ui->TwoFSat_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100000)))
    {
    on_spectralsaturationthresholdTip_clicked();

     ui->TwoFSat_lineEdit->setText(TwoFSatstr);
    }
}
void alamDlg4::range_limit_NullHigh(QString)
{
    bool ok;
    float a = ui->NullHigh_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100000)))
    {
      on_darkcurrenttoohighTip_clicked();

     ui->NullHigh_lineEdit->setText(NullHighstr);
    }
}
void alamDlg4::range_limit_NullLow(QString)
{
    bool ok;
    float a = ui->NullLow_lineEdit->text().toFloat(&ok);
    if(!((a>=-10000)&&(a<=100000)))
    {
     on_darkcurrenttoolow_clicked();

     ui->NullLow_lineEdit->setText(NullLowstr);
    }
}

void alamDlg4::on_ok_clicked()
{
    bool ok;
    float wait = ui->Tlimit_lineEdit->text().toFloat(&ok);
    float TwoFSat =ui->TwoFSat_lineEdit->text().toFloat(&ok);
    float NullHigh =ui->NullHigh_lineEdit->text().toFloat(&ok);
    float NullLow =ui->NullLow_lineEdit->text().toFloat(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->wait=wait;
         AnaParas_Ch0->TwoFSat=TwoFSat;
         AnaParas_Ch0->NullHigh=NullHigh;
         AnaParas_Ch0->NullLow=NullLow;

         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->wait=wait;
         AnaParas_Ch1->TwoFSat=TwoFSat;
         AnaParas_Ch1->NullHigh=NullHigh;
         AnaParas_Ch1->NullLow=NullLow;

         files->writefile(1);
     }
}

void alamDlg4::on_cancel_clicked()
{
     show_paras();
}
