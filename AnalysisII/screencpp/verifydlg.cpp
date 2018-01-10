#include "screeninclu/verifydlg.h"
#include "ui_verifydlg.h"


#include <QTime>
#include <QTimer>

#include <QMessageBox>
//add 6.14-5
extern fileoperate *files;

verifyDlg::verifyDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::verifyDlg)
{
    ui->setupUi(this);

    //时间计时器
 //   QTimer *timer = new QTimer(this);
  //  connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
 //   timer->start(1000);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);

    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->checkingconcentrationTip->setFocusPolicy(Qt::NoFocus);
    ui->checkingerrorallowanceTip->setFocusPolicy(Qt::NoFocus);
    ui->checkingswitchtimeTip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->PurgeTime_change->setFocusPolicy(Qt::NoFocus);
    ui->VAllowance_change->setFocusPolicy(Qt::NoFocus);
    ui->Vconc_change->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);

    //add 6.14-2
   ui->PurgeTime_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->Vconc_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->VAllowance_lineEdit->setFocusPolicy(Qt::NoFocus);


}

verifyDlg::~verifyDlg()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void verifyDlg::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}


void verifyDlg::on_checkingswitchtimeTip_clicked()
{
     QMessageBox::information(this,"input","input value(s)");
}

void verifyDlg::on_checkingconcentrationTip_clicked()
{
    QMessageBox::information(this,"input","input value(ppmv)");
}

void verifyDlg::on_checkingerrorallowanceTip_clicked()
{
    QMessageBox::information(this,"input","input value(%)");
}

void verifyDlg::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}


void verifyDlg::on_PurgeTime_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PurgeTime_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PurgeTime_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PurgeTime(QString)));

}

void verifyDlg::on_Vconc_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Vconc_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Vconc_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Vconc(QString)));

}

void verifyDlg::on_VAllowance_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->VAllowance_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->VAllowance_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_VAllowance(QString)));

}
void verifyDlg::on_pageDown_clicked()
{
    this->hide();
    down();
}
void verifyDlg::backtothis()
{
    this->show();
    this->show_paras();


}

void verifyDlg::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        PurgeTimestr = QString::number(AnaParas_Ch0->PurgeTime,10);//bool,int,long
        ui->PurgeTime_lineEdit->setText(PurgeTimestr);

        Vconcstr =  QString::number(AnaParas_Ch0->Vconc,'f',2);
        ui->Vconc_lineEdit->setText(Vconcstr);

        VAllowancestr =  QString::number(AnaParas_Ch0->VAllowance,'f',2);
        ui->VAllowance_lineEdit->setText(VAllowancestr);
    }
    else
    {
        PurgeTimestr = QString::number(AnaParas_Ch1->PurgeTime,10);//bool,int,long
        ui->PurgeTime_lineEdit->setText(PurgeTimestr);

        Vconcstr =  QString::number(AnaParas_Ch1->Vconc,'f',2);
        ui->Vconc_lineEdit->setText(Vconcstr);

        VAllowancestr =  QString::number(AnaParas_Ch1->VAllowance,'f',2);
        ui->VAllowance_lineEdit->setText(VAllowancestr);

}
}


  void verifyDlg::range_limit_PurgeTime(QString)
    {
        bool ok;
        int a = ui->PurgeTime_lineEdit->text().toInt(&ok,10);
        if(!((a>=0)&&(a<=100)))
        {
        on_checkingswitchtimeTip_clicked();

         ui->PurgeTime_lineEdit->setText(PurgeTimestr);
        }
    }
    void verifyDlg::range_limit_Vconc(QString)
    {
        bool ok;
        float a = ui->Vconc_lineEdit->text().toFloat(&ok);
        if(!((a>=0)&&(a<=1000)))
        {
        on_checkingconcentrationTip_clicked();

         ui->Vconc_lineEdit->setText(Vconcstr);
        }
    }
    void verifyDlg::range_limit_VAllowance(QString)
    {
        bool ok;
        float a = ui->VAllowance_lineEdit->text().toFloat(&ok);
        if(!((a>=0)&&(a<=100)))
        {
         on_checkingerrorallowanceTip_clicked();

         ui->VAllowance_lineEdit->setText(VAllowancestr);
        }
    }

void verifyDlg::on_ok_clicked()
{
    bool ok;
    int PurgeTime = ui->PurgeTime_lineEdit->text().toInt(&ok);
    float Vconc =ui->Vconc_lineEdit->text().toFloat(&ok);
    float VAllowance =ui->VAllowance_lineEdit->text().toFloat(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->PurgeTime=PurgeTime;
         AnaParas_Ch0->Vconc=Vconc;
         AnaParas_Ch0->VAllowance=VAllowance;
         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->PurgeTime=PurgeTime;
         AnaParas_Ch1->Vconc=Vconc;
         AnaParas_Ch1->VAllowance=VAllowance;
         files->writefile(1);
     }
}


void verifyDlg::on_cancel_clicked()
{
   show_paras();
}
