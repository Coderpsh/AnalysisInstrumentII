#include "screeninclu/calibrationdlg.h"
#include "ui_calibrationdlg.h"


#include <QTime>
#include <QTimer>
#include"global.h"

calibrationDlg::calibrationDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calibrationDlg)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    setFixedSize(800,480);

    iddlg1=new IDDlg;
    iddlg2=new IDDlg2;
    lddlg1=new LDDlg;
    lddlg2=new LDDlg2;
    demodulationDlg1=new demodulationDlg;
    interfaceAndCommunicationDlg1=new interfaceAndCommunicationDlg;
    spectrumselfregulatedlg =new spectrumSelfRegulateDlg;
    spectrumselfregulatedlg1=new spectrumselfregulateDlg1;
    interfaceandcommunicationdlg2=new interfaceandcommunicationDlg2;
    spectrumselfregulatedlg2=new spectrumSelfRegulateDlg2;
    spectrumselfregulatedlg3=new spectrumSelfRegulateDlg3;
    spectrumselfregulatedlg4=new spectrumselfregulateDlg4;
    alamdlg1 =new alamDlg;
    alamdlg2 =new alamDlg2;
    alamdlg3 =new alamDlg3;
    alamdlg4 =new alamDlg4;

    algorithmdlg=new algorithmDlg;
    algorithmdlg2=new algorithmDlg2;
    algorithmdld3=new algorithmDld3;

    verifyDlg1=new verifyDlg;
    verifydlg2=new verifyDlg2;
    calibrationParameterDlg1=new calibrationParameterDlg;
    calibrationParameterdlg2=new calibrationParameterDlg2;

    plsdlg=new plsDlg;

    referencecurvedlg=new referenceCurvedlg;
    referencecurvedlg2=new referenceCurvedlg2;
    referencecCurvedlg3=new referencecurvedlg3;


    connect(referencecurvedlg2, SIGNAL(up()),referencecurvedlg, SLOT(backtothis()));
    connect(referencecCurvedlg3, SIGNAL(up()),referencecurvedlg2 , SLOT(backtothis()));
    connect(referencecurvedlg, SIGNAL(down()),referencecurvedlg2 , SLOT(backtothis()));
    connect(referencecurvedlg2, SIGNAL(down()), referencecCurvedlg3 , SLOT(backtothis()));

   connect(alamdlg1, SIGNAL(down()), alamdlg2, SLOT(backtothis()));
   connect(alamdlg2, SIGNAL(down()), alamdlg3, SLOT(backtothis()));
   connect(alamdlg3, SIGNAL(down()), alamdlg4, SLOT(backtothis()));
   connect(alamdlg2, SIGNAL(up()), alamdlg1, SLOT(backtothis()));
   connect(alamdlg3, SIGNAL(up()), alamdlg2, SLOT(backtothis()));
   connect(alamdlg4, SIGNAL(up()), alamdlg3, SLOT(backtothis()));

   connect(calibrationParameterDlg1, SIGNAL(down()), calibrationParameterdlg2, SLOT(backtothis()));

   connect(calibrationParameterdlg2, SIGNAL(up()), calibrationParameterDlg1, SLOT(backtothis()));


   connect(algorithmdlg2, SIGNAL(up()),algorithmdlg , SLOT(backtothis()));
   connect(algorithmdld3, SIGNAL(up()), algorithmdlg2, SLOT(backtothis()));
   connect(algorithmdlg, SIGNAL(down()), algorithmdlg2, SLOT(backtothis()));
   connect(algorithmdlg2, SIGNAL(down()), algorithmdld3, SLOT(backtothis()));

   connect(spectrumselfregulatedlg, SIGNAL(up()), spectrumselfregulatedlg1, SLOT(backtothis()));
   connect(spectrumselfregulatedlg2, SIGNAL(up()), spectrumselfregulatedlg, SLOT(backtothis()));
   connect(spectrumselfregulatedlg3, SIGNAL(up()), spectrumselfregulatedlg2, SLOT(backtothis()));
   connect(spectrumselfregulatedlg4, SIGNAL(up()), spectrumselfregulatedlg3, SLOT(backtothis()));
   connect(spectrumselfregulatedlg1, SIGNAL(down()), spectrumselfregulatedlg, SLOT(backtothis()));
   connect(spectrumselfregulatedlg, SIGNAL(down()), spectrumselfregulatedlg2, SLOT(backtothis()));
   connect(spectrumselfregulatedlg2, SIGNAL(down()), spectrumselfregulatedlg3, SLOT(backtothis()));
   connect(spectrumselfregulatedlg2, SIGNAL(down()), spectrumselfregulatedlg3, SLOT(backtothis()));
   connect(spectrumselfregulatedlg3, SIGNAL(down()), spectrumselfregulatedlg4, SLOT(backtothis()));
   connect(iddlg2, SIGNAL(up()), iddlg1, SLOT(backtothis()));
   connect(iddlg1, SIGNAL(down()), iddlg2, SLOT(backtothis()));

  connect(lddlg2, SIGNAL(up()), lddlg1, SLOT(backtothis()));
  connect(lddlg1, SIGNAL(down()), lddlg2, SLOT(backtothis()));

  connect(interfaceandcommunicationdlg2, SIGNAL(up()), interfaceAndCommunicationDlg1, SLOT(backtothis()));
  connect(interfaceAndCommunicationDlg1, SIGNAL(down()), interfaceandcommunicationdlg2, SLOT(backtothis()));

  connect(lddlg2, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
  connect(iddlg2, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
  connect(spectrumselfregulatedlg1, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
  connect(spectrumselfregulatedlg2, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
  connect(spectrumselfregulatedlg3, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
  connect(algorithmdld3, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
  connect(algorithmdlg2, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
  connect(calibrationParameterdlg2, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));

 connect(alamdlg2, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
 connect(alamdlg3, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
 connect(alamdlg4, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
 connect(spectrumselfregulatedlg4, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
 connect(verifydlg2, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));

  connect(verifydlg2, SIGNAL(up()),verifyDlg1, SLOT(backtothis()));
  connect(verifyDlg1, SIGNAL(down()),verifydlg2, SLOT(backtothis()));


 connect(plsdlg, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));

 connect(referencecurvedlg, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
 connect(referencecurvedlg2, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
 connect(referencecCurvedlg3, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));

 connect(interfaceAndCommunicationDlg1, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));
 connect(interfaceandcommunicationdlg2, SIGNAL(backCalibrationdlg()), this, SLOT(backCalibrationdlg()));

 //  QTimer *timer=new QTimer;
 //  connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
 //  timer->start(1000);
   ui->alarm->setFocusPolicy(Qt::NoFocus);
   ui->algorithm->setFocusPolicy(Qt::NoFocus);
   ui->back->setFocusPolicy(Qt::NoFocus);
   ui->calibrationparameter->setFocusPolicy(Qt::NoFocus);
   ui->demodulation->setFocusPolicy(Qt::NoFocus);
   ui->ID->setFocusPolicy(Qt::NoFocus);
   ui->interfaceandcommunication->setFocusPolicy(Qt::NoFocus);
   ui->LD->setFocusPolicy(Qt::NoFocus);
   ui->PLS->setFocusPolicy(Qt::NoFocus);
   ui->referencecurve->setFocusPolicy(Qt::NoFocus);
   ui->spectrumselfregulate->setFocusPolicy(Qt::NoFocus);
   ui->verify->setFocusPolicy(Qt::NoFocus);
}

calibrationDlg::~calibrationDlg()
{
    delete ui;
    delete alamdlg1;
    delete alamdlg2;
    delete alamdlg3;
    delete alamdlg4;
    delete iddlg1;
    delete iddlg2;
    delete lddlg2;
    delete lddlg1;
    delete demodulationDlg1;
    delete interfaceAndCommunicationDlg1;
    delete interfaceandcommunicationdlg2;
    delete spectrumselfregulatedlg;
    delete spectrumselfregulatedlg1;
    delete spectrumselfregulatedlg2;
    delete spectrumselfregulatedlg3;
    delete spectrumselfregulatedlg4;
    delete algorithmdld3;
    delete algorithmdlg;
    delete algorithmdlg2;
    delete verifyDlg1;
    delete verifydlg2;
    delete calibrationParameterDlg1;
    delete calibrationParameterdlg2;
    delete plsdlg;
    delete referencecCurvedlg3;
    delete referencecurvedlg;
    delete referencecurvedlg2;


}

void calibrationDlg::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}



void calibrationDlg::on_ID_clicked()
{
    connect(iddlg1,SIGNAL(backCalibrationdlg()),this,SLOT(backCalibrationdlg()));
    iddlg1->show();
    this->hide();
    iddlg1->show_paras();
}

void calibrationDlg::on_LD_clicked()
{
    connect(lddlg1,SIGNAL(backCalibrationdlg()),this,SLOT(backCalibrationdlg()));
    lddlg1->show();
    this->hide();
    lddlg1->show_paras();
}

void calibrationDlg::on_demodulation_clicked()
{
    connect(demodulationDlg1,SIGNAL(backCalibrationdlg()),this,SLOT(backCalibrationdlg()));
    demodulationDlg1->show();
    this->hide();
    demodulationDlg1->show_paras();
}

void calibrationDlg::on_algorithm_clicked()
{
    connect(algorithmdlg,SIGNAL(backCalibrationdlg()),this,SLOT(backCalibrationdlg()));
    algorithmdlg->show();
    this->hide();
    algorithmdlg->show_paras();
}

void calibrationDlg::on_spectrumselfregulate_clicked()
{
    connect(spectrumselfregulatedlg,SIGNAL(backCalibrationdlg()),this,SLOT(backCalibrationdlg()));
    spectrumselfregulatedlg1->show();
    this->hide();
     spectrumselfregulatedlg1->show_paras();   //add 6.14
}

void calibrationDlg::on_alarm_clicked()
{
    connect(alamdlg1,SIGNAL(backCalibrationdlg()),this,SLOT(backCalibrationdlg()));
    alamdlg1->show();
    this->hide();
    alamdlg1->show_paras();
}

void calibrationDlg::on_interfaceandcommunication_clicked()
{
    connect(interfaceAndCommunicationDlg1,SIGNAL(backCalibrationdlg()),this,SLOT(backCalibrationdlg()));
    interfaceAndCommunicationDlg1->show();
    this->hide();
    interfaceAndCommunicationDlg1->show_paras();
}

void calibrationDlg::on_verify_clicked()
{
    connect(verifyDlg1,SIGNAL(backCalibrationdlg()),this,SLOT(backCalibrationdlg()));
    verifyDlg1->show();
    this->hide();
    verifyDlg1->show_paras();
}

void calibrationDlg::on_calibrationparameter_clicked()
{
    connect(calibrationParameterDlg1,SIGNAL(backCalibrationdlg()),this,SLOT(backCalibrationdlg()));
    calibrationParameterDlg1->show();
    this->hide();
    calibrationParameterDlg1->show_paras();
}



void calibrationDlg::on_PLS_clicked()
{
    plsdlg->show();
    this->hide();
    plsdlg->show_paras();
}

void calibrationDlg::on_back_clicked()
{
    set_mode(0,0);
    set_mode(1,0);
    for(int i=0;i<10;i++)
    {
      MovTemp[i]=20000;
    }
    backMainWindow();
    this->hide();
}
void calibrationDlg::backCalibrationdlg()
{
   this->show();
}



void calibrationDlg::showch()
{

    if(CH_Flag==0)
    {

       QString temp=ui->lineEdit->text();

        ui->lineEdit->setText("ch1");

    }

    else
    {

          QString temp=ui->lineEdit->text();

          ui->lineEdit->setText("ch2");
     }

}

void calibrationDlg::on_referencecurve_clicked()
{
    referencecurvedlg->show();
    this->hide();
    referencecurvedlg->show_paras();   //add 6.14
}
void calibrationDlg::tocalibration()
{
    if(permit_flag==0)
    {

      ui->ID->setEnabled(false);
      ui->LD->setEnabled(false);
      ui->demodulation->setEnabled(false);
      ui->algorithm->setEnabled(false);
      ui->calibrationparameter->setEnabled(false);
      ui->referencecurve->setEnabled(false);
      ui->PLS->setEnabled(false);
      this->show();
    }

   else
    {
        ui->ID->setEnabled(true);
        ui->LD->setEnabled(true);
        ui->demodulation->setEnabled(true);
        ui->algorithm->setEnabled(true);
        ui->calibrationparameter->setEnabled(true);
        ui->referencecurve->setEnabled(true);
        ui->PLS->setEnabled(true);
        this->show();
    }


}


