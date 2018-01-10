#include "screeninclu/spectrumselfregulatedlg3.h"
#include "ui_spectrumselfregulatedlg3.h"


#include <QTime>
#include <QTimer>

#include<QMessageBox>

//add 6.14-5
extern fileoperate *files;

spectrumSelfRegulateDlg3::spectrumSelfRegulateDlg3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::spectrumSelfRegulateDlg3)
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

    ui->findpeakmaximumpressureTip->setFocusPolicy(Qt::NoFocus);
    ui->findpeakmaximumtreperatureTip->setFocusPolicy(Qt::NoFocus);
    ui->findpeakminimumpressureTip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageUp->setFocusPolicy(Qt::NoFocus);
    ui->PkTrkPHigh_change->setFocusPolicy(Qt::NoFocus);
    ui->PkTrkPLow_change->setFocusPolicy(Qt::NoFocus);
    ui->PkTrkTHigh_change->setFocusPolicy(Qt::NoFocus);
    //add 6.14-2
    ui->PkTrkTHigh_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->PkTrkPLow_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->PkTrkPHigh_lineEdit->setFocusPolicy(Qt::NoFocus);


}

spectrumSelfRegulateDlg3::~spectrumSelfRegulateDlg3()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void spectrumSelfRegulateDlg3::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}

void spectrumSelfRegulateDlg3::on_findpeakmaximumtreperatureTip_clicked()
{
    QMessageBox::information(this,"input","input value(degree centigrade)");

}

void spectrumSelfRegulateDlg3::on_findpeakminimumpressureTip_clicked()
{
    QMessageBox::information(this,"input","input value(mbar)");

}

void spectrumSelfRegulateDlg3::on_findpeakmaximumpressureTip_clicked()
{
    QMessageBox::information(this,"input","input value(mbar)");
}


void spectrumSelfRegulateDlg3::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void spectrumSelfRegulateDlg3::on_pageUp_clicked()
{
    this->hide();
    up();
}
void spectrumSelfRegulateDlg3::backtothis()
{
    this->show();
    this->show_paras();

}

void spectrumSelfRegulateDlg3::on_PkTrkTHigh_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkTrkTHigh_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PkTrkTHigh_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkTrkTHigh(QString)));

}

void spectrumSelfRegulateDlg3::on_PkTrkPLow_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkTrkPLow_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PkTrkPLow_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkTrkPLow(QString)));


}

void spectrumSelfRegulateDlg3::on_PkTrkPHigh_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkTrkPHigh_lineEdit,SLOT(setText(QString)));

    keyboarddlg->show();

    QObject::connect(ui->PkTrkPHigh_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkTrkPHigh(QString)));

}


void spectrumSelfRegulateDlg3::on_pageDown_clicked()
{
    down();
    this->hide();
}

void spectrumSelfRegulateDlg3::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        PkTrkTHighstr = QString::number(AnaParas_Ch0->PkTrkTHigh,'f',2);//bool,int,long
        ui->PkTrkTHigh_lineEdit->setText(PkTrkTHighstr);

        PkTrkPLowstr =  QString::number(AnaParas_Ch0->PkTrkPLow,'f',2);
        ui->PkTrkPLow_lineEdit->setText(PkTrkPLowstr);

        PkTrkPHighstr =  QString::number((int)AnaParas_Ch0->PkTrkPHigh,'f',2); //
        ui->PkTrkPHigh_lineEdit->setText(PkTrkPHighstr);

    }
    else
    {
        PkTrkTHighstr = QString::number(AnaParas_Ch1-> PkTrkTHigh,'f',2);//bool,int,long
        ui->PkTrkTHigh_lineEdit->setText(PkTrkTHighstr);

       PkTrkPLowstr =  QString::number(AnaParas_Ch1->PkTrkPLow,'f',2);
        ui->PkTrkPLow_lineEdit->setText(PkTrkPLowstr);

        PkTrkPHighstr =  QString::number((int)AnaParas_Ch1->PkTrkPHigh,'f',2); //
        ui->PkTrkPHigh_lineEdit->setText(PkTrkPHighstr);
    }

}



void spectrumSelfRegulateDlg3::range_limit_PkTrkTHigh(QString)
{
    bool ok;
    float a =ui->PkTrkTHigh_lineEdit->text().toFloat(&ok);
    if(!((a>0)&&(a<10000)))
    {
    on_findpeakmaximumtreperatureTip_clicked();

      ui->PkTrkTHigh_lineEdit->setText(PkTrkTHighstr);
    }
}

void spectrumSelfRegulateDlg3::range_limit_PkTrkPLow(QString)
{
    bool ok;
    float a =ui->PkTrkPLow_lineEdit->text().toFloat(&ok);  //
    if(!((a>=0)&&(a<=100000)))
    {
      on_findpeakminimumpressureTip_clicked();
      ui->PkTrkPLow_lineEdit->setText(PkTrkPLowstr);
    }
}
void spectrumSelfRegulateDlg3::range_limit_PkTrkPHigh(QString)
{
    bool ok;
    float a =ui->PkTrkPHigh_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100000)))
    {
      on_findpeakmaximumpressureTip_clicked();

      ui->PkTrkPHigh_lineEdit->setText(PkTrkPHighstr);
    }
}

void spectrumSelfRegulateDlg3::on_cancel_clicked()
{
    show_paras();
}

void spectrumSelfRegulateDlg3::on_ok_clicked()
{
    bool ok;
    float PkTrkTHigh = ui->PkTrkTHigh_lineEdit->text().toFloat(&ok);
    float PkTrkPLow =ui->PkTrkPLow_lineEdit->text().toFloat(&ok);
    float PkTrkPHigh =ui->PkTrkPHigh_lineEdit->text().toFloat(&ok);

    if(CH_Flag==0)
     {
         AnaParas_Ch0->PkTrkTHigh=PkTrkTHigh;
         AnaParas_Ch0->PkTrkPLow=PkTrkPLow;
         AnaParas_Ch0->PkTrkPHigh=PkTrkPHigh;

         files->writefile(0);
     }
     else
     {
        AnaParas_Ch1->PkTrkTHigh=PkTrkTHigh;
        AnaParas_Ch1->PkTrkPLow=PkTrkPLow;
        AnaParas_Ch1->PkTrkPHigh=PkTrkPHigh;


        files->writefile(1);
     }
}
