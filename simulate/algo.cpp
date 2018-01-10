#include "algo.h"
#include <iostream>

#include <QTime>
#include <QThread>
#include"global.h"
using namespace std;
extern fileoperate * files;
extern  pci *pci0 ;
extern  pci *pci1 ;
algo::algo(QObject *parent) : QObject(parent)
{


    for(int i=0;i<8012;i++)
        buffer_copy[i]=0; //memset

    for(int i=0;i<1000;i++)
        ref_avg_buffer[i]=0; //memset

    mode_flag_copy=0;
    ref_avg_count=0;
    algo_start =0;
    transmit_start=0;
    PV_count=0;
    PV_temp =1;
    State=0;
    State1=0;
    State2=0;
    State3=0;
    State4=0;
    State5=0;
    State6=0;
    State7=0;
    State8=0;
    State9=0;
    State10=0;
    State11=0;
    State12=0;
    State13=0;
    State14=0;
    State15=0;
    Conc =0;
    //FOR PEAK;
    T =0;
    P=0;
    PkTrCount=0;
    DR_Flag_Ch1=1;
    DR_Flag =1;
    PV_Flag=1;
}

void algo::algo_init_spi0()
{
   spi0_copy_flag =1;
      for(int i=0;i<8012;i++)
       buffer_copy[i]=spi0_rbuf[i];//copy
       mode_flag_copy =mode_flag;//??
       PV_Flag = PV_Flag_Screen;

       DR_Flag =Debug_Flag;//
       DR_Flag_Ch1 =Debug_Flag_Ch1;//
     uint32_t*temp=(uint32_t*)buffer_copy;//转换

   spi0_copy_flag =0;

   for(int i=0;i<1000;i++)//average
    {
       DCavg[i]=(float)(temp[i]/(float)(AnaParas_Ch0->SpectrAvg));
       F2avg[i]=(float)(temp[i+1000]/(float)(AnaParas_Ch0->SpectrAvg));
   }
   Pressure_act = temp[2000]/(float)(AnaParas_Ch0->SpectrAvg);   //digital;
   Pressure_act =  (Pressure_act/32767)* 5.0;  //15 bit
   Pressure_act=((Pressure_act-1)/4.0)*2000;//DP101A   //((Pressure_act-0.51)/(5.0-0.6))*11000;//DP102A
   Temper_act = temp[2001]/(float)(AnaParas_Ch0->SpectrAvg);
   Temper_act = (Temper_act/32767)* 5.0;
   Temper_act=495.52*(Temper_act)*(1/(0.003851*1000))-1/0.003851;//数据转换
   Tec =temp[2002]/(float)(AnaParas_Ch0->SpectrAvg);
   Tec = (Tec/32767)* 5.0;
   //Tec=495.52*(Tec)*(1/(0.003851*1000))-1/0.003851;//数据转换
   T = Temper_act;
   P = Pressure_act;//@ mbar
}

void algo::algo_init_spi1()
{

    spi1_copy_flag =1;
    for(int i=0;i<8012;i++)
    buffer_copy[i]=spi1_rbuf[i];
    mode_flag_copy =mode_flag_1;//??
    PV_Flag = PV_Flag_Ch1_Screen;

    PV_Flag_Ch1_copy=PV_Flag;
   // DR_Flag_Ch1 =Debug_Flag_Ch1;
    uint32_t*temp=(uint32_t*)buffer_copy;

    spi1_copy_flag =0;

    for(int i=0;i<1000;i++)
     {
        DCavg_ch1[i]=(float)(temp[i]/(float)(AnaParas_Ch1->SpectrAvg));
        F2avg_ch1[i]=(float)(temp[i+1000]/(float)(AnaParas_Ch1->SpectrAvg));
        //DCavg_ch1[i]=DCavg[i];
        //F2avg_ch1[i]=F2avg[i];
    }
    Pressure_act_ch1 = temp[2000]/(float)(AnaParas_Ch1->SpectrAvg);   //digital;
    Pressure_act_ch1 =  (Pressure_act_ch1/32767)* 5.0;  //
    Pressure_act_ch1=((Pressure_act_ch1-1)/4.0)*2000;//DP101A //((Pressure_act_ch1-0.51)/(5.0-0.6))*11000;//DP102
    Temper_act_ch1 = temp[2001]/(float)(AnaParas_Ch1->SpectrAvg);
    Temper_act_ch1 = (Temper_act_ch1/32767)* 5.0;
    Temper_act_ch1=495.52*(Temper_act_ch1)*(1/(0.003851*1000))-1/0.003851;//数据转换

    //Pressure_act_ch1 = Pressure_act;
    //Temper_act_ch1 = Temper_act;
    Tec =temp[2002]/(float)(AnaParas_Ch1->SpectrAvg);
    Tec = (Tec/32767)* 5.0;
    Tec=495.52*(Tec)*(1/(0.003851*1000))-1/0.003851;//数据转换
    T = Temper_act_ch1;
    P = Pressure_act_ch1;//@mbar
}

long algo::findmin()
 {
    uint32_t*temp=(uint32_t*)buffer_copy;

    uint32_t min = temp[0];
    long minvalue=0;
    for(int i=0;i<1000;i++)
    {
        if(temp[i]<min)
            min=temp[i];
    }

    minvalue =(long)min;
    return minvalue;

}

long algo::findmax()
{
    uint32_t*temp=(uint32_t*)buffer_copy;
    long maxvalue=0;
    float max = DCavg_ch1[0];
    for(int i=0;i<1000;i++)
    {
        if(DCavg_ch1[i]>max)
            max=DCavg_ch1[i];
    }
     maxvalue =(long)max;
    return maxvalue;

}
void algo::handle_spi0()   //buffer0
{

   // long results =0;
    if(spi0_transmit_flag==0)  // no change buffer for spi0
    {
        spi0_transmit_flag=1;

        algo_init_spi0();  //spi0 buffer copy to algo;

        //DCsignals fileter 0 points;
        for(int i=0;i<1000;i++)
        {
            if(DCavg[i]==0)
               DCavg[i]=DCavg[i+1];
            if(F2avg[i]==0)
               F2avg[i]=F2avg[i+1];
        }

        float height = F2avg[0];
        for(int i=1;i<1000;i++)
        {
            if(height<F2avg[i])
                 height = F2avg[i];
        }
        if(height>AnaParas_Ch0->TwoFSat)
            State13 = 0x1000;


        //  signals pre_handle;
        for(int i=0;i<1000;i++) //DC信号反置
           DCavg[i] = 15760-DCavg[i];//16500-DCavg[i]
        kk=( DCavg[AnaParas_Ch0->DCNormStart] - DCavg[AnaParas_Ch0->DCNormEnd])/(AnaParas_Ch0->DCNormStart - AnaParas_Ch0->DCNormEnd )*1.0;
        for(int i=0;i<1000;i++)
          DCref[i] = kk*(i -AnaParas_Ch0->DCNormStart) + DCavg[AnaParas_Ch0->DCNormStart];

        float F2temp[135]={0};
        for(int i =0;i<135;i++)  //2f信号左移
          F2temp[i] = F2avg[i];

        for(int i =0;i<865;i++)  //2f信号左移
          F2avg[i] = F2avg[i+135];

        for(int i=0;i<135;i++)  //2f信号左移135个点
          F2avg[865+i] = F2temp[i];

        F2offset = 7900;
        for(int i=0;i<1000;i++)
           F2avg[i]=F2avg[i]-F2offset;

        for(int i=0;i<1000;i++) //处理前
           Raw_F2avg[i]=F2avg[i];
       if(AnaParas_Ch0->DFEnable)//数字滤波 (0：禁用 1：启用)
       {

         for(int Time_i=0;Time_i<9;Time_i++)
         {
            DigitalFilter(F2avg);
         }
       }
        for(int i=0;i<1000;i++) //归一化处理
           F2avg[i]=(F2avg[i]/DCref[i])*10000;


        for(int i=0;i<1000;i++)
           Spectrum[i]=F2avg[i];


        if(spi0_ref_flag)  //start ref_save
         {

            ref_avg_count++;
           //DC,2F ,T,P  -> save buffer
           int index = (int) AnaParas_Ch0->RefInd -1;
           data[index][0]= AnaParas_Ch0->RefInd;
           data[index][1]= Temper_act;
           data[index][2]= Pressure_act;
           data[index][3]= AnaParas_Ch0->ProRCon;//预设浓度/气瓶浓度
           data[index][4]= AnaParas_Ch0->ValRCon;
           data[index][5]= AnaParas_Ch0->Comp1;
           data[index][6]= AnaParas_Ch0->Comp2;
           data[index][7]= AnaParas_Ch0->Comp3;
           data[index][8]= AnaParas_Ch0->Comp4;
           data[index][9]= AnaParas_Ch0->Comp5;
           data[index][10]= AnaParas_Ch0->Comp6;
           data[index][11]= AnaParas_Ch0->Comp7;
           data[index][12]= AnaParas_Ch0->Comp8;

            for(int i=0;i<1000;i++)
              ref_avg_buffer[i]+=Spectrum[i];

             if(ref_avg_count ==AnaParas_Ch0->RefCurvAvg)
             {
                 set_mode(0,1);

                 for(int i=13;i<1013;i++)
                    data[index][i]=ref_avg_buffer[i-13]/(float)ref_avg_count;

                 for(int i=0;i<1000;i++)
                    ref_avg_buffer[i]=0;

                 ref_avg_count=0;

                 spi0_ref_flag=0;
                 files->Ref_write(0);
                 refspi0_save_ok=1;
                 files->Ref_read(0);

                  for(int i=0;i<1013;i++)
                   {
                      printf("%G\t",DCavg[i]);
                      printf("%G\n",data[index][i]);
                   }
             }
         }
         else if (PV_Flag == PV_temp) //PV no change
               {
                 PV_temp = PV_Flag;
                 algo_start =1;
               }
              else
               {
                 for(int i=0;i<10;i++)
                 {
                   PkTrkTemp[i]=20000;
                   MovTemp[i]=20000;
                 }
                 PV_count++;
                 if(PV_count==AnaParas_Ch0->PurgeTime/AnaParas_Ch0->SpectrAvg)
                 {
                    PV_count=0;
                    PV_temp = PV_Flag;
                    algo_start =1;
                 }

              }

        if(algo_start)  // algo pls,cls
        {
           algo_start=0;

           if(AnaParas_Ch0->Model ==0)  //get in  CLS model
           {
                Mk_Ref(0);
                cls(AnaParas_Ch0,Conc_Ch0,0,PV_Flag);//Conc_Ch0.CLSFitRatio  1 or 51;

               if(!PV_Flag)    //val model    //PV_Flag 0
               {
                  float Error;                 
                  Conc = Conc_Ch0->CLSFitRatio*data[0][3];//ppm
                  Conc = AnaParas_Ch0->VCoeff3*Conc*Conc*Conc+AnaParas_Ch0->VCoeff2*Conc*Conc+AnaParas_Ch0->VCoeff1*Conc+AnaParas_Ch0->VCoeff0;
                  //RunPeakTracking(PV_Flag,0,Spectrum,PRRef,AnaParas_Ch0);  //VRREF
                  Conc = AnaParas_Ch0->SSlope*Conc + AnaParas_Ch0->SOffset;//Conc  S

                  Error = ((Conc - AnaParas_Ch0->Vconc)/AnaParas_Ch0->RangeMax)*100;
                  if(Error < 0)
                      Error=-Error;
                  if(Error > AnaParas_Ch0->VAllowance)               //判断误差是否超出允许范围
                    {
                     State8 = 0x0080;
                      if( AnaParas_Ch0->VCorrection == 1)            //允许进行S参数的自动修正
                         AnaParas_Ch0->SSlope =AnaParas_Ch0->SSlope*AnaParas_Ch0->Vconc / Conc; //修正S参数	不存进Flash-enter
                    }

                  //RunPeakTracking(PV_Flag,0,Spectrum,VRRef,AnaParas_Ch0);  // VRREF
                  Conc= Mv_Ag(1,AnaParas_Ch0->MovAvg,Conc,0);

               }
               else         //pro model
               {
                  Conc =Conc_Ch0->CLSFitRatio*data[0][3]; //ppm
                  Conc = AnaParas_Ch0->PCoeff3*Conc*Conc*Conc+AnaParas_Ch0->PCoeff2*Conc*Conc+AnaParas_Ch0->PCoeff1*Conc+AnaParas_Ch0->PCoeff0;
                  RunPeakTracking(PV_Flag,0,Spectrum,PRRef,AnaParas_Ch0);  //VRREF
                  Conc = AnaParas_Ch0->SSlope*Conc + AnaParas_Ch0->SOffset;//Conc  S
                  Conc= Mv_Ag(1,AnaParas_Ch0->MovAvg,Conc,0);

               }
           }
           else   //get in PLS model;
           {
               if(!PV_Flag)    //val model
               {
                  float Error;
                  PLSprocess(AnaParas_Ch0,Conc_Ch0,0);//Conc = Conc_Ch0.PLSRATION;
                  Conc = 77;
                  Conc = AnaParas_Ch0->VCoeff3*Conc*Conc*Conc+AnaParas_Ch0->VCoeff2*Conc*Conc+AnaParas_Ch0->VCoeff1*Conc+AnaParas_Ch0->VCoeff0;
                  Conc = AnaParas_Ch0->SSlope*Conc + AnaParas_Ch0->SOffset;//Conc  S

                  Error = ((Conc - AnaParas_Ch0->Vconc)/AnaParas_Ch0->RangeMax)*100;
                  if(Error < 0)
                      Error=-Error;
                  if(Error > AnaParas_Ch0->VAllowance)             //判断误差是否超出允许范围
                    {
                     State7 = 0x0040;
                      if( AnaParas_Ch0->VCorrection == 1)            //允许进行S参数的自动修正
                         AnaParas_Ch0->SSlope =AnaParas_Ch0->SSlope*AnaParas_Ch0->Vconc / Conc; //修正S参数	不存进Flash-enter
                    }

                   //RunPeakTracking(PV_Flag,0,Spectrum,VRRef,AnaParas_Ch0);  // VRREF;
               }
               else   //pro model
               {
                   // PLSprocess(AnaParas_Ch0,Conc_Ch0,0);//Conc = Conc_Ch0.PLSRATION;
                   PLSprocess(AnaParas_Ch0,Conc_Ch0,0);//Conc = Conc_Ch0.PLSRATION;
                   Conc = 33;
                   //RunPeakTracking(PV_Flag,0,Spectrum,PRRef,AnaParas_Ch0);  // VRREF;
               }

           }


           //Null
           Null = DCavg[9];
           for(int i=10;i<60;i++)
           {
               if(Null>DCavg[i])
                    Null = DCavg[i];
           }


           Power = DCavg[1];
           for(int i=1;i<1000;i++)
           {
               if(Power<DCavg[i])
                    Power = DCavg[i];
           }

           //Alarm Flag
           if(T>AnaParas_Ch0->Tmax)
               State1=0x0001;
           if(T<AnaParas_Ch0->Tmin)
               State2=0x0002;
           if(P>AnaParas_Ch0->Pmax)
               State3=0x0004;
           if(P<AnaParas_Ch0->Pmin)
               State4=0x0008;
           if(Conc>AnaParas_Ch0->AlarmConcMax)
               State5=0x0010;
           if(Conc<AnaParas_Ch0->AlarmConcMin)
               State6=0x0020;
           if(Power>AnaParas_Ch0->DCHigh)
               State9=0x0100;
           if(Power<AnaParas_Ch0->DCLow)
               State10=0x0200;
           if(Null<AnaParas_Ch0->NullLow)
               State14=0x2000;
           if(Null>AnaParas_Ch0->NullHigh)
               State15=0x4000;
           State =(State1 |State2 |State3 |State4 |State5 |State6 | State7 |State8 |State9 |State10 |State11 |State12 |State13 |State14 |State15);

           Conc_Ch0->Status = State;

           State1=State2=State3=State4=State5=State6=State7=State8=State9=State10=State11=State12=State13=State14=State15=0;

           transmit_start=1;
        }


        if(transmit_start)//all pfintf
        {
           int peak;
           transmit_start=0;
           //Conc=10000.1234;//try
           //LCD display;
           if(AnaParas_Ch0->ConcUnit==1)//%
               Conc=Conc*0.1*0.1*0.1*0.1;
           //Conc=13;
           Conc_Ch0->Conc =  Conc;     //last  display;
           if(AnaParas_Ch0->Punit==1)
               P = P*0.1;
           Conc_Ch0->P=P;

           //T=50.0+(((rand()%10)+(rand()%10))-10)/100.0;

           Conc_Ch0->T=T;

           Conc_Ch0->Tec=Tec;

           Conc_Ch0->Peak=PeakAvg;

           peak =(int)PeakAvg;
           Conc_Ch0->PeakHeight = Spectrum[peak];

           Conc_Ch0->Null = Null;

           Conc_Ch0->Power =Power;//DC max

           Conc_Ch0->IStart = AnaParas_Ch0->IStart;

           Conc_Ch0->IAmp = AnaParas_Ch0->IRange;

           Conc_Ch0->Peakref = Peakref;

           result0_show();


           showRealTime();
           const char * str_data;
           str_data = DataStr.toStdString().c_str();

           Uart_Ok_Ch0 =1;   //rs232 transmint;


           printf("CH\t");
           printf("Time\t");
           //printf("\t");//Style of Linux to Debug
           printf("\t");
           printf("Conc\t");
           printf("T\t");
           printf("P\t");
           printf("DC\t");
           printf("Pk\t");
           printf("PkHgt\t");
           printf("PkRf\t");
           printf("Null\t");

           if(AnaParas_Ch0->DataFormat==0)
               printf("\n");
           else
           {
               printf("IStart\t");
               printf("IAmp\t");
               if(PV_Flag)//???
               {
                   printf("FRP\t");
                   //printf("0\t");
               }
               else
               {
                   //printf("0\t");
                   printf("CLSFitRatio\t");
               }

               if(xx_size>1)
                {
                   //for(int i=1;i<xx_size;i++)
                   //printf("%G\t",cls_a_ch0[i]);
                }

                printf("\n");

           }


           printf("1\t");
           printf("%s\t",str_data);
           printf("%.3lf\t",Conc_Ch0->Conc);
           printf("%.2lf\t",Conc_Ch0->T);
           printf("%G\t",Conc_Ch0->P);
           printf("%G\t",Conc_Ch0->Power);
           printf("%G\t",Conc_Ch0->Peak);
           printf("%G\t",Conc_Ch0->PeakHeight);
           printf("%G\t",Conc_Ch0->Peakref);
           printf("%G\t",Conc_Ch0->Null);

           if(AnaParas_Ch0->DataFormat==0)
               printf("\n");
           else
           {
               printf("%G\t",Conc_Ch0->IStart);
               printf("%G\t",Conc_Ch0->IAmp);
               if(PV_Flag)
               {
                   printf("%G\t",Conc_Ch0->CLSFitRatio);
                   //printf("0\t");
               }
               else
               {
                   //printf("0\t");
                   printf("%G\t",Conc_Ch0->CLSFitRatio);
               }

               if(xx_size>1)
                {
                   //for(int i=1;i<xx_size;i++)
                   //printf("%G\t",cls_a_ch0[i]);
                }

               printf("\n");
           }

          if(!DR_Flag)//start
           {
              if(!Re_flag)//@
              {
                  files->AnaParas_send(0);//Parameters for Ana//@
                  files->Ref_send(1,0);//Refcuv start: 1;ch: //@
                  Re_flag = true;//@
              }
            printf("Begin\n");
            printf("number\t");
            printf("Raw2f\t");
            printf("DC\t");
            printf("2f\t");
            printf("fitted2f\t");
                printf("PR\t");
                printf("R1\t");
                printf("R2\t");
                printf("R3\t");
                printf("VR\t");
            printf("\n");

            for(int i=0;i<1000;i++)
            {
              printf("%d\t",i);           //start ch0 uart;
              printf("%G\t",Raw_F2avg[i]);
              printf("%G\t",DCavg[i]);
              printf("%G\t",Spectrum[i]);
              printf("%G\t",fittedspectrum[i]);

             //该输出不支持启用Baseuse,若启用建议考虑更换Baseuse顺序为VRuse最后,再做条件输出
              for(int j =0;j<xx_size-1;j++)     //输出PR 和启用的[R1 R2 R3 (BA) VR]
                printf("%G\t",xx[i][j]);

              if(j<5)
              {                                 //输出验证了j的范围
                for(j=xx_size;j<Z-1;j++)        //R1 R2 R3 (BA) VR没启用的补零输出
                {
                   printf("0\t");
                }
              }
              printf("\n");

            }
            printf("End\n");
           }
            Uart_Ok_Ch0=0;

  /*         while (!Uart_Ok_Ch1){
                sleep(1);
            }*/

            printf("2\t");
            printf("%s\t",str_data);
            printf("%.3lf\t",Conc_Ch1->Conc);
            printf("%.2lf\t",Conc_Ch1->T);
            printf("%G\t",Conc_Ch1->P);
            //printf("Tec1 %G\t",Conc_Ch1->Tec);//@
            printf("%G\t",Conc_Ch1->Power);
            printf("%G\t",Conc_Ch1->Peak);
            printf("%G\t",Conc_Ch1->Peakref);
            printf("%G\t",Conc_Ch1->PeakHeight);
            printf("%G\t",Conc_Ch1->Null);

            if(AnaParas_Ch1->DataFormat==0)
                printf("\n");
            else
            {
                printf("%G\t",Conc_Ch1->IStart);
                printf("%G\t",Conc_Ch1->IAmp);

                if(PV_Flag_Ch1_copy)
                {
                    printf("%G\t",Conc_Ch1->CLSFitRatio);
                    //printf("0\t");
                }
                else
                {
                    //printf("0\t");
                    printf("%G\t",Conc_Ch1->CLSFitRatio);
                }

                if(xx_ch1_size>1)
                {
                   //for(int i=1;i<xx_ch1_size;i++)
                     //printf("%G\t",cls_a_ch1[i]);
                }
                printf("\n");
                printf("\n");


            }

           if(!DR_Flag_Ch1)
            {
               if(!Re_flag_ch1)//@
               {
                   files->AnaParas_send(1);//Parameters for Ana//@
                   files->Ref_send(1,1);//Refcuv start: 1;ch: //@
                   Re_flag_ch1 = true;//@
               }

               printf("Begin\n");
               printf("number\t");
               printf("Raw2f\t");
               printf("DC\t");
               printf("2f\t");
                  printf("fitted2f\t");
                  printf("PR\t");
                  printf("R1\t");
                  printf("R2\t");
                  printf("R3\t");
                  printf("VR\t");
              printf("\n");

             for(int i=0;i<1000;i++)
             {
               printf("%d\t",i);   //start ch0 uart;
               printf("%G\t",Raw_F2avg_Ch1[i]);//@
               printf("%G\t",DCavg_ch1[i]);
               printf("%G\t",Spectrum_ch1[i]);
               printf("%G\t",fittedspectrum_ch1[i]);
               for(int j =0;j<xx_ch1_size;j++)
                 printf("%G\t",xx_ch1[i][j]);
               printf("\n");
             }
             printf("End\n");
            }

             Uart_Ok_Ch1=0;

        }

        if(PlotData_Flag)
            plotter_start();
  }

}
void algo::handle_spi1()   //buffer1
{
    //long results =0;
    if(spi1_transmit_flag==0)
    {
      spi1_transmit_flag=1;

      algo_init_spi1();
      //DCsignals fileter 0 points;
      //DCsignals fileter 0 points;
      for(int i=0;i<1000;i++)
      {
          if(DCavg_ch1[i]==0)
             DCavg_ch1[i]=DCavg_ch1[i+1];
          if(F2avg_ch1[i]==0)
             F2avg_ch1[i]=F2avg_ch1[i+1];
      }

      float height = F2avg_ch1[0];
      for(int i=1;i<1000;i++)
      {
          if(height<F2avg_ch1[i])
               height = F2avg_ch1[i];
      }
      if(height>AnaParas_Ch1->TwoFSat)
          State13 = 0x1000;



      //  signals pre_handle;
      for(int i=0;i<1000;i++) //DC信号反置
         DCavg_ch1[i] = 15600-DCavg_ch1[i];//16500
      kk_ch1=( DCavg_ch1[AnaParas_Ch1->DCNormStart] - DCavg_ch1[AnaParas_Ch1->DCNormEnd])/(AnaParas_Ch1->DCNormStart - AnaParas_Ch1->DCNormEnd )*1.0;
      for(int i=0;i<1000;i++)
        DCref_ch1[i] = kk_ch1*(i -AnaParas_Ch1->DCNormStart) + DCavg_ch1[AnaParas_Ch1->DCNormStart];

      float F2temp[135]={0};
      for(int i =0;i<135;i++)  //2f信号左移
        F2temp[i] = F2avg_ch1[i];

      for(int i =0;i<865;i++)  //2f信号左移
        F2avg_ch1[i] = F2avg_ch1[i+135];

      for(int i=0;i<135;i++)  //2f信号左移20个点
        F2avg_ch1[865+i] = F2temp[i];



      F2offset = 7900;
      for(int i=0;i<1000;i++)
         F2avg_ch1[i]=F2avg_ch1[i]-F2offset;

      for(int i=0;i<1000;i++) //处理前
         Raw_F2avg_Ch1[i]=F2avg_ch1[i];

     if(AnaParas_Ch1->DFEnable)//@
       {
         for(int Time_i=0;Time_i<5;Time_i++)
         {
            DigitalFilter(F2avg_ch1);
         }
       }
      for(int i=0;i<1000;i++) //归一化处理
         F2avg_ch1[i]=(F2avg_ch1[i]/DCref_ch1[i])*10000;


      for(int i=0;i<1000;i++)
         Spectrum_ch1[i]=F2avg_ch1[i];


      if(spi1_ref_flag)  //start ref_save
       {
          ref_avg_count++;//??
          //DC,2F ,T,P  -> save buffer
         int index = (int) AnaParas_Ch1->RefInd -1;
         data_ch1[index][0]= AnaParas_Ch1->RefInd;
         data_ch1[index][1]= Temper_act_ch1;
         data_ch1[index][2]= Pressure_act_ch1;
         data_ch1[index][3]= AnaParas_Ch1->ProRCon;
         data_ch1[index][4]= AnaParas_Ch1->ValRCon;
         data_ch1[index][5]= AnaParas_Ch1->Comp1;
         data_ch1[index][6]= AnaParas_Ch1->Comp2;
         data_ch1[index][7]= AnaParas_Ch1->Comp3;
         data_ch1[index][8]= AnaParas_Ch1->Comp4;
         data_ch1[index][9]= AnaParas_Ch1->Comp5;
         data_ch1[index][10]= AnaParas_Ch1->Comp6;
         data_ch1[index][11]= AnaParas_Ch1->Comp7;
         data_ch1[index][12]= AnaParas_Ch1->Comp8;

          for(int i=0;i<1000;i++)
            ref_avg_buffer[i]+=Spectrum_ch1[i];//




               if(ref_avg_count ==AnaParas_Ch1->RefCurvAvg)
               {
                   set_mode(1,1);

                   for(int i=13;i<1013;i++)
                      data_ch1[index][i]=ref_avg_buffer[i-13]/(float)ref_avg_count;

                   for(int i=0;i<1000;i++)
                      ref_avg_buffer[i]=0;

                   ref_avg_count=0;

                   spi1_ref_flag=0;

                   files->Ref_write(1);

                   refspi1_save_ok=1;

                   files->Ref_read(1);

                    for(int i=0;i<1013;i++)
                     {
                        printf("%G\t",DCavg_ch1[i]);
                        printf("%G\n",data_ch1[index][i]);
                     }
               }
           }
           else if (PV_Flag == PV_temp) //PV no change
                 {
                   PV_temp = PV_Flag;
                   algo_start =1;
                 }
                else
                 {
                   for(int i=0;i<10;i++)
                   {
                     PkTrkTemp_ch1[i]=20000;
                     MovTemp_ch1[i]=20000;
                   }
                   PV_count++;
                   if(PV_count==AnaParas_Ch1->PurgeTime/2)
                   {
                      PV_count=0;
                      PV_temp = PV_Flag;
                      algo_start =1;
                   }

                }



          if(algo_start)  // algo pls,cls
          {
             algo_start=0;
             // ALGORITHM
             if(AnaParas_Ch1->Model ==0)  // get in  CLS MODEL
             {

                  Mk_Ref(1);

         //Try ref as mk
          files->Ref_read(1);
          for(int j=0;j<1000;j++)
          PRRef_ch1[j]=data_ch1[1][j+13];

                  cls(AnaParas_Ch1,Conc_Ch1,1,PV_Flag);//Conc_Ch0.CLSFitRatio  1 or 51;

                  //get conc ,then movang ??

                 if(!PV_Flag)    //val model
                 {
                    float Error;
                    Conc = Conc_Ch1->CLSFitRatio*data_ch1[0][3];
                    Conc = AnaParas_Ch1->VCoeff3*Conc*Conc*Conc+AnaParas_Ch1->VCoeff2*Conc*Conc+AnaParas_Ch1->VCoeff1*Conc+AnaParas_Ch1->VCoeff0;
                    Conc = AnaParas_Ch1->SSlope*Conc + AnaParas_Ch1->SOffset;//Conc  S

                    Error = ((Conc - AnaParas_Ch1->Vconc)/AnaParas_Ch1->RangeMax)*100;
                    if(Error < 0)
                        Error=-Error;
                    if(Error > AnaParas_Ch1->VAllowance)             //判断误差是否超出允许范围
                      {
                       State8 = 0x0080;
                        if( AnaParas_Ch1->VCorrection == 1)            //允许进行S参数的自动修正
                           AnaParas_Ch1->SSlope =AnaParas_Ch1->SSlope*AnaParas_Ch1->Vconc / Conc; //修正S参数	不存进Flash-enter
                      }

                    RunPeakTracking(PV_Flag,1,Spectrum_ch1,VRRef_ch1,AnaParas_Ch1);  // VRREF
                    Conc= Mv_Ag(1,AnaParas_Ch1->MovAvg,Conc,1);


                 }  // PV
                 else   //pro model
                 {
                     //PLSprocess(AnaParas_Ch1,Conc_Ch0,0);//Conc = Conc_Ch0.PLSRATION;

                    // printf("start peak find: \n");
                    Conc =Conc_Ch1->CLSFitRatio*data[0][3];  //ppm
                    RunPeakTracking(PV_Flag,1,Spectrum_ch1,PRRef_ch1,AnaParas_Ch1);  // VRREF

                    Conc= Mv_Ag(1,AnaParas_Ch1->MovAvg,Conc,1);
                    //Conc_Ch0->Conc =Conc;

                 }
             }
             else   //get in PLS model;
             {
                 if(!PV_Flag)    //val model
                 {
                    printf("get in CH2 PLS Val\n");//@@
                    float Error;

                    CV( AnaParas_Ch1,1);//first
                    PLSprocess(AnaParas_Ch1,Conc_Ch1,1);//Conc = Conc_Ch0.PLSRATION;



                    Conc = 77;
                    Conc = AnaParas_Ch1->VCoeff3*Conc*Conc*Conc+AnaParas_Ch1->VCoeff2*Conc*Conc+AnaParas_Ch1->VCoeff1*Conc+AnaParas_Ch1->VCoeff0;
                    Conc = AnaParas_Ch1->SSlope*Conc + AnaParas_Ch1->SOffset;//Conc  S

                    Error = ((Conc - AnaParas_Ch1->Vconc)/AnaParas_Ch1->RangeMax)*100;
                    if(Error < 0)
                        Error=-Error;
                    if(Error > AnaParas_Ch1->VAllowance)             //判断误差是否超出允许范围
                      {
                       State7 = 0x0040;
                        if( AnaParas_Ch1->VCorrection == 1)            //允许进行S参数的自动修正
                           AnaParas_Ch1->SSlope =AnaParas_Ch1->SSlope*AnaParas_Ch1->Vconc / Conc; //修正S参数	不存进Flash-enter
                      }

                     RunPeakTracking(PV_Flag,1,Spectrum_ch1,VRRef_ch1,AnaParas_Ch1);  // VRREF;

                 }  // PV
                 else   //pro model
                 {
                     printf("get in CH2 PLS Pro\n");//@
                     // PLSprocess(AnaParas_Ch1,Conc_Ch1,1);//Conc = Conc_Ch1.PLSRATION;
                     PLSprocess(AnaParas_Ch1,Conc_Ch1,1);//Conc = Conc_Ch1.PLSRATION;
                     Conc = 33;
                     RunPeakTracking(PV_Flag,1,Spectrum_ch1,PRRef_ch1,AnaParas_Ch1);  // VRREF;
                 }
             }


             //Null
             Null = DCavg_ch1[9];
             for(int i=10;i<60;i++)
             {
                 if(Null>DCavg_ch1[i])
                      Null = DCavg_ch1[i];
             }


             Power = DCavg_ch1[1];
             for(int i=1;i<1000;i++)
             {
                 if(Power<DCavg_ch1[i])
                      Power = DCavg_ch1[i];
             }

             //Alarm Flag
             if(T>AnaParas_Ch1->Tmax)
                 State1=0x0001;
             if(T<AnaParas_Ch1->Tmin)
                 State2=0x0002;
             if(P>AnaParas_Ch1->Pmax)
                 State3=0x0004;
             if(P<AnaParas_Ch1->Pmin)
                 State4=0x0008;
             if(Conc>AnaParas_Ch1->AlarmConcMax)
                 State5=0x0010;
             if(Conc<AnaParas_Ch1->AlarmConcMin)
                 State6=0x0020;
             if(Power>AnaParas_Ch1->DCHigh)
                 State9=0x0100;
             if(Power<AnaParas_Ch1->DCLow)
                 State10=0x0200;
             if(Null<AnaParas_Ch1->NullLow)
                 State14=0x2000;
             if(Null>AnaParas_Ch1->NullHigh)
                 State15=0x4000;
             State =(State1 |State2 |State3 |State4 |State5 |State6 | State7 |State8 |State9 |State10 |State11 |State12 |State13 |State14 |State15);

             Conc_Ch1->Status = State;

             State1=State2=State3=State4=State5=State6=State7=State8=State9=State10=State11=State12=State13=State14=State15=0;

            transmit_start=1;
          }


          if(transmit_start)
          {
              int peak;
              transmit_start=0;
              //LCD display;
              if(AnaParas_Ch1->ConcUnit==1)
                  Conc=Conc*0.1*0.1*0.1*0.1;
              Conc_Ch1->Conc =  Conc;     //last  display;
              if(AnaParas_Ch1->Punit==1)
                  P = P*0.1;
              Conc_Ch1->P=P;

              Conc_Ch1->T=T;

              Conc_Ch1->Tec=Tec;

              Conc_Ch1->Peak=PeakAvg;

              peak =(int)PeakAvg;
              Conc_Ch1->PeakHeight = Spectrum_ch1[peak];

              Conc_Ch1->Null = Null;

              Conc_Ch1->Power =Power;

              Conc_Ch1->IStart = AnaParas_Ch1->IStart;

              Conc_Ch1->IAmp = AnaParas_Ch1->IRange;

              Conc_Ch1->Peakref = Peakref;

              result1_show();//use



              Uart_Ok_Ch1 =1;

              while(Uart_Ok_Ch1){
                  //sleep(1);
              }
          }

      }
}

int algo::Pro_FindPeakIndex(float *curve, Para *paras)
{
  int Li_i, Li_PeakIndex = 0;
  float Lf_PeakMaxValue = -999999.0;
  for( Li_i = paras->PkTrkStart; Li_i <= paras->PkTrkEnd; Li_i++ )
  {
    if( Lf_PeakMaxValue < curve[ Li_i ] )
    {
      Lf_PeakMaxValue = curve[ Li_i ];
      Li_PeakIndex = Li_i;
    }
  }
  return( Li_PeakIndex );
}

int algo::Val_FindPeakIndex(float *curve, Para *paras)
{
    int Li_i, Li_PeakIndex = 0;
    float Lf_PeakMaxValue = -999999.0;
    for( Li_i = paras->ValPkTrkStart; Li_i <= paras->ValPkTrkEnd; Li_i++ )
    {
      if( Lf_PeakMaxValue < curve[ Li_i ] )
      {
        Lf_PeakMaxValue = curve[ Li_i ];
        Li_PeakIndex = Li_i;
      }
    }
    return( Li_PeakIndex );
}

float algo::FindFractionalPeakIndex(float *curve, Para *paras, int m)
{
    int X;
    double X2, M11, M12, M13, M21, M22, M23, M31, M32, M33, K1, K2, K3, L21, U22, U23, L31, L32, U33, b2, b3, a2, a1; //, a0;
    double Lf_PeakIndex;

    M11 = M12 = M13 = M21 = M22 = M23 = M31 = M32 = M33 = K1 = K2 = K3 = 0.0;
    for( X = m - paras->PkWdith; X <= m + paras->PkWdith; X++ )
    {
      X2 = X * X;
      M11 += X2;
      M12 += X2 * X;
      M13 += X2 * X2;
      M21 += X;
      K1 += X2 * curve[ X ];
      K2 += X * curve[ X ];
      K3 += curve[ X ];
    }
    M22 = M33 = M11;
    M23 = M12;
    M32 = M21;
    M31 = paras->PkWdith * 2 + 1;

    if (M11 == 0.0)
      return( (float)m );
    else
      L21 = M21/M11;//
    U22 = M22 - L21*M12;
    U23 = M23 - L21*M13;
    if (M11 == 0.0)
      return( (float)m );
    else
      L31 = M31/M11;
    if(U22 == 0.0)
      return( (float)m );
    else
      L32 = (M32 - L31*M12) / U22;
    U33 = M33 - L31*M13 - L32*U23;
    b2 = K2 - L21*K1;
    b3 = K3 - L31*K1 - L32*b2;
    if(U33 == 0.0)
      return( (float)m );
    else
      a2 = b3/U33;
    if(U22 == 0.0)
      return( (float)m );
    else
      a1 = (b2 - U23*a2) / U22;
    if(a2 == 0.0)
      return( (float)m );
    else
      Lf_PeakIndex = -a1 / (2.0 * a2);

    if( ( Lf_PeakIndex < ( m - paras->PkWdith ) )|| ( Lf_PeakIndex > ( m + paras->PkWdith ) ) )
      return( (float)m );
    else
      return( (float)Lf_PeakIndex );

}

float algo::RunPeakTracking(bool PVFlag, bool CHFlag, float *SampCurve, float *RefCurve, Para * paras)
{
   // float Lf_PeakShift=0.0;
    float Lf_FracPeakShift=0.0;
    float PeakTrackIndex=0.0;//实时谱峰坐标
    float PeakIndexRef=0.0;//参考谱峰坐标
    float PeakShift=0.0;//峰偏移量

    unsigned int IStartdoFlg=0;
    float delta_index=0.0;//最终寻峰计算峰偏移量
    float ThisMidCurrent=0.0;//电流值调节量
    int PkTrkinterIndex;
    float PkTrkshiftAvg =0.0;

    bool UpStart_pci0 = 1;
    bool UpStart_pci1 = 1;
    bool ValUpStart_pci0 = 1;
    bool ValUpStart_pci1 = 1;

    if(PVFlag) //pro
    {
        PeakTrackIndex = Pro_FindPeakIndex(SampCurve,paras); //Limit search peak;
        PeakIndexRef =  Pro_FindPeakIndex( RefCurve,paras);
    }
    else       //val
    {
       PeakTrackIndex = Val_FindPeakIndex(SampCurve,paras); //Limit search peak;
       PeakIndexRef =  Val_FindPeakIndex( RefCurve,paras);
    }
     //Lf_PeakShift =PeakIndexRef - PeakTrackIndex;

     //printf("Peak:%G\n",PeakTrackIndex);

    /******拟合*****/
    PeakTrackIndex = FindFractionalPeakIndex( SampCurve,paras, PeakTrackIndex );
    PeakIndexRef = FindFractionalPeakIndex( RefCurve,paras,PeakIndexRef );
    PkTrkinterIndex=(int)PeakTrackIndex;
    Lf_FracPeakShift =PeakIndexRef - PeakTrackIndex;

    PeakAvg = PeakTrackIndex;
    Peakref=PeakIndexRef;
   //printf("Peak(bl):%G\t Peak(Ref):%G\n",PeakTrackIndex,PeakIndexRef);
   //printf("PeakAvg:%G\n",PeakAvg);//C1:28  PeakAvg:528#1
   //printf("Peakref:%G\n",Peakref);//C1:28  Peakref:538#2


    PeakShift=Lf_FracPeakShift;
    //printf("PeakShift: %lf\n",PeakShift);
   //根据设定标志选择偏差计算方式
          if( fabs(paras->PkTarget) <= 0.01 )    delta_index =0 - PeakShift;  //left or right;
          else                            delta_index =0 - (paras->PkTarget - PeakTrackIndex);
   //计算平均偏差(滑动平均偏差)

    if( fabs(delta_index) <= paras->PkTrkIdxMax )  //out  range;


       {
       PkTrkshiftAvg = Mv_Ag(0,paras->PkTrkAvg ,delta_index,CHFlag) ;
        //计算start电流
      //printf("PkTrkshiftAvg:%G\n",PkTrkshiftAvg);//C1:28#3

     //  printf("PeakAvg(bl):%G\n",PkTrkshiftAvg);

       if(( PkTrkshiftAvg >= paras->PkTrkIdxMin )&&(PkTrkshiftAvg<=paras->PkTrkIdxMax))
        {
           if((T>=paras->PkTrkTLow)&&(T<=paras->PkTrkTHigh))
            {
               if((P>=paras->PkTrkPLow)&&(P<=paras->PkTrkPHigh))
               {
                   if((SampCurve[PkTrkinterIndex]>=paras->PkTrkHgtMin)&&(SampCurve[PkTrkinterIndex]<=paras->PkTrkHgtMax))
                   {
                      IStartdoFlg=1;

                      PkTrCount++;
                      if(PkTrCount=paras->PkShiftLmt)
                       {
                            State7 = 0x0040;
                            PkTrCount=0;
                            //报警；

                       }
                   }
               }
           }
        }
    }
    else
       printf("PeakShift Out of range\n");


  //激光器动作控制

    IStartdoFlg=1;//#
   if(IStartdoFlg==1)
   {//printf("paras->Ituning:%.4lf\n",paras->Ituning);//C1:28#4
      ThisMidCurrent = PkTrkshiftAvg * paras->Ituning;
        //printf("ThisMidCurrent:%G\n",ThisMidCurrent);//#5

      if(paras->PkTrk==0)
      {
         PkTrCount =0;
      }
      else if(paras->PkTrk==1)
      {
         //printf("Ana paras->IStart:%.4lf\n",paras->IStart);//#6

//pci change
         if(!CHFlag)
         {
             pci0->pci_open(0);
             pci0->get_all_parameter();//@
             pci0->pci_close();

            if(RePci_Flag)
            {
               paras->IStart=tc1*2.0+ThisMidCurrent;

              files->writefile(0);
              float c1 = paras->IStart /2.0;
              float c2 = paras->IRange/2.0;
              int null = paras->NullWidth;

              if(c1+c2>50)
              {
                  c1=50-c2;
                  printf("c1+c2 Out of range\n");
                  UpStart_pci0 = 0;
              }

              if(UpStart_pci0)
              {
               pci0->pci_open(0);
               pci0->set_laserscan(c1,c2,null);//@
               pci0->save2flash();
               pci0->pci_close();
              }
            }
            else
            {
                printf("Read PCI0 filed !\n");
            }

         }
         else
         {
             pci1->pci_open(1);
             pci1->get_all_parameter();//@
             pci1->pci_close();
   //printf("PCI1 RePci_Flag: %d\n",RePci_Flag);//#7
             if(RePci_Flag)
            {
              paras->IStart=tc1*2.0+ThisMidCurrent;
    //printf("tc1:%.4lf\n",tc1);//#8
              files->writefile(1);
              float c1 = paras->IStart /2.0;
              float c2 = paras->IRange/2.0;
              int null = paras->NullWidth;

              if(c1+c2>50)
              {
                  c1=50-c2;
                  printf("c1+c2 Out of range\n");
                  UpStart_pci1=0;
              }

              if(UpStart_pci1)
             {
              pci1->pci_open(1);
              pci1->set_laserscan(c1,c2,null);//@
              pci1->save2flash();
              pci1->pci_close();
             }
              //printf("PCI1 tc1:%.4lf\n",tc1);//#9
            }
            else
            {
                printf("Read PCI1 filed !\n");
            }

         }

      }


      else  if(paras->PkTrk==2)
      {
          if(!CHFlag)
          {
            paras->IStart = AnaParas_Ch0_init->IStart;
            files->writefile(0);
            float c1 = paras->IStart /2.0;
            float c2 = paras->IRange/2.0;
            int null = paras->NullWidth;

            if(c1+c2>50)
            {
                c1=50-c2;
                printf("val c1+c2 Out of range\n");
                ValUpStart_pci0=0;
            }
            if(ValUpStart_pci0)
            {
              pci0->pci_open(0);
              pci0->set_laserscan(c1,c2,null);
              pci0->save2flash();
              pci0->pci_close();
            }
          }
           else
          {
              paras->IStart = AnaParas_Ch1_init->IStart;
              files->writefile(1);
              float c1 = paras->IStart /2.0;
              float c2 = paras->IRange/2.0;
              int null = paras->NullWidth;

              if(c1+c2>50)
              {
                  c1=50-c2;
                  printf("val c1+c2 Out of range\n");
                  ValUpStart_pci1=0;
              }
              if(ValUpStart_pci1)
              {
                pci1->pci_open(1);
                pci1->set_laserscan(c1,c2,null);
                pci1->save2flash();
                pci1->pci_close();
              }

          }
          //重启
         paras->PkTrk = 1;
      }

   }
   else
   {
     PkTrCount =0;
   }

      if( paras->IStart < paras->Ilow )
      {
        paras->IStart = paras->Ilow;
        State12 = 0x0800;
        //gaojingma
        if(!CHFlag)
        {
          files->writefile(0);
          float c1 = paras->IStart /2.0;
          float c2 = paras->IRange/2.0;
          int null = paras->NullWidth;
          pci0->pci_open(0);
          pci0->set_laserscan(c1,c2,null);
          pci0->save2flash();
          pci0->pci_close();
        }
         else
        {
            files->writefile(1);
            float c1 = paras->IStart /2.0;
            float c2 = paras->IRange/2.0;
            int null = paras->NullWidth;
            pci1->pci_open(1);
            pci1->set_laserscan(c1,c2,null);
            pci1->save2flash();
            pci1->pci_close();

        }

        //pci change;
      }
      if( (paras->IStart + paras->IRange)> paras->IHigh )
      {
         paras->IStart = paras->IHigh -  paras->IRange;
         State11 = 0x0400;
        if(!CHFlag)
        {
          files->writefile(0);
          float c1 = paras->IStart /2.0;
          float c2 = paras->IRange/2.0;
          int null = paras->NullWidth;
          pci0->pci_open(0);
          pci0->set_laserscan(c1,c2,null);
          pci0->save2flash();
          pci0->pci_close();
        }
         else
        {
            files->writefile(1);
            float c1 = paras->IStart /2.0;
            float c2 = paras->IRange/2.0;
            int null = paras->NullWidth;
            pci1->pci_open(1);
            pci1->set_laserscan(c1,c2,null);
            pci1->save2flash();
            pci1->pci_close();

        }

        //pci change;
      }

      return ( paras->IStart);

}

void  algo::showRealTime()
{
    QDateTime date = QDateTime::currentDateTime();
    QTime time = QTime::currentTime();
    QString txtDate = date.toString("yy/MM/dd");
    QString txtTime = time.toString("hh:mm:ss");

    DataStr = txtDate;
    DataStr +=" ";
    DataStr +=txtTime;


}
