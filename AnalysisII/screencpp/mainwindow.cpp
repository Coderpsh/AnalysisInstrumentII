#include "screeninclu/mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QTimer>
#include <QDebug>
#include"global.h"
#include"include.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    calibration=new calibrationDlg;
    pic_sheet=new picture_sheetDlg;
    plotterdlg=new plotterDlg;//@
    keyboard=new keyboardDlg;
    logindlg=new LoginDlg;
    logindlg1=new Logindlg1;

    ui->calibration_btn->setFocusPolicy(Qt::NoFocus);//??
    ui->picture_sheetButton->setFocusPolicy(Qt::NoFocus);//@no
    ui->pro_valButton->setFocusPolicy(Qt::NoFocus);
    ui->run_debugButton->setFocusPolicy(Qt::NoFocus);


    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(800,480);

    //时间计时器
   // QTimer *timer = new QTimer(this);
   // connect(timer, SIGNAL(timeout()), this, SLOT(showRealTime()));
   // timer->start(1000);
    connect(calibration,SIGNAL(backMainWindow()),this,SLOT(backMainWindow()));
    connect(logindlg,SIGNAL(backMainWindow()),this,SLOT(backMainWindow()));

    connect(logindlg1,SIGNAL(backMainWindow()),this,SLOT(backMainWindow()));
    connect(logindlg,SIGNAL(tocalibration()),calibration,SLOT(tocalibration()));

    connect(logindlg1,SIGNAL(ChangeToDebug()),this,SLOT(ChangeToDebug()));
    connect(plotterdlg,SIGNAL(backMainWindow()),this,SLOT(backMainWindow()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete calibration;
    delete pic_sheet;
    delete plotterdlg;//@
    delete keyboard;
    delete logindlg;
    delete logindlg1;
}

//显示时间
void MainWindow::showRealTime()
{
    QDateTime date = QDateTime::currentDateTime();
    QTime time = QTime::currentTime();
    QString txtDate = date.toString("yy/MM/dd");
    QString txtTime = time.toString("hh:mm:ss"); // 这儿有各种格式，比如 ("yyyy-MM-dd hh:mm:ss dddd") 等等;
    ui->currentDate->setText(txtDate);
    ui->currentTime->setText(txtTime);
}

void MainWindow::backMainWindow()
{
    this->show();
    this->initWindow();

}

//设置Pro_Val状态
void MainWindow::on_pro_valButton_clicked()
{
    if(CH_Flag==0)
    {
        if(!PV_Flag_Screen)
            PV_Flag_Screen=1;
        else
            PV_Flag_Screen=0;  //val

     if(!PV_Flag_Screen)
        ui->P_VstatusEdit->setText("Val");
     else
        ui->P_VstatusEdit->setText("Pro");

    }
    else
    {
     if(!PV_Flag_Ch1_Screen)
            PV_Flag_Ch1_Screen=1;
      else
            PV_Flag_Ch1_Screen=0;  //val

     if(!PV_Flag_Ch1_Screen)
        ui->P_VstatusEdit_2->setText("Val");
     else
        ui->P_VstatusEdit_2->setText("Pro");

    }
}

//设置Run_Debug状态
void MainWindow::on_run_debugButton_clicked()
{


    if(CH_Flag==0)
    {
        if(!RD_flag)
            RD_flag=1;
        else
            RD_flag=0;

        if(RD_flag==1)
            logindlg1->show();
        else
            Debug_Flag =1;


       if(Debug_Flag)
        ui->R_DstatusEdit->setText("Run");
         else
        ui->R_DstatusEdit->setText("Debug");
    }

    else
    {

        if(!RD_flag_ch1)
            RD_flag_ch1=1;
        else
            RD_flag_ch1=0;

        if(RD_flag_ch1==1)
            logindlg1->show();
        else
            Debug_Flag_Ch1 =1;

          if(Debug_Flag_Ch1)
            ui->R_DstatusEdit_2->setText("Run");
          else
            ui->R_DstatusEdit_2->setText("Debug");
     }

}

//显示图、表页面//go use
void MainWindow::on_picture_sheetButton_clicked()
{
    this->hide();
    //connect(pic_sheet,SIGNAL(backMainWindow()),this,SLOT(backMainWindow()));
    plotterdlg->show();
    if(!PlotData_Flag)
        PlotData_Flag=1;
}

void MainWindow::on_calibration_btn_clicked()
{
    this->hide();
    connect(this,SIGNAL(showch()),calibration,SLOT(showch()));
    showch();
    set_mode(0,1);
    set_mode(1,1);
    logindlg->show();

}

void MainWindow::on_comboBox_activated(const QString &arg1)
{

    int index=ui->comboBox->currentIndex();
     if(index==0)
         CH_Flag=0;
     else
         CH_Flag=1;
}

void MainWindow::result0_show()
{
    QString Tstr = QString::number(Conc_Ch0->T,'f',2);
    QString Pstr = QString::number(Conc_Ch0->P,'f',2);//@@
    QString Statustr = QString("%1").arg(Conc_Ch0->Status,4,16,QLatin1Char('0'));
    QString Concstr;
//
    if(AnaParas_Ch0->ConcUnit==0)//ppm
    {
     if(Conc_Ch0->Conc>999)
          Concstr = QString::number(Conc_Ch0->Conc,'f',2);
     else if(Conc_Ch0->Conc<1)
          Concstr = QString::number(Conc_Ch0->Conc,'f',4);
     else
          Concstr = QString::number(Conc_Ch0->Conc,'f',3);
     }

    if(AnaParas_Ch0->ConcUnit==1)//%
     Concstr = QString::number(Conc_Ch0->Conc,'f',4);//QString Concstr = QString::number(Conc_Ch0->Conc,'g');
//
    ui->concentrationValueEdit->setText(Concstr);
    ui->Tvalue->setText(Tstr);
    ui->Pvalue->setText(Pstr);
    ui->analyerstatus_value->setText(Statustr);

}
void MainWindow::result1_show()//@
{
    //QString Tstr = QString::number(Conc_Ch1->T,'f',1);
    //QString Pstr = QString::number(Conc_Ch1->P,'f',2);
    //QString Statustr = QString("%1").arg(Conc_Ch1->Status,4,16,QLatin1Char('0'));
    QString Concstr;
//
    if(AnaParas_Ch1->ConcUnit==0)//ppm
    {
     if(Conc_Ch1->Conc>999)
          Concstr = QString::number(Conc_Ch1->Conc,'f',2);
     else if(Conc_Ch1->Conc<1)
          Concstr = QString::number(Conc_Ch1->Conc,'f',4);
     else
          Concstr = QString::number(Conc_Ch1->Conc,'f',3);
     }

    if(AnaParas_Ch1->ConcUnit==1)//%
     Concstr = QString::number(Conc_Ch1->Conc,'f',4);//QString Concstr = QString::number(Conc_Ch1->Conc,'g');
//
    ui->concentrationValueEdit_2->setText(Concstr);
    //ui->Tvalue->setText(Tstr);
    //ui->Pvalue->setText(Pstr);
    //ui->analyerstatus_value->setText(Statustr);
}

void MainWindow::initWindow()
{
    ui->Tunit->setText("C");
    if(PV_Flag_Screen)
        ui->P_VstatusEdit->setText("Pro");
    else
        ui->P_VstatusEdit->setText("Val");

    if(PV_Flag_Ch1_Screen)
        ui->P_VstatusEdit_2->setText("Pro");
    else
        ui->P_VstatusEdit_2->setText("Val");

    if(Debug_Flag)
       ui->R_DstatusEdit->setText("Run");
    else
       ui->R_DstatusEdit->setText("Debug");
    if(Debug_Flag_Ch1)
      ui->R_DstatusEdit_2->setText("Run");
    else
      ui->R_DstatusEdit_2->setText("Debug");

    if(AnaParas_Ch0->Punit==1)
        ui->Punit->setText("Kpa");
    else
        ui->Punit->setText("mbar");

    if(AnaParas_Ch0->ConcUnit==1)
       ui->concunit->setText("%");
    else
       ui->concunit->setText("ppm");

    if(AnaParas_Ch1->ConcUnit==1)
       ui->concunit_2->setText("%");
    else
       ui->concunit_2->setText("ppm");

    if(AnaParas_Ch0->Analyte==0)
        ui->ch1_air->setText("H2O");
    if(AnaParas_Ch0->Analyte==1)
        ui->ch1_air->setText("HCl");
    if(AnaParas_Ch0->Analyte==2)
        ui->ch1_air->setText("H2S");
    if(AnaParas_Ch0->Analyte==3)
        ui->ch1_air->setText("CO2");
    if(AnaParas_Ch0->Analyte==4)
        ui->ch1_air->setText("CO");
    if(AnaParas_Ch0->Analyte==5)
        ui->ch1_air->setText("CH4");
    if(AnaParas_Ch0->Analyte==6)
        ui->ch1_air->setText("C2H2");


    if(AnaParas_Ch1->Analyte==0)
        ui->ch2_air->setText("H2O");
    if(AnaParas_Ch1->Analyte==1)
        ui->ch2_air->setText("HCl");
    if(AnaParas_Ch1->Analyte==2)
        ui->ch2_air->setText("H2S");
    if(AnaParas_Ch1->Analyte==3)
        ui->ch2_air->setText("CO2");
    if(AnaParas_Ch1->Analyte==4)
        ui->ch2_air->setText("CO");
    if(AnaParas_Ch1->Analyte==5)
        ui->ch2_air->setText("CH4");
    if(AnaParas_Ch1->Analyte==6)
        ui->ch2_air->setText("C2H2");

}

void MainWindow::ChangeToDebug()
{
    initWindow();
}

void MainWindow::plotter_start()
{
   plotterdlg->drawing_all();
}
