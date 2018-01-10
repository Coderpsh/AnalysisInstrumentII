#include "screeninclu/spectrumselfregulatedlg.h"
#include "ui_spectrumselfregulatedlg.h"

#include <QTime>
#include <QTimer>
#include <QMessageBox>

//add 6.14-5
extern fileoperate *files;

spectrumSelfRegulateDlg::spectrumSelfRegulateDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::spectrumSelfRegulateDlg)
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
    ui->endingpointofpeakcalibrationTip->setFocusPolicy(Qt::NoFocus);
    ui->findaveragepeakTip->setFocusPolicy(Qt::NoFocus);
    ui->findpeakstartingpointTip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->pageUp->setFocusPolicy(Qt::NoFocus);
    ui->PkTarget_change->setFocusPolicy(Qt::NoFocus);
    ui->PkTrkAvg_change->setFocusPolicy(Qt::NoFocus);
    ui->PkTrkStart_change->setFocusPolicy(Qt::NoFocus);
    ui->startingpointofpeakcalibrationTip->setFocusPolicy(Qt::NoFocus);
    ui->targetpeakTip->setFocusPolicy(Qt::NoFocus);
    ui->ValPkTrkEnd_change->setFocusPolicy(Qt::NoFocus);
    ui->ValPkTrkStart_change->setFocusPolicy(Qt::NoFocus);

    //add 6.14-2
   ui->PkTrkAvg_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->PkTarget_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->PkTrkStart_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->ValPkTrkEnd_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->ValPkTrkStart_lineEdit->setFocusPolicy(Qt::NoFocus);

 }


spectrumSelfRegulateDlg::~spectrumSelfRegulateDlg()
{
    delete ui;
    delete keyboarddlg;
}


//显示时间
void spectrumSelfRegulateDlg::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}

void spectrumSelfRegulateDlg::on_findaveragepeakTip_clicked()
{
     QMessageBox::information(this,"input","input value(2-100)");
}

void spectrumSelfRegulateDlg::on_targetpeakTip_clicked()
{
    QMessageBox::information(this,"input","input value(0-1000)  0:automation  else:target peak");
}

void spectrumSelfRegulateDlg::on_startingpointofpeakcalibrationTip_clicked()
{
     QMessageBox::information(this,"input","input value(0-1000)");
}

void spectrumSelfRegulateDlg::on_endingpointofpeakcalibrationTip_clicked()
{
   QMessageBox::information(this,"input","input value(0-1000)");
}

void spectrumSelfRegulateDlg::on_findpeakstartingpointTip_clicked()
{
     QMessageBox::information(this,"input","input value(0-1000)");
}

void spectrumSelfRegulateDlg::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void spectrumSelfRegulateDlg::on_pageDown_clicked()
{

    this->hide();
    down();
}
void spectrumSelfRegulateDlg::backtothis()
{
    this->show();
    this->show_paras();
}

void spectrumSelfRegulateDlg::on_PkTrkAvg_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkTrkAvg_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PkTrkAvg_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkTrkAvg(QString)));
}

void spectrumSelfRegulateDlg::on_PkTarget_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkTarget_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PkTarget_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkTarget(QString)));
}

void spectrumSelfRegulateDlg::on_ValPkTrkStart_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->ValPkTrkStart_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->ValPkTrkEnd_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_ValPkTrkStart(QString)));
}

void spectrumSelfRegulateDlg::on_ValPkTrkEnd_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->ValPkTrkEnd_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->ValPkTrkEnd_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_ValPkTrkEnd(QString)));
}


void spectrumSelfRegulateDlg::on_PkTrkStart_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkTrkStart_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PkTrkStart_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkTrkStart(QString)));
}


void spectrumSelfRegulateDlg::on_pageUp_clicked()
{
    this->hide();
    up();
}

void spectrumSelfRegulateDlg::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        PkTrkAvgstr= QString::number(AnaParas_Ch0->PkTrkAvg,10);//bool,int,long
        ui->PkTrkAvg_lineEdit->setText(PkTrkAvgstr);

        PkTargetstr =  QString::number(AnaParas_Ch0->PkTarget,10);
        ui->PkTarget_lineEdit->setText(PkTargetstr);

        ValPkTrkStartstr= QString::number((int)AnaParas_Ch0->ValPkTrkStart,10);
        ui->ValPkTrkStart_lineEdit->setText(ValPkTrkStartstr);

        ValPkTrkEndstr = QString::number(AnaParas_Ch0->ValPkTrkEnd,10);//float ,double
        ui->ValPkTrkEnd_lineEdit->setText(ValPkTrkEndstr);

        PkTrkStartstr =  QString::number(AnaParas_Ch0->PkTrkStart,10);//float ,double
        ui->PkTrkStart_lineEdit->setText(PkTrkStartstr);


    }
    else
    {
        PkTrkAvgstr= QString::number(AnaParas_Ch1-> PkTrkAvg,10);//bool,int,long
        ui->PkTrkAvg_lineEdit->setText(PkTrkAvgstr);

        PkTargetstr =  QString::number(AnaParas_Ch1->PkTarget,10);
        ui->PkTarget_lineEdit->setText(PkTargetstr);

        ValPkTrkStartstr= QString::number((int)AnaParas_Ch1->ValPkTrkStart,10);
        ui->ValPkTrkStart_lineEdit->setText(ValPkTrkStartstr);

        ValPkTrkEndstr = QString::number(AnaParas_Ch1->ValPkTrkEnd,10);//float ,double
        ui->ValPkTrkEnd_lineEdit->setText(ValPkTrkEndstr);

        PkTrkStartstr =  QString::number(AnaParas_Ch1->PkTrkStart,10);//float ,double
        ui->PkTrkStart_lineEdit->setText(PkTrkStartstr);
    }

 }


void spectrumSelfRegulateDlg::range_limit_PkTrkAvg(QString)
{
    bool ok;
    int a =ui->PkTrkAvg_lineEdit->text().toInt(&ok,10);
    if(!((a>=2)&&(a<=100)))
    {

      on_findaveragepeakTip_clicked();
      ui->PkTrkAvg_lineEdit->setText(PkTrkAvgstr);
    }
}

void spectrumSelfRegulateDlg::range_limit_PkTarget(QString)
{
    bool ok;
    int a =ui->PkTarget_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=1000)))
    {

     on_targetpeakTip_clicked();
     ui->PkTarget_lineEdit->setText(PkTargetstr);
    }
}

void spectrumSelfRegulateDlg::range_limit_ValPkTrkStart(QString)
{
    bool ok;
    int a =ui->ValPkTrkStart_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=1000)))
    {

      on_startingpointofpeakcalibrationTip_clicked();
      ui->ValPkTrkStart_lineEdit->setText(ValPkTrkStartstr);
    }
}

void spectrumSelfRegulateDlg::range_limit_ValPkTrkEnd(QString)
{
    bool ok;
    int a =ui->ValPkTrkEnd_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=1000)))
    {

      on_endingpointofpeakcalibrationTip_clicked();
      ui->ValPkTrkEnd_lineEdit->setText(ValPkTrkEndstr);
    }
}

void spectrumSelfRegulateDlg::range_limit_PkTrkStart(QString)
{
    bool ok;
    int a =ui->PkTrkStart_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=1000)))
    {

      on_findpeakstartingpointTip_clicked();
      ui->PkTrkStart_lineEdit->setText(PkTrkStartstr);
    }
}

void spectrumSelfRegulateDlg::on_ok_clicked()
{
    bool ok;
    int PkTrkAvg = ui->PkTrkAvg_lineEdit->text().toInt(&ok,10);
    int PkTarget =ui->PkTarget_lineEdit->text().toInt(&ok,10);
    int ValPkTrkStart =ui->ValPkTrkStart_lineEdit->text().toInt(&ok,10);
    int ValPkTrkEnd =ui->ValPkTrkEnd_lineEdit->text().toInt(&ok,10);
    int PkTrkStart =ui->PkTrkStart_lineEdit->text().toInt(&ok,10);
     if(CH_Flag==0)
     {
         AnaParas_Ch0->PkTrkAvg=PkTrkAvg;
         AnaParas_Ch0->PkTarget=PkTarget;
         AnaParas_Ch0->ValPkTrkStart=ValPkTrkStart;
         AnaParas_Ch0->ValPkTrkEnd=ValPkTrkEnd;
         AnaParas_Ch0->PkTrkStart=PkTrkStart;
         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->PkTrkAvg=PkTrkAvg;
         AnaParas_Ch1->PkTarget=PkTarget;
         AnaParas_Ch1->ValPkTrkStart=ValPkTrkStart;
         AnaParas_Ch1->ValPkTrkEnd=ValPkTrkEnd;
         AnaParas_Ch1->PkTrkStart=PkTrkStart;
         files->writefile(1);

     }
}

void spectrumSelfRegulateDlg::on_cancel_clicked()
{
    show_paras();
}
