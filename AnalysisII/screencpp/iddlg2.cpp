#include "screeninclu/iddlg2.h"
#include "ui_iddlg2.h"

#include <QTime>
#include <QTimer>
#include <QMessageBox>
extern fileoperate *files;
IDDlg2::IDDlg2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IDDlg2)
{
    ui->setupUi(this);
    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);
//    QTimer *timer=new QTimer;
 //   connect(timer,SIGNAL(timeout()),this,SLOT(showRealTime()));
 //   timer->start(1000);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);
    ui->airchamberversionTip->setFocusPolicy(Qt::NoFocus);
    ui->analytesTip->setFocusPolicy(Qt::NoFocus);
    ui->Analyte_change->setFocusPolicy(Qt::NoFocus);
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->CellModel_change->setFocusPolicy(Qt::NoFocus);
    ui->maximunvalueoftherangeTip->setFocusPolicy(Qt::NoFocus);
    ui->minimunvalueoftherangeTip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageUp->setFocusPolicy(Qt::NoFocus);
    ui->RangeMax_change->setFocusPolicy(Qt::NoFocus);
    ui->RangeMin_change->setFocusPolicy(Qt::NoFocus);

    ui->CellModel_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->RangeMax_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->RangeMin_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->Analyte_lineEdit->setFocusPolicy(Qt::NoFocus);


}

void IDDlg2::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}


IDDlg2::~IDDlg2()
{
    delete ui;
    delete keyboarddlg;
}

void IDDlg2::on_airchamberversionTip_clicked()
{
    QMessageBox::information(this,"input","input value");
}

void IDDlg2::on_analytesTip_clicked()
{
    QMessageBox::information(this,"choose","0:H2O  1:HCL  2:H2S  3:CO2  4:CO  5:CH4  6:C2H2");
}

void IDDlg2::on_maximunvalueoftherangeTip_clicked()
{
     QMessageBox::information(this,"input","input value(0-1000000)");
}

void IDDlg2::on_minimunvalueoftherangeTip_clicked()
{
    QMessageBox::information(this,"input","input value(0-1000000)");
}

void IDDlg2::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}


void IDDlg2::backtothis()
{
    this->show();
    this->show_paras();
}

void IDDlg2::on_pageUp_clicked()
{
    this->hide();
    up();
}

void IDDlg2::on_CellModel_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->CellModel_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->CellModel_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_CellModel(QString)));
}

void IDDlg2::on_Analyte_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Analyte_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
   QObject::connect(ui->Analyte_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Analyte(QString)));
}

void IDDlg2::on_RangeMin_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->RangeMin_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
   QObject::connect(ui->RangeMin_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_RangeMin(QString)));
}

void IDDlg2::on_RangeMax_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->RangeMax_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->RangeMax_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_RangeMax(QString)));
}

void IDDlg2::show_paras()
{
    if(CH_Flag==0)  //ch0
    {
        CellModelstr = QString::number(AnaParas_Ch0->CellModel,10);
        ui->CellModel_lineEdit->setText(CellModelstr);

        Analytestr = QString::number(AnaParas_Ch0->Analyte,10);
        ui->Analyte_lineEdit->setText(Analytestr);

        RangeMinstr = QString::number(AnaParas_Ch0->RangeMin,'f',2);
        ui->RangeMin_lineEdit->setText(RangeMinstr);

        RangeMaxstr = QString::number(AnaParas_Ch0->RangeMax,'f',2);
        ui->RangeMax_lineEdit->setText(RangeMaxstr);

    }
    else
    {
        CellModelstr = QString::number(AnaParas_Ch1->CellModel,10);
        ui->CellModel_lineEdit->setText(CellModelstr);

        Analytestr = QString::number(AnaParas_Ch1->Analyte,10);
        ui->Analyte_lineEdit->setText(Analytestr);

        RangeMinstr = QString::number(AnaParas_Ch1->RangeMin,'f',2);
        ui->RangeMin_lineEdit->setText(RangeMinstr);

        RangeMaxstr = QString::number(AnaParas_Ch1->RangeMax,'f',2);
        ui->RangeMax_lineEdit->setText(RangeMaxstr);
    }

}

//add 6.14-4
void IDDlg2::range_limit_CellModel(QString)
{
    bool ok;
    long a = ui->CellModel_lineEdit->text().toLong(&ok);//bool toint
    if(!((a>=0)&&(a<=40000000)))
    {
     on_airchamberversionTip_clicked();

     ui->CellModel_lineEdit->setText(CellModelstr);
    }
}

void IDDlg2::range_limit_Analyte(QString)
{
    bool ok;
    int a = ui->Analyte_lineEdit->text().toInt(&ok);//bool toint
    if(!((a>=0)&&(a<=5)))
    {
     on_analytesTip_clicked();

     ui->Analyte_lineEdit->setText(Analytestr);
    }
}

void IDDlg2::range_limit_RangeMin(QString)
{
    bool ok;
    float a = ui->RangeMin_lineEdit->text().toFloat(&ok);//bool toint
    if(!((a>=0)&&(a<=1000000)))
    {
     on_minimunvalueoftherangeTip_clicked();

     ui->RangeMin_lineEdit->setText(RangeMinstr);
    }
}
void IDDlg2::range_limit_RangeMax(QString)
{
    bool ok;
    float a = ui->RangeMax_lineEdit->text().toFloat(&ok);//bool toint
    if(!((a>=0)&&(a<=1000000)))
    {
     on_maximunvalueoftherangeTip_clicked();
     ui->RangeMax_lineEdit->setText(RangeMaxstr);
    }
}


void IDDlg2::on_ok_clicked()
{
    bool ok;
    long CellModel =ui->CellModel_lineEdit->text().toLong(&ok);
    int Analyte =ui->Analyte_lineEdit->text().toInt(&ok);
    float RangeMin =ui->RangeMin_lineEdit->text().toFloat(&ok);
    float RangeMax =ui->RangeMax_lineEdit->text().toFloat(&ok);
     if(CH_Flag==0)
     {
         AnaParas_Ch0->CellModel=CellModel;
         AnaParas_Ch0->Analyte=Analyte;
         AnaParas_Ch0->RangeMin=RangeMin;
         AnaParas_Ch0->RangeMax=RangeMax;
         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->CellModel=CellModel;
         AnaParas_Ch1->Analyte=Analyte;
         AnaParas_Ch1->RangeMin=RangeMin;
         AnaParas_Ch1->RangeMax=RangeMax;
         files->writefile(1);
     }

}



void IDDlg2::on_cancel_clicked()
{
    show_paras();
}
