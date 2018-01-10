#include "screeninclu/alamdlg3.h"
#include "ui_alamdlg3.h"

#include <QTime>
#include <QTimer>
#include <QMessageBox>

//add 6.14-5
extern fileoperate *files;


alamDlg3::alamDlg3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::alamDlg3)
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
    ui->DCHigh_change->setFocusPolicy(Qt::NoFocus);
    ui->DCLow_change->setFocusPolicy(Qt::NoFocus);
    ui->FitQual_change->setFocusPolicy(Qt::NoFocus);
    ui->FitQual_Tip->setFocusPolicy(Qt::NoFocus);
    ui->IHigh_change->setFocusPolicy(Qt::NoFocus);
    ui->Ilow_change->setFocusPolicy(Qt::NoFocus);
    ui->lasercurrenttoohighTip->setFocusPolicy(Qt::NoFocus);
    ui->lasercurrenttoolowTip->setFocusPolicy(Qt::NoFocus);
    ui->laserpowertoohighTip->setFocusPolicy(Qt::NoFocus);
    ui->laserpowertoolowTip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->pageUp->setFocusPolicy(Qt::NoFocus);

    //add 6.14-2
    ui->FitQual_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->DCHigh_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->DCLow_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->Ihigh_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->Ilow_lineEdit->setFocusPolicy(Qt::NoFocus);

 }

alamDlg3::~alamDlg3()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void alamDlg3::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}

void alamDlg3::backtothis()
{
    this->show();
    this->show_paras();


}

void alamDlg3::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void alamDlg3::on_pageUp_clicked()
{
    up();
    this->hide();
}

void alamDlg3::on_pageDown_clicked()
{
    this->hide();
    down();
}

void alamDlg3::on_laserpowertoohighTip_clicked()
{
    QMessageBox::information(this,"input","input value");
}

void alamDlg3::on_laserpowertoolowTip_clicked()
{
     QMessageBox::information(this,"input","input value");
}

void alamDlg3::on_lasercurrenttoohighTip_clicked()
{
    QMessageBox::information(this,"input","input value");
}

void alamDlg3::on_lasercurrenttoolowTip_clicked()
{
    QMessageBox::information(this,"input","input value");
}

void alamDlg3::on_DCHigh_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->DCHigh_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->FitQual_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_FitQual(QString)));

}

void alamDlg3::on_DCLow_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->DCLow_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->DCHigh_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_DCHigh(QString)));

}

void alamDlg3::on_IHigh_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Ihigh_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->DCLow_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_DCLow(QString)));

}

void alamDlg3::on_Ilow_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Ilow_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Ihigh_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_IHigh(QString)));

}



void alamDlg3::on_FitQual_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->FitQual_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Ilow_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Ilow(QString)));

}

void alamDlg3::on_FitQual_Tip_clicked()
{
    QMessageBox::information(this,"input","input value");
}

void alamDlg3::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        FitQualstr = QString::number(AnaParas_Ch0->FitQual,'f',2);
        ui->FitQual_lineEdit->setText(FitQualstr);

        DCHighstr =  QString::number(AnaParas_Ch0->DCHigh,'f',2);
        ui->DCHigh_lineEdit->setText(DCHighstr);

        DCLowstr =  QString::number((int)AnaParas_Ch0->DCLow,'f',2);
        ui->DCLow_lineEdit->setText(DCLowstr);

        IHighstr =  QString::number(AnaParas_Ch0->IHigh,'f',2);
        ui->Ihigh_lineEdit->setText(IHighstr);

        Ilowstr =  QString::number(AnaParas_Ch0->Ilow,'f',2);
        ui->Ilow_lineEdit->setText(Ilowstr);

    }
    else
    {
        FitQualstr = QString::number(AnaParas_Ch1->FitQual,'f',2);
        ui->FitQual_lineEdit->setText(FitQualstr);

        DCHighstr =  QString::number(AnaParas_Ch1->DCHigh,'f',2);
        ui->DCHigh_lineEdit->setText(DCHighstr);

        DCLowstr =  QString::number((int)AnaParas_Ch1->DCLow,'f',2);
        ui->DCLow_lineEdit->setText(DCLowstr);

        IHighstr =  QString::number(AnaParas_Ch1->IHigh,'f',2);
        ui->Ihigh_lineEdit->setText(IHighstr);

        Ilowstr =  QString::number(AnaParas_Ch1->Ilow,'f',2);
        ui->Ilow_lineEdit->setText(Ilowstr);

    }

}

void alamDlg3::range_limit_FitQual(QString)
{
    bool ok;
    float a = ui->FitQual_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=1000)))
    {
     on_FitQual_Tip_clicked();

     ui->FitQual_lineEdit->setText(FitQualstr);
    }
}
void alamDlg3::range_limit_DCHigh(QString)
{
    bool ok;
    float a = ui->DCHigh_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=1000)))
    {
    on_laserpowertoohighTip_clicked();

     ui->DCHigh_lineEdit->setText(DCHighstr);
    }
}
void alamDlg3::range_limit_DCLow(QString)
{
    bool ok;
    float a = ui->DCLow_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=1000)))
    {
     on_laserpowertoolowTip_clicked();

     ui->DCLow_lineEdit->setText(DCLowstr);
    }
}
void alamDlg3::range_limit_IHigh(QString)
{
    bool ok;
    float a = ui->Ihigh_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=1000)))
    {
     on_lasercurrenttoohighTip_clicked();

     ui->Ihigh_lineEdit->setText(IHighstr);
    }
}

 void alamDlg3::range_limit_Ilow(QString)
    {
        bool ok;
        float a = ui->Ilow_lineEdit->text().toFloat(&ok);
        if(!((a>=0)&&(a<=1000)))
        {
         on_lasercurrenttoolowTip_clicked();

         ui->Ilow_lineEdit->setText(Ilowstr);
        }
 }

void alamDlg3::on_ok_clicked()
{

    bool ok;
    float FitQual = ui->FitQual_lineEdit->text().toFloat(&ok);
    float DCHigh =ui->DCHigh_lineEdit->text().toFloat(&ok);
    float DCLow =ui->DCLow_lineEdit->text().toFloat(&ok);
    float IHigh =ui->Ihigh_lineEdit->text().toFloat(&ok);
    float Ilow =ui->Ilow_lineEdit->text().toFloat(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->FitQual=FitQual;
         AnaParas_Ch0->DCHigh=DCHigh;
         AnaParas_Ch0->DCLow=DCLow;
         AnaParas_Ch0->IHigh=IHigh;
         AnaParas_Ch0->Ilow=Ilow;
         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->FitQual=FitQual;
         AnaParas_Ch1->DCHigh=DCHigh;
         AnaParas_Ch1->DCLow=DCLow;
         AnaParas_Ch1->IHigh=IHigh;
         AnaParas_Ch1->Ilow=Ilow;
         files->writefile(1);
     }
}

void alamDlg3::on_cancel_clicked()
{
    show_paras();
}
