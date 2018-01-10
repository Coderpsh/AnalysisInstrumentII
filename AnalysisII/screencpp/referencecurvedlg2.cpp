#include "screeninclu/referencecurvedlg2.h"
#include "ui_referencecurvedlg2.h"

#include <QTime>
#include <QTimer>
#include <QMessageBox>

//add 6.14-5
extern fileoperate *files;

referenceCurvedlg2::referenceCurvedlg2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::referenceCurvedlg2)
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
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->component1_change->setFocusPolicy(Qt::NoFocus);
    ui->component1_Tip->setFocusPolicy(Qt::NoFocus);
    ui->component2_change->setFocusPolicy(Qt::NoFocus);
    ui->component2_Tip->setFocusPolicy(Qt::NoFocus);
    ui->component3_change->setFocusPolicy(Qt::NoFocus);
    ui->component3_Tip->setFocusPolicy(Qt::NoFocus);
    ui->component4_change->setFocusPolicy(Qt::NoFocus);
    ui->component4_Tip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->pageUp->setFocusPolicy(Qt::NoFocus);
    //add 6.14-2
    ui->component1_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->component2_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->component3_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->component4_lineEdit->setFocusPolicy(Qt::NoFocus);

}

referenceCurvedlg2::~referenceCurvedlg2()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void referenceCurvedlg2::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}

void referenceCurvedlg2::on_component1_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->component1_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    //add 6.14
    QObject::connect(ui->component1_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Comp1(QString)));

}


void referenceCurvedlg2::on_component2_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->component2_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    //add 6.14
    QObject::connect(ui->component2_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Comp2(QString)));
}


void referenceCurvedlg2::on_component3_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->component3_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    //add 6.14
    QObject::connect(ui->component3_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Comp3(QString)));
}

void referenceCurvedlg2::on_component4_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->component4_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    //add 6.14
    QObject::connect(ui->component4_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Comp4(QString)));
}

void referenceCurvedlg2::on_component1_Tip_clicked()
{
    QMessageBox::information(this,"input","input value(%)");
}

void referenceCurvedlg2::on_component2_Tip_clicked()
{
     QMessageBox::information(this,"input","input value(%)");
}

void referenceCurvedlg2::on_component3_Tip_clicked()
{
     QMessageBox::information(this,"input","input value(%)");
}

void referenceCurvedlg2::on_component4_Tip_clicked()
{
    QMessageBox::information(this,"input","input value(%)");
}

void referenceCurvedlg2::on_pageUp_clicked()
{
    this->hide();
    up();
}

void referenceCurvedlg2::on_pageDown_clicked()
{
    this->hide();
    down();
}

void referenceCurvedlg2::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}
void referenceCurvedlg2::backtothis() //add 6.14-3.1
{
    this->show();
    this->show_paras();

}

void referenceCurvedlg2::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        Comp1str = QString::number(AnaParas_Ch0->Comp1,'f',2);//bool,int,long
        ui->component1_lineEdit->setText(Comp1str);

        Comp2str =  QString::number(AnaParas_Ch0->Comp2,'f',2);
        ui->component2_lineEdit->setText(Comp2str);

        Comp3str =  QString::number((int)AnaParas_Ch0->Comp3,'f',2);
        ui->component3_lineEdit->setText(Comp3str);

        Comp4str =  QString::number(AnaParas_Ch0->Comp4,'f',2);//float ,double
        ui->component4_lineEdit->setText(Comp4str);

    }
    else
    {
        Comp1str = QString::number(AnaParas_Ch1->Comp1,'f',2);//bool,int,long
        ui->component1_lineEdit->setText(Comp1str);

        Comp2str =  QString::number(AnaParas_Ch1->Comp2,'f',2);
        ui->component2_lineEdit->setText(Comp2str);

        Comp3str =  QString::number((int)AnaParas_Ch1->Comp3,'f',2);
        ui->component3_lineEdit->setText(Comp3str);

        Comp4str =  QString::number(AnaParas_Ch1->Comp4,'f',2);//float ,double
        ui->component4_lineEdit->setText(Comp4str);
    }

}
//add 6.14-4
void referenceCurvedlg2::range_limit_Comp1(QString)
{
    bool ok;
    float a = ui->component1_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100)))
    {
     on_component1_Tip_clicked();

     ui->component1_lineEdit->setText(Comp1str);
    }
}
void referenceCurvedlg2::range_limit_Comp2(QString)
{
    bool ok;
    float a = ui->component2_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100)))
    {
     on_component2_Tip_clicked();

     ui->component2_lineEdit->setText(Comp2str);
    }
}
void referenceCurvedlg2::range_limit_Comp3(QString)
{
    bool ok;
    float a = ui->component3_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100)))
    {
     on_component3_Tip_clicked();

     ui->component3_lineEdit->setText(Comp3str);
    }
}
void referenceCurvedlg2::range_limit_Comp4(QString)
{
    bool ok;
    float a = ui->component4_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100)))
    {
     on_component4_Tip_clicked();

     ui->component4_lineEdit->setText(Comp4str);
    }
}


void referenceCurvedlg2::on_ok_clicked()
{
    bool ok;
    float Comp1 = ui->component1_lineEdit->text().toFloat(&ok);
    float Comp2 =ui->component2_lineEdit->text().toFloat(&ok);
    float Comp3 =ui->component3_lineEdit->text().toFloat(&ok);
    float Comp4 =ui->component4_lineEdit->text().toFloat(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->Comp1=Comp1;
         AnaParas_Ch0->Comp2=Comp2;
         AnaParas_Ch0->Comp3=Comp3;
         AnaParas_Ch0->Comp4=Comp4;

         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->Comp1=Comp1;
         AnaParas_Ch1->Comp2=Comp2;
         AnaParas_Ch1->Comp3=Comp3;
         AnaParas_Ch1->Comp4=Comp4;

         files->writefile(1);
     }
}

void referenceCurvedlg2::on_cancel_clicked()
{
    show_paras();
}
