#include "screeninclu/interfaceandcommunicationdlg2.h"
#include "ui_interfaceandcommunicationdlg2.h"
#include <QTime>
#include <QTimer>

#include <QMessageBox>
//add 6.14-5
extern fileoperate *files;


interfaceandcommunicationDlg2::interfaceandcommunicationDlg2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::interfaceandcommunicationDlg2)
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
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->DataFormat_change->setFocusPolicy(Qt::NoFocus);
    ui->DataFormat_Tip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageUp->setFocusPolicy(Qt::NoFocus);
    ui->DataFormat_lineEdit->setFocusPolicy(Qt::NoFocus);
}

interfaceandcommunicationDlg2::~interfaceandcommunicationDlg2()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void interfaceandcommunicationDlg2::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}

void interfaceandcommunicationDlg2::backtothis()
{
    this->show();
    this->show_paras();
}

void interfaceandcommunicationDlg2::on_DataFormat_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->DataFormat_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->DataFormat_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_DataFormat(QString)));

}

void interfaceandcommunicationDlg2::on_DataFormat_Tip_clicked()
{
     QMessageBox::information(this,"choose","choose(0:operator 1:RD)");
}

void interfaceandcommunicationDlg2::on_pageUp_clicked()
{
    this->hide();
    up();
}

void interfaceandcommunicationDlg2::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}
void interfaceandcommunicationDlg2::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        DataFormatstr = QString::number(AnaParas_Ch0->DataFormat,10);//bool,int,long
        ui->DataFormat_lineEdit->setText(DataFormatstr);


    }
    else
    {
        DataFormatstr = QString::number(AnaParas_Ch1->DataFormat,10);//bool,int,long
        ui->DataFormat_lineEdit->setText(DataFormatstr);
    }

}

void interfaceandcommunicationDlg2::range_limit_DataFormat(QString)
{
    bool ok;
    int a = ui->DataFormat_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=1)))
    {
     on_DataFormat_Tip_clicked();
     ui->DataFormat_lineEdit->setText(DataFormatstr);
    }
}
void interfaceandcommunicationDlg2::on_ok_clicked()
{
    bool ok;
    int DataFormat = ui->DataFormat_lineEdit->text().toInt(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->DataFormat=DataFormat;

         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->DataFormat=DataFormat;
         files->writefile(1);
     }
}

void interfaceandcommunicationDlg2::on_cancel_clicked()
{
    show_paras();
}
