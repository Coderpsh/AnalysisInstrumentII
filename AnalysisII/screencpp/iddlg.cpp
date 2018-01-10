#include "screeninclu/iddlg.h"
#include "ui_iddlg.h"

#include <QTime>
#include <QTimer>

#include <QMessageBox>
extern fileoperate *files;

IDDlg::IDDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IDDlg)
{
    ui->setupUi(this);
//    QTimer *timer=new QTimer;
//    connect(timer,SIGNAL(timeout()),this,SLOT(showRealTime()));
//    timer->start(1000);
    setFocusPolicy(Qt::NoFocus);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);
    ui->airchamberSHTip->setFocusPolicy(Qt::NoFocus);
    ui->analyzerserialnumberTip->setFocusPolicy(Qt::NoFocus);
    ui->analyzerSNTip->setFocusPolicy(Qt::NoFocus);
    ui->AnaModel_change->setFocusPolicy(Qt::NoFocus);
    ui->AnaSN_change->setFocusPolicy(Qt::NoFocus);
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->CellSN_change->setFocusPolicy(Qt::NoFocus);
    ui->FWRev_change->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->softwareversionTip->setFocusPolicy(Qt::NoFocus);

    ui->AnaModel_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->AnaSN_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->FWRev_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->CellSN_lineEdit->setFocusPolicy(Qt::NoFocus);
}

IDDlg::~IDDlg()
{
    delete ui;
    delete keyboarddlg;
}

void IDDlg::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}

void IDDlg::on_analyzerSNTip_clicked()
{
    QMessageBox::information(this,"input","input value");

}

void IDDlg::on_analyzerserialnumberTip_clicked()
{
     QMessageBox::information(this,"input","input value");
}

void IDDlg::on_softwareversionTip_clicked()
{
    QMessageBox::information(this,"input","input value");
}

void IDDlg::on_airchamberSHTip_clicked()
{
     QMessageBox::information(this,"input","input value");
}

void IDDlg::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void IDDlg::on_pageDown_clicked()
{
    this->hide();
    down();
}
void IDDlg::backtothis()
{
    this->show();
    this->show_paras();
}

void IDDlg::on_AnaSN_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->AnaSN_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->AnaSN_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_AnaSN(QString)));
}

void IDDlg::on_AnaModel_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->AnaModel_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->AnaModel_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_AnaModel(QString)));
}

void IDDlg::on_FWRev_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->FWRev_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
     QObject::connect(ui->FWRev_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_FWRev(QString)));
}

void IDDlg::on_CellSN_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->CellSN_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->CellSN_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_CellSN(QString)));
}
void IDDlg::show_paras()
{
    if(CH_Flag==0)  //ch0
    {
        AnaSNstr = QString::number(AnaParas_Ch0->AnaSN);
        ui->AnaSN_lineEdit->setText(AnaSNstr);


        AnaModelstr = QString::number(AnaParas_Ch0->AnaModel);
        ui->AnaModel_lineEdit->setText(AnaModelstr);

        FWRevstr = QString::number(AnaParas_Ch0->FWRev);
        ui->FWRev_lineEdit->setText(FWRevstr);

        CellSNstr = QString::number(AnaParas_Ch0->CellSN);
        ui->CellSN_lineEdit->setText(CellSNstr);

    }
    else
    {
        AnaSNstr = QString::number(AnaParas_Ch1->AnaSN);
        ui->AnaSN_lineEdit->setText(AnaSNstr);

        AnaModelstr = QString::number(AnaParas_Ch1->AnaModel);
        ui->AnaModel_lineEdit->setText(AnaModelstr);

        FWRevstr = QString::number(AnaParas_Ch1->FWRev);
        ui->FWRev_lineEdit->setText(FWRevstr);

        CellSNstr = QString::number(AnaParas_Ch1->CellSN);
        ui->CellSN_lineEdit->setText(CellSNstr);
    }


}

//add 6.14-4
void  IDDlg::range_limit_AnaSN(QString)
{
    bool ok;
    long a = ui->AnaSN_lineEdit->text().toLong(&ok);//bool toint
    if(!((a>19990101)&&(a<30000101)))
    {
     on_analyzerSNTip_clicked();
     ui->AnaSN_lineEdit->setText(AnaSNstr);
    }
}
void  IDDlg::range_limit_AnaModel(QString)
{
    bool ok;
    long a = ui->AnaModel_lineEdit->text().toLong(&ok);//bool toint
    if(!((a>=0)&&(a<30000101)))
    {
     on_analyzerserialnumberTip_clicked();
     ui->AnaModel_lineEdit->setText(AnaModelstr);
    }
}
void  IDDlg::range_limit_FWRev(QString)
{
    bool ok;
    long a = ui->FWRev_lineEdit->text().toLong(&ok);//bool toint
    if(!((a>0)&&(a<30000101)))
    {
     on_softwareversionTip_clicked();
     ui->FWRev_lineEdit->setText(FWRevstr);
    }
}
void  IDDlg::range_limit_CellSN(QString)
{
    bool ok;
    long a = ui->CellSN_lineEdit->text().toLong(&ok);//bool toint
    if(!((a>0)&&(a<30000101)))
    {
     on_airchamberSHTip_clicked();
     ui->CellSN_lineEdit->setText(CellSNstr);
    }
}



void IDDlg::on_ok_clicked()
{
    bool ok;
    float AnaSN =ui->AnaSN_lineEdit->text().toLong(&ok);
    float AnaModel =ui->AnaModel_lineEdit->text().toLong(&ok);
    float FWRev =ui->FWRev_lineEdit->text().toLong(&ok);
    float CellSN =ui->CellSN_lineEdit->text().toLong(&ok);
     if(CH_Flag==0)
     {
         AnaParas_Ch0->AnaSN=AnaSN;
         AnaParas_Ch0->AnaModel=AnaModel;
         AnaParas_Ch0->FWRev=FWRev;
         AnaParas_Ch0->CellSN=CellSN;
         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->AnaSN=AnaSN;
         AnaParas_Ch1->AnaModel=AnaModel;
         AnaParas_Ch1->FWRev=FWRev;
         AnaParas_Ch1->CellSN=CellSN;
         files->writefile(1);
     }

}

void IDDlg::on_cancel_clicked()
{
    show_paras();
}
