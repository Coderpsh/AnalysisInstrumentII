#include "screeninclu/calibrationparameterdlg2.h"
#include "ui_calibrationparameterdlg2.h"


#include <QTime>
#include <QTimer>
#include <QMessageBox>
extern fileoperate *files;

calibrationParameterDlg2::calibrationParameterDlg2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calibrationParameterDlg2)
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
    ui->calibrationfirstorderparameterTip->setFocusPolicy(Qt::NoFocus);
    ui->calibrationsecondorderparameterTip->setFocusPolicy(Qt::NoFocus);
    ui->calibrationthirdorderparameterTip->setFocusPolicy(Qt::NoFocus);
    ui->calibrationzeroorderparameterTip->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageUp->setFocusPolicy(Qt::NoFocus);
    ui->VCoeff0_change->setFocusPolicy(Qt::NoFocus);
    ui->VCoeff1_change->setFocusPolicy(Qt::NoFocus);
    ui->VCoeff2_change->setFocusPolicy(Qt::NoFocus);
    ui->VCoeff3_chamge->setFocusPolicy(Qt::NoFocus);

    ui->VCoeff0_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->VCoeff1_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->VCoeff2_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->VCoeff3_lineEdit->setFocusPolicy(Qt::NoFocus);

}


calibrationParameterDlg2::~calibrationParameterDlg2()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void calibrationParameterDlg2::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime_2->setText(txtDateTime);

}

void calibrationParameterDlg2::on_calibrationzeroorderparameterTip_clicked()
{
    QMessageBox::information(this,"input","input value(index)");

}

void calibrationParameterDlg2::on_calibrationfirstorderparameterTip_clicked()
{
     QMessageBox::information(this,"input","input value(index)");
}

void calibrationParameterDlg2::on_calibrationsecondorderparameterTip_clicked()
{
     QMessageBox::information(this,"input","input value(index)");
}

void calibrationParameterDlg2::on_calibrationthirdorderparameterTip_clicked()
{
    QMessageBox::information(this,"input","input value(index)");
}

void calibrationParameterDlg2::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void calibrationParameterDlg2::backtothis()
{
    this->show();
    this->show_paras();
}


void calibrationParameterDlg2::on_VCoeff0_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->VCoeff0_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
   QObject::connect(ui->VCoeff0_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_VCoeff0(QString)));

}

void calibrationParameterDlg2::on_VCoeff1_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->VCoeff1_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->VCoeff1_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_VCoeff1(QString)));
}

void calibrationParameterDlg2::on_VCoeff2_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->VCoeff2_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
     QObject::connect(ui->VCoeff2_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_VCoeff2(QString)));
}

void calibrationParameterDlg2::on_VCoeff3_chamge_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->VCoeff3_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->VCoeff3_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_VCoeff3(QString)));
}


void calibrationParameterDlg2::on_pageUp_clicked()
{
    up();
    this->hide();
}
void calibrationParameterDlg2::show_paras()
{
    if(CH_Flag==0)  //ch0
    {
        VCoeff0str = QString::number(AnaParas_Ch0->VCoeff0,'f',2);
        ui->VCoeff0_lineEdit->setText(VCoeff0str);

        VCoeff1str = QString::number(AnaParas_Ch0->VCoeff1,'f',2);
        ui->VCoeff1_lineEdit->setText(VCoeff1str);

        VCoeff2str = QString::number(AnaParas_Ch0->VCoeff2,'f',2);
        ui->VCoeff2_lineEdit->setText(VCoeff2str);

        VCoeff3str = QString::number(AnaParas_Ch0->VCoeff3,'f',2);
        ui->VCoeff3_lineEdit->setText(VCoeff3str);

    }
    else
    {
        VCoeff0str = QString::number(AnaParas_Ch1->VCoeff0,'f',2);
        ui->VCoeff0_lineEdit->setText(VCoeff0str);

        VCoeff1str = QString::number(AnaParas_Ch1->VCoeff1,'f',2);
        ui->VCoeff1_lineEdit->setText(VCoeff1str);

        VCoeff2str = QString::number(AnaParas_Ch1->VCoeff2,'f',2);
        ui->VCoeff2_lineEdit->setText(VCoeff2str);

        VCoeff3str = QString::number(AnaParas_Ch1->VCoeff3,'f',2);
        ui->VCoeff3_lineEdit->setText(VCoeff3str);
    }


}

//add 6.14-4
void calibrationParameterDlg2::range_limit_VCoeff0(QString)
{
    bool ok;
    float a = ui->VCoeff0_lineEdit->text().toFloat(&ok);//bool toint
    if(!((a>-1000)&&(a<1000)))
    {
     on_calibrationzeroorderparameterTip_clicked();

     ui->VCoeff0_lineEdit->setText(VCoeff0str);
    }
}
void calibrationParameterDlg2::range_limit_VCoeff1(QString)
{
    bool ok;
    float a = ui->VCoeff1_lineEdit->text().toFloat(&ok);//bool toint
    if(!((a>-1000)&&(a<1000)))
    {
     on_calibrationfirstorderparameterTip_clicked();

     ui->VCoeff1_lineEdit->setText(VCoeff1str);
    }
}
void calibrationParameterDlg2::range_limit_VCoeff2(QString)
{
    bool ok;
    float a = ui->VCoeff2_lineEdit->text().toFloat(&ok);//bool toint
    if(!((a>-1000)&&(a<1000)))
    {
     on_calibrationsecondorderparameterTip_clicked();

     ui->VCoeff2_lineEdit->setText(VCoeff2str);
    }
}
void calibrationParameterDlg2::range_limit_VCoeff3(QString)
{
    bool ok;
    float a = ui->VCoeff3_lineEdit->text().toFloat(&ok);//bool toint
    if(!((a>-1000)&&(a<1000)))
    {
     on_calibrationthirdorderparameterTip_clicked();
     ui->VCoeff3_lineEdit->setText(VCoeff3str);
    }
}




void calibrationParameterDlg2::on_ok_clicked()
{
    bool ok;
    float VCoeff0 =ui->VCoeff0_lineEdit->text().toFloat(&ok);
    float VCoeff1 =ui->VCoeff1_lineEdit->text().toFloat(&ok);
    float VCoeff2 =ui->VCoeff2_lineEdit->text().toFloat(&ok);
    float VCoeff3 =ui->VCoeff3_lineEdit->text().toFloat(&ok);
     if(CH_Flag==0)
     {
         AnaParas_Ch0->VCoeff0=VCoeff0;
         AnaParas_Ch0->VCoeff1=VCoeff1;
         AnaParas_Ch0->VCoeff2=VCoeff2;
         AnaParas_Ch0->VCoeff3=VCoeff3;
         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->VCoeff0=VCoeff0;
         AnaParas_Ch1->VCoeff1=VCoeff1;
         AnaParas_Ch1->VCoeff2=VCoeff2;
         AnaParas_Ch1->VCoeff3=VCoeff3;
         files->writefile(1);
     }

}

void calibrationParameterDlg2::on_cancel_clicked()
{
    show_paras();
}
