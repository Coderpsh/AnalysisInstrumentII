#include "screeninclu/lddlg.h"
#include "ui_lddlg.h"

#include <QTime>
#include <QTimer>

#include <QMessageBox>
//add 6.14-5
extern fileoperate *files;
extern  pci *pci0 ;
extern  pci *pci1 ;

LDDlg::LDDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LDDlg)
{
    ui->setupUi(this);
    //时间计时器
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
//    timer->start(1000);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);
    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->currentstartingpointTip->setFocusPolicy(Qt::NoFocus);
    ui->currenttuningTip->setFocusPolicy(Qt::NoFocus);
    ui->IRange_change->setFocusPolicy(Qt::NoFocus);
    ui->IStart_change->setFocusPolicy(Qt::NoFocus);
    ui->Ituning_change->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->pageDown->setFocusPolicy(Qt::NoFocus);
    ui->scanrangeTip->setFocusPolicy(Qt::NoFocus);
    ui->ScanTime_change->setFocusPolicy(Qt::NoFocus);
    ui->sweeptimeTip->setFocusPolicy(Qt::NoFocus);

    //add 6.14-2
    ui->IStart_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->IRange_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->Ituning_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->ScanTime_lineEdit->setFocusPolicy(Qt::NoFocus);
}


LDDlg::~LDDlg()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void LDDlg::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime_2->setText(txtDateTime);
}

void LDDlg::on_currentstartingpointTip_clicked()
{
     QMessageBox::information(this,"input","input value(mA)0-200");
}

void LDDlg::on_scanrangeTip_clicked()
{
    QMessageBox::information(this,"input","input value(0-200)");
}

void LDDlg::on_currenttuningTip_clicked()
{
    QMessageBox::information(this,"input","input value(mA/Cnt 0-1)");
}


void LDDlg::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void LDDlg::on_pageDown_clicked()
{
    this->hide();
    down();
}

void LDDlg::backtothis()
{
    this->show();
    this->show_paras();
}

void LDDlg::on_sweeptimeTip_clicked()
{
   QMessageBox::information(this,"input","input value(ms) 100-1000");
}




void LDDlg::on_IStart_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->IStart_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->IStart_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_IStart(QString)));

}

void LDDlg::on_IRange_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->IRange_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->IRange_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_IRange(QString)));

}

void LDDlg::on_Ituning_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Ituning_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Ituning_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Ituning(QString)));

}

void LDDlg::on_ScanTime_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->ScanTime_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->ScanTime_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_ScanTime(QString)));

}

void LDDlg::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        IStartstr = QString::number(AnaParas_Ch0->IStart,'f',2);//bool,int,long
        ui->IStart_lineEdit->setText(IStartstr);

        IRangestr =  QString::number(AnaParas_Ch0->IRange,'f',2);
        ui->IRange_lineEdit->setText(IRangestr);

        Ituningstr =  QString::number(AnaParas_Ch0->Ituning,'g');
        ui->Ituning_lineEdit->setText(Ituningstr);

        ScanTimestr =  QString::number(AnaParas_Ch0->ScanTime,10);//float ,double
        ui->ScanTime_lineEdit->setText(ScanTimestr);

    }
    else
    {
        IStartstr = QString::number(AnaParas_Ch1->IStart,'f',2);//bool,int,long
        ui->IStart_lineEdit->setText(IStartstr);

        IRangestr =  QString::number(AnaParas_Ch1->IRange,'f',2);
        ui->IRange_lineEdit->setText(IRangestr);

        Ituningstr =  QString::number(AnaParas_Ch1->Ituning,'g');
        ui->Ituning_lineEdit->setText(Ituningstr);

        ScanTimestr =  QString::number(AnaParas_Ch1->ScanTime,10);//float ,double
        ui->ScanTime_lineEdit->setText(ScanTimestr);
    }

}


//add 6.14-4
void LDDlg::range_limit_IStart(QString)
{
    bool ok;
    float a = ui->IStart_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=200)))
    {
     on_currentstartingpointTip_clicked();

     ui->IStart_lineEdit->setText(IStartstr);
    }
}
void LDDlg::range_limit_IRange(QString)
{
    bool ok;
    float a =ui->IRange_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=200)))
    {
      on_scanrangeTip_clicked();
      ui->IRange_lineEdit->setText(IRangestr);
    }

}

void LDDlg::range_limit_Ituning(QString)
{
    bool ok;
    float a =ui->Ituning_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=1)))
    {
     on_currenttuningTip_clicked();

      ui->Ituning_lineEdit->setText(Ituningstr);
    }
}

void LDDlg::range_limit_ScanTime(QString)
{
    bool ok;
    long a =ui->ScanTime_lineEdit->text().toLong(&ok);
    if(!((a>=100)&&(a<=10000)))
    {
      on_sweeptimeTip_clicked();
      ui->ScanTime_lineEdit->setText(ScanTimestr);
    }
}
void LDDlg::on_ok_clicked()
{
   bool ok;
   float IStart =ui->IStart_lineEdit->text().toFloat(&ok);
   float IRange =ui->IRange_lineEdit->text().toFloat(&ok);
   float Ituning =ui->Ituning_lineEdit->text().toFloat(&ok);
   long ScanTime =ui->ScanTime_lineEdit->text().toLong(&ok);
    if(CH_Flag==0)
    {
        AnaParas_Ch0->IStart=IStart;
        AnaParas_Ch0->IRange=IRange;
        AnaParas_Ch0->Ituning=Ituning;
        AnaParas_Ch0->ScanTime=ScanTime;
        files->writefile(0);
        float c1 = IStart /2.0;
        float c2 = IRange /2.0;
        int nullpoint = AnaParas_Ch0->NullWidth;
        pci0->pci_open(0);

        pci0->laser_open(0);//@

        pci0->set_laserscan(c1,c2,nullpoint);
        pci0->set_scanperiod(ScanTime);
        //pci0->save2flash();

        if(AnaParas_Ch0->Ldwork_Flag==1)//@
        pci0->laser_open(1);//@

        pci0->save2flash();//@
        pci0->pci_close();

        QMessageBox::information(this,"OK","save flash success");

    }
    else
    {
        AnaParas_Ch1->IStart=IStart;
        AnaParas_Ch1->IRange=IRange;
        AnaParas_Ch1->Ituning=Ituning;
        AnaParas_Ch1->ScanTime=ScanTime;
        files->writefile(1);
        float c1 = IStart /2.0;
        float c2 = IRange /2.0;
        int nullpoint = AnaParas_Ch1->NullWidth;
        pci1->pci_open(1);

        pci1->set_laserscan(c1,c2,nullpoint);
        pci1->set_scanperiod(ScanTime);
        pci1->save2flash();
        pci1->pci_close();

       QMessageBox::information(this,"OK","save flash success");
    }










}

void LDDlg::on_cancel_clicked()
{
    show_paras();
}
