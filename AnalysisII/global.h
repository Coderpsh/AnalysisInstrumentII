#ifndef GLOBAL_H
#define GLOBAL_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include"fileoperate.h"
#include"pci.h"
#define N 59//最多为60组数据
#define M 999//数据有449-2+1个点
#define L 1//y的列数
#define A 10//主成分最大计算值
#define Z 7//x列范围
#define S 1000


 typedef struct  pcipara
{
    long scanperiod;
    long offset;
    long frequency;
    long amplitude;
    long bandwidth;
    long phase;
    long gain;
    double c1;
    double c2;
    long nullpoint;
}PCIPARA;   //no_use

typedef struct para
{
    int CH_Flag;
    int average;

}PARA;      //no_use

typedef struct AnaPara{
    //ID paras 8
    long AnaSN;
    long AnaModel;
    long FWRev;
    long CellSN;
    long CellModel;
    int Analyte;
    float RangeMin;  //for DA;
    float RangeMax;  //for DA;4~20MA;
     //LD paras 9
    float IStart;
    float IRange;
    float Ituning;
    long ScanTime;
    float ModRange;
    int SpectrAvg;
    int NullWidth;
    float ModFreq;
    bool Ldwork_Flag; //lineedit,
    //jie tiao  ,PCIpara 4
    long  Phase;
    float Gain2f;
    float Cent2f;
    long BandWidth;
    //jie  mian; 4
    int Punit;
    int ConcUnit;
    int BaudRate;
    int DataFormat;

    //puzitiao ; 8 + 9
    int PkTrk;
    int PkTrkAvg;
    int PkTarget;
    int ValPkTrkStart;
    int ValPkTrkEnd;
    int PkTrkStart;
    int PkTrkEnd;
    int PkShiftLmt; //

    float PkTrkIdxMax;
    float PkTrkIdxMin;
    float PkTrkTLow;
    float PkTrkTHigh;
    float PkTrkPLow;
    float PkTrkPHigh;
    float PkTrkHgtMin;
    float PkTrkHgtMax;
    float PkWdith;


    //alarm; 8+9
    int Alarm;
    float Pmax;
    float Pmin;
    int AlarmConcMax;
    int AlarmConcMin;
    float Tmax;
    float Tmin;
    int PkTrkLimit;

    float FitQual;
    float DCHigh;
    float DCLow;
    float IHigh;
    float Ilow;
    float wait;//wait
    float TwoFSat;
    float NullHigh;
    float NullLow;

     // algo 13+1(guhua)
     int Model;//计算模型，PLS=1;cls=0
    // int ProValMode;//过程态校验态切换，PRO=1 VAL=0 CLS(guhua;)
     int SpectraStart;//选谱起点	输入数值（1-1000）
     int SpectraEnd;//选谱终点	输入数值（1-1000）
     int DFEnable;  //数字滤波   (0：禁用 1：启用)
     int DCNormStart;//归一化起始点(0~4000)
     int DCNormEnd;//归一化点(0~4000)
     int MovAvg;

      /********以下为CLS的参数******/
     int PRuse;//PR选用		选择:（0.关， 1 Pro 2. Val 3. Both）
     int R1use;//R1选用		选择:（0.关， 1 Pro 2. Val 4. Both）
     int R2use;//R2选用		选择:（0.关， 1 Pro 2. Val 5. Both）
     int R3use;//R3选用		选择:（0.关， 1 Pro 2. Val 6. Both）
     int Baseuse;//基线选用	选择:（0.关， 1 Pro 2. Val 7. Both）
     int VRuse;//VR选用		选择:（0.关， 1 Pro 2. Val 8. Both）

   /********以下为PLS的参数******/
     int BuildMode;//PLS模型是否重建的标志(1:重构，0：不重构)
     float erref;//误差控制精度
     int errcirNum;//误差控制循环次数
   /********PLS的参数******/
    // bool CV_Flag;
  /********以下为交叉检验的参数******/
     int PLS_K;  //K为折数，
     int PLS_A;
     int PLS_N;

     //jiaoyan
     int PurgeTime;
     float Vconc;
     float VAllowance;
     int VCorrection;
     float SSlope;
     float SOffset;

     //jiaozhun
     float PCoeff0;
     float PCoeff1;
     float PCoeff2;
     float PCoeff3;
     float VCoeff0;
     float VCoeff1;
     float VCoeff2;
     float VCoeff3;
     //refcurve
     long CalDate;
     int RefCurvAvg;
     float RefInd;
     float ProRCon;
     float ValRCon;
     float Comp1;
     float Comp2;
     float Comp3;
     float Comp4;
     float Comp5;
     float Comp6;
     float Comp7;
     float Comp8;
}Para;

typedef struct Result{
float CLSFitRatio;//CLS返回值，回归系数的第一个数作为浓度
float PLSFitRatio;
float Conc;
float T;
float P;
float Tec;//@
float Power;
float Peak;
float Peakref;
float Peakrefhigh;
float PeakHeight;
float Null;
float IStart;
float IAmp;
float RatioP;
float RatioV;
float Ratio1;
float Ratio2;
float Ratio3;
float RatioBase;
float ModelQaulity;

uint16_t Status;
//PLS中的函数CV以及plsnipals的返回值都在全局数组Bpls[][0]以及全局变量pt中
}Conc;


extern PCIPARA *pci0_paras;
extern PCIPARA *pci1_paras;
extern PARA*paras_ch0;
extern PARA*paras_ch1;

extern Conc*Conc_Ch0;
extern Conc*Conc_Ch1;
extern Para * AnaParas_Ch0;
extern Para * AnaParas_Ch1;
extern Para * AnaParas_Ch0_init;
extern Para * AnaParas_Ch1_init;

extern bool  mode_flag;
extern bool  mode_flag_1;
extern uint8_t spi0_tbuf[];
extern uint8_t spi1_tbuf[];
extern uint8_t spi0_rbuf[];
extern uint8_t spi1_rbuf[];
extern struct DeviceInfo spi1;
extern struct DeviceInfo spi0;

/*extern float DC_CH0[];
extern float DC_CH1[];
extern float f2_CH0[];
extern float f2_CH1[];
extern float P_CH0[];
extern float P_CH1[];
extern float T_CH0[];
extern float T_CH1[];
extern float Tec_CH0[];
extern float Tec_CH1[];*/

/********全局变量********/
extern bool refspi0_save_ok;
extern bool refspi1_save_ok;

//extern float Uart_Buff_Ch0[];
//extern float Uart_Buff_Ch1[];
extern bool Uart_Ok_Ch0;
extern bool Uart_Ok_Ch1;
extern float Try_temp;//@try printf
extern bool RePci_Flag;
//for  PCI
extern long tscanperiod;
extern long toffset;
extern long tfrequency;
extern long tamplitude;
extern long tbandwidth;
extern long tphase;
extern long tgain;
extern double tc1;
extern double tc2;
extern long tnullpoint;



// for algo
extern float fittedspectrum[1000];
extern float fittedspectrum_ch1[1000];
extern float Pressure_act;//实时压强
extern float Temper_act;//实时温度
extern float Pressure_act_ch1;//实时压强
extern float Temper_act_ch1;//实时温度
extern float MovTemp[10];//滑动平均最大为10，后期可修改
extern float MovTemp_ch1[10];
extern float PkTrkTemp[10];
extern float PkTrkTemp_ch1[10];
extern double xx[M][Z],yy[M];
extern double xx_ch1[M][Z],yy_ch1[M];
extern int xx_size;
extern int xx_ch1_size;//for download xx;
extern float kk;
extern float kk_ch1;
extern double temp_1[Z][M];
extern double temp_1_ch1[Z][M];
extern  float DCavg[1000];
extern float DCavg_ch1[1000];
extern float F2avg[1000];
extern float Raw_F2avg[1000];//@
extern float F2avg_ch1[1000];
extern float Raw_F2avg_Ch1[1000];//@
extern float DCref[1000];
extern float DCref_ch1[1000];
extern float xpara_1[1000];//xcal 数据的平均值
extern double xpara_1_ch1[1000];//xcal 数据的平均值
extern float ypara_1[1];//ycal数据的平均值
extern double ypara_1_ch1[1];//ycal数据的平均值
extern float y_1[N];
extern float y_1_ch1[N];
extern float Q[N][L];//plsnipals 中用到
extern double Q_ch1[N][L];//plsnipals 中用到
extern float Wstar[M][A];//plsnipals
extern double Wstar_ch1[M][A];//plsnipals
extern float W[M][A];//plsnipals
extern double W_ch1[M][A];//plsnipals
extern float PW[A][A];        //inverse求逆时使用的数组（PW）^-1
extern double PW_ch1[A][A];        //inverse求逆时使用的数组（PW）^-1
extern float x_cal[N][M],y_cal[N][L];    //训练集数据  CV中定义 plsnipals要用
extern double x_cal_ch1[N][M],y_cal_ch1[N][L];    //训练集数据  CV中定义 plsnipals要用
extern float P[M][A];
extern double P_ch1[M][A];
extern float T[N][A];
extern double T_ch1[N][A];
extern float C[S][1];
extern double C_ch1[S][1];
extern float x_teste[60][S];
extern double x_teste_ch1[60][S];
extern float Bpls[450][1];//PLS 模型 系数矩阵
extern double Bpls_ch1[M][1];//PLS 模型 系数矩阵
extern int Num;
extern int Num_ch1;
extern int pt;//最佳主成分数
extern int pt_ch1;//最佳主成分数
extern float x[N][M],y[N][L];//pls 和cv子函数用到
extern double x_ch1[N][M],y_ch1[N][L];//pls 和cv子函数用到
extern float data[60][1013];//参比曲线矩阵
extern float data_ch1[60][1013];//参比曲线矩阵//@@
/********************************************CV中的大数组******************************/

extern float yp[60][S],YP[60][S],YP_1[60][A];     //YP为N行A列
extern double yp_ch1[60][S],YP_ch1[60][S],YP_1_ch1[60][A];     //YP为N行A列
extern float x_test[60][S],y_test[60][S];   //x测试集 y测试集，x_teste为计算回归系数矩阵时使用
extern double x_test_ch1[60][S],y_test_ch1[60][S];   //x测试集 y测试集，x_teste为计算回归系数矩阵时使用
extern float coef_1[S][1];     //回归系数矩阵
extern double coef_1_ch1[S][1];     //回归系数矩阵
extern float error[60][A];          //误差
extern float error_ch1[60][A];          //误差
extern float error2_MEAN[S],cv[S];   //误差均值，标准差，误差计算中间寄存，CV
extern float error2_MEAN_ch1[S],cv_ch1[S];   //误差均值，标准差，误差计算中间寄存，CV
extern double cls_a_ch0[Z];
extern double cls_a_ch1[Z];

/********************************************PLSPROSS中的大数组******************************/
extern float coef[S][1];
extern float coef_ch1[S][1];

    /********************************************以下为类中的数据******************************/
extern float Spectrum[1000];//CLS、PLS的实时谱
extern float Spectrum_ch1[1000];//CLS、PLS的实时谱
/********************************************以上为类中的数据******************************/

//CLS x矩阵建立  各个参考曲线谱线

extern float Ref1[1000];
extern float BaseSpectra[1000];
extern float Ref2[1000];
extern  float Ref3[1000];
extern  float PRRef[1000];
extern float VRRef[1000];
extern float Ref1_ch1[1000];
extern float BaseSpectra_ch1[1000];
extern float Ref3_ch1[1000];
extern float Ref2_ch1[1000];
extern float PRRef_ch1[1000];
extern float VRRef_ch1[1000];


//for MainWindow
extern bool spi0_transmit_flag;
extern bool spi1_transmit_flag;
extern int CH_Flag;
extern int permit_flag;

extern bool spi0_copy_flag;
extern bool spi1_copy_flag;

extern bool RD_flag;
extern bool RD_flag_ch1;

extern bool PV_Flag_Screen;
extern bool PV_Flag_Ch1_Screen;

extern bool Debug_Flag;
extern bool Debug_Flag_Ch1;

extern bool PlotData_Flag;

extern bool Re_flag;
extern bool Re_flag_ch1;
//for plotter
extern bool Ploat_Channel;

extern bool PV_Flag_Ch1_copy;

//for plotterdlg
extern bool DCavg_drawing_Flag;
extern bool Raw2f_drawing_Flag;
extern bool F2avg_drawing_Flag;
extern bool PR_drawing_Flag;
extern bool Fitted_drawing_Flag;

//for spi0and spi1 communication
extern unsigned int spi0_hand_sig_H;  // PD4-J4-11
extern unsigned int spi0_hand_sig_L;   // PD2-J4-13
extern unsigned int spi1_hand_sig_H;  // PC10-J4-15
extern unsigned int spi1_hand_sig_L;   // PD14-J4-17
extern unsigned int spi0_mode_sig;
extern unsigned int spi1_mode_sig;
extern unsigned int spi0_data_sig;
extern unsigned int spi1_data_sig;

extern int fd_spi0_hand_sig_H;
extern int fd_spi0_hand_sig_L;
extern int fd_spi1_hand_sig_H;
extern int fd_spi1_hand_sig_L;
extern int fd_spi0_mode_sig;
extern int fd_spi1_mode_sig;
extern int fd_spi0_data_sig;
extern int fd_spi1_data_sig;
extern bool spi0_ref_flag;
extern bool spi1_ref_flag;//use to ref_save_start

//poltterDlg
extern int CH1;
extern int CH2;
extern int CH3;
extern int CH4;

void CV( Para *pa,int channel);
void plsnipals(int n,int a_1,Para *pa,int channel);
char inverse(int a,int channel);
void PLSprocess( Para *pa,Conc *Rs,int channel);
void cls(Para *pa,Conc *Rs,int channel,bool PV_Flag);
void DigitalFilter( float *Spectrum1 );
float Mv_Ag(int flag1,int Num1,float Conc,int channel);
int Sea_Lim_Ch0(int k_min,int k_max);//@
int Sea_Lim_Ch1(int k_min,int k_max);//@
void Mk_Ref(int channel);

int get_data_status(int ch);

void set_mode(int ch,int mode);

#endif // GLOBAL_H

