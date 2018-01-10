#include "screeninclu/verifydlg2.h"
#include "ui_verifydlg2.h"
#include <QMessageBox>
//add 6.14-5
extern fileoperate *files;


verifyDlg2::verifyDlg2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::verifyDlg2)
{
    ui->setupUi(this);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);
    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->checkingcorrectionTip->setFocusPolicy(Qt::NoFocus);
    ui->correctionfactorTip->setFocusPolicy(Qt::NoFocus);
    ui->offsetcorrectionTip->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);

    ui->SOffset_change->setFocusPolicy(Qt::NoFocus);
    ui->SSlope_change->setFocusPolicy(Qt::NoFocus);
    ui->VCorrection_change->setFocusPolicy(Qt::NoFocus);

    //add 6.14-2
   ui->VCorrection_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->SSlope_lineEdit->setFocusPolicy(Qt::NoFocus);
   ui->SOffset_lineEdit->setFocusPolicy(Qt::NoFocus);
}

verifyDlg2::~verifyDlg2()
{
    delete ui;
    delete keyboarddlg;
}


void verifyDlg2::on_VCorrection_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->VCorrection_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->VCorrection_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_VCorrection(QString)));

}

void verifyDlg2::on_checkingcorrectionTip_clicked()
{
     QMessageBox::information(this,"input","input value(0:forbidden  1:open");
}

void verifyDlg2::on_SSlope_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->SSlope_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->SSlope_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_SSlope(QString)));

}

void verifyDlg2::on_SOffset_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->SOffset_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->SOffset_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_SOffset(QString)));

}

void verifyDlg2::on_correctionfactorTip_clicked()
{
    QMessageBox::information(this,"input","input value");
}

void verifyDlg2::on_offsetcorrectionTip_clicked()
{
    QMessageBox::information(this,"input","input value");
}

void verifyDlg2::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}


void verifyDlg2::backtothis()
{
    this->show();
    this->show_paras();
}


void verifyDlg2::on_pageUp_clicked()
{
    this->hide();
    up();
}

void verifyDlg2::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        VCorrectionstr = QString::number(AnaParas_Ch0->VCorrection,10);//bool,int,long
        ui->VCorrection_lineEdit->setText(VCorrectionstr);

        SSlopestr =  QString::number(AnaParas_Ch0->SSlope,'f',2);
        ui->SSlope_lineEdit->setText(SSlopestr);

        SOffsetstr =  QString::number((int)AnaParas_Ch0->SOffset,'f',2);
        ui->SOffset_lineEdit->setText(SOffsetstr);

    }
    else
    {
        VCorrectionstr = QString::number(AnaParas_Ch1->VCorrection,10);//bool,int,long
        ui->VCorrection_lineEdit->setText(VCorrectionstr);

        SSlopestr =  QString::number(AnaParas_Ch1->SSlope,'f',2);
        ui->SSlope_lineEdit->setText(SSlopestr);

        SOffsetstr =  QString::number((int)AnaParas_Ch1->SOffset,'f',2);
        ui->SOffset_lineEdit->setText(SOffsetstr);

    }

}


void verifyDlg2::range_limit_VCorrection(QString)
{
    bool ok;
    int a = ui->VCorrection_lineEdit->text().toInt(&ok,10);//bool toint
    if(!((a>=0)&&(a<=1)))
    {
     on_checkingcorrectionTip_clicked();

     ui->VCorrection_lineEdit->setText(VCorrectionstr);
    }
}
void verifyDlg2::range_limit_SSlope(QString)
{
    bool ok;
    float a =ui->SSlope_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100)))
    {
       on_correctionfactorTip_clicked();

      ui->SSlope_lineEdit->setText(SSlopestr);
    }

}

void verifyDlg2::range_limit_SOffset(QString)
{
    bool ok;
    float a =ui->SOffset_lineEdit->text().toFloat(&ok); //
    if(!((a>=0)&&(a<=100)))
    {
        on_offsetcorrectionTip_clicked();

      ui->SOffset_lineEdit->setText(SOffsetstr);
    }
}

void verifyDlg2::on_ok_clicked()

{
    bool ok;
    int VCorrection = ui->VCorrection_lineEdit->text().toInt(&ok);
    float SSlope =ui->SSlope_lineEdit->text().toFloat(&ok);
    float SOffset =ui->SOffset_lineEdit->text().toFloat(&ok);

     if(CH_Flag==0)
     {
         AnaParas_Ch0->VCorrection=VCorrection;
         AnaParas_Ch0->SSlope=SSlope;
         AnaParas_Ch0->SOffset=SOffset;


         files->writefile(0);
     }
     else
     {
         AnaParas_Ch1->VCorrection=VCorrection;
         AnaParas_Ch1->SSlope=SSlope;
         AnaParas_Ch1->SOffset=SOffset;

         files->writefile(1);
     }

}

void verifyDlg2::on_cancel_clicked()
{
    show_paras();
}
