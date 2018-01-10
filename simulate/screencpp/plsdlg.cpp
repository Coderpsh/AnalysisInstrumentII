#include "screeninclu/plsdlg.h"
#include "ui_plsdlg.h"


#include <QTime>
#include <QTimer>
#include<QMessageBox>

//add 6.14-5
extern fileoperate *files;

plsDlg::plsDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plsDlg)
{
    ui->setupUi(this);

    //时间计时器
 //   QTimer *timer = new QTimer(this);
 //   connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
 //   timer->start(1000);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);
    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);
    ui->A_change->setFocusPolicy(Qt::NoFocus);
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->errcirNum_change->setFocusPolicy(Qt::NoFocus);
    ui->erref_change->setFocusPolicy(Qt::NoFocus);
    ui->errorcontrolcycleTip->setFocusPolicy(Qt::NoFocus);
    ui->errorcontrolprecisionTip->setFocusPolicy(Qt::NoFocus);
    ui->K_change->setFocusPolicy(Qt::NoFocus);
    ui->largestprinciplecomponentTip->setFocusPolicy(Qt::NoFocus);
    ui->moduling->setFocusPolicy(Qt::NoFocus);
    ui->PLS_N_change->setFocusPolicy(Qt::NoFocus);
    ui->PLS_N_Tip->setFocusPolicy(Qt::NoFocus);
    //add 6.14-2

    ui->erref_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->errcirNum_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->K_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->A_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->PLS_N_lineEdit->setFocusPolicy(Qt::NoFocus);




}

plsDlg::~plsDlg()
{
    delete ui;
    delete keyboarddlg;
}


void plsDlg::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}


void plsDlg::on_errorcontrolprecisionTip_clicked()
{
    QMessageBox::information(this,"input","input value(1e-10~1e-5)");
}

void plsDlg::on_errorcontrolcycleTip_clicked()
{
    QMessageBox::information(this,"input","input value(200-2000)");
}

void plsDlg::on_bendnumberTip_clicked()
{
    QMessageBox::information(this,"input","input value(2-10)");
}

void plsDlg::on_largestprinciplecomponentTip_clicked()
{
    QMessageBox::information(this,"input","input value(2-20)");
}

void plsDlg::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void plsDlg::on_erref_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->erref_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->erref_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_erref(QString)));

}

void plsDlg::on_errcirNum_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->errcirNum_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->errcirNum_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_errcirNum(QString)));

}

void plsDlg::on_K_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->K_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->K_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PLS_K(QString)));

}

void plsDlg::on_A_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->A_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->A_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PLS_A(QString)));

}


void plsDlg::on_PLS_N_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PLS_N_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PLS_N_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PLS_N(QString)));

}

void plsDlg::on_PLS_N_Tip_clicked()
{
    QMessageBox::information(this,"input","input value(0-60)");
}


void plsDlg::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        errefstr = QString::number(AnaParas_Ch0->erref,'g');//bool,int,long
        ui->erref_lineEdit->setText(errefstr);

        errcirNumstr =  QString::number(AnaParas_Ch0->errcirNum,10);
        ui->errcirNum_lineEdit->setText(errcirNumstr);

        PLS_Kstr =  QString::number(AnaParas_Ch0->PLS_K,10);
        ui->K_lineEdit->setText(PLS_Kstr);

        PLS_Astr =  QString::number(AnaParas_Ch0->PLS_A,10);//float ,double
        ui->A_lineEdit->setText(PLS_Astr);

        PLS_Nstr =  QString::number(AnaParas_Ch0->PLS_N,10);//float ,double
        ui->PLS_N_lineEdit->setText(PLS_Nstr);

    }
    else
    {
        errefstr = QString::number(AnaParas_Ch1->erref,'g');//bool,int,long
        ui->erref_lineEdit->setText(errefstr);

        errcirNumstr =  QString::number(AnaParas_Ch1->errcirNum,10);
        ui->errcirNum_lineEdit->setText(errcirNumstr);

        PLS_Kstr =  QString::number(AnaParas_Ch1->PLS_K,10);
        ui->K_lineEdit->setText(PLS_Kstr);

        PLS_Astr =  QString::number(AnaParas_Ch1->PLS_A,10);//float ,double
        ui->A_lineEdit->setText(PLS_Astr);

        PLS_Nstr =  QString::number(AnaParas_Ch1->PLS_N,10);//float ,double
        ui->PLS_N_lineEdit->setText(PLS_Nstr);

    }

}

void plsDlg::range_limit_erref(QString)
{
    bool ok;
    float a = ui->erref_lineEdit->text().toFloat(&ok);
    if(!((a>=1e-10)&&(a<=1e-5)))
    {
     on_errorcontrolprecisionTip_clicked();
     ui->erref_lineEdit->setText(errefstr);
    }
}
void plsDlg::range_limit_errcirNum(QString)
{
    bool ok;
    int a = ui->errcirNum_lineEdit->text().toInt(&ok,10);
    if(!((a>=200)&&(a<=2000)))
    {
     on_errorcontrolcycleTip_clicked();

     ui->errcirNum_lineEdit->setText(errcirNumstr);
    }
}
void plsDlg::range_limit_PLS_K(QString)
{
    bool ok;
    int a = ui->K_lineEdit->text().toInt(&ok,10);
    if(!((a>=2)&&(a<=10)))
    {
     on_bendnumberTip_clicked();

     ui->K_lineEdit->setText(PLS_Kstr);
    }
}
void plsDlg::range_limit_PLS_A(QString)
{
    bool ok;
    int a = ui->A_lineEdit->text().toInt(&ok,10);
    if(!((a>=2)&&(a<=20)))
    {
     on_largestprinciplecomponentTip_clicked();

     ui->A_lineEdit->setText(PLS_Astr);
    }
}

void plsDlg::range_limit_PLS_N(QString)
{
    bool ok;
    int a = ui->PLS_N_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=60)))//@ 10
    {
     on_PLS_N_Tip_clicked();

     ui->PLS_N_lineEdit->setText(PLS_Nstr);
    }
}



void plsDlg::on_cancel_clicked()
{
    show_paras();
}

void plsDlg::on_moduling_clicked()
{
    bool ok;
    int errcirNum =ui->errcirNum_lineEdit->text().toInt(&ok);
    int PLS_K =ui->K_lineEdit->text().toInt(&ok);
    int PLS_A =ui->A_lineEdit->text().toInt(&ok);
    int PLS_N =ui->PLS_N_lineEdit->text().toInt(&ok);
    float erref =ui->erref_lineEdit->text().toFloat(&ok);
     if(CH_Flag==0)
     {
          AnaParas_Ch0->erref=erref;
          AnaParas_Ch0->errcirNum=errcirNum;
          AnaParas_Ch0->PLS_K=PLS_K;
          AnaParas_Ch0->PLS_A=PLS_A;
          AnaParas_Ch0->PLS_N=PLS_N;
          files->writefile(0);
          //AnaParas_Ch0->CV_Flag=true;

     }
     else
     {
         AnaParas_Ch1->erref=erref;
         AnaParas_Ch1->errcirNum=errcirNum;
         AnaParas_Ch1->PLS_K=PLS_K;
         AnaParas_Ch1->PLS_A=PLS_A;
         AnaParas_Ch1->PLS_N=PLS_N;
         files->writefile(1);
         //AnaParas_Ch1->CV_Flag=true;
     }
}
