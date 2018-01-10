#include "screeninclu/alamdlg2.h"
#include "ui_alamdlg2.h"

#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include"global.h"
//add 6.14-5
extern fileoperate *files;


alamDlg2::alamDlg2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alamDlg2)
{
    ui->setupUi(this);
    //时间计时器
   // QTimer *timer = new QTimer(this);
   // connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
   // timer->start(1000);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);
    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);
    ui->AlarmConcMin_change->setFocusPolicy(Qt::NoFocus);
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->lowerlimitalarmvalueTip->setFocusPolicy(Qt::NoFocus);
    ui->maximumtemperatureTip->setFocusPolicy(Qt::NoFocus);
    ui->minimumtemperatureTip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->pageUp->setFocusPolicy(Qt::NoFocus);
    ui->Tmax_change->setFocusPolicy(Qt::NoFocus);
    ui->Tmin_change->setFocusPolicy(Qt::NoFocus);

    //add 6.14-2
    ui->AlarmConcMin_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->Tmax_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->Tmin_lineEdit->setFocusPolicy(Qt::NoFocus);

}

alamDlg2::~alamDlg2()
{
    delete ui;
    delete keyboarddlg;
}


void alamDlg2::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}

void alamDlg2::on_lowerlimitalarmvalueTip_clicked()
{
     QMessageBox::information(this,"input","input value(ppmv)");
}

void alamDlg2::on_maximumtemperatureTip_clicked()
{
    QMessageBox::information(this,"input","input value(degree centigrade)");
}

void alamDlg2::on_minimumtemperatureTip_clicked()
{
     QMessageBox::information(this,"input","input value(degree centigrade)");
}



void alamDlg2::backtothis()
{
    this->show();
    this->show_paras();


}

void alamDlg2::on_pageUp_clicked()
{
    up();
    this->hide();
}

void alamDlg2::on_pageDown_clicked()
{
    if(permit_flag==0)
    {
        QMessageBox::information(this,"warning","you are not avaliable to continue");

    }
    else
    {
       down();
       this->hide();
    }


}

void alamDlg2::on_AlarmConcMin_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->AlarmConcMin_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->AlarmConcMin_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_AlarmConcMin(QString)));

}

void alamDlg2::on_Tmax_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Tmax_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Tmax_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Tmax(QString)));

}

void alamDlg2::on_Tmin_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Tmin_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Tmin_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Tmin(QString)));

}


void alamDlg2::on_back_clicked()
{
   backCalibrationdlg();
    this->hide();
}

void alamDlg2::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        AlarmConcMinstr = QString::number(AnaParas_Ch0->AlarmConcMin,10);//bool,int,long
        ui->AlarmConcMin_lineEdit->setText(AlarmConcMinstr);

        Tmaxstr =  QString::number(AnaParas_Ch0->Tmax,'f',2);
        ui->Tmax_lineEdit->setText(Tmaxstr);

        Tminstr =  QString::number(AnaParas_Ch0->Tmin,'f',2);//float ,double
        ui->Tmin_lineEdit->setText(Tminstr);

    }
    else
    {
        AlarmConcMinstr = QString::number(AnaParas_Ch1->AlarmConcMin,10);//bool,int,long
        ui->AlarmConcMin_lineEdit->setText(AlarmConcMinstr);

        Tmaxstr =  QString::number(AnaParas_Ch1->Tmax,'f',2);
        ui->Tmax_lineEdit->setText(Tmaxstr);

        Tminstr =  QString::number(AnaParas_Ch1->Tmin,'f',2);//float ,double
        ui->Tmin_lineEdit->setText(Tminstr);
    }

}

void alamDlg2::range_limit_AlarmConcMin(QString)
{
    bool ok;
    int a = ui->AlarmConcMin_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=100)))
    {
     on_lowerlimitalarmvalueTip_clicked();

     ui->AlarmConcMin_lineEdit->setText(AlarmConcMinstr);
    }
}
void alamDlg2::range_limit_Tmax(QString)
{
    bool ok;
    float a = ui->Tmax_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100)))
    {
     on_maximumtemperatureTip_clicked();

     ui->Tmax_lineEdit->setText(Tmaxstr);
    }
}
void alamDlg2::range_limit_Tmin(QString)
{
    bool ok;
    float a = ui->Tmin_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100)))
    {
      on_minimumtemperatureTip_clicked();

     ui->Tmin_lineEdit->setText(Tminstr);
    }
}


void alamDlg2::on_ok_clicked()
{
    bool ok;
    int AlarmConcMin = ui->AlarmConcMin_lineEdit->text().toFloat(&ok);
    float Tmax =ui->Tmax_lineEdit->text().toFloat(&ok);
    float Tmin =ui->Tmin_lineEdit->text().toFloat(&ok);


     if(CH_Flag==0)
     {
         AnaParas_Ch0->AlarmConcMin=AlarmConcMin;
         AnaParas_Ch0->Tmax=Tmax;
         AnaParas_Ch0->Tmin=Tmin;

         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->AlarmConcMin=AlarmConcMin;
         AnaParas_Ch1->Tmax=Tmax;
         AnaParas_Ch1->Tmin=Tmin;
         files->writefile(1);
     }
}

void alamDlg2::on_cancel_clicked()
{
     show_paras();
}
