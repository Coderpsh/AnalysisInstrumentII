#include "screeninclu/demodulationdlg.h"
#include "ui_demodulationdlg.h"

#include <QTime>
#include <QTimer>

#include <QMessageBox>
extern fileoperate *files;
extern  pci *pci0 ;
extern  pci *pci1 ;

demodulationDlg::demodulationDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::demodulationDlg)
{
    ui->setupUi(this);
    //add 6.14-1
    setFocusPolicy(Qt::NoFocus);

    //时间计时器
 //   QTimer *timer = new QTimer(this);
 //   connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
 //   timer->start(1000);
    keyboarddlg=new keyboardDlg;
    setWindowFlags(Qt::FramelessWindowHint);
    ui->back->setFocusPolicy(Qt::NoFocus);
    ui->BandWidth->setFocusPolicy(Qt::NoFocus);
    ui->BandWidth_change->setFocusPolicy(Qt::NoFocus);
    ui->bias2fTip->setFocusPolicy(Qt::NoFocus);
    ui->cancel->setFocusPolicy(Qt::NoFocus);
    ui->Cent2f_change->setFocusPolicy(Qt::NoFocus);
    ui->gain2fTip->setFocusPolicy(Qt::NoFocus);
    ui->Gain2f_change->setFocusPolicy(Qt::NoFocus);
    ui->ok->setFocusPolicy(Qt::NoFocus);
    ui->phase2fTip->setFocusPolicy(Qt::NoFocus);
    ui->Phase2f_change->setFocusPolicy(Qt::NoFocus);

    ui->BandWidth_lineEdit->setFocusPolicy(Qt::NoFocus);
     ui->Cent2f_lineEdit->setFocusPolicy(Qt::NoFocus);
      ui->Gain2f_lineEdit->setFocusPolicy(Qt::NoFocus);
       ui->Phase2f_lineEdit->setFocusPolicy(Qt::NoFocus);


}

//显示时间
void demodulationDlg::showRealTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString txtDateTime=dateTime.toString("yy/MM/dd hh:mm:ss");
    ui->dateTime->setText(txtDateTime);
}



demodulationDlg::~demodulationDlg()
{
    delete ui;
    delete keyboarddlg;
}

void demodulationDlg::on_phase2fTip_clicked()
{
    QMessageBox::information(this,"input","input value(0-360)");
}

void demodulationDlg::on_gain2fTip_clicked()
{
    QMessageBox::information(this,"input","input value(1-1000)");
}

void demodulationDlg::on_bias2fTip_clicked()
{
     QMessageBox::information(this,"input","input value(%):0-100");
}

void demodulationDlg::on_BandWidth_clicked()
{
    QMessageBox::information(this,"input","input value(25-2500HZ)");
}

void demodulationDlg::on_back_clicked()
{
    backCalibrationdlg();
    this->hide();
}

void demodulationDlg::on_Phase2f_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Phase2f_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Phase2f_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Phase(QString)));
}

void demodulationDlg::on_Gain2f_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Gain2f_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
     QObject::connect(ui->Gain2f_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Gain2f(QString)));
}

void demodulationDlg::on_Cent2f_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->Cent2f_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->Cent2f_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_Cent2f(QString)));
}

void demodulationDlg::on_BandWidth_change_clicked()
{
    keyboarddlg->hide();
    QObject::disconnect(keyboarddlg,SIGNAL(getInput(QString)),0,0);
    QObject::connect(keyboarddlg,SIGNAL(getInput(QString)),ui->BandWidth_lineEdit,SLOT(setText(QString)));
    keyboarddlg->show();
    QObject::connect(ui->BandWidth_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(range_limit_BandWidth(QString)));
}

void demodulationDlg::show_paras()
{
    if(CH_Flag==0)  //ch0
    {
        Phasestr = QString::number(AnaParas_Ch0->Phase,10);
        ui->Phase2f_lineEdit->setText(Phasestr);

        Gain2fstr = QString::number(AnaParas_Ch0->Gain2f,'f',2);
        ui->Gain2f_lineEdit->setText(Gain2fstr);

        Cent2fstr = QString::number(AnaParas_Ch0->Cent2f,'f',2);
        ui->Cent2f_lineEdit->setText(Cent2fstr);

        BandWidthstr = QString::number(AnaParas_Ch0->BandWidth,10);
        ui-> BandWidth_lineEdit->setText(BandWidthstr);

    }
    else
    {
        Phasestr = QString::number(AnaParas_Ch1->Phase,10);
        ui->Phase2f_lineEdit->setText(Phasestr);

        Gain2fstr = QString::number(AnaParas_Ch1->Gain2f,'f',2);
        ui->Gain2f_lineEdit->setText(Gain2fstr);

        Cent2fstr = QString::number(AnaParas_Ch1->Cent2f,'f',2);
        ui->Cent2f_lineEdit->setText(Cent2fstr);

        BandWidthstr = QString::number(AnaParas_Ch1->BandWidth,10);
        ui-> BandWidth_lineEdit->setText(BandWidthstr);
    }


}

//add 6.14-4
void demodulationDlg::range_limit_Phase(QString)
{
    bool ok;
    long a = ui->Phase2f_lineEdit->text().toLong(&ok);//bool toint
    if(!((a>=0)&&(a<=360)))
    {
     on_phase2fTip_clicked();

     ui->Phase2f_lineEdit->setText(Phasestr);
    }
}

void demodulationDlg::range_limit_BandWidth(QString)
{
    bool ok;
    long a = ui->BandWidth_lineEdit->text().toLong(&ok);//bool toint
    if(!((a>=25)&&(a<=2500)))
    {
     on_BandWidth_clicked();

     ui->BandWidth_lineEdit->setText(BandWidthstr);
    }
}

void demodulationDlg::range_limit_Gain2f(QString)
{
    bool ok;
    float a = ui->Gain2f_lineEdit->text().toFloat(&ok);//bool toint
    if(!((a>=0)&&(a<=1000)))
    {
     on_gain2fTip_clicked();

     ui->Gain2f_lineEdit->setText(Gain2fstr);
    }
}

void demodulationDlg::range_limit_Cent2f(QString)
{
    bool ok;
    float a = ui->Cent2f_lineEdit->text().toFloat(&ok);//bool toint
    if(!((a>=0)&&(a<=100)))
    {
     on_bias2fTip_clicked();
     ui->Cent2f_lineEdit->setText(Cent2fstr);
    }
}







void demodulationDlg::on_ok_clicked()
{
    bool ok;
    int delay=1000;
    long Phase =ui->Phase2f_lineEdit->text().toLong(&ok);
    long BandWidth =ui->BandWidth_lineEdit->text().toLong(&ok);
    float Gain2f =ui->Gain2f_lineEdit->text().toFloat(&ok);
    float Cent2f =ui->Cent2f_lineEdit->text().toFloat(&ok);
     if(CH_Flag==0)
     {
         AnaParas_Ch0->Phase=Phase;
         AnaParas_Ch0->BandWidth=BandWidth;
         AnaParas_Ch0->Gain2f=Gain2f;
         AnaParas_Ch0->Cent2f=Cent2f;
         files->writefile(0);

         long Gain = (long)Gain2f;
         long Cent = (long)Cent2f;

printf("%d\t",Phase);
printf("%d\t",Gain);
printf("%lf\t",Cent2f);
printf("%d\t",BandWidth);


         pci0->pci_open(0);

         pci0->laser_open(0);//@


         pci0->set_gain(Gain);
         pci0->set_offset(Cent);
         pci0->set_phase(Phase);
         //pci0->set_bandwidth(BandWidth);


         if(AnaParas_Ch0->Ldwork_Flag==1)//@
         {
             pci0->laser_open(1);//@
             printf("Ch0_laser_open(1)\t");
         }
         else
         {
             printf("Ch0_laser_open(0)\t");
         }

         pci0->save2flash();
         pci0->pci_close();

         for(int i=9999;i>1;i--)//#
             for(int j=9999;j>1;j--)
                 ;
         //Try
                  pci0->pci_open(0);
                  pci0->get_all_parameter();//@
                  pci0->pci_close();

                  printf("frequency %ld\n",tfrequency);//@
                  printf("amplitude %ld\t",tamplitude);//@
                  printf("bandwidth %ld\t",tbandwidth);//@
                  printf("scanperiod %ld\t",tscanperiod);//@
                  printf("phase %ld\t",tphase);//@
                  printf("gain %ld\t",tgain);//@
                  printf("c1 %lf\t",tc1);//@
                  printf("c2 %lf\t",tc2);//@
                  printf("nullpoint %ld\n",tnullpoint);//@

         QMessageBox::information(this,"OK","save flash success");



     }
     else
     {
         AnaParas_Ch1->Phase=Phase;
         AnaParas_Ch1->BandWidth=BandWidth;
         AnaParas_Ch1->Gain2f=Gain2f;
         AnaParas_Ch1->Cent2f=Cent2f;
         files->writefile(1);

         long Gain = (long)Gain2f;
         long Cent = (long)Cent2f;

         pci1->pci_open(1);
         pci1->set_gain(Gain);
         pci1->set_offset(Cent);
         pci1->set_phase(Phase);
         //pci1->set_bandwidth(BandWidth);
         pci1->save2flash();
         pci1->pci_close();



         QMessageBox::information(this,"OK","save flash success");


     }



}

void demodulationDlg::on_cancel_clicked()
{
    show_paras();
}
