#include "screeninclu/spectrumselfregulatedlg1.h"
#include "ui_spectrumselfregulatedlg1.h"

#include <QTime>
#include <QTimer>

#include <QMessageBox>
//add 6.14-5
extern fileoperate *files;


spectrumselfregulateDlg1::spectrumselfregulateDlg1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::spectrumselfregulateDlg1)
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
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->PkTrk_change->setFocusPolicy(Qt::NoFocus);
    ui->PkTrk_Tip->setFocusPolicy(Qt::NoFocus);

    //add 6.14-2
     ui->PkTrk_lineEdit->setFocusPolicy(Qt::NoFocus);
}

spectrumselfregulateDlg1::~spectrumselfregulateDlg1()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void spectrumselfregulateDlg1::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}


void spectrumselfregulateDlg1::on_PkTrk_change_clicked()
{

     keyboarddlg->hide();
     QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
     QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkTrk_lineEdit,SLOT(setText(QString)));
     keyboarddlg->show();
    //add 6.14
    QObject::connect(ui->PkTrk_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkTrk(QString)));


}

void spectrumselfregulateDlg1::on_PkTrk_Tip_clicked()
{
     QMessageBox::information(this,"choose","choose(0:close 1:open 2:restart)");
}


void spectrumselfregulateDlg1::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void spectrumselfregulateDlg1::on_pageDown_clicked()
{
    if(permit_flag==0)
    {
        QMessageBox::information(this,"warning","you are not avaliable to continue");

    }
    else
    {
         down();
         this->hide();
    }

 }

void spectrumselfregulateDlg1::backtothis()
{
    this->show();
    this->show_paras();

}

void spectrumselfregulateDlg1::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        PkTrkstr = QString::number(AnaParas_Ch0->PkTrk,10);
        ui->PkTrk_lineEdit->setText(PkTrkstr);


    }
    else
    {
        PkTrkstr = QString::number(AnaParas_Ch1->PkTrk,10);
        ui->PkTrk_lineEdit->setText(PkTrkstr);
    }

}

void spectrumselfregulateDlg1::range_limit_PkTrk(QString)
{
    bool ok;
    int a = ui->PkTrk_lineEdit->text().toInt(&ok,10);//bool toint
    if(!((a>=0)&&(a<=2)))
    {
     on_PkTrk_Tip_clicked();

     ui->PkTrk_lineEdit->setText(PkTrkstr);
    }
}

void spectrumselfregulateDlg1::on_ok_clicked()
{
    bool ok;
    int PkTrk = ui->PkTrk_lineEdit->text().toInt(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->PkTrk=PkTrk;
         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->PkTrk=PkTrk;
         files->writefile(1);
     }

}

void spectrumselfregulateDlg1::on_cancel_clicked()
{
     show_paras();
}
