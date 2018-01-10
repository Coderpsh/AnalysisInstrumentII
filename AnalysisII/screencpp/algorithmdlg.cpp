#include "screeninclu/algorithmdlg.h"
#include "ui_algorithmdlg.h"

#include <QTime>
#include <QTimer>

#include <QMessageBox>
//add 6.14-5
extern fileoperate *files;


algorithmDlg::algorithmDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::algorithmDlg)
{
    ui->setupUi(this);
    //时间计时器
 //   QTimer *timer = new QTimer(this);
  //  connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
  //  timer->start(1000);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);
    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->calculationmodelTip->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->DFEnable_change->setFocusPolicy(Qt::NoFocus);
    ui->digitalfilteringTip->setFocusPolicy(Qt::NoFocus);
    ui->Model_change->setFocusPolicy(Qt::NoFocus);
    ui->movingaverage_change->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->slidingaveragetimeTip->setFocusPolicy(Qt::NoFocus);

    //add 6.14-2
    ui->Model_lineEdt->setFocusPolicy(Qt::NoFocus);
    ui->DFEnable_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->MovAvg_lineEdit->setFocusPolicy(Qt::NoFocus);
}

algorithmDlg::~algorithmDlg()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void algorithmDlg::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
    keyboarddlg=new keyboardDlg;

}



void algorithmDlg::on_calculationmodelTip_clicked()
{
    QMessageBox::information(this,"choose","0:CLS  1:PLS");
}

void algorithmDlg::on_digitalfilteringTip_clicked()
{
    QMessageBox::information(this,"choose","0:forbidden  1:open");
}

void algorithmDlg::on_slidingaveragetimeTip_clicked()
{
    QMessageBox::information(this,"input","input value");
}

void algorithmDlg::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}
void algorithmDlg::backtothis()
{
    this->show();
    this->show_paras();
}


void algorithmDlg::on_pageDown_clicked()
{
    this->hide();
    down();
}

void algorithmDlg::on_Model_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Model_lineEdt,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Model_lineEdt,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Model(QString)));


}

void algorithmDlg::on_DFEnable_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->DFEnable_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->DFEnable_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_DFEnable(QString)));

}

void algorithmDlg::on_movingaverage_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->MovAvg_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->MovAvg_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_MovAvg(QString)));

}


void algorithmDlg::show_paras() //add 6.14-3
{

    if(CH_Flag==0)
    {
        Modelstr = QString::number(AnaParas_Ch0->Model,10);
        ui->Model_lineEdt->setText(Modelstr);

        DFEnablestr =  QString::number(AnaParas_Ch0->DFEnable,10);
        ui->DFEnable_lineEdit->setText(DFEnablestr);

        MovAvgstr =  QString::number(AnaParas_Ch0->MovAvg,10);
        ui->MovAvg_lineEdit->setText(MovAvgstr);
    }
    else
    {
        Modelstr = QString::number(AnaParas_Ch1->Model,10);
        ui->Model_lineEdt->setText(Modelstr);

        DFEnablestr =  QString::number(AnaParas_Ch1->DFEnable,10);
        ui->DFEnable_lineEdit->setText(DFEnablestr);

        MovAvgstr =  QString::number(AnaParas_Ch1->MovAvg,10);
        ui->MovAvg_lineEdit->setText(MovAvgstr);
    }

}

void algorithmDlg::range_limit_Model(QString)
{
    bool ok;
    int a = ui->Model_lineEdt->text().toInt(&ok);
    if(!((a>=0)&&(a<=1)))
    {
    on_calculationmodelTip_clicked();

     ui->Model_lineEdt->setText(Modelstr);
    }
}
void algorithmDlg::range_limit_DFEnable(QString)
{
    bool ok;
    int a = ui->DFEnable_lineEdit->text().toInt(&ok);
    if(!((a>=0)&&(a<=1)))
    {
     on_digitalfilteringTip_clicked();

     ui->DFEnable_lineEdit->setText(DFEnablestr);
    }
}
void algorithmDlg::range_limit_MovAvg(QString)
{
    bool ok;
    int a = ui->MovAvg_lineEdit->text().toInt(&ok);
    if(!((a>=0)&&(a<=100)))
    {
      on_slidingaveragetimeTip_clicked();

     ui->MovAvg_lineEdit->setText(MovAvgstr);
    }
}

void algorithmDlg::on_ok_clicked()
{
    bool ok;
    int Model = ui->Model_lineEdt->text().toInt(&ok);
    int DFEnable =ui->DFEnable_lineEdit->text().toInt(&ok);
    int MovAvg =ui->MovAvg_lineEdit->text().toInt(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->Model=Model;
         AnaParas_Ch0->DFEnable=DFEnable;
         AnaParas_Ch0->MovAvg=MovAvg;
         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->Model=Model;
         AnaParas_Ch1->DFEnable=DFEnable;
         AnaParas_Ch1->MovAvg=MovAvg;
         files->writefile(1);
     }
}

void algorithmDlg::on_cancel_clicked()
{
     show_paras();
}
