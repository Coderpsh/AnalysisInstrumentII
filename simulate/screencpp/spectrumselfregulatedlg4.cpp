#include "screeninclu/spectrumselfregulatedlg4.h"
#include "ui_spectrumselfregulatedlg4.h"
#include <QMessageBox>

//add 6.14-5
extern fileoperate *files;

spectrumselfregulateDlg4::spectrumselfregulateDlg4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::spectrumselfregulateDlg4)
{
    ui->setupUi(this);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);
    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);

    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->findpeakfittingwindowTip->setFocusPolicy(Qt::NoFocus);
    ui->findpeakmaximumheightTip->setFocusPolicy(Qt::NoFocus);
    ui->findpeakminimumheightTip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageUp->setFocusPolicy(Qt::NoFocus);
    ui->PkTrkHgtMax_change->setFocusPolicy(Qt::NoFocus);
    ui->PkTrkHgtMin_change->setFocusPolicy(Qt::NoFocus);
    ui->PkWdith_change->setFocusPolicy(Qt::NoFocus);

    //add 6.14-2
   ui->PkTrkHgtMin_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->PkTrkHgtMax_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->PkWdith_lineEdit->setFocusPolicy(Qt::NoFocus);

}

spectrumselfregulateDlg4::~spectrumselfregulateDlg4()
{
    delete ui;
    delete keyboarddlg;
}

void spectrumselfregulateDlg4::on_PkTrkHgtMin_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkTrkHgtMin_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PkTrkHgtMin_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkTrkHgtMin(QString)));

}

void spectrumselfregulateDlg4::on_PkTrkHgtMax_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkTrkHgtMax_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PkTrkHgtMax_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkTrkHgtMax(QString)));

}

void spectrumselfregulateDlg4::on_PkWdith_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->PkWdith_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->PkWdith_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_PkWdith(QString)));

}

void spectrumselfregulateDlg4::on_findpeakminimumheightTip_clicked()
{
     QMessageBox::information(this,"input","input value(0-4000)");
}

void spectrumselfregulateDlg4::on_findpeakmaximumheightTip_clicked()
{
    QMessageBox::information(this,"input","input value(0-4000)");
}

void spectrumselfregulateDlg4::on_findpeakfittingwindowTip_clicked()
{
     QMessageBox::information(this,"input","input value(0:close   >0: +/- peak)");
}

void spectrumselfregulateDlg4::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void spectrumselfregulateDlg4::on_pageUp_clicked()
{
    this->hide();
    up();
}
void spectrumselfregulateDlg4::backtothis()
{
    this->show();
    this->show_paras();

}


void spectrumselfregulateDlg4::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        PkTrkHgtMinstr = QString::number(AnaParas_Ch0->PkTrkHgtMin,'f',2);//bool,int,long
        ui->PkTrkHgtMin_lineEdit->setText(PkTrkHgtMinstr);

        PkTrkHgtMaxstr =  QString::number(AnaParas_Ch0->PkTrkHgtMax,'f',2);
        ui->PkTrkHgtMax_lineEdit->setText(PkTrkHgtMaxstr);

        PkWdithstr =  QString::number((int)AnaParas_Ch0->PkWdith,'f',2);
        ui->PkWdith_lineEdit->setText(PkWdithstr);

    }
    else
    {
        PkTrkHgtMinstr = QString::number(AnaParas_Ch1->PkTrkHgtMin,'f',2);//bool,int,long
        ui->PkTrkHgtMin_lineEdit->setText(PkTrkHgtMinstr);

        PkTrkHgtMaxstr =  QString::number(AnaParas_Ch1->PkTrkHgtMax,'f',2);
        ui->PkTrkHgtMax_lineEdit->setText(PkTrkHgtMaxstr);

        PkWdithstr =  QString::number((int)AnaParas_Ch1->PkWdith,'f',2);
        ui->PkWdith_lineEdit->setText(PkWdithstr);
    }

}



void spectrumselfregulateDlg4::range_limit_PkTrkHgtMin(QString)
{
    bool ok;
    float a = ui->PkTrkHgtMin_lineEdit->text().toFloat(&ok);
    if(!((a>0)&&(a<400000)))
    {
     on_findpeakminimumheightTip_clicked();
     ui->PkTrkHgtMin_lineEdit->setText(PkTrkHgtMinstr);
    }
}
void spectrumselfregulateDlg4::range_limit_PkTrkHgtMax(QString)
{
    bool ok;
    float a =ui->PkTrkHgtMax_lineEdit->text().toFloat(&ok);
    if(!((a>0)&&(a<400000)))
    {
     on_findpeakmaximumheightTip_clicked();

      ui->PkTrkHgtMax_lineEdit->setText(PkTrkHgtMaxstr);
    }

}

void spectrumselfregulateDlg4::range_limit_PkWdith(QString)
{
    bool ok;
    float a =ui->PkWdith_lineEdit->text().toFloat(&ok);
    if(!((a>0)))
    {
      on_findpeakfittingwindowTip_clicked();

      ui->PkWdith_lineEdit->setText(PkWdithstr);
    }
}

void spectrumselfregulateDlg4::on_ok_clicked()
{
    bool ok;
    float PkTrkHgtMin = ui->PkTrkHgtMin_lineEdit->text().toFloat(&ok);
    float PkTrkHgtMax =ui->PkTrkHgtMax_lineEdit->text().toFloat(&ok);

    float PkWdith =ui->PkWdith_lineEdit->text().toFloat(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->PkTrkHgtMin=PkTrkHgtMin;
         AnaParas_Ch0->PkTrkHgtMax=PkTrkHgtMax;
         AnaParas_Ch0->PkWdith=PkWdith;
         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->PkTrkHgtMin=PkTrkHgtMin;
         AnaParas_Ch1->PkTrkHgtMax=PkTrkHgtMax;
         AnaParas_Ch1->PkWdith=PkWdith;
         files->writefile(1);
     }

}

void spectrumselfregulateDlg4::on_cancel_clicked()
{
    show_paras();
}
