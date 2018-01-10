#include "screeninclu/lddlg2.h"
#include "ui_lddlg2.h"

#include <QTime>
#include <QTimer>

#include <QMessageBox>

//add 6.14-5
extern fileoperate *files;
extern  pci *pci0 ;
extern  pci *pci1 ;

LDDlg2::LDDlg2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LDDlg2)
{
    ui->setupUi(this);
    //setFocusPolicy(Qt::NoFocus);//@
    //时间计时器
    //QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
    //timer->start(1000);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);
    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);
    ui->averageoforiginalspectrumTip->setFocusPolicy(Qt::NoFocus);
    ui->back->setFocusPolicy(Qt::NoFocus);//
    ui->cancel->setFocusPolicy(Qt::NoFocus);//
    ui->laserclosingtimeTip->setFocusPolicy(Qt::NoFocus);
    ui->ModFreq_change->setFocusPolicy(Qt::NoFocus);
    ui->ModRange_change->setFocusPolicy(Qt::NoFocus);
    ui->modulationfrequencyTip->setFocusPolicy(Qt::NoFocus);
    ui->modulationrangeTip->setFocusPolicy(Qt::NoFocus);
    ui->NullWidth_change->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);//
    ui->pageUp->setFocusPolicy(Qt::NoFocus);
    ui->SpectrAvg_change->setFocusPolicy(Qt::NoFocus);

    //add 6.14-2
    ui->ModRange_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->SpectrAvg_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->NullWidth_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->ModFreq_lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->comboBox->setFocusPolicy(Qt::NoFocus);



}

LDDlg2::~LDDlg2()
{
    delete ui;
    delete keyboarddlg;
}

//显示时间
void LDDlg2::showRealTime()//
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}

void LDDlg2::backtothis()//
{
    this->show();
    this->show_paras();

}

void LDDlg2::on_modulationrangeTip_clicked()//
{
   QMessageBox::information(this,"input","input value(0-100)");
}

void LDDlg2::on_averageoforiginalspectrumTip_clicked()
{
   QMessageBox::information(this,"input","input value(2-100)");
}

void LDDlg2::on_laserclosingtimeTip_clicked()
{
    QMessageBox::information(this,"input","input value(60-90)");
}

void LDDlg2::on_modulationfrequencyTip_clicked()
{
     QMessageBox::information(this,"input","input value(31.2-31.6)");
}

void LDDlg2::on_back_clicked()//Back button
{
    backCalibrationdlg();
    this->hide();
}

void LDDlg2::on_pageUp_clicked()//Prev.Page button
{

    this->hide();
    up();
}

void LDDlg2::on_ModRange_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->ModRange_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->ModRange_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_ModRange(QString)));

}

void LDDlg2::on_SpectrAvg_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->SpectrAvg_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->SpectrAvg_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_SpectrAvg(QString)));

}

void LDDlg2::on_NullWidth_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->NullWidth_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->NullWidth_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_NullWidth(QString)));

}

void LDDlg2::on_ModFreq_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->ModFreq_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->ModFreq_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_ModFreq(QString)));

}

void LDDlg2::show_paras() //add 6.14-3
{

    if(CH_Flag==0)  //ch0
    {
        ModRangestr = QString::number(AnaParas_Ch0->ModRange,'f',2);//bool,int,long
        ui->ModRange_lineEdit->setText(ModRangestr);

        SpectrAvgstr =  QString::number(AnaParas_Ch0->SpectrAvg,10);
        ui->SpectrAvg_lineEdit->setText(SpectrAvgstr);

        NullWidthstr =  QString::number((int)AnaParas_Ch0->NullWidth,10);
        ui->NullWidth_lineEdit->setText(NullWidthstr);

        ModFreqstr =  QString::number(AnaParas_Ch0->ModFreq,'f',2);//float ,double
        ui->ModFreq_lineEdit->setText(ModFreqstr);

        if(AnaParas_Ch0->Ldwork_Flag==0)
        {
           ui->comboBox->setCurrentIndex(0);
        }
        else

        {
            ui->comboBox->setCurrentIndex(1);
        }



    }
    else
    {
        ModRangestr = QString::number(AnaParas_Ch1->ModRange,'f',2);//bool,int,long
        ui->ModRange_lineEdit->setText(ModRangestr);

        SpectrAvgstr =  QString::number(AnaParas_Ch1->SpectrAvg,10);
        ui->SpectrAvg_lineEdit->setText(SpectrAvgstr);

        NullWidthstr =  QString::number((int)AnaParas_Ch1->NullWidth,10);
        ui->NullWidth_lineEdit->setText(NullWidthstr);

        ModFreqstr =  QString::number(AnaParas_Ch1->ModFreq,'f',2);//float ,double
        ui->ModFreq_lineEdit->setText(ModFreqstr);

        if(AnaParas_Ch1->Ldwork_Flag==0)
        {
           ui->comboBox->setCurrentIndex(0);

        }
        else

        {
          ui->comboBox->setCurrentIndex(1);
        }


    }

}

//add 6.14-4
void LDDlg2::range_limit_ModRange(QString)//
{
    bool ok;
    float a = ui->ModRange_lineEdit->text().toFloat(&ok);
    if(!((a>=0)&&(a<=100)))
    {
     on_modulationrangeTip_clicked();

     ui->ModRange_lineEdit->setText(ModRangestr);
    }
}
void LDDlg2::range_limit_SpectrAvg(QString)
{
    bool ok;
    int a = ui->SpectrAvg_lineEdit->text().toInt(&ok,10);
    if(!((a>=2)&&(a<=400)))
    {
     on_averageoforiginalspectrumTip_clicked();

     ui->SpectrAvg_lineEdit->setText(SpectrAvgstr);
    }
}
void LDDlg2::range_limit_NullWidth(QString)
{
    bool ok;
    int a = ui->NullWidth_lineEdit->text().toInt(&ok,10);
    if(!((a>=60)&&(a<=90)))
    {
     on_laserclosingtimeTip_clicked();

     ui->NullWidth_lineEdit->setText(NullWidthstr);
    }
}
void LDDlg2::range_limit_ModFreq(QString)
{
    bool ok;
    float a = ui->ModFreq_lineEdit->text().toFloat(&ok);
    if(!((a>=31.2)&&(a<=31.6)))
    {
     on_modulationrangeTip_clicked();

     ui->ModFreq_lineEdit->setText(ModFreqstr);
    }
}

void LDDlg2::on_ok_clicked()
{
    bool ok;
    bool  Ldwork_Flag=ui->comboBox->currentIndex();//from  Ldwork
    float ModRange = ui->ModRange_lineEdit->text().toFloat(&ok);
    int SpectrAvg =ui->SpectrAvg_lineEdit->text().toInt(&ok);
    int NullWidth =ui->NullWidth_lineEdit->text().toInt(&ok);
    float ModFreq =ui->ModFreq_lineEdit->text().toFloat(&ok);



     if(CH_Flag==0)
     {
         AnaParas_Ch0->Ldwork_Flag=Ldwork_Flag;
         AnaParas_Ch0->ModRange=ModRange;
         AnaParas_Ch0->SpectrAvg=SpectrAvg;
         AnaParas_Ch0->NullWidth=NullWidth;
         AnaParas_Ch0->ModFreq=ModFreq;
         files->writefile(0);


         float c1 = AnaParas_Ch0->IStart /2.0;
         float c2 = AnaParas_Ch0->IRange/2.0;
         int null = NullWidth;
         long frequency = (long)(ModFreq*1000);
         pci0->pci_open(0);
         /*
         if(!Ldwork_Flag)
         {
             //close
             pci0->laser_open(0);
         }
         else
         {
            pci0->laser_open(1);

         }
         */

         pci0->laser_open(0);//@

         pci0->set_laserscan(c1,c2,null);//can changed
         pci0->set_amplitude((long)ModRange);//can changed
         pci0->set_frequency(frequency);//about can changed
         //pci0->save2flash();
         if(AnaParas_Ch0->Ldwork_Flag==1)//@
         {
             pci0->laser_open(1);//@
             printf("Ch0_laser_open(1)\t");
         }
         else
         {
             printf("Ch0_laser_open(0)\t");
         }
         pci0->save2flash();//@
         pci0->pci_close();
         //pci0->get_all_parameter();
         QMessageBox::information(this,"OK","save flash success");
     }
     else
     {
         AnaParas_Ch1->Ldwork_Flag=Ldwork_Flag;
         AnaParas_Ch1->ModRange=ModRange;
         AnaParas_Ch1->SpectrAvg=SpectrAvg;
         AnaParas_Ch1->NullWidth=NullWidth;
         AnaParas_Ch1->ModFreq=ModFreq;
         files->writefile(1);


         float c1 = AnaParas_Ch1->IStart/2.0;
         float c2 = AnaParas_Ch1->IRange/2.0;
         int null = NullWidth;
         long frequency = (long)(ModFreq*1000);


         pci1->pci_open(0);
         /*
         if(!Ldwork_Flag)
         {
             pci1->laser_open(0);
         }
         else
         {
            pci1->laser_open(1);
         }
         */
         pci1->laser_open(0);//@
         pci1->set_laserscan(c1,c2,null);
         pci1->set_amplitude((long)ModRange);
         pci1->set_frequency(frequency);
         //pci1->save2flash();
         if(AnaParas_Ch1->Ldwork_Flag==1)//@
         {
             pci1->laser_open(1);//@
             printf("Ch1_laser_open(1)\t");
         }
         else
         {
             printf("Ch1_laser_open(0)\t");
         }
         pci1->save2flash();//@
         pci1->pci_close();

         QMessageBox::information(this,"OK","save flash success");

     }
}

void LDDlg2::on_cancel_clicked()
{
    show_paras();
}


