
#include "screeninclu/algorithmdld3.h"
#include "ui_algorithmdld3.h"

#include <QTime>
#include <QTimer>
#include <QMessageBox>
extern Para *pa;
////add 6.14-5
extern fileoperate *files;

algorithmDld3::algorithmDld3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::algorithmDld3)
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
    ui->BasechooseTip->setFocusPolicy(Qt::NoFocus);
    ui->Baseuse_change->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageUp->setFocusPolicy(Qt::NoFocus);
    ui->PRchooseTip->setFocusPolicy(Qt::NoFocus);
    ui->Pruse_change->setFocusPolicy(Qt::NoFocus);
    ui->R1chooseTip->setFocusPolicy(Qt::NoFocus);
    ui->R1use_change->setFocusPolicy(Qt::NoFocus);
    ui->R2chooseTip->setFocusPolicy(Qt::NoFocus);
    ui->R2use_change->setFocusPolicy(Qt::NoFocus);
    ui->R3chooseTip->setFocusPolicy(Qt::NoFocus);
    ui->R3use_change->setFocusPolicy(Qt::NoFocus);
    ui->VRchooseTip->setFocusPolicy(Qt::NoFocus);
    ui->Vruse_change->setFocusPolicy(Qt::NoFocus);
    //add 6.14-2
    ui->Rruse_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->Vruse_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->R1use_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->R2use_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->R3use_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->Baseuse_lineEdit->setFocusPolicy(Qt::NoFocus);

}

algorithmDld3::~algorithmDld3()
{
    delete ui;
    delete keyboarddlg;
}
//显示时间
void algorithmDld3::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}

void algorithmDld3::on_PRchooseTip_clicked()
{
    QMessageBox::information(this,"choose","0:close  1:Pro  2:Val  3:Both");
}

void algorithmDld3::on_VRchooseTip_clicked()
{
   QMessageBox::information(this,"choose","0:close  1:Pro  2:Val  3:Both");

}

void algorithmDld3::on_R1chooseTip_clicked()
{
    QMessageBox::information(this,"choose","0:close  1:Pro  2:Val  3:Both");
}

void algorithmDld3::on_R2chooseTip_clicked()
{
    QMessageBox::information(this,"choose","0:close  1:Pro  2:Val  3:Both");
}

void algorithmDld3::on_R3chooseTip_clicked()
{
    QMessageBox::information(this,"choose","0:close  1:Pro  2:Val  3:Both");
}

void algorithmDld3::on_BasechooseTip_clicked()
{
    QMessageBox::information(this,"choose","0:close  1:Pro  2:Val  3:Both");
}

void algorithmDld3::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void algorithmDld3::backtothis()
{
    this->show();
    this->show_paras();
}



void algorithmDld3::on_pageUp_clicked()
{
    this->hide();
    up();
}

void algorithmDld3::on_Pruse_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Rruse_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Rruse_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PRuse(QString)));

}


void algorithmDld3::on_Vruse_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Vruse_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Vruse_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_VRuse(QString)));
    //QObject::connect(ui->Vruse_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_R1use(QString)));//???


}

void algorithmDld3::on_R1use_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->R1use_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->R1use_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_R2use(QString)));
}

void algorithmDld3::on_R2use_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->R2use_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->R2use_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_R3use(QString)));
}

void algorithmDld3::on_R3use_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->R3use_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->R3use_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Baseuse(QString)));
}

void algorithmDld3::on_Baseuse_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Baseuse_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Baseuse_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_VRuse(QString)));
}


void algorithmDld3::show_paras() //add 6.14-3  显示参数
{

    if(CH_Flag==0)  //ch0
    {
        PRusestr = QString::number(AnaParas_Ch0->PRuse,10);//bool,int,long
        ui->Rruse_lineEdit->setText(PRusestr);

        R1usestr =  QString::number(AnaParas_Ch0->R1use,10);
        ui->R1use_lineEdit->setText(R1usestr);

        R2usestr =  QString::number(AnaParas_Ch0->R2use,10);
        ui->R2use_lineEdit->setText(R2usestr);

        R3usestr =  QString::number(AnaParas_Ch0->R3use,10);//float ,double
        ui->R3use_lineEdit->setText(R3usestr);

        Baseusestr =  QString::number(AnaParas_Ch0->Baseuse,10);
        ui->Baseuse_lineEdit->setText(Baseusestr);

        VRusestr =  QString::number(AnaParas_Ch0->VRuse,10);//float ,double
        ui->Vruse_lineEdit->setText(VRusestr);

    }
    else
    {
        PRusestr = QString::number(AnaParas_Ch1->PRuse,10);//bool,int,long
        ui->Rruse_lineEdit->setText(PRusestr);

        R1usestr =  QString::number(AnaParas_Ch1->R1use,10);
        ui->R1use_lineEdit->setText(R1usestr);

        R2usestr =  QString::number((int)AnaParas_Ch1->R2use,10);
        ui->R2use_lineEdit->setText(R2usestr);

        R3usestr =  QString::number(AnaParas_Ch1->R3use,10);//float ,double
        ui->R3use_lineEdit->setText(R3usestr);

        Baseusestr =  QString::number((int)AnaParas_Ch1->Baseuse,10);
        ui->Baseuse_lineEdit->setText(Baseusestr);

        VRusestr =  QString::number(AnaParas_Ch1->VRuse,10);//float ,double
        ui->Vruse_lineEdit->setText(VRusestr);

    }

}

void algorithmDld3::range_limit_PRuse(QString)
{
    bool ok;
    int a = ui->Rruse_lineEdit->text().toInt(&ok,10);

    if(((a>=0)&&(a<=3)))
    {
      //情况1
      if(AnaParas_Ch0->VRuse==1)
      {
        if((a==1)||(a==3))
        {
          QMessageBox::information(this,"choose","PR VR collision");
           ui->Rruse_lineEdit->setText(PRusestr);//错误数据设不进去,依然显示上次结果
        }

      }
      //情况2
      else if(AnaParas_Ch0->VRuse==2)
      {
        if((a==2)||(a==3))
        {
           QMessageBox::information(this,"choose","PR VR collision");
           ui->Rruse_lineEdit->setText(PRusestr);
        }

      }
      //情况3
      else if(AnaParas_Ch0->VRuse==3)
      {
        if((a==1)||(a==2)||(a==3))
        {

          QMessageBox::information(this,"choose","PR VR collision");
           ui->Rruse_lineEdit->setText(PRusestr);
        }

      }
      else
      {
         ;//printf("other\t");
      }

    }
    else
    {
        on_PRchooseTip_clicked();
      ui->Rruse_lineEdit->setText(PRusestr);
    }
 
}

void algorithmDld3::range_limit_R1use(QString)
{
    bool ok;
    int a = ui->R1use_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=3)))
    {
            on_R1chooseTip_clicked();

     ui->R1use_lineEdit->setText(R1usestr);
    }
}
void algorithmDld3::range_limit_R2use(QString)
{
    bool ok;
    int a = ui->R2use_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=3)))
    {
      on_R2chooseTip_clicked();
     ui->R2use_lineEdit->setText(R2usestr);
    }
}
void algorithmDld3::range_limit_R3use(QString)
{
    bool ok;
    int a = ui->R3use_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=3)))
    {
      on_R3chooseTip_clicked();

     ui->R3use_lineEdit->setText(R3usestr);
    }
}
void algorithmDld3::range_limit_Baseuse(QString)
{
    bool ok;
    int a = ui->Baseuse_lineEdit->text().toInt(&ok,10);
    if(!((a>=0)&&(a<=3)))
    {
     on_BasechooseTip_clicked();

     ui->Baseuse_lineEdit->setText(Baseusestr);
    }
}
void algorithmDld3::range_limit_VRuse(QString)
{
    bool ok;
    int a = ui->Vruse_lineEdit->text().toInt(&ok,10);//???

  if(((a>=0)&&(a<=3)))
  {
      //情况1
      if(AnaParas_Ch0->PRuse==1)
      {
        if((a==1)||(a==3))
        {
          QMessageBox::information(this,"choose","PR VR collision");
          ui->Vruse_lineEdit->setText(VRusestr);

        }

      }
      //情况2
      else if(AnaParas_Ch0->PRuse==2)
      {
        if((a==2)||(a==3))
        {
          QMessageBox::information(this,"choose","PR VR collision");
          ui->Vruse_lineEdit->setText(VRusestr);

        }

      }
      //情况3
      else if(AnaParas_Ch0->PRuse==3)
      {
        if((a==1)||(a==2)||(a==3))
        {
          QMessageBox::information(this,"choose","PR VR collision");
          ui->Vruse_lineEdit->setText(VRusestr);
        }

      }
      else
      {
          ;//printf("other \n");//no message

      }
  }
  else
  {
        on_VRchooseTip_clicked();
        ui->Vruse_lineEdit->setText(VRusestr);
  }

}


void algorithmDld3::on_ok_clicked()
{
    bool ok;
    int PRuse = ui->Rruse_lineEdit->text().toInt(&ok);
    int R1use =ui->R1use_lineEdit->text().toInt(&ok);
    int R2use =ui->R2use_lineEdit->text().toInt(&ok);
    int R3use =ui->R3use_lineEdit->text().toInt(&ok);
    int Baseuse =ui->Baseuse_lineEdit->text().toInt(&ok);
    int VRuse =ui->Vruse_lineEdit->text().toInt(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->PRuse=PRuse;
         AnaParas_Ch0->R1use=R1use;
         AnaParas_Ch0->R2use=R2use;
         AnaParas_Ch0->R3use=R3use;
         AnaParas_Ch0->Baseuse=Baseuse;
         AnaParas_Ch0->VRuse=VRuse;

         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->PRuse=PRuse;
         AnaParas_Ch1->R1use=R1use;
         AnaParas_Ch1->R2use=R2use;
         AnaParas_Ch1->R3use=R3use;
         AnaParas_Ch1->Baseuse=Baseuse;
         AnaParas_Ch1->VRuse=VRuse;
         files->writefile(1);
     }


}

void algorithmDld3::on_cancel_clicked()
{
    show_paras();

}
