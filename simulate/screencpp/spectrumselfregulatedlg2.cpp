#include "screeninclu/spectrumselfregulatedlg2.h"
#include "ui_spectrumselfregulatedlg2.h"

#include <QTime>
#include <QTimer>
#include <QMessageBox>
//add 6.14-5
extern fileoperate *files;

spectrumSelfRegulateDlg2::spectrumSelfRegulateDlg2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::spectrumSelfRegulateDlg2)
{
    ui->setupUi(this);

    //时间计时器
 //   QTimer *timer = new QTimer(this);
 //   connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
 //   timer->start(1000);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);
    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->endpointoffindingpeakTip->setFocusPolicy(Qt::NoFocus);
    ui->findpeakmaximunmagnitude->setFocusPolicy(Qt::NoFocus);
    ui->findpeakminimummagnitudeTip->setFocusPolicy(Qt::NoFocus);
    ui->findpeakminimumtemperatureTip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->pageUp->setFocusPolicy(Qt::NoFocus);
    ui->peakshiftlimitTip->setFocusPolicy(Qt::NoFocus);
    ui->PkShiftLmt_change->setFocusPolicy(Qt::NoFocus);
    ui->PkTrkEnd_change->setFocusPolicy(Qt::NoFocus);
    ui->PkTrkIdxMax_change->setFocusPolicy(Qt::NoFocus);
    ui->PkTrkIdxMin_change->setFocusPolicy(Qt::NoFocus);
    ui->PkTrkTLow_change->setFocusPolicy(Qt::NoFocus);

    //add 6.14-2
   ui->PkTrkEnd_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->PkShiftLmt_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->PkTrkIdxMax_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->PkTrkIdxMin_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->PkTrkTLow_lineEdit->setFocusPolicy(Qt::NoFocus);



}

spectrumSelfRegulateDlg2::~spectrumSelfRegulateDlg2()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void spectrumSelfRegulateDlg2::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}


void spectrumSelfRegulateDlg2::on_endpointoffindingpeakTip_clicked()
{
    QMessageBox::information(this,"input","input value(0-1000)");
}

void spectrumSelfRegulateDlg2::on_peakshiftlimitTip_clicked()
{
    QMessageBox::information(this,"input","input value(0-1000)");
}

void spectrumSelfRegulateDlg2::on_findpeakmaximunmagnitude_clicked()
{
    QMessageBox::information(this,"input","input value(index)");
}

void spectrumSelfRegulateDlg2::on_findpeakminimummagnitudeTip_clicked()
{
    QMessageBox::information(this,"input","input value(index)");
}

void spectrumSelfRegulateDlg2::on_findpeakminimumtemperatureTip_clicked()
{
    QMessageBox::information(this,"input","input value(degree centigrade)");
}

void spectrumSelfRegulateDlg2::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}


void spectrumSelfRegulateDlg2::on_pageDown_clicked()
{
    this->hide();
    down();
}
void spectrumSelfRegulateDlg2::backtothis()
{
    this->show();
    this->show_paras();

}

void spectrumSelfRegulateDlg2::on_PkTrkEnd_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkTrkEnd_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PkTrkEnd_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkTrkEnd(QString)));

}

void spectrumSelfRegulateDlg2::on_PkShiftLmt_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkShiftLmt_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PkShiftLmt_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkShiftLmt(QString)));
}

void spectrumSelfRegulateDlg2::on_PkTrkIdxMax_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkTrkIdxMax_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PkTrkIdxMax_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkTrkIdxMax(QString)));
}

void spectrumSelfRegulateDlg2::on_PkTrkIdxMin_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkTrkIdxMin_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PkTrkIdxMin_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkTrkIdxMin(QString)));
}

void spectrumSelfRegulateDlg2::on_PkTrkTLow_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkTrkTLow_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PkTrkTLow_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkTrkTLow(QString)));
}


void spectrumSelfRegulateDlg2::on_pageUp_clicked()
{
    this->hide();
    up();
}

void spectrumSelfRegulateDlg2::show_paras() //add 6.14-3
{


    if(CH_Flag==0)  //ch0
    {

        PkTrkEndstr= QString::number(AnaParas_Ch0->PkTrkEnd,10);//bool,int,long
        ui->PkTrkEnd_lineEdit->setText(PkTrkEndstr);

        PkShiftLmtstr =  QString::number(AnaParas_Ch0->PkShiftLmt,10);
        ui->PkShiftLmt_lineEdit->setText(PkShiftLmtstr);

        PkTrkIdxMaxstr =  QString::number((int)AnaParas_Ch0->PkTrkIdxMax,'f',2);
        ui->PkTrkIdxMax_lineEdit->setText(PkTrkIdxMaxstr);

        PkTrkIdxMinstr =  QString::number(AnaParas_Ch0->PkTrkIdxMin,'f',2);//float ,double
        ui->PkTrkIdxMin_lineEdit->setText(PkTrkIdxMinstr);

        PkTrkTLowstr =  QString::number(AnaParas_Ch0->PkTrkTLow,'f',2);//float ,double
        ui->PkTrkTLow_lineEdit->setText(PkTrkTLowstr);

    }
    else
    {
        PkTrkEndstr= QString::number(AnaParas_Ch1->PkTrkEnd,10);//bool,int,long
        ui->PkTrkEnd_lineEdit->setText(PkTrkEndstr);

        PkShiftLmtstr =  QString::number(AnaParas_Ch1->PkShiftLmt,10);
        ui->PkShiftLmt_lineEdit->setText(PkShiftLmtstr);

        PkTrkIdxMaxstr =  QString::number((int)AnaParas_Ch1->PkTrkIdxMax,'f',2);
        ui->PkTrkIdxMax_lineEdit->setText(PkTrkIdxMaxstr);

        PkTrkIdxMinstr =  QString::number(AnaParas_Ch1->PkTrkIdxMin,'f',2);//float ,double
        ui->PkTrkIdxMin_lineEdit->setText(PkTrkIdxMinstr);

        PkTrkTLowstr =  QString::number(AnaParas_Ch1->PkTrkTLow,'f',2);//float ,double
        ui->PkTrkTLow_lineEdit->setText(PkTrkTLowstr);

    }

}

void spectrumSelfRegulateDlg2::range_limit_PkTrkEnd(QString)
{
    bool ok;
    int a = ui->PkTrkEnd_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=100000)))
    {
    on_endpointoffindingpeakTip_clicked();
     ui->PkTrkEnd_lineEdit->setText(PkTrkEndstr);
    }
}
void spectrumSelfRegulateDlg2::range_limit_PkShiftLmt(QString)
{
    bool ok;
    int a = ui->PkShiftLmt_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=100000)))
    {
     on_peakshiftlimitTip_clicked();
     ui->PkShiftLmt_lineEdit->setText(PkShiftLmtstr);
    }
}
void spectrumSelfRegulateDlg2::range_limit_PkTrkIdxMax(QString)
{
    bool ok;
    float a = ui->PkTrkIdxMax_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100000)))
    {

     on_findpeakmaximunmagnitude_clicked();
     ui->PkTrkIdxMax_lineEdit->setText(PkTrkIdxMaxstr);
    }
}
void spectrumSelfRegulateDlg2::range_limit_PkTrkIdxMin(QString)
{
    bool ok;
    float a = ui->PkTrkIdxMin_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100000)))
    {

     on_findpeakminimummagnitudeTip_clicked();
     ui->PkTrkIdxMin_lineEdit->setText(PkTrkIdxMinstr);
    }
}

void spectrumSelfRegulateDlg2::range_limit_PkTrkTLow(QString)
{
    bool ok;
    float a = ui->PkTrkTLow_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=10000)))
    {
     on_findpeakminimumtemperatureTip_clicked();

     ui->PkTrkTLow_lineEdit->setText(PkTrkTLowstr);
    }
}


void spectrumSelfRegulateDlg2::on_ok_clicked()
{
    bool ok;
    int PkTrkEnd = ui->PkTrkEnd_lineEdit->text().toInt(&ok);
    int PkShiftLmt =ui->PkShiftLmt_lineEdit->text().toInt(&ok);
    float PkTrkIdxMax =ui->PkTrkIdxMax_lineEdit->text().toFloat(&ok);
    float PkTrkIdxMin =ui->PkTrkIdxMin_lineEdit->text().toFloat(&ok);
    float PkTrkTLow =ui->PkTrkTLow_lineEdit->text().toFloat(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->PkTrkEnd=PkTrkEnd;
         AnaParas_Ch0->PkShiftLmt=PkShiftLmt;
         AnaParas_Ch0->PkTrkIdxMax=PkTrkIdxMax;
         AnaParas_Ch0->PkTrkIdxMin=PkTrkIdxMin;
         AnaParas_Ch0->PkTrkTLow=PkTrkTLow;

         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->PkTrkEnd=PkTrkEnd;
         AnaParas_Ch1->PkShiftLmt=PkShiftLmt;
         AnaParas_Ch1->PkTrkIdxMax=PkTrkIdxMax;
         AnaParas_Ch1->PkTrkIdxMin=PkTrkIdxMin;
         AnaParas_Ch1->PkTrkTLow=PkTrkTLow;
         files->writefile(1);
     }
}

void spectrumSelfRegulateDlg2::on_cancel_clicked()
{
     show_paras();
}
