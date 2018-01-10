#include "screeninclu/plotterdlg.h"
#include "ui_plotterdlg.h"
#include "global.h"

#include<QTime>
#include<QTimer>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>


plotterDlg::plotterDlg(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::plotterDlg)
{
    ui->setupUi(this);

    setFocusPolicy(Qt::NoFocus);
    setWindowFlags(Qt::FramelessWindowHint);

    curve1=new QwtPlotCurve();//实例化另一条线

    curve2=new QwtPlotCurve();

    curve3=new QwtPlotCurve();

    curve4=new QwtPlotCurve();

    curve5=new QwtPlotCurve();

}

plotterDlg::~plotterDlg()
{
    delete ui;
    delete curve1;
    delete curve2;
    delete curve3;
    delete curve4;
    delete curve5;
}

void plotterDlg::on_Plot_CH_activated(const QString &arg1)
{
    int index=ui->Plot_CH->currentIndex();
     if(index==0)
         Ploat_Channel=0;
     else
         Ploat_Channel=1;
}
//绘制曲线标志
void plotterDlg::on_DCavg_btn_clicked()
{
    if(!DCavg_drawing_Flag)
        DCavg_drawing_Flag=1;
    else
       DCavg_drawing_Flag=0;

}
void plotterDlg::on_Raw2f_btn_clicked()
{
    if(!Raw2f_drawing_Flag)
        Raw2f_drawing_Flag=1;
    else
        Raw2f_drawing_Flag=0;
}
void plotterDlg::on_F2avg_btn_clicked()
{
    if(!F2avg_drawing_Flag)
        F2avg_drawing_Flag=1;
    else
        F2avg_drawing_Flag=0;
}
void plotterDlg::on_PR_btn_clicked()
{
    if(!PR_drawing_Flag)
        PR_drawing_Flag=1;
    else
        PR_drawing_Flag=0;
}
void plotterDlg::on_Fitted_btn_clicked()
{
    if(!Fitted_drawing_Flag)
        Fitted_drawing_Flag=1;
    else
        Fitted_drawing_Flag=0;
}
void plotterDlg::concentration0_show()//@
{
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
     Concstr = QString::number(Conc_Ch0->Conc,'f',4);//QString Concstr = QString::number(Conc_Ch1->Conc,'g');
//
    ui->concentrationPloatValueEdit->setText(Concstr);

}
void plotterDlg::concentration1_show()//@
{
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
    ui->concentrationPloatValueEdit->setText(Concstr);

}

//描点
void plotterDlg::graph1()
{

    double time[100];
    double arr[1000];

    ui->plot->setAxisScale(QwtPlot::xBottom, 0, 1000);
    ui->plot->setAxisScale(QwtPlot::yLeft, -5000, -15000);

    for(int i=0;i<1000;i++)
    {
       time[i]=i;
    }

    for(int i=0; i<1000; i++)
    {
       //brr[i]=int (DCavg[i])%10;
       arr[i]=(double)DCavg[i];//(double)DCavg[i]/230;

    }

      //描点画图
      QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
      QBrush( Qt::yellow ), QPen( Qt::red, 1 ), QSize( 2, 2) );//设置样本点的颜色、大小
      curve1->setSymbol( symbol );                             //添加样本点形状

      curve1->setSamples(time,arr,1000);
      curve1->attach(ui->plot);
      ui->plot->replot();
}

//over here
void plotterDlg::do_showplotterdlg()
{
  this->show();
}

void plotterDlg::drawing_all()//画图
{
  if(Ploat_Channel==0)
   {
    //DCavg_drawing_Flag
    if(DCavg_drawing_Flag)
    {
      concentration0_show();//Con
      curve1->detach();
      ui->plot->replot();

      double time[1000];
      double arr[1000];
      ui->plot->setAxisScale(QwtPlot::xBottom, 0, 1000);//@ 设置坐标范围0：100
      ui->plot->setAxisScale(QwtPlot::yLeft, -5000, 15000);//-360, -200);
      for(int i=0;i<1000;i++)
      {
        time[i]=i;
        arr[i]=(double)DCavg[i];
      }
      curve1->setPen(Qt::yellow,2);//设置画笔

      curve1->setSamples(time,arr,1000);//@ x y
      curve1->attach(ui->plot);
      ui->plot->replot();
    }
   else
     {
        curve1->detach();
        ui->plot->replot();
     }

     //Raw2f_drawing_Flag
     if(Raw2f_drawing_Flag)
      {
        curve2->detach();
        ui->plot->replot();

        double time[1000];
        double arr[1000];
        ui->plot->setAxisScale(QwtPlot::xBottom, 0, 1000);//@ 设置坐标范围0：100
        ui->plot->setAxisScale(QwtPlot::yLeft, -5000, 15000);//-360, -200);
        for(int i=0;i<1000;i++)
        {
          time[i]=i;
          arr[i]=(double)Raw_F2avg[i];
        }

        curve2->setPen(Qt::blue,2);
        curve2->setSamples(time,arr,1000);//@ x y
        curve2->attach(ui->plot);
        ui->plot->replot();
      }
      else
       {
         curve2->detach();
         ui->plot->replot();
       }

        //F2avg_drawing_Flag
         if(F2avg_drawing_Flag)
          {
            curve3->detach();
            ui->plot->replot();

            double time[1000];
            double arr[1000];
            ui->plot->setAxisScale(QwtPlot::xBottom, 0, 1000);//@ 设置坐标范围0：100
            ui->plot->setAxisScale(QwtPlot::yLeft, -5000, 15000);//-360, -200);
            for(int i=0;i<1000;i++)
            {
              time[i]=i;
              arr[i]=(double)Spectrum[i];
            }

            curve3->setPen(Qt::green,2);
            curve3->setSamples(time,arr,1000);//@ x y
            curve3->attach(ui->plot);
            ui->plot->replot();
          }
          else
           {
             curve3->detach();
             ui->plot->replot();
           }

          //Fitted_drawing_Flag
          if(Fitted_drawing_Flag)
            {
              curve4->detach();
              ui->plot->replot();

              double time[1000];
              double arr[1000];
              ui->plot->setAxisScale(QwtPlot::xBottom, 0, 1000);//@ 设置坐标范围0：100
              ui->plot->setAxisScale(QwtPlot::yLeft, -5000, 15000);//-360, -200);
              for(int i=0;i<1000;i++)
              {
                time[i]=i;
                arr[i]=(double)fittedspectrum[i];
              }

              curve4->setPen(Qt::red,2);
              curve4->setSamples(time,arr,1000);//@ x y
              curve4->attach(ui->plot);
              ui->plot->replot();
             }
             else
             {
               curve4->detach();
               ui->plot->replot();
             }

         //PR_drawing_Flag
          if(PR_drawing_Flag)
            {
              curve5->detach();
              ui->plot->replot();

              double time[1000];
              double arr[1000];
              ui->plot->setAxisScale(QwtPlot::xBottom, 0, 1000);//@ 设置坐标范围0：100
              ui->plot->setAxisScale(QwtPlot::yLeft, -5000, 15000);//-360, -200);
              for(int i=0;i<1000;i++)
              {
                time[i]=i;
                arr[i]=(double)xx[i][0];
              }

              curve5->setPen(Qt::black,2);
              curve5->setSamples(time,arr,1000);//@ x y
              curve5->attach(ui->plot);
              ui->plot->replot();
             }
             else
             {
               curve5->detach();
               ui->plot->replot();
             }
       }
  else
  {
      //DCavg_drawing_Flag
      if(DCavg_drawing_Flag)
      {
        concentration1_show();//Con

        curve1->detach();
        ui->plot->replot();

        double time[1000];
        double arr[1000];
        ui->plot->setAxisScale(QwtPlot::xBottom, 0, 1000);//@ 设置坐标范围0：100
        ui->plot->setAxisScale(QwtPlot::yLeft, -5000, 15000);//-360, -200);
        for(int i=0;i<1000;i++)
        {
          time[i]=i;
          arr[i]=(double)DCavg_ch1[i];
        }
        curve1->setPen(Qt::yellow,2);//设置画笔
        curve1->setSamples(time,arr,1000);//@ x y
        curve1->attach(ui->plot);
        ui->plot->replot();
      }
     else
       {
          curve1->detach();
          ui->plot->replot();
       }

       //Raw2f_drawing_Flag
       if(Raw2f_drawing_Flag)
        {
          curve2->detach();
          ui->plot->replot();

          double time[1000];
          double arr[1000];
          ui->plot->setAxisScale(QwtPlot::xBottom, 0, 1000);//@ 设置坐标范围0：100
          ui->plot->setAxisScale(QwtPlot::yLeft, -5000, 15000);//-360, -200);
          for(int i=0;i<1000;i++)
          {
            time[i]=i;
            arr[i]=(double)Raw_F2avg_Ch1[i];
          }

          curve2->setPen(Qt::blue,2);
          curve2->setSamples(time,arr,1000);//@ x y
          curve2->attach(ui->plot);
          ui->plot->replot();
        }
        else
         {
           curve2->detach();
           ui->plot->replot();
         }

          //F2avg_drawing_Flag
           if(F2avg_drawing_Flag)
            {
              curve3->detach();
              ui->plot->replot();

              double time[1000];
              double arr[1000];
              ui->plot->setAxisScale(QwtPlot::xBottom, 0, 1000);//@ 设置坐标范围0：100
              ui->plot->setAxisScale(QwtPlot::yLeft, -5000, 15000);//-360, -200);
              for(int i=0;i<1000;i++)
              {
                time[i]=i;
                arr[i]=(double)Spectrum_ch1[i];
              }

              curve3->setPen(Qt::green,2);
              curve3->setSamples(time,arr,1000);//@ x y
              curve3->attach(ui->plot);
              ui->plot->replot();
            }
            else
             {
               curve3->detach();
               ui->plot->replot();
             }

            //Fitted_drawing_Flag
            if(Fitted_drawing_Flag)
              {
                curve4->detach();
                ui->plot->replot();

                double time[1000];
                double arr[1000];
                ui->plot->setAxisScale(QwtPlot::xBottom, 0, 1000);//@ 设置坐标范围0：100
                ui->plot->setAxisScale(QwtPlot::yLeft, -5000, 15000);//-360, -200);
                for(int i=0;i<1000;i++)
                {
                  time[i]=i;
                  arr[i]=(double)fittedspectrum_ch1[i];
                }

                curve4->setPen(Qt::red,2);
                curve4->setSamples(time,arr,1000);//@ x y
                curve4->attach(ui->plot);
                ui->plot->replot();
               }
               else
               {
                 curve4->detach();
                 ui->plot->replot();
               }

           //PR_drawing_Flag
            if(PR_drawing_Flag)
              {
                curve5->detach();
                ui->plot->replot();

                double time[1000];
                double arr[1000];
                ui->plot->setAxisScale(QwtPlot::xBottom, 0, 1000);//@ 设置坐标范围0：100
                ui->plot->setAxisScale(QwtPlot::yLeft, -5000, 15000);//-360, -200);
                for(int i=0;i<1000;i++)
                {
                  time[i]=i;
                  arr[i]=(double)xx_ch1[i][0];
                }

                curve5->setPen(Qt::black,2);
                curve5->setSamples(time,arr,1000);//@ x y
                curve5->attach(ui->plot);
                ui->plot->replot();
               }
               else
               {
                 curve5->detach();
                 ui->plot->replot();
               }
  }

}


void plotterDlg::on_Back_btn_clicked()
{
    backMainWindow();
    this->hide();
    PlotData_Flag=0;
}
/*
void plotterDlg::on_Clean_all_btn_clicked()
{
     DCavg_drawing_Flag=0;
     Raw2f_drawing_Flag=0;
     F2avg_drawing_Flag=0;
     Fitted_drawing_Flag=0;
     //ui->plot->detachItems();
     //ui->plot->replot();
}
*/


