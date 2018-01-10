#include "screeninclu/referencecurvedlg.h"
#include "ui_referencecurvedlg.h"

#include <QTime>
#include <QTimer>
#include <QMessageBox>
//add 6.14-5
extern fileoperate *files;


referenceCurvedlg::referenceCurvedlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::referenceCurvedlg)
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
    ui->CalDate_change->setFocusPolicy(Qt::NoFocus);
    ui->CalDate_Tip->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->ProRCon_change->setFocusPolicy(Qt::NoFocus);
    ui->ProRCon_Tip->setFocusPolicy(Qt::NoFocus);
    ui->RefCurvAvg_change->setFocusPolicy(Qt::NoFocus);
    ui->RefCurvAvg_Tip->setFocusPolicy(Qt::NoFocus);
    ui->RefInd_change->setFocusPolicy(Qt::NoFocus);
    ui->RefInd_Tip->setFocusPolicy(Qt::NoFocus);
    ui->ValRCon_change->setFocusPolicy(Qt::NoFocus);
    ui->ValRCon_Tip->setFocusPolicy(Qt::NoFocus);
   //add 6.14-2
    ui->CalDate_linEdit->setFocusPolicy(Qt::NoFocus);
    ui->RefCurvAvg_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->ProRCon_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->ValRCon_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->RefInd_lineEdit->setFocusPolicy(Qt::NoFocus);
}

referenceCurvedlg::~referenceCurvedlg()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void referenceCurvedlg::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}

void referenceCurvedlg::on_CalDate_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->CalDate_linEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    //add 6.14
    QObject::connect(ui->CalDate_linEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_CalDate(QString)));
}

//add 6.14-6
void referenceCurvedlg::on_RefCurvAvg_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->RefCurvAvg_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    //add 6.14
    QObject::connect(ui->RefCurvAvg_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_RefCurvAvg(QString)));
}
void referenceCurvedlg::on_ProRCon_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->ProRCon_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    //add 6.14
    QObject::connect(ui->ProRCon_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_ProRCon(QString)));
}

void referenceCurvedlg::on_ValRCon_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->ValRCon_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    //add 6.14
    QObject::connect(ui->ValRCon_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_ValRCon(QString)));

}

void referenceCurvedlg::on_RefInd_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->RefInd_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    //add 6.1
    QObject::connect(ui->RefInd_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_RefInd(QString)));
}

void referenceCurvedlg::on_CalDate_Tip_clicked()
{
   QMessageBox::information(this,"input","inpput date(yyyy-mm-dd");
}

void referenceCurvedlg::on_RefCurvAvg_Tip_clicked()
{
    QMessageBox::information(this,"input","input value");
}

void referenceCurvedlg::on_RefInd_Tip_clicked()
{
    QMessageBox::information(this,"input","input value");
}

void referenceCurvedlg::on_ProRCon_Tip_clicked()
{
    QMessageBox::information(this,"input","input value(ppm)");
}

void referenceCurvedlg::on_ValRCon_Tip_clicked()
{
    QMessageBox::information(this,"input","input value(ppm)");
}
void referenceCurvedlg::backtothis() //add 6.14
{
    this->show();
    this->show_paras();  //add 6.14
}

void referenceCurvedlg::on_pageDown_clicked()
{
    this->hide();
    down();
}

void referenceCurvedlg::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void referenceCurvedlg::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        CalDatestr = QString::number(AnaParas_Ch0->CalDate,10);//bool,int,long
        ui->CalDate_linEdit->setText(CalDatestr);

        RefCurvAvgstr =  QString::number(AnaParas_Ch0->RefCurvAvg,10);
        ui->RefCurvAvg_lineEdit->setText(RefCurvAvgstr);

        RefIndstr =  QString::number((int)AnaParas_Ch0->RefInd,10); //
        ui->RefInd_lineEdit->setText(RefIndstr);

        ProRConstr =  QString::number(AnaParas_Ch0->ProRCon,'f',2);//float ,double
        ui->ProRCon_lineEdit->setText(ProRConstr);

        ValRConstr =  QString::number(AnaParas_Ch0->ValRCon,'f',2);
        ui->ValRCon_lineEdit->setText(ValRConstr);
    }
    else
    {
        CalDatestr = QString::number(AnaParas_Ch1->CalDate,10);

        ui->CalDate_linEdit->setText(CalDatestr);
        RefCurvAvgstr =  QString::number(AnaParas_Ch1->RefCurvAvg,10);

        ui->RefCurvAvg_lineEdit->setText(RefCurvAvgstr);
        RefIndstr =  QString::number((int)AnaParas_Ch1->RefInd,10); //

        ui->RefInd_lineEdit->setText(RefIndstr);
        ProRConstr =  QString::number(AnaParas_Ch1->ProRCon,'f',2);

        ui->ProRCon_lineEdit->setText(ProRConstr);
        ValRConstr =  QString::number(AnaParas_Ch1->ValRCon,'f',2);

        ui->ValRCon_lineEdit->setText(ValRConstr);
    }

}

//add 6.14-4
void referenceCurvedlg::range_limit_CalDate(QString)
{
    bool ok;
    long a = ui->CalDate_linEdit->text().toLong(&ok);//bool toint
    if(!((a>20000101)&&(a<40000101)))
    {
     on_CalDate_Tip_clicked();

     ui->CalDate_linEdit->setText(CalDatestr);
    }
}
void referenceCurvedlg::range_limit_RefCurvAvg(QString)
{
    bool ok;
    int a =ui->RefCurvAvg_lineEdit->text().toInt(&ok,10);
    if(!((a>0)&&(a<1000)))
    {
     on_RefCurvAvg_Tip_clicked();

      ui->RefCurvAvg_lineEdit->setText(RefCurvAvgstr);
    }

}

void referenceCurvedlg::range_limit_RefInd(QString)
{
    bool ok;
    int a =(int)ui->RefInd_lineEdit->text().toFloat(&ok); //
    if(!((a>0)&&(a<61)))
    {
     on_RefInd_Tip_clicked();

      ui->RefInd_lineEdit->setText(RefIndstr);
    }
}

void referenceCurvedlg::range_limit_ProRCon(QString)
{
    bool ok;
    float a =ui->ProRCon_lineEdit->text().toFloat(&ok);  //@
    if(!((a>=0)&&(a<=1000000)))
    {
      on_ProRCon_Tip_clicked();

      ui->ProRCon_lineEdit->setText(ProRConstr);
    }
}
void referenceCurvedlg::range_limit_ValRCon(QString)
{
    bool ok;
    float a =ui->ValRCon_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=1000000)))
    {
      on_ValRCon_Tip_clicked();

      ui->ValRCon_lineEdit->setText(ValRConstr);
    }
}

//6.14-5  --ui  /ok   /cancl
void referenceCurvedlg::on_ok_clicked() //flash
{
    bool ok;
    long CalDate = ui->CalDate_linEdit->text().toLong(&ok);
    int RefCurvAvg =ui->RefCurvAvg_lineEdit->text().toInt(&ok,10);
    float RefInd =ui->RefInd_lineEdit->text().toFloat(&ok);
    float ProRCon =ui->ProRCon_lineEdit->text().toFloat(&ok);
    float ValRCon =ui->ValRCon_lineEdit->text().toFloat(&ok);
     if(CH_Flag==0)
     {
         AnaParas_Ch0->CalDate=CalDate;
         AnaParas_Ch0->RefCurvAvg=RefCurvAvg;
         AnaParas_Ch0->RefInd=RefInd;
         AnaParas_Ch0->ProRCon=ProRCon;
         AnaParas_Ch0->ValRCon=ValRCon;
         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->CalDate=CalDate;
         AnaParas_Ch1->RefCurvAvg=RefCurvAvg;
         AnaParas_Ch1->RefInd=RefInd;
         AnaParas_Ch1->ProRCon=ProRCon;
         AnaParas_Ch1->ValRCon=ValRCon;
         files->writefile(1);
     }

}

void referenceCurvedlg::on_cancel_clicked()
{
    show_paras();
}
