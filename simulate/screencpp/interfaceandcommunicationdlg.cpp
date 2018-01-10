#include "screeninclu/interfaceandcommunicationdlg.h"
#include "ui_interfaceandcommunicationdlg.h"

#include <QTime>
#include <QTimer>
//add 6.14-5
extern fileoperate *files;

#include <QMessageBox>
#include"global.h"

interfaceAndCommunicationDlg::interfaceAndCommunicationDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::interfaceAndCommunicationDlg)
{
    ui->setupUi(this);
    //时间计时器
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
//    timer->start(1000);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);
    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->BaudRate_change->setFocusPolicy(Qt::NoFocus);
    ui->BaudrateTip->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->concentrationunitTip->setFocusPolicy(Qt::NoFocus);
    ui->ConcUnit_change->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->pressureunitTip->setFocusPolicy(Qt::NoFocus);
    ui->Punit_change->setFocusPolicy(Qt::NoFocus);
    //add 6.14-2
    ui->Punit_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->ConcUnit_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->BaudRate_lineEdit->setFocusPolicy(Qt::NoFocus);

}

interfaceAndCommunicationDlg::~interfaceAndCommunicationDlg()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void interfaceAndCommunicationDlg::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}

void interfaceAndCommunicationDlg::backtothis()
{
    this->show();
    this->show_paras();
}

void interfaceAndCommunicationDlg::on_pressureunitTip_clicked()
{
     QMessageBox::information(this,"choose","0:mb  1:kpa");
}

void interfaceAndCommunicationDlg::on_concentrationunitTip_clicked()
{
     QMessageBox::information(this,"choose","0:ppm  1:% ");
}


void interfaceAndCommunicationDlg::on_BaudrateTip_clicked()
{
     QMessageBox::information(this,"choose","0:19  1:38  2:57  3:115");
}

void interfaceAndCommunicationDlg::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}


void interfaceAndCommunicationDlg::on_Punit_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Punit_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Punit_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Punit(QString)));

}

void interfaceAndCommunicationDlg::on_ConcUnit_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->ConcUnit_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->ConcUnit_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_ConcUnit(QString)));

}


void interfaceAndCommunicationDlg::on_BaudRate_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->BaudRate_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->BaudRate_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_BaudRate(QString)));

}


void interfaceAndCommunicationDlg::on_pageDown_clicked()
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


void interfaceAndCommunicationDlg::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        Punitstr = QString::number(AnaParas_Ch0->Punit,10);//bool,int,long
        ui->Punit_lineEdit->setText(Punitstr);

        ConcUnitstr =  QString::number(AnaParas_Ch0->ConcUnit,10);
        ui->ConcUnit_lineEdit->setText(ConcUnitstr);

        BaudRatestr =  QString::number((int)AnaParas_Ch0->BaudRate,10);
        ui->BaudRate_lineEdit->setText(BaudRatestr);

    }
    else
    {
        Punitstr = QString::number(AnaParas_Ch1->Punit,10);//bool,int,long
        ui->Punit_lineEdit->setText(Punitstr);

        ConcUnitstr =  QString::number(AnaParas_Ch1->ConcUnit,10);
        ui->ConcUnit_lineEdit->setText(ConcUnitstr);

        BaudRatestr =  QString::number((int)AnaParas_Ch1->BaudRate,10);
        ui->BaudRate_lineEdit->setText(BaudRatestr);

    }

}



//add 6.14-4
void interfaceAndCommunicationDlg::range_limit_Punit(QString)
{
    bool ok;
    int a = ui->Punit_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=1)))
    {
     on_pressureunitTip_clicked();

     ui->Punit_lineEdit->setText(Punitstr);
    }
}
void interfaceAndCommunicationDlg::range_limit_ConcUnit(QString)
{
    bool ok;
    int a = ui->ConcUnit_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=1)))
    {
    on_concentrationunitTip_clicked();

     ui->ConcUnit_lineEdit->setText(ConcUnitstr);
    }
}
void interfaceAndCommunicationDlg::range_limit_BaudRate(QString)
{
    bool ok;
    int a = ui->BaudRate_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=3)))
    {
      on_BaudrateTip_clicked();

     ui->BaudRate_lineEdit->setText(BaudRatestr);
    }
}

void interfaceAndCommunicationDlg::on_ok_clicked()
{
    bool ok;
    int Punit = ui->Punit_lineEdit->text().toInt(&ok);
    int ConcUnit =ui->ConcUnit_lineEdit->text().toInt(&ok);
    int BaudRate =ui->BaudRate_lineEdit->text().toInt(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->Punit=Punit;
         AnaParas_Ch0->ConcUnit=ConcUnit;
         AnaParas_Ch0->BaudRate=BaudRate;
         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->Punit=Punit;
         AnaParas_Ch1->ConcUnit=ConcUnit;
         AnaParas_Ch1->BaudRate=BaudRate;

         files->writefile(1);
     }
}

void interfaceAndCommunicationDlg::on_cancel_clicked()
{
    show_paras();
}
