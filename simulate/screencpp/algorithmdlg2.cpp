#include "screeninclu/algorithmdlg2.h"
#include "ui_algorithmdlg2.h"

#include <QTime>
#include <QTimer>
#include <QMessageBox>

//add 6.14-5
extern fileoperate *files;


algorithmDlg2::algorithmDlg2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::algorithmDlg2)
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
    ui->choosedspectrumendingpointTip->setFocusPolicy(Qt::NoFocus);
    ui->choosedspectrumstartingpointTip->setFocusPolicy(Qt::NoFocus);
    ui->DCNormEnd_change->setFocusPolicy(Qt::NoFocus);
    ui->DCNormStart_change->setFocusPolicy(Qt::NoFocus);
    ui->normalizedendingpointTip->setFocusPolicy(Qt::NoFocus);
    ui->normalizedstartingpointTip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->pageUp->setFocusPolicy(Qt::NoFocus);
    ui->SpectraEnd_change->setFocusPolicy(Qt::NoFocus);
    ui->SpectraStart_change->setFocusPolicy(Qt::NoFocus);

    //add 6.14-2
    ui->DCNormStart_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->DCNormEnd_LineEdit->setFocusPolicy(Qt::NoFocus);
    ui->SpectraStart_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->SpectraEnd_lineEdit->setFocusPolicy(Qt::NoFocus);


}

algorithmDlg2::~algorithmDlg2()
{
    delete ui;
    delete keyboarddlg;
}

void algorithmDlg2::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}



void algorithmDlg2::on_normalizedstartingpointTip_clicked()
{
    QMessageBox::information(this,"input","input value(index)");

}

void algorithmDlg2::on_normalizedendingpointTip_clicked()
{
    QMessageBox::information(this,"input","input value(index)");
}

void algorithmDlg2::on_choosedspectrumstartingpointTip_clicked()
{
    QMessageBox::information(this,"input","input value(1-1000)");
}

void algorithmDlg2::on_choosedspectrumendingpointTip_clicked()
{
    QMessageBox::information(this,"input","input value(1-1000)");
}

void algorithmDlg2::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void algorithmDlg2::backtothis()
{
    this->show();
    this->show_paras();
}

void algorithmDlg2::on_pageUp_clicked()
{
    this->hide();
    up();
}

void algorithmDlg2::on_pageDown_clicked()
{
    this->hide();
    down();
}

void algorithmDlg2::on_DCNormStart_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->DCNormStart_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->DCNormStart_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_DCNormStart(QString)));


}

void algorithmDlg2::on_DCNormEnd_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->DCNormEnd_LineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->DCNormEnd_LineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_DCNormEnd(QString)));
}


void algorithmDlg2::on_SpectraStart_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->SpectraStart_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->SpectraStart_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_SpectraStart(QString)));

}

void algorithmDlg2::on_SpectraEnd_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->SpectraEnd_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->SpectraEnd_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_SpectraEnd(QString)));
}


void algorithmDlg2::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        DCNormStartstr = QString::number(AnaParas_Ch0->DCNormStart,10);//bool,int,long
        ui->DCNormStart_lineEdit->setText(DCNormStartstr);

        DCNormEndstr =  QString::number(AnaParas_Ch0->DCNormEnd,10);
        ui->DCNormEnd_LineEdit->setText(DCNormEndstr);

        SpectraStartstr =  QString::number(AnaParas_Ch0->SpectraStart,10);
        ui->SpectraStart_lineEdit->setText(SpectraStartstr);

        SpectraEndstr =  QString::number(AnaParas_Ch0->SpectraEnd,10);//float ,double
        ui->SpectraEnd_lineEdit->setText(SpectraEndstr);

    }
    else
    {
        DCNormStartstr = QString::number(AnaParas_Ch1->DCNormStart,10);//bool,int,long
        ui->DCNormStart_lineEdit->setText(DCNormStartstr);

        DCNormEndstr =  QString::number(AnaParas_Ch1->DCNormEnd,10);
        ui->DCNormEnd_LineEdit->setText(DCNormEndstr);

        SpectraStartstr =  QString::number(AnaParas_Ch1->SpectraStart,10);

        ui->SpectraStart_lineEdit->setText(SpectraStartstr);

        SpectraEndstr =  QString::number(AnaParas_Ch1->SpectraEnd,10);//float ,double
        ui->SpectraEnd_lineEdit->setText(SpectraEndstr);

    }

}


void algorithmDlg2::range_limit_DCNormStart(QString)
{
    bool ok;
    int a = ui->DCNormStart_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=1000)))
    {

     on_normalizedstartingpointTip_clicked();
     ui->DCNormStart_lineEdit->setText(DCNormStartstr);
    }
}
void algorithmDlg2::range_limit_DCNormEnd(QString)
{
    bool ok;
    int a = ui->DCNormEnd_LineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=1000)))
    {
     on_normalizedendingpointTip_clicked();

     ui->DCNormEnd_LineEdit->setText(DCNormEndstr);
    }
}
void algorithmDlg2::range_limit_SpectraStart(QString)
{
    bool ok;
    int a = ui->SpectraStart_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=4000)))
    {
     on_choosedspectrumstartingpointTip_clicked();
     ui->SpectraStart_lineEdit->setText(SpectraStartstr);
    }
}
void algorithmDlg2::range_limit_SpectraEnd(QString)
{
    bool ok;
    int a = ui->SpectraEnd_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=4000)))
    {

     on_choosedspectrumendingpointTip_clicked();

     ui->SpectraEnd_lineEdit->setText(SpectraEndstr);
    }
}


void algorithmDlg2::on_ok_clicked()
{
    bool ok;
    int DCNormStart = ui->DCNormStart_lineEdit->text().toInt(&ok);
    int DCNormEnd =ui->DCNormEnd_LineEdit->text().toInt(&ok);
    int SpectraStart =ui->SpectraStart_lineEdit->text().toInt(&ok);
    int SpectraEnd =ui->SpectraEnd_lineEdit->text().toInt(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->DCNormStart=DCNormStart;
         AnaParas_Ch0->DCNormEnd=DCNormEnd;
         AnaParas_Ch0->SpectraStart=SpectraStart;
         AnaParas_Ch0->SpectraEnd=SpectraEnd;

         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->DCNormStart=DCNormStart;
         AnaParas_Ch1->DCNormEnd=DCNormEnd;
         AnaParas_Ch1->SpectraStart=SpectraStart;
         AnaParas_Ch1->SpectraEnd=SpectraEnd;


         files->writefile(1);
     }
}

void algorithmDlg2::on_cancel_clicked()
{
    show_paras();
}
