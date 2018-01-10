#include "screeninclu/alamdlg.h"
#include "ui_alamdlg.h"

#include <QTime>
#include <QTimer>
#include <QMessageBox>

//add 6.14-5
extern fileoperate *files;
//extern QString context;


alamDlg::alamDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alamDlg)
{
    ui->setupUi(this);
    ui->AlarmConcMax_ch->setFocusPolicy(Qt::NoFocus);
    ui->alarmprocessionTip->setFocusPolicy(Qt::NoFocus);
    ui->Alarm_ch->setFocusPolicy(Qt::NoFocus);
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->highlimitalarmvalueTip->setFocusPolicy(Qt::NoFocus);
    ui->maximumpressureTip->setFocusPolicy(Qt::NoFocus);
    ui->minimumpressureTip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->Pmax_ch->setFocusPolicy(Qt::NoFocus);
    ui->Pmin_ch->setFocusPolicy(Qt::NoFocus);

    setWindowFlags(Qt::FramelessWindowHint);
    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);
    //时间计时器
   // QTimer *timer = new QTimer(this);
   // connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
   // timer->start(1000);
    keyboarddlg=new keyboardDlg;

    //add 6.14-2
   ui->Alarm_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->Pmax_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->Pmin_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->AlarmConcMax_lineEdit->setFocusPolicy(Qt::NoFocus);

}

alamDlg::~alamDlg()
{
    delete ui;
    delete keyboarddlg;
}

void alamDlg::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}


void alamDlg::backtothis()
{
    this->show();
    this->show_paras();

}


void alamDlg::on_alarmprocessionTip_clicked()
{
    QMessageBox::information(this,"choose","0:open  1:forbidden   2:eliminate");
}

void alamDlg::on_maximumpressureTip_clicked()
{
     QMessageBox::information(this,"input","input value(mbar)");
}

void alamDlg::on_minimumpressureTip_clicked()
{
     QMessageBox::information(this,"input","input value(mbar)");
}

void alamDlg::on_highlimitalarmvalueTip_clicked()
{
     QMessageBox::information(this,"input","input value(ppmv)");
}

void alamDlg::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void alamDlg::on_pageDown_clicked()
{
    this->hide();
    down();
}

void alamDlg::on_Alarm_ch_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Alarm_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Alarm_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Alarm(QString)));

}

void alamDlg::on_Pmax_ch_clicked()
{

    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Pmax_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Pmax_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Pmax(QString)));


}

void alamDlg::on_Pmin_ch_clicked()
{

    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Pmin_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Pmin_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Pmin(QString)));

}

void alamDlg::on_AlarmConcMax_ch_clicked()
{

    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->AlarmConcMax_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->AlarmConcMax_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_AlarmConcMax(QString)));
}

void alamDlg::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        Alarmstr = QString::number(AnaParas_Ch0->Alarm,10);//bool,int,long
        ui->Alarm_lineEdit->setText(Alarmstr);

        Pmaxstr =  QString::number(AnaParas_Ch0->Pmax,'f',2);
        ui->Pmax_lineEdit->setText(Pmaxstr);

        Pminstr =  QString::number((int)AnaParas_Ch0->Pmin,'f',2);
        ui->Pmin_lineEdit->setText(Pminstr);

        AlarmConcMaxstr =  QString::number(AnaParas_Ch0->AlarmConcMax,10);//float ,double
        ui->AlarmConcMax_lineEdit->setText(AlarmConcMaxstr);

    }
    else
    {
        Alarmstr = QString::number(AnaParas_Ch1->Alarm,10);//bool,int,long
        ui->Alarm_lineEdit->setText(Alarmstr);

        Pmaxstr =  QString::number(AnaParas_Ch1->Pmax,'f',2);
        ui->Pmax_lineEdit->setText(Pmaxstr);

        Pminstr =  QString::number((int)AnaParas_Ch1->Pmin,'f',2);
        ui->Pmin_lineEdit->setText(Pminstr);

        AlarmConcMaxstr =  QString::number(AnaParas_Ch1->AlarmConcMax,10);//float ,double
        ui->AlarmConcMax_lineEdit->setText(AlarmConcMaxstr);
    }

  }

 void alamDlg::range_limit_Alarm(QString)
    {
        bool ok;
        int a = ui->Alarm_lineEdit->text().toInt(&ok,10);
        if(!((a>=0)&&(a<=1)))
        {
         on_alarmprocessionTip_clicked();

         ui->Alarm_lineEdit->setText(Alarmstr);
        }
    }
    void alamDlg::range_limit_Pmax(QString)
    {
        bool ok;
        float a = ui->Pmax_lineEdit->text().toFloat(&ok);
        if(!((a>=0)&&(a<=100000)))
        {
         on_maximumpressureTip_clicked();

         ui->Pmax_lineEdit->setText(Pmaxstr);
        }
    }
    void alamDlg::range_limit_Pmin(QString)
    {
        bool ok;
        float a = ui->Pmin_lineEdit->text().toFloat(&ok);
        if(!((a>=-10000)&&(a<=100000)))
        {
         on_minimumpressureTip_clicked();

         ui->Pmin_lineEdit->setText(Pminstr);
        }
    }
    void alamDlg::range_limit_AlarmConcMax(QString)
    {
        bool ok;
        int a = ui->AlarmConcMax_lineEdit->text().toInt(&ok);
        if(!((a>=0)&&(a<=1000)))
        {
         on_highlimitalarmvalueTip_clicked();

         ui->AlarmConcMax_lineEdit->setText(AlarmConcMaxstr);
        }
    }


void alamDlg::on_ok_clicked()
{
    bool ok;
    int Alarm = ui->Alarm_lineEdit->text().toInt(&ok);
    float Pmax =ui->Pmax_lineEdit->text().toFloat(&ok);
    float Pmin =ui->Pmin_lineEdit->text().toFloat(&ok);
    int AlarmConcMax =ui->AlarmConcMax_lineEdit->text().toInt(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->Alarm=Alarm;
         AnaParas_Ch0->Pmax=Pmax;
         AnaParas_Ch0->Pmin=Pmin;
         AnaParas_Ch0->AlarmConcMax=AlarmConcMax;

         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->Alarm=Alarm;
         AnaParas_Ch1->Pmax=Pmax;
         AnaParas_Ch1->Pmin=Pmin;
         AnaParas_Ch1->AlarmConcMax=AlarmConcMax;

         files->writefile(1);
     }
}

void alamDlg::on_cancel_clicked()
{
     show_paras();
}
