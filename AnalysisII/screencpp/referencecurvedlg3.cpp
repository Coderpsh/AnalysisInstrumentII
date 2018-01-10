#include "screeninclu/referencecurvedlg3.h"
#include "ui_referencecurvedlg3.h"

#include <QTime>
#include <QTimer>
#include <QMessageBox>

//add 6.14-5
extern fileoperate *files;


referencecurvedlg3::referencecurvedlg3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::referencecurvedlg3)
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
    ui->component5_change->setFocusPolicy(Qt::NoFocus);
    ui->component5_Tip->setFocusPolicy(Qt::NoFocus);
    ui->component6_change->setFocusPolicy(Qt::NoFocus);
    ui->component6_Tip->setFocusPolicy(Qt::NoFocus);
    ui->component7_change->setFocusPolicy(Qt::NoFocus);
    ui->component7_Tip->setFocusPolicy(Qt::NoFocus);
    ui->component8_change->setFocusPolicy(Qt::NoFocus);
    ui->component8_Tip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageUp->setFocusPolicy(Qt::NoFocus);
    ui->save->setFocusPolicy(Qt::NoFocus);
    //add 6.14-2
     ui->component5_lineEdit->setFocusPolicy(Qt::NoFocus);
     ui->component6_lineEdit->setFocusPolicy(Qt::NoFocus);
     ui->component7_lineEdit->setFocusPolicy(Qt::NoFocus);
     ui->component8_linEdit->setFocusPolicy(Qt::NoFocus);
}

referencecurvedlg3::~referencecurvedlg3()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void  referencecurvedlg3::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");

    ui->dateTime->setText(txtDateTime);
}

void referencecurvedlg3::on_component5_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->component5_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    //add 6.14
    QObject::connect(ui->component5_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Comp5(QString)));

}

void referencecurvedlg3::on_component6_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->component6_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    //add 6.14
    QObject::connect(ui->component6_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Comp6(QString)));
}

void referencecurvedlg3::on_component7_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->component7_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    //add 6.14
    QObject::connect(ui->component7_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Comp7(QString)));
}

void referencecurvedlg3::on_component8_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->component8_linEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    //add 6.14
    QObject::connect(ui->component8_linEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Comp8(QString)));
}

void referencecurvedlg3::on_component5_Tip_clicked()
{
    QMessageBox::information(this,"input","input value(%)");
}

void referencecurvedlg3::on_component6_Tip_clicked()
{
     QMessageBox::information(this,"input","input value(%)");
}

void referencecurvedlg3::on_component7_Tip_clicked()
{
    QMessageBox::information(this,"input","input value(%)");
}

void referencecurvedlg3::on_component8_Tip_clicked()
{
     QMessageBox::information(this,"input","input value(%)");
}

void referencecurvedlg3::on_pageUp_clicked()
{
    this->hide();
    up();
}

void referencecurvedlg3::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}
void referencecurvedlg3::backtothis()
{
    this->show();
    this->show_paras();  //add 6.14

}

void referencecurvedlg3::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        Comp5str = QString::number(AnaParas_Ch0->Comp5,'f',2);//bool,int,long
        ui->component5_lineEdit->setText(Comp5str);

        Comp6str =  QString::number(AnaParas_Ch0->Comp6,'f',2);
        ui->component6_lineEdit->setText(Comp6str);

        Comp7str =  QString::number(AnaParas_Ch0->Comp7,'f',2);
        ui->component7_lineEdit->setText(Comp7str);

        Comp8str =  QString::number(AnaParas_Ch0->Comp8,'f',2);//float ,double
        ui->component8_linEdit->setText(Comp8str);
    }
    else
    {
        Comp5str = QString::number(AnaParas_Ch1->Comp5,'f',2);//bool,int,long
        ui->component5_lineEdit->setText(Comp5str);

        Comp6str =  QString::number(AnaParas_Ch1->Comp6,'f',2);
        ui->component6_lineEdit->setText(Comp6str);

        Comp7str =  QString::number(AnaParas_Ch1->Comp7,'f',2);
        ui->component7_lineEdit->setText(Comp7str);

        Comp8str =  QString::number(AnaParas_Ch1->Comp8,'f',2);//float ,double
        ui->component8_linEdit->setText(Comp8str);
    }

}

//add 6.14-4
void referencecurvedlg3::range_limit_Comp5(QString)
{
    bool ok;
    float a = ui->component5_lineEdit->text().toFloat(&ok);//bool toint
    if(!((a>=0)&&(a<=100)))
    {
      on_component5_Tip_clicked();

     ui->component5_lineEdit->setText(Comp5str);
    }
}
void referencecurvedlg3::range_limit_Comp6(QString)
{
    bool ok;
    float a =ui->component6_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100)))
    {
      on_component6_Tip_clicked();

      ui->component6_lineEdit->setText(Comp6str);
    }

}

void referencecurvedlg3::range_limit_Comp7(QString)
{
    bool ok;
    float a =ui->component7_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100)))
    {
      on_component7_Tip_clicked();

      ui->component7_lineEdit->setText(Comp7str);
    }
}

void referencecurvedlg3::range_limit_Comp8(QString)
{
    bool ok;
    float a =ui->component8_linEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100)))
    {
      on_component8_Tip_clicked();
      ui->component8_linEdit->setText(Comp8str);
    }
}


void referencecurvedlg3::on_ok_clicked()
{
    bool ok;
    float Comp5 = ui->component5_lineEdit->text().toFloat(&ok);
    float Comp6 =ui->component6_lineEdit->text().toFloat(&ok);
    float Comp7 =ui->component7_lineEdit->text().toFloat(&ok);
    float Comp8 =ui->component8_linEdit->text().toFloat(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->Comp5=Comp5;
         AnaParas_Ch0->Comp6=Comp6;
         AnaParas_Ch0->Comp7=Comp7;
         AnaParas_Ch0->Comp8=Comp8;

         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->Comp5=Comp5;
         AnaParas_Ch1->Comp6=Comp6;
         AnaParas_Ch1->Comp7=Comp7;
         AnaParas_Ch1->Comp8=Comp8;

         files->writefile(1);
     }
}

void referencecurvedlg3::on_cancel_clicked()
{
    show_paras();
}

void referencecurvedlg3::on_save_clicked()
{
    if( CH_Flag ==0)
    {
        spi0_ref_flag =1;  //go to save model

        set_mode(0,0);

        while(!refspi0_save_ok);

        printf("save ch0 refcurve ok");

        refspi0_save_ok =0;

        QMessageBox::information(this,"input","save ch0 refcurve ok!(%)");

    }
    else
    {
        spi1_ref_flag=1;

        set_mode(1,0);

        while(!refspi1_save_ok);

        printf("save ch1 refcurve ok");

        refspi1_save_ok =0;

        QMessageBox::information(this,"input","save ch1 refcurve ok!(%)");

    }

}
