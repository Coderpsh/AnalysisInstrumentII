#include "screeninclu/calibrationparameterdlg.h"
#include "ui_calibrationparameterdlg.h"

#include <QTime>
#include <QTimer>

#include <QMessageBox>
extern fileoperate *files;

calibrationParameterDlg::calibrationParameterDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calibrationParameterDlg)
{
    ui->setupUi(this);
    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);
    //时间计时器
 //   QTimer *timer = new QTimer(this);
 //   connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
 //   timer->start(1000);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->PCoeff0_change->setFocusPolicy(Qt::NoFocus);
    ui->PCoeff1_change->setFocusPolicy(Qt::NoFocus);
    ui->PCoeff2_change->setFocusPolicy(Qt::NoFocus);
    ui->PCoeff3_change->setFocusPolicy(Qt::NoFocus);
    ui->processfirstorderparameterTip->setFocusPolicy(Qt::NoFocus);
    ui->processsecondorderparameterTip->setFocusPolicy(Qt::NoFocus);
    ui->processthirdorderparameterTip->setFocusPolicy(Qt::NoFocus);
    ui->processzeroorderparameterTip->setFocusPolicy(Qt::NoFocus);

    ui->PCoeff0_linEdit->setFocusPolicy(Qt::NoFocus);
    ui->PCoeff1_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->PCoeff2_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->PCoeff3_lineEdit->setFocusPolicy(Qt::NoFocus);
}


//显示时间
void calibrationParameterDlg::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}


calibrationParameterDlg::~calibrationParameterDlg()
{
    delete ui;
    delete keyboarddlg;
}

void calibrationParameterDlg::on_processzeroorderparameterTip_clicked()
{
   QMessageBox::information(this,"input","input value");
}

void calibrationParameterDlg::on_processfirstorderparameterTip_clicked()
{
   QMessageBox::information(this,"input","input value(index)");
}

void calibrationParameterDlg::on_processsecondorderparameterTip_clicked()
{
     QMessageBox::information(this,"input","input value(index)");
}

void calibrationParameterDlg::on_processthirdorderparameterTip_clicked()
{
    QMessageBox::information(this,"input","input value(index)");
}

void calibrationParameterDlg::backtothis()
{
    this->show();
    this->show_paras();
}

void calibrationParameterDlg::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void calibrationParameterDlg::on_pageDown_clicked()
{
    this->hide();
    down();
}

void calibrationParameterDlg::on_PCoeff0_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PCoeff0_linEdit,SLOT(setText(QString)));
    keyboarddlg->show();

   QObject::connect(ui->PCoeff0_linEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PCoeff0(QString)));
}

void calibrationParameterDlg::on_PCoeff1_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PCoeff1_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
   QObject::connect(ui->PCoeff1_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PCoeff1(QString)));
}

void calibrationParameterDlg::on_PCoeff2_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PCoeff2_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
   QObject::connect(ui->PCoeff2_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PCoeff2(QString)));
}

void calibrationParameterDlg::on_PCoeff3_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PCoeff3_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
   QObject::connect(ui->PCoeff3_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PCoeff3(QString)));
}

void calibrationParameterDlg::show_paras()
{
    if(CH_Flag==0)  //ch0
    {
        PCoeff0str = QString::number(AnaParas_Ch0->PCoeff0,'f',2);
        ui->PCoeff0_linEdit->setText(PCoeff0str);

        PCoeff1str = QString::number(AnaParas_Ch0->PCoeff1,'f',2);
        ui->PCoeff1_lineEdit->setText(PCoeff1str);

        PCoeff2str = QString::number(AnaParas_Ch0->PCoeff2,'f',2);
        ui->PCoeff2_lineEdit->setText(PCoeff2str);

        PCoeff3str = QString::number(AnaParas_Ch0->PCoeff3,'f',2);
        ui->PCoeff3_lineEdit->setText(PCoeff3str);

    }
    else
    {
        PCoeff0str = QString::number(AnaParas_Ch1->PCoeff0,'f',2);
        ui->PCoeff0_linEdit->setText(PCoeff0str);

        PCoeff1str = QString::number(AnaParas_Ch1->PCoeff1,'f',2);
        ui->PCoeff1_lineEdit->setText(PCoeff1str);

        PCoeff2str = QString::number(AnaParas_Ch1->PCoeff2,'f',2);
        ui->PCoeff2_lineEdit->setText(PCoeff2str);

        PCoeff3str = QString::number(AnaParas_Ch1->PCoeff3,'f',2);
        ui->PCoeff3_lineEdit->setText(PCoeff3str);
    }


}

//add 6.14-4
void calibrationParameterDlg::range_limit_PCoeff0(QString)
{
    bool ok;
    float a = ui->PCoeff0_linEdit->text().toFloat(&ok);//bool toint
    if(!((a>-1000)&&(a<1000)))
    {
     on_processzeroorderparameterTip_clicked();

     ui->PCoeff0_linEdit->setText(PCoeff0str);
    }
}
void calibrationParameterDlg::range_limit_PCoeff1(QString)
{
    bool ok;
    float a = ui->PCoeff1_lineEdit->text().toFloat(&ok);//bool toint
    if(!((a>-1000)&&(a<1000)))
    {
     on_processfirstorderparameterTip_clicked();

     ui->PCoeff1_lineEdit->setText(PCoeff1str);
    }
}
void calibrationParameterDlg::range_limit_PCoeff2(QString)
{
    bool ok;
    float a = ui->PCoeff2_lineEdit->text().toFloat(&ok);//bool toint
    if(!((a>-1000)&&(a<1000)))
    {
     on_processsecondorderparameterTip_clicked();

     ui->PCoeff2_lineEdit->setText(PCoeff2str);
    }
}
void calibrationParameterDlg::range_limit_PCoeff3(QString)
{
    bool ok;
    float a = ui->PCoeff3_lineEdit->text().toFloat(&ok);//bool toint
    if(!((a>-1000)&&(a<1000)))
    {
     on_processthirdorderparameterTip_clicked();

     ui->PCoeff3_lineEdit->setText(PCoeff3str);
    }
}



void calibrationParameterDlg::on_ok_clicked()
{
    bool ok;
    float PCoeff0 =ui->PCoeff0_linEdit->text().toFloat(&ok);
    float PCoeff1 =ui->PCoeff1_lineEdit->text().toFloat(&ok);
    float PCoeff2 =ui->PCoeff2_lineEdit->text().toFloat(&ok);
    float PCoeff3 =ui->PCoeff3_lineEdit->text().toFloat(&ok);
     if(CH_Flag==0)
     {
         AnaParas_Ch0->PCoeff0=PCoeff0;
         AnaParas_Ch0->PCoeff1=PCoeff1;
         AnaParas_Ch0->PCoeff2=PCoeff2;
         AnaParas_Ch0->PCoeff3=PCoeff3;
         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->PCoeff0=PCoeff0;
         AnaParas_Ch1->PCoeff1=PCoeff1;
         AnaParas_Ch1->PCoeff2=PCoeff2;
         AnaParas_Ch1->PCoeff3=PCoeff3;
         files->writefile(1);
     }

}



void calibrationParameterDlg::on_cancel_clicked()
{
    show_paras();
}
