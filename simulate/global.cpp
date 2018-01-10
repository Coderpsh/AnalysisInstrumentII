#include <global.h>


bool mode_flag =1;  //0:min , 1:max
bool mode_flag_1=1;


Para * AnaParas_Ch0 = new Para;
Para * AnaParas_Ch1 = new Para;
Para * AnaParas_Ch0_init = new Para;
Para * AnaParas_Ch1_init = new Para;

Conc * Conc_Ch0 =new Conc;
Conc * Conc_Ch1 =new Conc;
fileoperate * files = new fileoperate;



pci *pci0 = new pci;
pci *pci1 = new pci;

PCIPARA *pci0_paras=new PCIPARA;
PCIPARA *pci1_paras=new PCIPARA;
PCIPARA *a=new PCIPARA;//@
PARA *paras_ch0 = new PARA;

PARA *paras_ch1 = new PARA;


/*float DC_CH0[1000]={0};
float DC_CH1[1000]={0};
float f2_CH0[1000]={0};
float f2_CH1[1000]={0};
float P_CH0[1000]={0};
float P_CH1[1000]={0};
float T_CH0[1000]={0};
float T_CH1[1000]={0};
float Tec_CH0[1000]={0};
float Tec_CH1[1000]={0};*/

float Try_temp;//@try printf
bool RePci_Flag;// for PCI read flag
//for
 long tscanperiod;
 long toffset;
 long tfrequency;
 long tamplitude;
 long tbandwidth;
 long tphase;
 long tgain;
 double tc1;
 double tc2;
 long tnullpoint;

int CH_Flag =0;
int permit_flag=0;

bool RD_flag=0; //use to password
bool RD_flag_ch1=0;

bool PV_Flag_Screen =1;  // 1 pro
bool PV_Flag_Ch1_Screen =1;
bool PV_Flag_Ch1_copy =1;

bool Debug_Flag =1;
bool Debug_Flag_Ch1 =1;

bool PlotData_Flag=0;

bool Re_flag=true;//@
bool Re_flag_ch1=true;//@
//for ploatter
bool Ploat_Channel=0;

//plotterdlg
bool DCavg_drawing_Flag=1;
bool Raw2f_drawing_Flag=1;
bool F2avg_drawing_Flag=1;
bool PR_drawing_Flag=1;
bool Fitted_drawing_Flag=1;


bool spi0_transmit_flag = 1;
bool spi1_transmit_flag = 1;//process of transmit cannt copy;
bool spi0_copy_flag = 0;
bool spi1_copy_flag = 0;
bool spi0_ref_flag =0;
bool spi1_ref_flag =0;


uint8_t spi0_tbuf[8012]={0},spi0_rbuf[8012]={0};
uint8_t spi1_tbuf[8012]={0},spi1_rbuf[8012]={0};
//ref_save flag;

bool refspi0_save_ok =0;
bool refspi1_save_ok =0;

//float Uart_Buff_Ch0[1100]={0};
//float Uart_Buff_Ch1[1100]={0};

bool Uart_Ok_Ch0 = 0;
bool Uart_Ok_Ch1 = 0;


//algo
/********全局变量********/
float Pressure_act;//实时压强
float Temper_act;//实时温度
float Pressure_act_ch1;//实时压强
float Temper_act_ch1;//实时温度
float MovTemp[10]={20000,20000,20000,20000,20000,20000,20000,20000,20000,20000};//滑动平均最大为10，后期可修改
float MovTemp_ch1[10]={20000,20000,20000,20000,20000,20000,20000,20000,20000,20000};
float PkTrkTemp[10]={20000,20000,20000,20000,20000,20000,20000,20000,20000,20000};
float PkTrkTemp_ch1[10]={20000,20000,20000,20000,20000,20000,20000,20000,20000,20000};
double xx[M][Z],yy[M];
double xx_ch1[M][Z],yy_ch1[M];
int xx_size =0;
int xx_ch1_size =0;
float kk;
float kk_ch1;  //DC ref k
double temp_1[Z][M];
double temp_1_ch1[Z][M];
float DCavg[1000]={0};  //DC signals
float DCavg_ch1[1000]={0};
float F2avg[1000]={0};
float Raw_F2avg[1000]={0};//@
float F2avg_ch1[1000]={0};
float Raw_F2avg_Ch1[1000]={0};//@
float DCref[1000]={0};   //DC ref;
float DCref_ch1[1000]={0};
float xpara_1[1000];//xcal 数据的平均值
double xpara_1_ch1[1000];//xcal 数据的平均值
float ypara_1[1];//ycal数据的平均值
double ypara_1_ch1[1];//ycal数据的平均值
float y_1[N];
float y_1_ch1[N];
float Q[N][L];//plsnipals 中用到
double Q_ch1[N][L];//plsnipals 中用到
float Wstar[M][A];//plsnipals
double Wstar_ch1[M][A];//plsnipals
float W[M][A];//plsnipals
double W_ch1[M][A];//plsnipals
float PW[A][A];        //inverse求逆时使用的数组（PW）^-1
double PW_ch1[A][A];        //inverse求逆时使用的数组（PW）^-1
float x_cal[N][M],y_cal[N][L];    //训练集数据  CV中定义 plsnipals要用
double x_cal_ch1[N][M],y_cal_ch1[N][L];    //训练集数据  CV中定义 plsnipals要用//@
float P[M][A];
double P_ch1[M][A];
float T[N][A];
double T_ch1[N][A];
float C[S][1];
double C_ch1[S][1];
float x_teste[60][S];
double x_teste_ch1[60][S];
float Bpls[450][1];//PLS 模型 系数矩阵
double Bpls_ch1[M][1];//PLS 模型 系数矩阵
int Num=M;
int Num_ch1=M;
int pt;//最佳主成分数
int pt_ch1;//最佳主成分数
float x[N][M],y[N][L];//pls 和cv子函数用到
double x_ch1[N][M],y_ch1[N][L];//pls 和cv子函数用到
float data[60][1013];//参比曲线矩阵
float data_ch1[60][1013];//参比曲线矩阵   //data_ch1[60][1013];//参比曲线矩阵 //@@
/********************************************CV中的大数组******************************/

    float yp[60][S],YP[60][S],YP_1[60][A];     //YP为N行A列
    double yp_ch1[60][S],YP_ch1[60][S],YP_1_ch1[60][A];     //YP为N行A列
    float x_test[60][S],y_test[60][S];   //x测试集 y测试集，x_teste为计算回归系数矩阵时使用
    double x_test_ch1[60][S],y_test_ch1[60][S];   //x测试集 y测试集，x_teste为计算回归系数矩阵时使用
    float coef_1[S][1];     //回归系数矩阵
    double coef_1_ch1[S][1];     //回归系数矩阵
    float error[60][A];          //误差
    float error_ch1[60][A];          //误差
    float error2_MEAN[S],cv[S];   //误差均值，标准差，误差计算中间寄存，CV
    float error2_MEAN_ch1[S],cv_ch1[S];   //误差均值，标准差，误差计算中间寄存，CV
    float fittedspectrum[1000]={0};
    float fittedspectrum_ch1[1000]={0};
    double cls_a_ch0[Z]={0};
    double cls_a_ch1[Z]={0};
/********************************************PLSPROSS中的大数组******************************/
     float coef[S][1];
     float coef_ch1[S][1];

    /********************************************以下为类中的数据******************************/
float Spectrum[1000];//CLS、PLS的实时谱
float Spectrum_ch1[1000];//CLS、PLS的实时谱
/********************************************以上为类中的数据******************************/

//CLS x矩阵建立  各个参考曲线谱线

        float Ref1[1000];
        float BaseSpectra[1000];
        float Ref2[1000];
        float Ref3[1000];
        float PRRef[1000];
        float VRRef[1000];
     float Ref1_ch1[1000];
        float BaseSpectra_ch1[1000];
        float Ref3_ch1[1000];
        float Ref2_ch1[1000];
        float PRRef_ch1[1000];
        float VRRef_ch1[1000];

 unsigned int spi0_hand_sig_H=74;  // PD4-J4-11
 unsigned int spi0_hand_sig_L=78;   // PD2-J4-13
 unsigned int spi1_hand_sig_H=100;  // PC10-J4-15
 unsigned int spi1_hand_sig_L=98;   // PD14-J4-17
 unsigned int spi0_mode_sig=75; //stm32_pe14
 unsigned int spi1_mode_sig=97; //stm32_2pe14
 unsigned int spi0_data_sig=79; //stm32_PE12
 unsigned int spi1_data_sig=99;

 int fd_spi0_hand_sig_H=-1;
 int fd_spi0_hand_sig_L=-1;
 int fd_spi1_hand_sig_H=-1;
 int fd_spi1_hand_sig_L=-1;
 int fd_spi0_mode_sig=-1;
 int fd_spi1_mode_sig=-1;
 int fd_spi0_data_sig=-1;
 int fd_spi1_data_sig=-1;
//plotterDlg
 int CH1=0;
 int CH2=0;
 int CH3=0;
 int CH4=0;
 /*****************MK算法 程序************/
 int  Sea_Lim_Ch0(int k_min,int k_max)
 {
       int k;
       int temp;
       int i_max;

         for(k=k_min;k<k_max;k++)
         {
            if(data[k][2]<data[k+1][2])
               temp=k+2;
            else
            {
               i_max=temp;
               break;
            }

           if(k==k_max-1)
             i_max=k_max;
          }
         if(k==k_min)
           i_max=k_min+1;

         i_max=i_max-1;

     return i_max;
  }
 int  Sea_Lim_Ch1(int k_min,int k_max)
 {
       int k;
       int temp;
       int i_max;

         for(k=k_min;k<k_max;k++)
         {
            if(data_ch1[k][2]<data_ch1[k+1][2])
               temp=k+2;
            else
            {
               i_max=temp;
               break;
            }

           if(k==k_max-1)
             i_max=k_max;
          }
         if(k==k_min)
           i_max=k_min+1;

         i_max=i_max-1;

     return i_max;
  }
//for @data  8-11//@
 void Mk_Ref(int channel)
 {
     if(channel==0)
     {
     int i,j;
     int i_Max;//@
     float fac1,fac2,fac3,fac4,fac5,fac6;


     i_Max=Sea_Lim_Ch0(0,10);//@
     for(i=0;i<i_Max;i++)
     {
         if(data[i][2]<=Pressure_act&&Pressure_act<=data[i+1][2])
         {
           fac1=(Pressure_act-data[i][2])/(data[i+1][2]-data[i][2]);
             for(j=0;j<1000;j++)
           PRRef[j]=(data[i+1][j+13]-data[i][j+13])*fac1+data[i][j+13];
         }

         if(Pressure_act<data[0][2])
         {
             for(j=0;j<1000;j++)
               PRRef[j]=(data[0][j+13]);
         }
         if(Pressure_act>data[i_Max][2])
         {
             for(j=0;j<1000;j++)
               PRRef[j]=(data[i_Max][j+13]);
         }
/*
         printf("PRRef\n");
         for(int j =0;j<1000;j++)
           printf("%G\n",PRRef[j]);
*/
     }

     i_Max=Sea_Lim_Ch0(10,20);//@
     for(i=10;i<i_Max;i++)
     {
         if(data[i][2]<=Pressure_act&&Pressure_act<=data[i+1][2])
         {
           fac2=(Pressure_act-data[i][2])/(data[i+1][2]-data[i][2]);
             for(j=0;j<1000;j++)
           Ref1[j]=(data[i+1][j+13]-data[i][j+13])*fac2+data[i][j+13];
         }
         if(Pressure_act<data[10][2])
         {
             for(j=0;j<1000;j++)
           Ref1[j]=(data[10][j+13]);
         }
         if(Pressure_act>data[i_Max][2])
         {
             for(j=0;j<1000;j++)
           Ref1[j]=(data[i_Max][j+13]);
         }

     }

     i_Max=Sea_Lim_Ch0(20,30);//@
     for(i=20;i<i_Max;i++)
     {
         if(data[i][2]<=Pressure_act&&Pressure_act<=data[i+1][2])
         {
            fac3=(Pressure_act-data[i][2])/(data[i+1][2]-data[i][2]);
             for(j=0;j<1000;j++)
           Ref2[j]=(data[i+1][j+13]-data[i][j+13])*fac3+data[i][j+13];
         }
         if(Pressure_act<data[20][2])
         {
             for(j=0;j<1000;j++)
           Ref2[j]=(data[20][j+13]);
         }
         if(Pressure_act>data[i_Max][2])
         {
             for(j=0;j<1000;j++)
           Ref2[j]=(data[i_Max][j+13]);
         }
     }

     i_Max=Sea_Lim_Ch0(30,40);//@
     for(i=30;i<i_Max;i++)
     {
        if(data[i][2]<=Pressure_act&&Pressure_act<=data[i+1][2])
         {
            fac4=(Pressure_act-data[i][2])/(data[i+1][2]-data[i][2]);
             for(j=0;j<1000;j++)
           Ref3[j]=(data[i+1][j+13]-data[i][j+13])*fac4+data[i][j+13];
         }
         if(Pressure_act<data[30][2])
         {
             for(j=0;j<1000;j++)
           Ref3[j]=(data[30][j+13]);
         }
         if(Pressure_act>data[i_Max][2])
         {
             for(j=0;j<1000;j++)
           Ref3[j]=(data[i_Max][j+13]);
         }
     }

     i_Max=Sea_Lim_Ch0(40,50);//@
     for(i=40;i<i_Max;i++)
     {
         if(data[i][2]<=Pressure_act&&Pressure_act<=data[i+1][2])
         {
           fac5=(Pressure_act-data[i][2])/(data[i+1][2]-data[i][2]);
             for(j=0;j<1000;j++)
           BaseSpectra[j]=(data[i+1][j+13]-data[i][j+13])*fac5+data[i][j+13];
         }

         if(Pressure_act<data[40][2])
         {
             for(j=0;j<1000;j++)
           BaseSpectra[j]=(data[40][j+13]);
         }
         if(Pressure_act>data[i_Max][2])
         {
             for(j=0;j<1000;j++)
           BaseSpectra[j]=(data[i_Max][j+13]);
         }
     }

     i_Max=Sea_Lim_Ch0(50,60);//@

     for(i=50;i<i_Max;i++)
     {
     if(data[i][2]<=Pressure_act&&Pressure_act<=data[i+1][2])
     {
         fac6=(Pressure_act-data[i][2])/(data[i+1][2]-data[i][2]);
          for(j=0;j<1000;j++)
       VRRef[j]=(data[i+1][j+13]-data[i][j+13])*fac6+data[i][j+13];
     }

     if(Pressure_act<data[50][2])
     {
         for(j=0;j<1000;j++)
       VRRef[j]=(data[50][j+13]);
     }
     if(Pressure_act>data[i_Max][2])
     {
         for(j=0;j<1000;j++)
       VRRef[j]=(data[i_Max][j+13]);
     }

   }

  }

   else
   {
     int i,j;
     int i_Max;//@
     float fac1,fac2,fac3,fac4,fac5,fac6;


     i_Max=Sea_Lim_Ch1(0,10);//@
     for(i=0;i<i_Max;i++)
     {
         if(data_ch1[i][2]<=Pressure_act_ch1&&Pressure_act_ch1<=data_ch1[i+1][2])
         {
            fac1=(Pressure_act_ch1-data_ch1[i][2])/(data_ch1[i+1][2]-data_ch1[i][2]);
             for(j=0;j<1000;j++)
           PRRef_ch1[j]=(data_ch1[i+1][j+13]-data_ch1[i][j+13])*fac1+data_ch1[i][j+13];
         }

         if(Pressure_act_ch1<data_ch1[0][2])
         {
             for(j=0;j<1000;j++)
           PRRef_ch1[j]=(data_ch1[0][j+13]);
         }
         if(Pressure_act_ch1>data_ch1[i_Max][2])
         {
             for(j=0;j<1000;j++)
           PRRef_ch1[j]=(data_ch1[i_Max][j+13]);
         }

     }

     i_Max=Sea_Lim_Ch1(10,20);
     for(i=10;i<i_Max;i++)
     {
         if(data_ch1[i][2]<=Pressure_act_ch1&&Pressure_act_ch1<=data_ch1[i+1][2])
         {
            fac2=(Pressure_act_ch1-data_ch1[i][2])/(data_ch1[i+1][2]-data_ch1[i][2]);
             for(j=0;j<1000;j++)
           Ref1_ch1[j]=(data_ch1[i+1][j+13]-data_ch1[i][j+13])*fac2+data_ch1[i][j+13];
         }
         if(Pressure_act_ch1<data_ch1[10][2])
         {
             for(j=0;j<1000;j++)
           Ref1_ch1[j]=(data_ch1[10][j+13]);
         }
         if(Pressure_act_ch1>data_ch1[i_Max][2])
         {
             for(j=0;j<1000;j++)
           Ref1_ch1[j]=(data_ch1[i_Max][j+13]);
         }
     }

     i_Max=Sea_Lim_Ch1(20,30);
     for(i=20;i<i_Max;i++)
     {
         if(data_ch1[i][2]<=Pressure_act_ch1&&Pressure_act_ch1<=data_ch1[i+1][2])
         {
            fac3=(Pressure_act_ch1-data_ch1[i][2])/(data_ch1[i+1][2]-data_ch1[i][2]);
             for(j=0;j<1000;j++)
           Ref2_ch1[j]=(data_ch1[i+1][j+13]-data_ch1[i][j+13])*fac3+data_ch1[i][j+13];
         }
         if(Pressure_act_ch1<data_ch1[20][2])
         {
             for(j=0;j<1000;j++)
           Ref2_ch1[j]=(data_ch1[20][j+13]);
         }
         if(Pressure_act_ch1>data_ch1[i_Max][2])
         {
             for(j=0;j<1000;j++)
           Ref2_ch1[j]=(data_ch1[i_Max][j+13]);
         }
     }

     i_Max=Sea_Lim_Ch1(30,40);
     for(i=30;i<i_Max;i++)
     {
         if(data_ch1[i][2]<=Pressure_act_ch1&&Pressure_act_ch1<=data_ch1[i+1][2])
         {
            fac4=(Pressure_act_ch1-data_ch1[i][2])/(data_ch1[i+1][2]-data_ch1[i][2]);
             for(j=0;j<1000;j++)
            Ref3_ch1[j]=(data_ch1[i+1][j+13]-data_ch1[i][j+13])*fac4+data_ch1[i][j+13];
         }
         if(Pressure_act_ch1<data_ch1[30][2])
         {
             for(j=0;j<1000;j++)
           Ref3_ch1[j]=(data_ch1[30][j+13]);
         }
         if(Pressure_act_ch1>data_ch1[i_Max][2])
         {
             for(j=0;j<1000;j++)
           Ref3_ch1[j]=(data_ch1[i_Max][j+13]);
         }
     }

     i_Max=Sea_Lim_Ch1(40,50);
     for(i=40;i<i_Max;i++)
     {
         if(data_ch1[i][2]<=Pressure_act_ch1&&Pressure_act_ch1<=data_ch1[i+1][2])
         {
           fac5=(Pressure_act_ch1-data_ch1[i][2])/(data_ch1[i+1][2]-data_ch1[i][2]);
             for(j=0;j<1000;j++)
          BaseSpectra_ch1[j]=(data_ch1[i+1][j+13]-data_ch1[i][j+13])*fac5+data_ch1[i][j+13];
         }
         if(Pressure_act_ch1<data_ch1[40][2])
         {
             for(j=0;j<1000;j++)
           BaseSpectra_ch1[j]=(data_ch1[40][j+13]);
         }
         if(Pressure_act_ch1>data_ch1[i_Max][2])
         {
             for(j=0;j<1000;j++)
           BaseSpectra_ch1[j]=(data_ch1[i_Max][j+13]);
         }
     }

     i_Max=Sea_Lim_Ch1(50,60);
     for(i=50;i<i_Max;i++)
     {
         if(data_ch1[i][2]<=Pressure_act_ch1&&Pressure_act_ch1<=data_ch1[i+1][2])
         {
           fac6=(Pressure_act_ch1-data_ch1[i][2])/(data_ch1[i+1][2]-data_ch1[i][2]);
             for(j=0;j<1000;j++)
           VRRef_ch1[j]=(data_ch1[i+1][j+13]-data_ch1[i][j+13])*fac6+data_ch1[i][j+13];
         }
         if(Pressure_act_ch1<data_ch1[50][2])
         {
             for(j=0;j<1000;j++)
           VRRef_ch1[j]=(data_ch1[50][j+13]);
         }
         if(Pressure_act_ch1>data_ch1[i_Max][2])
         {
             for(j=0;j<1000;j++)
           VRRef_ch1[j]=(data_ch1[i_Max][j+13]);
         }
      }
   }

 }



 /****CV中调用的子函数求不同主成分数下的Bpls*******/
 void plsnipals(int n,int a_1,Para *pa,int channel)   //n为训练集样本数
 {
     if(channel==0)
     {
     int a=a_1;//主成分数
     int i,j,k;                    //作为行列中间计数量
     int neither;
     float u[S],newu[S],w[S],t[S],q[S],p[S];
     float tp[N][M]={0},tq[N][L]={0};    //中间储存矩阵，无特殊意义
     float varX=0,varY=0;
     float su,st,sw,sq;     //中间变量  u'u t't w'w q'q
     float norm_1=0,norm_2=0;      //计算范数时的中间变量
     /*printf("输入矩阵\n");
     for(i=0;i<n;i++)
     {
         for(j=0;j<M;j++)
         {
             printf("%f ",x_cal[i][j]);
         }
         printf("\n");
     }*/
     for(i=0;i<n;i++)            //varX=sum(sum(X.^2))
     {
         for(j=0;j<M;j++)
         {
             varX+=x_cal[i][j]*x_cal[i][j];
         }
     }

     for(i=0;i<n;i++)            //varY=sum(sum(Y.^2))
     {
         for(j=0;j<L;j++)
         {
             varY+=y_cal[i][j]*y_cal[i][j];
         }
     }
     //printf("varX:%f \n",varX);
     //printf("varY:%f \n",varY);
     for(k=0;k<a;k++)
     {
         float error=1;
         //printf("u:\n");
                for(i=0; i<n; i++)       //第一步 即从Y中选第一列数据，令u=y1
         {
             u[i]=y_cal[i][0];
         //	printf("%f \n",u[i]);
         }
         neither=0;
         while (error>pa->erref && neither<pa->errcirNum)
         {
             for(su=0.0,i=0; i<n; i++)
                 su += u[i]*u[i];            //su=u'u
             for(j=0;j<Num;j++)
             {
                 w[j]=0.0;
                 for(i=0;i<n;i++)
                     w[j]+=x_cal[i][j]*u[i];
                 w[j]/=su;                 //第二步 计算X权值向量  w=X'u/(u'u)
             }

             for(sw=0.0,j=0; j<Num; j++)
                 sw += w[j]*w[j];
             sw=sqrt(sw);             //计算  ||w'||
             for(j=0; j<Num; j++)
             {
                 w[j] /= sw;          //第三步 归一化权值   neww=w/||w||
                 //printf("%f ",w[j]);
             }
             for(i=0;i<n;i++)
             {
                 t[i]=0.0;
                 for(j=0;j<Num;j++)
                     t[i]+=x_cal[i][j]*w[j];   //第四步 计算t=Xw
             }
             for(st=0.0,i=0;i<n;i++)
                 st+=t[i]*t[i];            //st=t't
             for(j=0;j<L;j++)
             {
                 q[j]=0.0;
                 for(i=0;i<n;i++)
                     q[j]+=y_cal[i][j]*t[i];
                 q[j]/=st;                //q=Y't/t't
             }
             for(sq=0.0,i=0;i<L;i++)
                 sq+=q[i]*q[i];            //sq=q'q
             for(i=0;i<n;i++)
             {
                 newu[i]=0.0;
                 for(j=0;j<L;j++)
                     newu[i]+=y_cal[i][j]*q[j];
                 newu[i]/=sq;                 //newu=Yq/q'q
             }
             for(i=0;i<n;i++)
             {
                 norm_1+=(newu[i]-u[i])*(newu[i]-u[i]);
             }
             norm_1=sqrt(norm_1);                    //norm(u1-u)
             for(i=0;i<n;i++)
             {
                 norm_2+=u[i]*u[i];
             }
             norm_2=sqrt(norm_2); //norm(u)
             error=norm_1/norm_2;               //cony：新增,观察U和T是否相等,计算误差是否满足条件
             for(i=0;i<n;i++)
                 u[i]=newu[i];
             neither++;
         }                              //while 结束
         for(st=0.0,i=0;i<n;i++)
             st+=t[i]*t[i];            // 重新计算st=t't
         for(j=0;j<Num;j++)
         {
             for(p[j]=0,i=0;i<n;i++)// 之前是i<N
                 p[j]+=x_cal[i][j]*t[i];
             p[j]/=st;                //p=X'*t/(t'*t)
         }
         /*printf("p:\n");
         for(i=0;i<Num;i++)
         {
             printf("%f \n",p[i]);    //显示p
         }
         printf("t:\n");
         for(i=0;i<n;i++)
         {
             printf("%f \n",t[i]);    //显示t
         } */
         for(i=0;i<n;i++)
         {
             for(j=0;j<Num;j++)
                 tp[i][j]=t[i]*p[j];
         }
         for(i=0;i<n;i++)
         {
             for(j=0;j<Num;j++)
             {
                 x_cal[i][j]-=tp[i][j];      //计算残差矩阵  X=X-tp'
             }
         }
         /*printf("cancha X\n");
         for(i=0;i<n;i++)
         {
             for(j=0;j<Num;j++)
             {
                 printf("%f ",x_cal[i][j]);    //显示残差矩阵X
             }
             printf("\n");
         } */
         for(i=0;i<n;i++)
         {
             for(j=0,tq[i][j]=0;j<L;j++)
             {
                 tq[i][j]=t[i]*q[j];
             }
         }
     /*	printf("显示t:\n");
         for(i=0;i<n;i++)
         {
             printf("%.15f \n",t[i]);
         }
         printf("显示q:\n");
         for(i=0;i<L;i++)
         {
             printf("%.15f \n",q[i]);
         } */
         for(i=0;i<n;i++)
         {
             for(j=0;j<L;j++)
             {
                 y_cal[i][j]-=tq[i][j];       //计算残差矩阵Y=Y-tq'
                 //y_cal[i][j]/=2;
             }
         }
         /*printf("cancha Y\n");
         for(i=0;i<n;i++)
         {
             for(j=0;j<L;j++)
             {
                 printf("%f ",y_cal[i][j]);    //显示残差矩阵Y
             }
             printf("\n");
         } */
         for(i=0;i<Num;i++)
         {
             W[i][k]=w[i];              // W(:,i)=w  存储W T P Q Num行A列
         }
         for(i=0;i<n;i++)
         {
             T[i][k]=t[i];              //T为N行A列矩阵
         }
         for(i=0;i<Num;i++)
         {
             P[i][k]=p[i];              //P为M行A列矩阵
         }
         for(i=0;i<L;i++)               //Q为L行A列矩阵
         {
             Q[i][k]=q[i];
         }
     }

      /* printf("W\n");
     for(i=0;i<Num;i++)
     {
         for(k=0;k<A;k++)
             printf("%G",W[i][k]);
         printf("\n");
     }
   printf("T\n");
     for(i=0;i<n;i++)
     {
         for(k=0;k<A;k++)
             printf("%f   ",T[i][k]);
         printf("\n");
     }
     printf("P\n");
     for(i=0;i<Num;i++)
     {
         for(k=0;k<A;k++)
             printf("%f   ",P[i][k]);
         printf("\n");
     }
     printf("Q\n");
     for(i=0;i<L;i++)
     {
         for(k=0;k<A;k++)
             printf("%f   ",Q[i][k]);
         printf("\n");
     }*/ //输出检测W T P Q矩阵


     for(j=0;j<a;j++)
     {
         for(k=0;k<a;k++)
         {
             for(PW[j][k]=0,i=0;i<Num;i++)
                 PW[j][k]+=P[i][j]*W[i][k];    //计算P'W
         }
     }
     /*for(i=0;i<a;i++)
     {
         for(j=0;j<a;j++)
         {
             printf("%f ",PW[i][j]);
         }
         printf("\n");
     }*/
     inverse(a,0);
     for(j=0;j<Num;j++)
     {
         for(k=0;k<a;k++)
         {
             for(Wstar[j][k]=0,i=0;i<a;i++)
                 Wstar[j][k]+=W[j][i]*PW[i][k];    //计算Wstar=W*(P'W)^-1
         }
     }
     for(j=0;j<Num;j++)
     {
         for(k=0;k<L;k++)
         {
             for(Bpls[j][k]=0,i=0;i<a;i++)
                 Bpls[j][k]+=Wstar[j][i]*Q[k][i];    //计算Bpls=Wstar*Q'
         }
     }
 /*		printf("Bpls\n");
         for(i=0;i<Num;i++)
         {
             for(j=0;j<1;j++)
                 printf("%f ",Bpls[i][j]);         //显示Bpls
             printf("\n");
         }

 */
     }
     else
     {
     int a=a_1;//主成分数
     int i,j,k;                    //作为行列中间计数量
     int neither;
     double u[S],newu[S],w[S],t[S],q[S],p[S];
     double tp[N][M]={0},tq[N][L]={0};    //中间储存矩阵，无特殊意义
     double varX=0,varY=0;
     double su,st,sw,sq;      //中间变量  u'u t't w'w q'q
     double norm_1=0,norm_2=0;      //计算范数时的中间变量
/*
     printf("matrix x_cal_ch1\n");
     for(i=0;i<n;i++)
     {
         for(j=0;j<M;j++)
         {
             printf("%d\t",j);
             printf("%f\n",x_cal_ch1[i][j]);
         }
         printf("\n");
     }
*/
     for(i=0;i<n;i++)            //varX=sum(sum(X.^2))
     {
         for(j=0;j<M;j++)
         {
             varX+=x_cal_ch1[i][j]*x_cal_ch1[i][j];
         }
     }

     for(i=0;i<n;i++)            //varY=sum(sum(Y.^2))
     {
         for(j=0;j<L;j++)
         {
             varY+=y_cal_ch1[i][j]*y_cal_ch1[i][j];
         }
     }
     //printf("varX:%f \n",varX);
     //printf("varY:%f \n",varY);
     for(k=0;k<a;k++)
     {
         printf("k %d \n",k);
         float error=1;
         //printf("u:\n");
         for(i=0; i<n; i++)              //第一步 即从Y中选第一列数据，令u=y1
         {
             u[i]=y_cal_ch1[i][0];
            //printf("%f \n",u[i]);
         }
         //printf("pa->erref %.9lf \n",pa->erref);
         //printf("pa->errcirNum %d \n",pa->errcirNum);
         neither=0;
         while (error>pa->erref && neither<1000)//pa->errcirNum
         {
             for(su=0.0,i=0; i<n; i++)
                 su += u[i]*u[i];            //su=u'u  //su=u'*u
             //printf("su %.14lf \n",su);
             for(j=0;j<Num;j++)
             {
                 w[j]=0.0;
                 for(i=0;i<n;i++)
                     w[j]+=x_cal_ch1[i][j]*u[i];

                 w[j]/=su;                 //第二步 计算X权值向量  w=X'u/(u'u)
                 //printf("%d\t",j);
                 //printf("%.14lf \n",w[j]);       //catch  1
             }

             for(sw=0.0,j=0; j<Num; j++)
                 sw += w[j]*w[j];
             sw=sqrt(sw);             //计算  ||w'||
             for(j=0; j<Num; j++)
             {
                 w[j] /= sw;          //第三步 归一化权值   neww=w/||w|| 
                 //printf("%d\t",j);
                 //printf("%.14lf \n",w[j]);      //catch  2
             }


             for(i=0;i<n;i++)
             {
                 t[i]=0.0;
                 for(j=0;j<Num;j++)
                     t[i]+=x_cal_ch1[i][j]*w[j];   //第四步 计算t=Xw
                 //printf("%d\t",i);
                 //printf("t[i] %.14lf \n",t[i]);      //catch  3
             }
             for(st=0.0,i=0;i<n;i++)
                 st+=t[i]*t[i];            //st=t't
             for(j=0;j<L;j++)
             {
                 q[j]=0.0;
                 for(i=0;i<n;i++)
                     q[j]+=y_cal_ch1[i][j]*t[i];
                 q[j]/=st;                //q=Y't/t't
                 //printf("%.14f \n", q[j]);          //catch  4
             }
             for(sq=0.0,i=0;i<L;i++)
                 sq+=q[i]*q[i];            //sq=q'q
             for(i=0;i<n;i++)
             {
                 newu[i]=0.0;
                 for(j=0;j<L;j++)
                     newu[i]+=y_cal_ch1[i][j]*q[j];
                 newu[i]/=sq;                 //newu=Yq/q'q
                 //printf("%.14f \n", newu[i]);
             }

             for(i=0;i<n;i++)
             {
                 norm_1+=(newu[i]-u[i])*(newu[i]-u[i]);
             }
             norm_1=sqrt(norm_1);                    //norm(u1-u)
             //printf("norm_1 %.14lf \n", norm_1);
             for(i=0;i<n;i++)
             {
                 norm_2+=u[i]*u[i];
             }
             norm_2=sqrt(norm_2); //norm(u)
             error=norm_1/norm_2;               //cony：新增,观察U和T是否相等,计算误差是否满足条件
             //printf("k %d \n",k);
             //printf("error %.14lf \n", error);
             norm_1=0;//Debug
             norm_2=0;//Debug
             for(i=0;i<n;i++)
                 u[i]=newu[i];
             //printf("neither %d \n",neither);
             neither++;
         }                              //while 结束
         for(st=0.0,i=0;i<n;i++)
             st+=t[i]*t[i];            // 重新计算st=t't
         for(j=0;j<Num;j++)
         {
             for(p[j]=0,i=0;i<n;i++)// 之前是i<N
                 p[j]+=x_cal_ch1[i][j]*t[i];
             p[j]/=st;                //p=X'*t/(t'*t)
         }
/*
         printf("k %d \n",k);
         printf("p:\n");
         for(i=0;i<Num;i++)
         {
             printf("%.6lf \n",p[i]);    //显示p@
         }
*/
        /*
         printf("t:\n");
         for(i=0;i<n;i++)
         {
             printf("%f \n",t[i]);    //显示t
         } */
         for(i=0;i<n;i++)
         {
             for(j=0;j<Num;j++)
                 tp[i][j]=t[i]*p[j];
         }
         for(i=0;i<n;i++)
         {
             for(j=0;j<Num;j++)
             {
                 x_cal_ch1[i][j]-=tp[i][j];      //计算残差矩阵  X=X-tp'
             }
         }
         /*printf("cancha X\n");
         for(i=0;i<n;i++)
         {
             for(j=0;j<Num;j++)
             {
                 printf("%f ",x_cal[i][j]);    //显示残差矩阵X
             }
             printf("\n");
         } */
         for(i=0;i<n;i++)
         {
             for(j=0,tq[i][j]=0;j<L;j++)
             {
                 tq[i][j]=t[i]*q[j];
             }
         }
     /*	printf("显示t:\n");
         for(i=0;i<n;i++)
         {
             printf("%.15f \n",t[i]);
         }
         printf("显示q:\n");
         for(i=0;i<L;i++)
         {
             printf("%.15f \n",q[i]);
         } */
         for(i=0;i<n;i++)
         {
             for(j=0;j<L;j++)
             {
                 y_cal_ch1[i][j]-=tq[i][j];       //计算残差矩阵Y=Y-tq'
                 //y_cal[i][j]/=2;
             }
         }
         //printf("Y=Y-tq' Y\n");
         /*
         for(i=0;i<n;i++)
         {
             for(j=0;j<L;j++)
             {
                 printf("%f ",y_cal_ch1[i][j]);    //显示残差矩阵Y
             }
             printf("\n");
         }*/
         for(i=0;i<Num;i++)
         {
             W_ch1[i][k]=w[i];              // W(:,i)=w  存储W T P Q Num行A列
         }
         for(i=0;i<n;i++)
         {
             T_ch1[i][k]=t[i];              //T为N行A列矩阵
         }
         for(i=0;i<Num;i++)
         {
             P_ch1[i][k]=p[i];              //P为M行A列矩阵
         }
         for(i=0;i<L;i++)               //Q为L行A列矩阵
         {
             Q_ch1[i][k]=q[i];
         }
     }

    /*printf("W\n");
     for(i=0;i<Num;i++)
     {
         for(k=0;k<A;k++)
             printf("%G",W_ch1[i][k]);
         printf("\n");
     }
     printf("T\n");
     for(i=0;i<n;i++)
     {
         for(k=0;k<A;k++)
             printf("%f   ",T[i][k]);
         printf("\n");
     }
     printf("P\n");
     for(i=0;i<Num;i++)
     {
         for(k=0;k<A;k++)
             printf("%f   ",P[i][k]);
         printf("\n");
     }
     printf("Q\n");
     for(i=0;i<L;i++)
     {
         for(k=0;k<A;k++)
             printf("%f   ",Q[i][k]);
         printf("\n");
     }*/ //输出检测W T P Q矩阵


     for(j=0;j<a;j++)
     {
         for(k=0;k<a;k++)
         {
             for(PW_ch1[j][k]=0,i=0;i<Num;i++)
                 PW_ch1[j][k]+=P_ch1[i][j]*W_ch1[i][k];    //计算P'W
         }
     }
     /*for(i=0;i<a;i++)
     {
         for(j=0;j<a;j++)
         {
             printf("%f ",PW[i][j]);
         }
         printf("\n");
     }*/
     inverse(a,1);
     for(j=0;j<Num;j++)
     {
         for(k=0;k<a;k++)
         {
             for(Wstar_ch1[j][k]=0,i=0;i<a;i++)
                 Wstar_ch1[j][k]+=W_ch1[j][i]*PW_ch1[i][k];    //计算Wstar=W*(P'W)^-1
         }
     }
     for(j=0;j<Num;j++)
     {
         for(k=0;k<L;k++)
         {
             for(Bpls_ch1[j][k]=0,i=0;i<a;i++)
                 Bpls_ch1[j][k]+=Wstar_ch1[j][i]*Q_ch1[k][i];    //计算Bpls=Wstar*Q'
         }
     }
/*
        printf("Bpls_ch1\n");
         for(i=0;i<Num;i++)
         {
             for(j=0;j<1;j++)
                 printf("%f ",Bpls_ch1[i][j]);         //显示Bpls
             printf("\n");
         }
        printf("go\n");
*/
  }
 }

 /***********求逆运算子函数,PLS和CLS计算过程中具有调用********/
 /********其中PW为公用矩阵，因此两种算法不能同时进行*********/

 char inverse(int x,int channel)    //x传递维度，此处等于M
 {
     if(channel==0)
     {
     float a[A][A];
     float l[A][A],U[A][A],out[A][A];
     float r[A][A],u[A][A];
     int n=x;
     int k,i,j;
     float s,t;

     for(i=0;i<n;i++)
     {
         for(j=0;j<n;j++)
             a[i][j]=PW[i][j];     //用a矩阵替换PW矩阵
     }
     //	memset( a , 0 , sizeof(a));
     memset( l , 0 , sizeof(l));
     memset( U , 0 , sizeof(U));	//矩阵清零
     memset( r , 0 , sizeof(r));
     memset( u , 0 , sizeof(u));
     for(j=0;j<n;j++)
         a[0][j]=a[0][j];  //计算U矩阵的第一行

     for(i=1;i<n;i++)
         a[i][0]=a[i][0]/a[0][0];   //计算L矩阵的第1列
     for(k=1;k<n;k++)
     {
         for(j=k;j<n;j++)
         {
             s=0;
             for (i=0;i<k;i++)
                 s=s+a[k][i]*a[i][j];   //累加
             a[k][j]=a[k][j]-s; //计算U矩阵的其他元素
         }
         for(i=k+1;i<n;i++)
         {
             t=0;
             for(j=0;j<k;j++)
                 t=t+a[i][j]*a[j][k];   //累加
             a[i][k]=(a[i][k]-t)/a[k][k];    //计算L矩阵的其他元素
         }
     }
     for(i=0;i<n;i++)
         for(j=0;j<n;j++)
         {
             if(i>j)
             {
                 l[i][j]=a[i][j]; U[i][j]=0;}//如果i>j，说明行大于列，计算矩阵的下三角部分，得出L的值，U的//为0
             else
             {
                 U[i][j]=a[i][j];
                 if(i==j)
                     l[i][j]=1;  //否则如果i<j，说明行小于列，计算矩阵的上三角部分，得出U的//值，L的为0
                 else
                     l[i][j]=0;
             }
         }

             /////////////////////求L和U矩阵的逆
         for (i=0;i<n;i++) /*求矩阵U的逆 */
         {
                           if (U[i][i]==0)
                                 return (1);//出现计算错误
                           else

                                 u[i][i]=1/U[i][i];//对角元素的值，直接取倒数

                 for (k=i-1;k>=0;k--)
                 {
                     s=0;
                     for (j=k+1;j<=i;j++)
                         s=s+U[k][j]*u[j][i];
                             u[k][i]=-s/U[k][k];//迭代计算，按列倒序依次得到每一个值，
                 }
         }
         for (i=0;i<n;i++) //求矩阵L的逆
         {
                 r[i][i]=1; //对角元素的值，直接取倒数，这里为1
                 for (k=i+1;k<n;k++)
                 {
                     for (j=i;j<=k-1;j++)
                         r[k][i]=r[k][i]-l[k][j]*r[j][i];   //迭代计算，按列顺序依次得到每一个值
                 }
         }
 //////////将r和u相乘，得到逆矩阵
 //printf("\n原矩阵的逆矩阵:\n");
         for(i=0;i<n;i++)
         {
             for(j=0;j<n;j++)
             {out[i][j]=0;}
             }
         for(i=0;i<n;i++)
         {
             for(j=0;j<n;j++)
             {
                     for(k=0;k<n;k++)
                 {
                                   out[i][j]+=u[i][k]*r[k][j];
                                 }
             }
         }
 //PW即为矩阵的逆
         for(i=0;i<n;i++)
         {
             for(j=0;j<n;j++)
                 PW[i][j]=out[i][j];
         }

         return(0);//没有计算错误
         }
         else
         {
     double a[A][A];
     double l[A][A],U[A][A],out[A][A];
     double r[A][A],u[A][A];
     int n=x;
     int k,i,j;
     double s,t;

     for(i=0;i<n;i++)
     {
         for(j=0;j<n;j++)
             a[i][j]=PW_ch1[i][j];     //用a矩阵替换PW矩阵
     }
     //	memset( a , 0 , sizeof(a));
     memset( l , 0 , sizeof(l));
     memset( U , 0 , sizeof(U));	//矩阵清零
     memset( r , 0 , sizeof(r));
     memset( u , 0 , sizeof(u));
     for(j=0;j<n;j++)
         a[0][j]=a[0][j];  //计算U矩阵的第一行

     for(i=1;i<n;i++)
         a[i][0]=a[i][0]/a[0][0];   //计算L矩阵的第1列
     for(k=1;k<n;k++)
     {
         for(j=k;j<n;j++)
         {
             s=0;
             for (i=0;i<k;i++)
                 s=s+a[k][i]*a[i][j];   //累加
             a[k][j]=a[k][j]-s; //计算U矩阵的其他元素
         }
         for(i=k+1;i<n;i++)
         {
             t=0;
             for(j=0;j<k;j++)
                 t=t+a[i][j]*a[j][k];   //累加
             a[i][k]=(a[i][k]-t)/a[k][k];    //计算L矩阵的其他元素
         }
     }
     for(i=0;i<n;i++)
         for(j=0;j<n;j++)
         {
             if(i>j)
             {
                 l[i][j]=a[i][j]; U[i][j]=0;}//如果i>j，说明行大于列，计算矩阵的下三角部分，得出L的值，U的//为0
             else
             {
                 U[i][j]=a[i][j];
                 if(i==j)
                     l[i][j]=1;  //否则如果i<j，说明行小于列，计算矩阵的上三角部分，得出U的//值，L的为0
                 else
                     l[i][j]=0;
             }
         }

             /////////////////////求L和U矩阵的逆
         for (i=0;i<n;i++) /*求矩阵U的逆 */
         {
                           if (U[i][i]==0)
                                 return (1);//出现计算错误
                           else

                                 u[i][i]=1/U[i][i];//对角元素的值，直接取倒数

                 for (k=i-1;k>=0;k--)
                 {
                     s=0;
                     for (j=k+1;j<=i;j++)
                         s=s+U[k][j]*u[j][i];
                             u[k][i]=-s/U[k][k];//迭代计算，按列倒序依次得到每一个值，
                 }
         }
         for (i=0;i<n;i++) //求矩阵L的逆
         {
                 r[i][i]=1; //对角元素的值，直接取倒数，这里为1
                 for (k=i+1;k<n;k++)
                 {
                     for (j=i;j<=k-1;j++)
                         r[k][i]=r[k][i]-l[k][j]*r[j][i];   //迭代计算，按列顺序依次得到每一个值
                 }
         }
 //////////将r和u相乘，得到逆矩阵
 //printf("\n原矩阵的逆矩阵:\n");
         for(i=0;i<n;i++)
         {
             for(j=0;j<n;j++)
             {out[i][j]=0;}
             }
         for(i=0;i<n;i++)
         {
             for(j=0;j<n;j++)
             {
                     for(k=0;k<n;k++)
                 {
                                   out[i][j]+=u[i][k]*r[k][j];
                                 }
             }
         }
 //PW即为矩阵的逆
         for(i=0;i<n;i++)
         {
             for(j=0;j<n;j++)
                 PW_ch1[i][j]=out[i][j];
         }

         return(0);//没有计算错误
 }
 }

 /*******交叉检验确定最佳主成分数**********/
 void CV( Para *pa,int channel)
 {
     if(channel==0)
     {
     int a=pa->PLS_A;                    //将主成分数寄存
     //int K=5;//method,process,order;   //K为折数，method为预处理方法,process选择时候打印进程，order选择数据排序方法
     int i,j,k;                //中间计数变量
     float temp_1,temp_2;   //中间寄存变量

     float y_1[N];            //
     float **yytest;
     float **YR=0;           //用于yytest和YR矩阵的二维空间分配

     int group,groups[N];      // group为测试集矩阵，groups为训练集矩阵
     int cal_1=0,test_1=0,temp;     //cal_1为训练集样本数，test_1为预测集样本数
     float *ypred;      //用于ypred动态分配
     int indexyy[N];            //按y大小排序后的次序
     float PRESS[N];


         //构造X矩阵
     for(i=0;i<pa->PLS_N;i++)
     {
         for(j=pa->SpectraStart;j<pa->SpectraEnd;j++)
             x[i][j-pa->SpectraStart]=data[i][j+13];//cun guangpu quxian
     }

         //构造Y矩阵
     for(i=0;i<pa->PLS_N;i++)
             y[i][0]=data[i][1];

      for(i=0;i<pa->PLS_N;i++)
         indexyy[i]=i;
     for(i=0;i<pa->PLS_N;i++)
         y_1[i]=y[i][0];      //将原始y存入y_1，由于后续程序在y上直接进行操作，可能造成原始y数据丢失，所以做备份



         for(i=0;i<pa->PLS_N;i++)
         {
             for(temp_1=0,j=0;j<pa->PLS_N-i-1;j++)      //此排序方法为冒泡法排序，冒泡法排序为稳定排序方法，由于y数据中有数据相等情况，此时稳定排序方法能保证数据相等时仍然对相等数据按照次序进行排序，而不是随机排序
             {
                 if(y[j][0]>y[j+1][0])//升序排列
                 {
                     temp_1=y[j][0];
                     y[j][0]=y[j+1][0];
                     y[j+1][0]=temp_1;
                     temp=indexyy[j];
                     indexyy[j]=indexyy[j+1];
                     indexyy[j+1]=temp;
                     for(k=0;k<Num;k++)
                     {
                         temp_2=x[j][k];
                         x[j][k]=x[j+1][k];
                         x[j+1][k]=temp_2;
                     }
                 }

             }
         }

     yytest=(float **)malloc(sizeof(float*)*pa->PLS_N);  //分配yytest矩阵空间N行
     for(i=0;i<pa->PLS_N;i++)
     {
         yytest[i]=(float*)malloc(sizeof(float)*1);   //每行分配1个空间     建立N行1列矩阵yytest
     }
     /*printf("yytest\n");
     for(i=0;i<N;i++)
     {
         yytest[i][0]=y[i][0];
         printf("%f \n",yytest[i][0]);               //测试yytest
     }*/

     YR=(float **)malloc(sizeof(float*)*pa->PLS_N);     //分配YR矩阵空间N行
     for(i=0;i<pa->PLS_N;i++)
     {
         YR[i]=(float*)malloc(sizeof(float)*a);   //每行分配a个空间     即建立N行a列矩阵YR
     }
     /*	printf("YR\n");
     for(i=0;i<N;i++)
     {
         for(j=0;j<a;j++)
         {
             YR[i][j]=x[i][j];
             printf("%f ",YR[i][j]);               //测试YR
         }
         printf("\n");
     }*/
     for(i=0;i<pa->PLS_N;i++)
     {
         groups[i]=i%pa->PLS_K+1;
             //printf("%d ",groups[i]);
     }
     for(group=1;group<pa->PLS_K+1;group++)
     {
         test_1=0;
         cal_1=0;
         for(i=0;i<pa->PLS_N;i++)
         {
             if(group==groups[i])       //计算测试集样本数
                 test_1++;
             else
                 cal_1++;               //计算训练集样本数
         }
         //printf("cal_1 is %d\n",cal_1);
     //	printf("group %d cal_1 %d test_1 %d\n",group,cal_1,test_1);
         for(i=0,k=0;i<pa->PLS_N;i++)                //将原数据矩阵分配到建好的x_cal,y_cal.x_test.y_test矩阵中
         {
             if(group==groups[i])
             {
                 for(j=0;j<Num;j++)
                 x_test[k][j]=x[i][j];
                 y_test[k][0]=y[i][0];
                 k++;
             }
         }
         for(i=0,k=0;i<pa->PLS_N;i++)
         {
             if(group!=groups[i])
             {
                 for(j=0;j<Num;j++)
                 x_cal[k][j]=x[i][j];
                 y_cal[k][0]=y[i][0];
                 k++;
             }
         }
         /*printf("x_cal\n");
         for(i=0;i<cal_1;i++)
         {
             for(j=0;j<M;j++)
                 printf("%f  ",x_cal[i][j]);         //显示x_cal
             printf("\n");
         }
         printf("y_cal\n");
         for(i=0;i<cal_1;i++)
             printf("%f ",y_cal[i][0]);             //显示y_cal
         printf("\nx_test\n");
         for(i=0;i<test_1;i++)
         {
             for(j=0;j<M;j++)
                 printf("%f  ",x_test[i][j]);       //显示x_test
             printf("\n");
         }
         printf("y_test\n");
         for(i=0;i<test_1;i++)
             printf("%f ",y_test[i][0]);             //显示y_test
         printf("\n");*/

         ypred=(float*)malloc(sizeof(double)*test_1);         //建立ypred
         for(i=0;i<Num;i++)
         {
             for(j=0,temp_1=0;j<cal_1;j++)
                 temp_1+=x_cal[j][i];
             temp_1/=cal_1;
             xpara_1[i]=temp_1;             //计算xpara_1 每列求平均
         }


                 //PSH:xpara_1[i]的值需要存入Flash

     /*	printf("xpara_1\n");
         for(i=0;i<M;i++)
             printf("%f  ",xpara_1[i]);                   //显示xpara_1  为每列均值
         printf("\n");*/

         for(i=0;i<1;i++)
         {
             for(j=0,temp_1=0;j<cal_1;j++)
                 temp_1+=y_cal[j][i];
             temp_1/=cal_1;//cony:每次试验都会得出相应的正确率，这几次结果的正确率的平均值作为对算法精度的估计
             ypara_1[i]=temp_1;             //计算ypara_1
         }

                 //PSH:ypara_1的值需要存入Flash

         /*printf("ypara_1\n");
         for(i=0;i<1;i++)
             printf("%f  ",ypara_1[i]);                   //显示ypara_1  为每列均值
         printf("\n");*/
         for(i=0;i<Num;i++)
         {
             for(j=0;j<cal_1;j++)
                 x_cal[j][i]-=xpara_1[i];       //每列的数据归一化？          //中心化x_cal
         }
         for(i=0;i<1;i++)
         {
             for(j=0;j<cal_1;j++)
                 y_cal[j][i]-=ypara_1[i];                 //中心化y_cal
         }
         //printf("x_cal\n");
         /*for(i=0;i<cal_1;i++)
         {
             for(j=0;j<M;j++)
                 printf("%f ",x_cal[i][j]);         //显示处理后的数据x_cal
             printf("\n");
         }
         printf("y_cal\n");
         for(i=0;i<cal_1;i++)
             printf("%f \n",y_cal[i][0]);  */           //显示处理后的数据y_cal

         plsnipals(cal_1,a,pa,0);   //plsnipals 迭代算法


         for(k=0;k<a;k++)
         {
             for(i=0;i<Num;i++)
                 Bpls[i][0]=0;
             for(i=0;i<Num;i++)
             {
                 for(j=0;j<k+1;j++)
                 {
                 Bpls[i][0]+=Wstar[i][j]*Q[0][j];    //分别对主成分数为不同值时计算回归系数
             //	printf("%f  ",Bpls[i][0]);
                 }
             }


             //printf("\n");
             for(i=0;i<Num;i++)
                 C[i][0]=Bpls[i][0]*1/1;          //??  C=ypara2*Bpls./xpara2'   C为M行1列
             for(i=0;i<Num;i++)
                 coef_1[i][0]=C[i][0];
             temp_1=0;
             for(i=0;i<Num;i++)
                 temp_1+=xpara_1[i]*C[i][0];
         //	printf("x*C=%f\n",temp_1);
         //	printf("ypara_1=%f\n",ypara_1[0]);
             coef_1[M][0]=ypara_1[0]-temp_1;            //coef_1比其余矩阵多一行，误差值，在coef的最后一行ypara1-xpara1*C
         /*	printf("coef\n");
             for(i=0;i<M+1;i++)
                 printf("%f\n",coef_1[i][0]);*/
             for(i=0;i<test_1;i++)//test_1测试集样本数
             {
                 for(j=0;j<Num;j++)
                     x_teste[i][j]=x_test[i][j];     //令x_teste=x_test
             }
             for(i=0;i<test_1;i++)
                 x_teste[i][Num]=1;                  //将x_teste最后一列置一 ，x_teste多加了一列1
             /*printf("x_test\n");
             for(i=0;i<test_1;i++)
             {
                 for(j=0;j<M;j++)
                     printf("%f ",x_test[i][j]);
                 printf("\n");
             }
             printf("x_teste\n");
             for(i=0;i<test_1;i++)
             {
                 for(j=0;j<M+1;j++)
                     printf("%f ",x_teste[i][j]);
                 printf("\n");
             }*/
             for(i=0;i<test_1;i++)
             {
                 ypred[i]=0;
                 for(j=0;j<M+1;j++)
                     ypred[i]+=x_teste[i][j]*coef_1[j][0];      //根据回归系数计算预测值,相当于加上了误差
             }
             /*printf("ypred:\n");
             for(i=0;i<test_1;i++)
                 printf("%f\n",ypred[i]);*/
             for(i=0;i<test_1;i++)
                 yp[i][k]=ypred[i];
         }


         /*printf("yp: \n");
         for(i=0;i<test_1;i++)
         {
             for(j=0;j<a;j++)
                 printf("%f ",yp[i][j]);
             printf("\n");
         }*/
         for(i=0,k=0;i<pa->PLS_N;i++)                //YR(indexyy,:)=YR     %%将YR与y重新排序成原矩阵
         {
             if(group==groups[i])
             {
                 for(j=0;j<Num;j++)
                 {
                     YP[i][j]=yp[k][j];
                     yytest[i][0]=y_test[k][0];      //    YR(testk,:)=[yp]         %%将真值矩阵重构 yytest(testk,:)=ytest
                 }
                 k++;
             }
         }
     /*	printf("YR: \n");
         for(i=0;i<N;i++)
         {
             for(j=0;j<a;j++)
                 printf("%f ",YP[i][j]);               //显示YR
             printf("\n");
         }
         printf("yytest\n");
         for(i=0;i<N;i++)
             printf("%f\n",yytest[i][0]);*/
         //if(process==1)
             //printf("The %dth group finished.\n",group);     //显示PROCESS

     }

     for(i=0;i<pa->PLS_N;i++)
         y[i][0]=y_1[i];             //y(indexyy)=y;

     for(i=0;i<pa->PLS_N;i++)
     {
         for(j=0;j<pa->PLS_A;j++)
             YP_1[i][j]=YP[i][j];
     }
     for(i=0;i<pa->PLS_N;i++)
     {
         temp=indexyy[i];
         for(j=0;j<pa->PLS_N;j++)
         {
             YP[temp][j]=YP_1[i][j];     //    %%将YR与y重新排序成原矩阵
         }

     }

         /*for(i=0;i<N;i++)
         {
             for(temp_1=0,j=0;j<N-i-1;j++)
             {
                 if(y[j][0]>y[j+1][0])
                 {
                     temp_1=y[j][0];
                     y[j][0]=y[j+1][0];
                     y[j+1][0]=temp_1;
                     for(k=0;k<M;k++)
                     {
                         temp_2=x[j][k];
                         x[j][k]=x[j+1][k];
                         x[j+1][k]=temp_2;
                     }
                 }

             }
         }*/

         /*printf("YR: \n");
         for(i=0;i<N;i++)
         {
             for(j=0;j<a;j++)
                 printf("%f ",YP[i][j]);               //显示YR
             printf("\n");
         }*/
 /*	printf("y:\n");
     for(i=0;i<N;i++)
         printf("%f\n",y[i][0]);             //显示y*/
     for(i=0;i<pa->PLS_N;i++)
     {
         for(j=0;j<a;j++)
             error[i][j]=YP[i][j]-y[i][0];     //计算误差
     }
 /*	printf("error: \n");
     for(i=0;i<N;i++)
     {
             for(j=0;j<a;j++)
                 printf("%f ",error[i][j]);
             printf("\n");
     }*/
     for(i=0;i<pa->PLS_N;i++)
     {
         for(j=0;j<a;j++)
             error[i][j]=error[i][j]*error[i][j];          //误差乘方
     }
     /*printf("error: \n");
     for(i=0;i<N;i++)
     {
             for(j=0;j<a;j++)
                 printf("%f ",error[i][j]);
             printf("\n");
     }*/
     for(j=0;j<a;j++)
     {
         PRESS[j]=0;
         for(i=0;i<pa->PLS_N;i++)
             PRESS[j]+=error[i][j];
     }
     //printf("PRESS:\n");
     /*
         for(i=0;i<a;i++)
         printf("%f ",PRESS[i]);
     printf("\n");
         */
     for(i=0;i<a;i++)
     {
         error2_MEAN[i]=0;
         for(j=0;j<pa->PLS_N;j++)
             error2_MEAN[i]+=error[j][i];          //error2_MEAN=sum(error2)/Mx  Mx为行数 此时的error为error2
     }
     for(i=0;i<a;i++)
         error2_MEAN[i]/=pa->PLS_N;
     /*printf("error2_MEAN\n");
     for(i=0;i<a;i++)
         printf("%f  ",error2_MEAN[i]);
     printf("\n");*/

     for(i=0;i<a;i++)
         cv[i]=sqrt(error2_MEAN[i]);
     /*printf("CV:\n");
     for(i=0;i<a;i++)
         printf("%f  ",cv[i]);
     printf("\n");*/
     for(i=0,temp_1=cv[0];i<a;i++)
     {
         if(cv[i]<temp_1)
         {
             temp_1=cv[i];            //[RMSEP,index]=min(cv);  %%RMSEP返回cv中列最小值，index返回每列最小值的行号
             pt=i+1;                    //这里temp_1为RMSEP，pt为index
         }
     }
     //printf("index为：%d\n",pt);


   //******* 计算最佳主成分数对应的矩阵Bpls，并将其存入flash*********
           for(j=0;j<M;j++)
     {
         for(k=0;k<L;k++)
         {
             for(Bpls[j][k]=0,i=0;i<pt;i++)
                 Bpls[j][k]+=Wstar[j][i]*Q[k][i];    //计算B=Wstar*Q'cony:此时计算的是最优的主成分数所对应的Bpls
         }
     }


     free(yytest);
     free(YR);
     free(ypred);
     }
     else{
     int a=pa->PLS_A;                    //将主成分数寄存
     //int K=5;//method,process,order;   //K为折数，method为预处理方法,process选择时候打印进程，order选择数据排序方法
     int i,j,k;                //中间计数变量
     double temp_1,temp_2;   //中间寄存变量

     double y_1[N];            //
     double **yytest;
     double **YR=0;           //用于yytest和YR矩阵的二维空间分配

     int group,groups[N];      // group为测试集矩阵，groups为训练集矩阵
     int cal_1=0,test_1=0,temp;     //cal_1为训练集样本数，test_1为预测集样本数
     double *ypred;      //用于ypred动态分配
     int indexyy[N];            //按y大小排序后的次序
     double PRESS[N];



         //构造X矩阵
     for(i=0;i<pa->PLS_N;i++)//@##  for(i=0;i<pa->PLS_N;i++)
     {
         //printf("data_ch1 i\n");
         for(j=pa->SpectraStart;j<pa->SpectraEnd;j++)
         {
             x_ch1[i][j-pa->SpectraStart]=data_ch1[i][j+13];//data_ch1[i][j+13];//@@
         }
         for(j=(pa->SpectraEnd-pa->SpectraStart);j<Num_ch1;j++)
         {
             x_ch1[i][j]=0.0;//data_ch1[i][j+13];//@@
         }
     }
/*
     for(i=0;i<Num_ch1;i++)    //(63--962) as (0--900) point; last 0(901--999) ;all(0--999)//OK 4
     {
         printf("%d\t",i);
         printf("%f\t",x_ch1[0][i]);
         printf("%f\t",x_ch1[1][i]);
         printf("%f\t",x_ch1[2][i]);
         printf("%f\t",x_ch1[3][i]);
         printf("%f\n",x_ch1[4][i]);
     }
 */
    printf("pa->PLS_N %d\n",pa->PLS_N); //  Change @1
    printf("pa->SpectraStart %d\n",pa->SpectraStart);//@2
         //构造Y矩阵
     for(i=0;i<pa->PLS_N;i++)
     {
             y_ch1[i][0]=data_ch1[i][4];//@## data_ch1[i][1];
      //printf("y_ch1[i][0] %G\n",y_ch1[i][0]);//OK 2
     }

     //printf("i %d\n",i);
      for(i=0;i<pa->PLS_N;i++)
         indexyy[i]=i;

     for(i=0;i<pa->PLS_N;i++)
         y_1[i]=y_ch1[i][0];      //将原始y存入y_1，由于后续程序在y上直接进行操作，可能造成原始y数据丢失，所以做备份



         for(i=0;i<pa->PLS_N;i++)
         {
             for(temp_1=0,j=0;j<pa->PLS_N-i-1;j++)      //此排序方法为冒泡法排序，冒泡法排序为稳定排序方法，由于y数据中有数据相等情况，此时稳定排序方法能保证数据相等时仍然对相等数据按照次序进行排序，而不是随机排序
             {
                 if(y_ch1[j][0]>y_ch1[j+1][0])//升序排列
                 {
                     temp_1=y_ch1[j][0];
                     y_ch1[j][0]=y_ch1[j+1][0];
                     y_ch1[j+1][0]=temp_1;
                     temp=indexyy[j];
                     indexyy[j]=indexyy[j+1];
                     indexyy[j+1]=temp;
                     for(k=0;k<Num;k++)
                     {
                         temp_2=x_ch1[j][k];
                         x_ch1[j][k]=x_ch1[j+1][k];
                         x_ch1[j+1][k]=temp_2;  //MAX J+1 5 //K  Num  M  999
                     }
                 }
             }
         }

/*
         for(i=0;i<pa->PLS_N;i++)
         {
          printf("i %d\n",i);
          printf("y_ch1[i][0] %G\n",y_ch1[i][0]);  //OK 3
         }
*/
/*
         for(i=0;i<=Num;i++)      //63--899 as 900 point  //OK 4
         {
             printf("%d\t",i);
             printf("%G\t",x_ch1[0][i]);
             printf("%G\t",x_ch1[1][i]);
             printf("%G\t",x_ch1[2][i]);
             printf("%G\t",x_ch1[3][i]);
             printf("%G\n",x_ch1[4][i]);
         }
*/
     yytest=(double **)malloc(sizeof(double*)*pa->PLS_N);  //分配yytest矩阵空间N行
     for(i=0;i<pa->PLS_N;i++)
     {
         yytest[i]=(double*)malloc(sizeof(double)*1);   //每行分配1个空间     建立N行1列矩阵yytest
     }
/*
     printf("yytest\n");
     for(i=0;i<pa->PLS_N;i++)
     {
         yytest[i][0]=y[i][0];
         printf("%f \n",yytest[i][0]);               //测试yytest
     }
*/
     YR=(double **)malloc(sizeof(double*)*pa->PLS_N);     //分配YR矩阵空间N行
     for(i=0;i<pa->PLS_N;i++)
     {
         YR[i]=(double*)malloc(sizeof(double)*a);   //每行分配a个空间     即建立N行a列矩阵YR
     }
/*
     printf("YR\n");              //All 0.00    //测试YR //OK 5
     for(i=0;i<N;i++)
     {
         for(j=0;j<a;j++)
         {
             YR[i][j]=x[i][j];
             printf("%f ",YR[i][j]);
         }
         printf("\n");
     }

*/

     for(i=0;i<pa->PLS_N;i++)
     {
         groups[i]=i%pa->PLS_K+1;
           //printf("i %d ",i);
           //printf("groups[i] %d ",groups[i]);      //OK   6
           //printf("\n");
     }

     for(group=1;group<pa->PLS_K+1;group++)
     {
         printf("group %d \n",group);
         test_1=0;
         cal_1=0;
         for(i=0;i<pa->PLS_N;i++)
         {
             if(group==groups[i])       //计算测试集样本数 Fold=2 test_1 3
                 test_1++;
             else
                 cal_1++;               //计算训练集样本数  Fold=2 cal_1 4
         }
        //printf("cal_1 is %d\n",cal_1);
        printf("pa->PLS_N is %d\n",pa->PLS_N);
        //printf("group %d cal_1 %d test_1 %d\n",group,cal_1,test_1);   //OK 7
         for(i=0,k=0;i<pa->PLS_N;i++)                //将原数据矩阵分配到建好的x_cal,y_cal.x_test.y_test矩阵中
         {
             if(group==groups[i])
             {
                 for(j=0;j<Num;j++)
                 x_test_ch1[k][j]=x_ch1[i][j];
                 y_test_ch1[k][0]=y_ch1[i][0];
                 //printf("%d\n",k);                                    //OK 8
                 //printf("y_test_ch1[k][0] is %G\n",y_test_ch1[k][0]); //y_ch1[i][0]
                 k++;
             }
         }

         for(i=0,k=0;i<pa->PLS_N;i++)
         {
             //printf("ffx_cal_ch1\n");                               //x_cal_ch1 建模数据 kko
             if(group!=groups[i])
             {
                 for(j=0;j<Num;j++)
               {
                 x_cal_ch1[k][j]=x_ch1[i][j];
                 //printf("%d\t",j);
                 //printf("%f \n",x_cal_ch1[k][j]);
               }
                 y_cal_ch1[k][0]=y_ch1[i][0];
                 k++;
             }
         }
/*
         printf("x_test\n");
         for(i=0;i<cal_1;i++)
         {
             for(j=0;j<Num;j++)
             {
                 printf("%d \t",j);
                 printf("%f \t",x_test_ch1[i][j]);       //x_test_ch1    //OK 9
                 printf("\n");
             }
           printf("\n");
         }
*/
 /*
         printf("x_cal_ch1\n");
         for(i=0;i<test_1;i++)
         {
             for(j=0;j<Num;j++)
             {
                 printf("%d \t",j);
                 printf("%.14lf \t",x_cal_ch1[i][j]);       //x_cal_ch1    //OK
                 printf("\n");
             }
           printf("\n");
         }
*/
        /* printf("y_cal\n");
         for(i=0;i<cal_1;i++)
             printf("%f ",y_cal[i][0]);             //显示y_cal
        */

         ypred=(double*)malloc(sizeof(double)*test_1);         //建立ypred
         for(i=0;i<Num;i++)//??
         {
             for(j=0,temp_1=0;j<cal_1;j++)
                 temp_1+=x_cal_ch1[j][i];
             temp_1/=cal_1;
             xpara_1_ch1[i]=temp_1;             //计算xpara_1 每列求平均
         }

                  //PSH:xpara_1[i]的值需要存入Flash
/*
        printf("xpara_1_ch1\n");
         for(i=0;i<Num;i++)
            {
             printf("%d \t",i);
             printf("%.14lf\t",xpara_1_ch1[i]);                   //显示xpara_1  为每列均值//OK 10
             printf("\n");
            }
*/
         for(i=0;i<1;i++)
         {
             for(j=0,temp_1=0;j<cal_1;j++)
                 temp_1+=y_cal_ch1[j][i];
             temp_1/=cal_1;//cony:每次试验都会得出相应的正确率，这几次结果的正确率的平均值作为对算法精度的估计
             //printf("cal_1%d\t",cal_1);
             //printf("temp_1%G\t",temp_1);
             ypara_1_ch1[i]=temp_1;                    //计算ypara_1
             //printf("ypara_1[i] %G",ypara_1_ch1[i]);                    //OK 11
         }


       //PSH:ypara_1的值需要存入Flash
/*
         printf("ypara_1\n");
         for(i=0;i<1;i++)
         {
             printf("%d \t",i);
             printf("%f  ",ypara_1[i]);                   //显示ypara_1  为每列均值
             printf("\n");
         }
*/
//data
         for(i=0;i<Num;i++)
         {
             for(j=0;j<cal_1;j++)
                 x_cal_ch1[j][i]-=xpara_1_ch1[i];       //每列的数据归一化？          //中心化x_cal
         }
         for(i=0;i<1;i++)
         {
             for(j=0;j<cal_1;j++)
                 y_cal_ch1[j][i]-=ypara_1_ch1[i];                 //中心化y_cal
         }
/*
         printf("x_cal_ch1\n");                                    //OK 12
         //printf("cal_1 %d\n",cal_1);
         for(i=0;i<Num;i++)
         {
             for(j=0;j<cal_1;j++)
                printf("%.4lf\t",x_cal_ch1[j][i]);
             printf("\n");
         }
*/
         //printf("cal_1 %d\n",cal_1);
         /*for(i=0;i<cal_1;i++)
         {
             for(j=0;j<M;j++)
                 printf("%.2lf  ",x_cal[i][j]);         //显示x_cal
             printf("\n");
         }
         x_cal_ch1
         for(i=0;i<cal_1;i++)
             printf("%f \n",y_cal[i][0]);  */           //显示处理后的数据y_cal

         plsnipals(cal_1,a,pa,1);   //plsnipals 迭代算法   (a:主成分数pa->PLS_A)

/*
             printf("Bpls_ch1\n");
               for(i=0;i<Num;i++)
               {
                  for(j=0;j<1;j++)
                      printf("%f ",Bpls_ch1[i][j]);         //显示Bpls
                   printf("\n");
               }
              printf("go\n");
*/

         for(k=0;k<a;k++)
         {
             for(i=0;i<Num;i++)
                 Bpls_ch1[i][0]=0;
             for(i=0;i<Num;i++)
             {
                 for(j=0;j<k+1;j++)
                 {
                 Bpls_ch1[i][0]+=Wstar_ch1[i][j]*Q_ch1[0][j];    //分别对主成分数为不同值时计算回归系数
             //	printf("%f  ",Bpls[i][0]);
                 }
             }


             //printf("\n");
             for(i=0;i<Num;i++)
                 C_ch1[i][0]=Bpls_ch1[i][0]*1/1;          //??  C=ypara2*Bpls./xpara2'   C为M行1列
             for(i=0;i<Num;i++)
                 coef_1_ch1[i][0]=C_ch1[i][0];
             temp_1=0;
             for(i=0;i<Num;i++)
                 temp_1+=xpara_1_ch1[i]*C_ch1[i][0];
         //	printf("x*C=%f\n",temp_1);
         //	printf("ypara_1=%f\n",ypara_1[0]);
             coef_1_ch1[M][0]=ypara_1_ch1[0]-temp_1;            //coef_1比其余矩阵多一行，误差值，在coef的最后一行ypara1-xpara1*C
         /*	printf("coef\n");
             for(i=0;i<M+1;i++)
                 printf("%f\n",coef_1[i][0]);*/
             for(i=0;i<test_1;i++)//test_1测试集样本数
             {
                 for(j=0;j<Num;j++)
                     x_teste_ch1[i][j]=x_test_ch1[i][j];     //令x_teste=x_test
             }
             for(i=0;i<test_1;i++)
                 x_teste_ch1[i][Num]=1;                  //将x_teste最后一列置一 ，x_teste多加了一列1
             /*printf("x_test\n");
             for(i=0;i<test_1;i++)
             {
                 for(j=0;j<M;j++)
                     printf("%f ",x_test[i][j]);
                 printf("\n");
             }
             printf("x_teste\n");
             for(i=0;i<test_1;i++)
             {
                 for(j=0;j<M+1;j++)
                     printf("%f ",x_teste[i][j]);
                 printf("\n");
             }*/
             for(i=0;i<test_1;i++)
             {
                 ypred[i]=0;
                 for(j=0;j<M+1;j++)
                     ypred[i]+=x_teste_ch1[i][j]*coef_1_ch1[j][0];      //根据回归系数计算预测值,相当于加上了误差
             }
//@data 10-27

             printf("ypred:\n");
             for(i=0;i<test_1;i++)
                 printf("%f\n",ypred[i]);

             for(i=0;i<test_1;i++)
                 yp_ch1[i][k]=ypred[i];

         }
//@data 11-01 now
//printf("get in CH2 PLS Val CV\n");//@ ok
         /*printf("yp: \n");
         for(i=0;i<test_1;i++)
         {
             for(j=0;j<a;j++)
                 printf("%f ",yp[i][j]);
             printf("\n");
         }*/
         for(i=0,k=0;i<pa->PLS_N;i++)                //YR(indexyy,:)=YR     %%将YR与y重新排序成原矩阵
         {
             if(group==groups[i])
             {
                 for(j=0;j<Num;j++)
                 {
                     YP_ch1[i][j]=yp_ch1[k][j];
                     yytest[i][0]=y_test_ch1[k][0];      //    YR(testk,:)=[yp]         %%将真值矩阵重构 yytest(testk,:)=ytest
                 }
                 k++;
             }
         }
 //printf("get in CH2 PLS Val CV\n");//@ ok
     /*	printf("YR: \n");
         for(i=0;i<N;i++)
         {
             for(j=0;j<a;j++)
                 printf("%f ",YP[i][j]);               //显示YR
             printf("\n");
         }
         printf("yytest\n");
         for(i=0;i<N;i++)
             printf("%f\n",yytest[i][0]);*/
         //if(process==1)
             //printf("The %dth group finished.\n",group);     //显示PROCESS
//printf("get in CH2 PLS Val CV OK\n");//OK
     }

     for(i=0;i<pa->PLS_N;i++)
         y_ch1[i][0]=y_1[i];             //y(indexyy)=y;

     for(i=0;i<pa->PLS_N;i++)
     {
         for(j=0;j<pa->PLS_A;j++)
             YP_1_ch1[i][j]=YP_ch1[i][j];
     }
     for(i=0;i<pa->PLS_N;i++)
     {
         temp=indexyy[i];
         for(j=0;j<pa->PLS_N;j++)
         {
             YP_ch1[temp][j]=YP_1_ch1[i][j];     //    %%将YR与y重新排序成原矩阵
         }

     }
//printf("get in CH2 PLS Val CV NO\n");//@  //NO  //OK
         /*for(i=0;i<N;i++)
         {
             for(temp_1=0,j=0;j<N-i-1;j++)
             {
                 if(y[j][0]>y[j+1][0])
                 {
                     temp_1=y[j][0];
                     y[j][0]=y[j+1][0];
                     y[j+1][0]=temp_1;
                     for(k=0;k<M;k++)
                     {
                         temp_2=x[j][k];
                         x[j][k]=x[j+1][k];
                         x[j+1][k]=temp_2;
                     }
                 }

             }
         }*/

         /*printf("YR: \n");
         for(i=0;i<N;i++)
         {
             for(j=0;j<a;j++)
                 printf("%f ",YP[i][j]);               //显示YR
             printf("\n");
         }*/
 /*	printf("y:\n");
     for(i=0;i<N;i++)
         printf("%f\n",y[i][0]);             //显示y*/
     for(i=0;i<pa->PLS_N;i++)
     {
         for(j=0;j<a;j++)
             error_ch1[i][j]=YP_ch1[i][j]-y_ch1[i][0];     //计算误差
     }
 /*	printf("error: \n");
     for(i=0;i<N;i++)
     {
             for(j=0;j<a;j++)
                 printf("%f ",error[i][j]);
             printf("\n");
     }*/
     for(i=0;i<pa->PLS_N;i++)
     {
         for(j=0;j<a;j++)
             error_ch1[i][j]=error_ch1[i][j]*error_ch1[i][j];          //误差乘方
     }
     /*printf("error: \n");
     for(i=0;i<N;i++)
     {
             for(j=0;j<a;j++)
                 printf("%f ",error[i][j]);
             printf("\n");
     }*/
     for(j=0;j<a;j++)
     {
         PRESS[j]=0;
         for(i=0;i<pa->PLS_N;i++)
             PRESS[j]+=error_ch1[i][j];
     }
     //printf("get in CH2 PLS Val CV\n");//@
     //printf("PRESS:\n");
     /*
         for(i=0;i<a;i++)
         printf("%f ",PRESS[i]);
     printf("\n");
         */
     for(i=0;i<a;i++)
     {
         error2_MEAN_ch1[i]=0;
         for(j=0;j<pa->PLS_N;j++)
             error2_MEAN_ch1[i]+=error_ch1[j][i];          //error2_MEAN=sum(error2)/Mx  Mx为行数 此时的error为error2
     }
     for(i=0;i<a;i++)
         error2_MEAN_ch1[i]/=pa->PLS_N;
     /*printf("error2_MEAN\n");
     for(i=0;i<a;i++)
         printf("%f  ",error2_MEAN[i]);
     printf("\n");*/

     for(i=0;i<a;i++)
         cv_ch1[i]=sqrt(error2_MEAN_ch1[i]);
     /*printf("CV:\n");
     for(i=0;i<a;i++)
         printf("%f  ",cv[i]);
     printf("\n");*/
     for(i=0,temp_1=cv_ch1[0];i<a;i++)
     {
         if(cv_ch1[i]<temp_1)
         {
             temp_1=cv_ch1[i];            //[RMSEP,index]=min(cv);  %%RMSEP返回cv中列最小值，index返回每列最小值的行号
             pt_ch1=i+1;                    //这里temp_1为RMSEP，pt为index
         }
     }
     //printf("index为：%d\n",pt);

printf("get in CH2 PLS Val CV NO\n");//@  //P Ok
   //******* 计算最佳主成分数对应的矩阵Bpls，并将其存入flash*********
           for(j=0;j<M;j++)
     {
         for(k=0;k<L;k++)
         {
             for(Bpls_ch1[j][k]=0,i=0;i<pt_ch1;i++)
                 Bpls_ch1[j][k]+=Wstar_ch1[j][i]*Q_ch1[k][i];    //计算B=Wstar*Q'cony:此时计算的是最优的主成分数所对应的Bpls
         }
     }
  //printf("get in CH2 PLS Val CV NO1\n");//@  //NO

     free(yytest);
     free(YR);
     free(ypred);
     }
 }

 void DigitalFilter( float *Spectrum1)//多项式平滑滤波
 {

  // int i, j, k;
    float DFSum =0.0;
    int DFstart;
    int DFHalf = 12;//@
    int DFend;
    int POINTS = 1000;
    int DFh[13]={467,462,447,422,387,322,287,222,147,62,-33,-138,-253};//@
    float DFdata[1000];

       DFSum = 0.0;
       DFstart = DFHalf;
       DFend = POINTS - DFHalf;
       for( int i = 0; i < POINTS; i++ )
       {
         DFdata[i] = Spectrum1[i];   // equivalent to *(Spectrum + i)
       }
       for(int j = DFstart; j < DFend; j++ )
       {
         for(int k = 1; k <= DFHalf; k++ )
         {
           DFSum = DFSum + (DFh[k] * DFdata[j + k]) + (DFh[k] * DFdata[j - k]);//多项式滤波，DFh[]是固定系数，-k和k是对称相等的、
         }
         Spectrum1[j] = (DFSum + DFh[0] * DFdata[j])/5175;//@
         DFSum = 0.0;
       }

     for(int i = 0; i < DFHalf; i++ )
     {
       Spectrum1[i] = 0.0;
     }
     for(int  i = DFend; i < POINTS; i++ )
     {
       Spectrum1[i] = 0.0;
     }
 }
 float Mv_Ag(int flag1,int Num1,float data11,int channel)//flag1=1代表浓度，0代表峰值,Num1代表滑动平均次数，data11代表需要滑动平均的数据
 {
     if(channel==0)
     {
     int m;
     int n;
     int MovCount=0,PkTrkCount=0;
     float Conc,Height;
     if(flag1==1)
     {
       Conc=data11;
       for( m=Num1-1;m>0;m--)
       {MovTemp[Num1-m-1] = MovTemp[Num1-m];}
       MovTemp[Num1-1] = Conc;
       Conc = 0.0;
       for( n=0;n<Num1;n++)
       {
        if(MovTemp[n] != 20000)
         {MovCount++; Conc = Conc + MovTemp[n]; }
       }
      return Conc =(1.0* Conc)/MovCount;                         //最终汇报的Conc
      //  MovCount=0;
     }
     else
     {
      Height=data11;
      for( m=Num1-1;m>0;m--)
          {PkTrkTemp[Num1-m-1] = PkTrkTemp[Num1-m];}
      PkTrkTemp[Num1-1] = Height;
      Height = 0.0;
      for( n=0;n<Num1;n++)
      {
       if(PkTrkTemp[n] != 20000)
       {PkTrkCount++; Height = Height + PkTrkTemp[n]; }
      }
      Height =(1.0* Height)/PkTrkCount;                     //最终汇报的PeakHeight
      return    Height;
     // PkTrkCount=0;
     }
     }
     else
     {
     int m;
     int n;
     int MovCount=0,PkTrkCount=0;
     float Conc,Height;
     if(flag1==1)
     {
         Conc=data11;
  for( m=Num1-1;m>0;m--)
       {MovTemp_ch1[Num1-m-1] = MovTemp_ch1[Num1-m];}
       MovTemp_ch1[Num1-1] = Conc;
       Conc = 0.0;
       for( n=0;n<Num1;n++)
       {
        if(MovTemp_ch1[n] != 20000)
         {MovCount++; Conc = Conc + MovTemp_ch1[n]; }
       }
      return Conc =(1.0* Conc)/MovCount;                         //最终汇报的Conc
     //  MovCount=0;
     }
     else
     {
         Height=data11;
      for( m=Num1-1;m>0;m--)
          {PkTrkTemp_ch1[Num1-m-1] = PkTrkTemp_ch1[Num1-m];}
      PkTrkTemp_ch1[Num1-1] = Height;
      Height = 0.0;
      for( n=0;n<Num1;n++)
      {
       if(PkTrkTemp_ch1[n] != 20000)
       {PkTrkCount++; Height = Height + PkTrkTemp_ch1[n]; }
      }
      Height =(1.0* Height)/PkTrkCount;                         //最终汇报的PeakHeight
      return   Height  ;
     // PkTrkCount=0;
     }
     }
 }


 /*****************CLS算法 程序************/
 void cls(Para *pa,Conc *Rs,int channel,bool PV_Flag)
 {
     //printf("cls PV_Flag %d\n",PV_Flag);
     if(channel==0)
     {
         int Number;
         int i=0;
         int j=-1;
         int l= -1;
         int k;
         int count;
         int MatrixSize;//x的列数
         double a[Z];

         pa->SpectraStart=80;//截取光谱计算
         pa->SpectraEnd=800;

         j=-1;

         Number=pa->SpectraEnd-pa->SpectraStart;//数据长度80---799

 //判断过程气参考谱 构造X矩阵
      if (PV_Flag)     //Pro
      {

          if((pa->PRuse==1)||(pa->PRuse==3))
          {   j++;
              for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
              xx[i-pa->SpectraStart][j]=PRRef[i];        //R1   PROCESS REF
          }

         if((pa->R1use==1)||(pa->R1use==3))
         {   j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx[i-pa->SpectraStart][j]=Ref1[i];         //R2    CH4
         }
         if((pa->R2use==1)||(pa->R2use==3))
         {   j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx[i-pa->SpectraStart][j]=Ref2[i];         //R3
         }
         if((pa->R3use==1)||(pa->R3use==3))
         {
             j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx[i-pa->SpectraStart][j]=Ref3[i];         //R4
         }
         if((pa->Baseuse==1)||(pa->Baseuse==3))
        {	j++;
            for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
            xx[i-pa->SpectraStart][j]=BaseSpectra[i];   //R5
        }
         if((pa->VRuse==1)||(pa->VRuse==3))
         {	j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx[i-pa->SpectraStart][j]=VRRef[i];       //R6  VALIDATION REF
         }
          j++;
         for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)   //C0
         xx[i-pa->SpectraStart][j]=1.0;

         MatrixSize = j+1;
      }
      //判断校验气参考谱 构造X矩阵
      else    //Val
      {

          if((pa->PRuse==2)||(pa->PRuse==3))
          {   j++;
              for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
              xx[i-pa->SpectraStart][j]=PRRef[i];       //R1   PROCESS REF
          }
         if((pa->R1use==2)||(pa->R1use==3))
         {   j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx[i-pa->SpectraStart][j]=Ref1[i];        //R2    CH4
          }
         if((pa->R2use==2)||(pa->R2use==3))
         {   j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx[i-pa->SpectraStart][j]=Ref2[i];         //R3
         }
         if((pa->R3use==2)||(pa->R3use==3))
         {
             j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx[i-pa->SpectraStart][j]=Ref3[i];         //R4
         }
         if((pa->Baseuse==2)||(pa->Baseuse==3))
         {	j++;
            for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
            xx[i-pa->SpectraStart][j]=BaseSpectra[i];   //R5
         }
         if((pa->VRuse==2)||(pa->VRuse==3))
         {	j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx[i-pa->SpectraStart][j]=VRRef[i];       //R6  VALIDATION REF
         }
         j++;
         for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)  //C0
         xx[i-pa->SpectraStart][j]=1.0;

         MatrixSize = j+1;
      }
/*
       printf("pa->PRuse %d\n",pa->PRuse);
       printf("pa->R1use %d\n",pa->R1use);
       printf("pa->R2use %d\n",pa->R2use);
       printf("pa->R3use %d\n",pa->R3use);
       printf("pa->Baseuse %d\n",pa->Baseuse);
       printf("pa->VRuse %d\n",pa->VRuse);
*/

         for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
         {
                yy[i- pa->SpectraStart]= Spectrum[i];
         }


         for(j=0;j<MatrixSize;j++)
         {
             for(k=0;k<MatrixSize;k++)
             {
                 for(PW[j][k]=0,i=0;i<Number;i++)
                     PW[j][k]+=xx[i][j]*xx[i][k];
             }
         }


         if((inverse(MatrixSize,0))==0)      //此处的MatrixSize为传递的维度。inverse之后得到的数据就为求逆之后的了。

         {
         for(i=0;i<MatrixSize;i++)
         {
             for(j=0;j<Number;j++)
             {
                 for(temp_1[i][j]=0,k=0;k<MatrixSize;k++)
                     temp_1[i][j]+=PW[i][k]*xx[j][k];
             }
         }
         for(i=0;i<MatrixSize;i++)
         {
             for(a[i]=0,j=0;j<Number;j++)
                 a[i]+=temp_1[i][j]*yy[j];
         }

         Rs->CLSFitRatio=a[0];
         }

         xx_size =  MatrixSize;

         //printf("xx_size %d\n",xx_size);


         l=-1;

         if (PV_Flag)//PVModel=1 过程气
         {

             if((pa->PRuse==1)||(pa->PRuse==3))
             {   l++;
                 for(int i=0;i<1000;i++)
                 xx[i][l]=PRRef[i];       //PR   PROCESS REF
             }
            if((pa->R1use==1)||(pa->R1use==3))
            {   l++;
                for(int i=0;i<1000;i++)
                xx[i][l]=Ref1[i];        //R1 CH4
             }
            if((pa->R2use==1)||(pa->R2use==3))
            {   l++;
                for(int i=0;i<1000;i++)
                xx[i][l]=Ref2[i];         //R2
            }
            if((pa->R3use==1)||(pa->R3use==3))
            {
                l++;
                for(int i=0;i<1000;i++)
                xx[i][l]=Ref3[i];         //R3
            }

            if((pa->Baseuse==1)||(pa->Baseuse==3))
            {	l++;
                for(int i=0;i<1000;i++)
                xx[i][l]=BaseSpectra[i];   // baseline
            }
            if((pa->VRuse==1)||(pa->VRuse==3))
            {	l++;
                for(int i=0;i<1000;i++)
                xx[i][l]=VRRef[i];         //VR  VALIDATION REF
            }

         }
         //判断校验气参考谱 构造X矩阵
         else
         {
             if((pa->PRuse==2)||(pa->PRuse==3))
             {   l++;
                 for(int i=0;i<1000;i++)
                 xx[i][l]=PRRef[i];       //PR   PROCESS REF
             }
            if((pa->R1use==2)||(pa->R1use==3))
            {   l++;
                for(int i=0;i<1000;i++)
                xx[i][l]=Ref1[i];         //R1 CH4
             }
            if((pa->R2use==2)||(pa->R2use==3))
            {   l++;
                for(int i=0;i<1000;i++)
                xx[i][l]=Ref2[i];         //R2
            }
            if((pa->R3use==2)||(pa->R3use==3))
            {
                l++;
                for(int i=0;i<1000;i++)
                xx[i][l]=Ref3[i];         //R3
            }
            if((pa->Baseuse==2)||(pa->Baseuse==3))
            {	l++;
                for(int i=0;i<1000;i++)
                xx[i][l]=BaseSpectra[i];  // baseline
            }
            if((pa->VRuse==2)||(pa->VRuse==3))
            {	l++;
                for(int i=0;i<1000;i++)
                xx[i][l]=VRRef[i];        //VR  VALIDATION REF
            }


         }

         for(int i = 0; i<1000;i++)
               fittedspectrum[i]=0;

         for(int i = pa->SpectraStart; i<pa->SpectraEnd;i++)
         {
             for(int j = 0; j<MatrixSize;j++)
             {
                 fittedspectrum[i] += a[j]*xx[i][j];
             }
         }


         for(int i =0;i<Z;i++)
             cls_a_ch0[i] = a[i];


        }
        else
        {
         int Number;
         int i=0;
         int l=-1;
         int j=-1;
         int k;
        int count;
     //	const int filecount=60; //TEXT文件夹里存在的文本文档数
         int MatrixSize   ;//x的列数
         double a[Z];
     //	char file_head[30] ="data";
     //	char filename[10];
     //	FILE *fp1;
         pa->SpectraStart=80;
         pa->SpectraEnd=800;
     /*	for(count=1;count<=filecount;count++)
         {

             sprintf(filename,"%s%d.txt",file_head,count);
             printf("\n正在打开------------%d\n",count);
             // fp1=fopen(filename,"r");//打开文件以便写入数据
              if((fp1 = fopen(filename, "rb")) == NULL)

                 {

                 printf("cannot open text.txt!\n");


                 }
 */
              /******make reference的算法**********/
 /*			for(i=0;i<M;i=i+2)
             {
               fscanf(fp1,"%G",&Spectrum[i]);
               fscanf(fp1,"%G",&Re->BaseLine[i]);
               fscanf(fp1,"%G",&Re->BaseSpectra[i]);
               fscanf(fp1,"%G",&Re->Ref3[i]);

             }
             for(i=1;i<M;i=i+2)
             {
               Re->BaseLine[i]=( Re->BaseLine[i-1]+ Re->BaseLine[i+1])/2.0;
               Re->BaseSpectra[i]=( Re->BaseSpectra[i-1]+ Re->BaseSpectra[i+1])/2.0;
               Re->Ref3[i]=( Re->Ref3[i-1]+ Re->Ref3[i+1])/2.0;
               Spectrum[i]=(Spectrum[i-1]+Spectrum[i+1])/2.0;
             }
             */


         Number=pa->SpectraEnd-pa->SpectraStart;//数据长度

         //判断过程气参考谱 构造X矩阵
      if (PV_Flag)//PVModel=1 过程气
      {

          if((pa->PRuse==1)||(pa->PRuse==3))
          {   j++;
              for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
              xx_ch1[i-pa->SpectraStart][j]=PRRef_ch1[i];       //PR   PROCESS REF
          }
         if((pa->R1use==1)||(pa->R1use==3))
         {   j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx_ch1[i-pa->SpectraStart][j]=Ref1_ch1[i];         //R1 CH4
          }
         if((pa->R2use==1)||(pa->R2use==3))
         {   j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx_ch1[i-pa->SpectraStart][j]=Ref2_ch1[i];         //R2
         }
         if((pa->R3use==1)||(pa->R3use==3))
         {
             j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx_ch1[i-pa->SpectraStart][j]=Ref3_ch1[i];         //R3
         }

         if((pa->Baseuse==1)||(pa->Baseuse==3))
         {	j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx_ch1[i-pa->SpectraStart][j]=BaseSpectra_ch1[i];  // baseline
         }
         if((pa->VRuse==1)||(pa->VRuse==3))
         {	j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx_ch1[i-pa->SpectraStart][j]=VRRef_ch1[i];      //VR  VALIDATION REF
         }
         j++;
         for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
         xx_ch1[i-pa->SpectraStart][j]=1.0;

         MatrixSize = j+1;
      }
      //判断校验气参考谱 构造X矩阵
      else
      {
          if((pa->PRuse==2)||(pa->PRuse==3))
          {   j++;
              for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
              xx_ch1[i-pa->SpectraStart][j]=PRRef_ch1[i];       //PR   PROCESS REF
          }
         if((pa->R1use==2)||(pa->R1use==3))
         {   j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx_ch1[i-pa->SpectraStart][j]=Ref1_ch1[i];         //R1 CH4
          }
         if((pa->R2use==2)||(pa->R2use==3))
         {   j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx_ch1[i-pa->SpectraStart][j]=Ref2_ch1[i];         //R2
         }
         if((pa->R3use==2)||(pa->R3use==3))
         {
             j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx_ch1[i-pa->SpectraStart][j]=Ref3_ch1[i];         //R3
         }
         if((pa->Baseuse==2)||(pa->Baseuse==3))
        {	j++;
            for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
            xx_ch1[i-pa->SpectraStart][j]=BaseSpectra_ch1[i];  //baseline
        }
         if((pa->VRuse==2)||(pa->VRuse==3))
         {	j++;
             for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
             xx_ch1[i-pa->SpectraStart][j]=VRRef_ch1[i];    //VR  VALIDATION REF
         }
         j++;
         for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
         xx_ch1[i-pa->SpectraStart][j]=1.0;

         MatrixSize = j+1;

      }
 //构造Y矩阵
         for(i=pa->SpectraStart;i<pa->SpectraEnd;i++)
         {
                yy_ch1[i- pa->SpectraStart]= Spectrum_ch1[i];
          }

 //计算X'X
         for(j=0;j<MatrixSize;j++)
         {
             for(k=0;k<MatrixSize;k++)
             {
                 for(PW_ch1[j][k]=0,i=0;i<Number;i++)
                     PW_ch1[j][k]+=xx_ch1[i][j]*xx_ch1[i][k];
             }
         }

 //求PW矩阵的逆
         if((inverse(MatrixSize,1))==0)  //此处的MatrixSize为传递的维度。inverse之后得到的数据就为求逆之后的了。

         {
         for(i=0;i<MatrixSize;i++)
         {
             for(j=0;j<Number;j++)
             {
                 for(temp_1_ch1[i][j]=0,k=0;k<MatrixSize;k++)
                     temp_1_ch1[i][j]+=PW_ch1[i][k]*xx_ch1[j][k];
             }
         }
         for(i=0;i<MatrixSize;i++)
         {
             for(a[i]=0,j=0;j<Number;j++)
                 a[i]+=temp_1_ch1[i][j]*yy_ch1[j];
         }

         Rs->CLSFitRatio=a[0];
         //printf("%f ",Rs->CLSFitRatio);
         }

          xx_ch1_size =  MatrixSize;

          l=-1;

          if (PV_Flag)//PVModel=1 过程气
          {
              if((pa->PRuse==1)||(pa->PRuse==3))
              {   l++;
                  for(int i=0;i<1000;i++)
                  xx_ch1[i][l]=PRRef_ch1[i];       //PR   PROCESS REF
              }
             if((pa->R1use==1)||(pa->R1use==3))
             {   l++;
                 for(int i=0;i<1000;i++)
                 xx_ch1[i][l]=Ref1_ch1[i];         //R1 CH4
              }
             if((pa->R2use==1)||(pa->R2use==3))
             {   l++;
                 for(int i=0;i<1000;i++)
                 xx_ch1[i][l]=Ref2_ch1[i];         //R2
             }
             if((pa->R3use==1)||(pa->R3use==3))
             {
                 l++;
                 for(int i=0;i<1000;i++)
                 xx_ch1[i][l]=Ref3_ch1[i];          //R3
             }
             if((pa->Baseuse==1)||(pa->Baseuse==3))
             {	l++;
                 for(int i=0;i<1000;i++)
                 xx_ch1[i][l]=BaseSpectra_ch1[i];   // baseline
             }
             if((pa->VRuse==1)||(pa->VRuse==3))
             {	l++;
                 for(int i=0;i<1000;i++)
                 xx_ch1[i][l]=VRRef_ch1[i];    //VR VALIDATION REF
             }

          }
          //判断校验气参考谱 构造X矩阵
          else
          {
              if((pa->PRuse==2)||(pa->PRuse==3))
              {   l++;
                  for(int i=0;i<1000;i++)
                  xx_ch1[i][l]=PRRef_ch1[i];       //PR   PROCESS REF
              }
             if((pa->R1use==2)||(pa->R1use==3))
             {   l++;
                 for(int i=0;i<1000;i++)
                 xx_ch1[i][l]=Ref1_ch1[i];         //R1 CH4
              }
             if((pa->R2use==2)||(pa->R2use==3))
             {   l++;
                 for(int i=0;i<1000;i++)
                 xx_ch1[i][l]=Ref2_ch1[i];         //R2
             }
             if((pa->R3use==2)||(pa->R3use==3))
             {
                 l++;
                 for(int i=0;i<1000;i++)
                 xx_ch1[i][l]=Ref3_ch1[i];         //R3
             }
             if((pa->Baseuse==2)||(pa->Baseuse==3))
            {	l++;
                for(int i=0;i<1000;i++)
                xx_ch1[i][l]=BaseSpectra_ch1[i];  // baseline
            }
             if((pa->VRuse==2)||(pa->VRuse==3))
             {	l++;
                 for(int i=0;i<1000;i++)
                 xx_ch1[i][l]=VRRef_ch1[i];       //VR  VALIDATION REF
             }

          }


        for(int i = 0; i<1000;i++)
              fittedspectrum_ch1[i]=0;


         for(int i = pa->SpectraStart; i<pa->SpectraEnd;i++)
         {
             for(int j = 0; j<MatrixSize;j++)
             {
                 fittedspectrum_ch1[i] += a[j]*xx_ch1[i][j];
             }
         }

         for(int i =0;i<Z;i++)
             cls_a_ch1[i] = a[i];

   }

 }



 /*****用最佳主成分数计算得出的系数矩阵Bpls 计算实时谱的预测值***********/
 void PLSprocess(Para *pa,Conc *Rs,int channel)
 {

     if(channel==0)
     {
     int i,j;
     float temp_1;
     float ypred;


         //PHS:这里需要添加将flash中的Bpls读取出来的语句
         for(i=0;i<M;i++)
                 coef[i][0]=Bpls[i][0];
         temp_1=0;
         for(i=0;i<M;i++)
                 temp_1+=xpara_1[i]*coef[i][0];
                 coef[M][0]=ypara_1[0]-temp_1;



         ypred=0;
         for(j=0;j<M;j++)
             ypred+=Spectrum[j]*coef[j][0];

     ypred+=1*coef[M][0];
     Rs->PLSFitRatio=Mv_Ag(1,pa->MovAvg,ypred,0);

     printf("ypred\n");
         printf("%f   ",ypred);
     }
     else
     {
         printf("get in CH2 PLS \n");
     int i,j;
     float temp_1;
     float ypred;


         //PHS:这里需要添加将flash中的Bpls读取出来的语句
         for(i=0;i<M;i++)
                 coef_ch1[i][0]=Bpls_ch1[i][0];
         temp_1=0;
         for(i=0;i<M;i++)
                 temp_1+=xpara_1_ch1[i]*coef_ch1[i][0];
                 coef_ch1[M][0]=ypara_1_ch1[0]-temp_1;



         ypred=0;
         for(j=0;j<M;j++)
             ypred+=Spectrum_ch1[j]*coef_ch1[j][0];

     ypred+=1*coef_ch1[M][0];
     Rs->PLSFitRatio= ypred;
     // Mv_Ag(1,pa->MovAvg,ypred,1);


     }
 }



