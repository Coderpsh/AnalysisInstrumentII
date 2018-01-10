#ifndef ALGO_H
#define ALGO_H

#include <QObject>
#include <QThread>
#include "global.h"
class algo : public QObject
{
    Q_OBJECT
public:
    explicit algo(QObject *parent = 0);
    void algo_init_spi0();
    void algo_init_spi1();
    long findmin();
    long findmax();
    int Pro_FindPeakIndex(float *curve, Para *paras );
    int Val_FindPeakIndex(float *curve, Para *paras );
    float FindFractionalPeakIndex( float *curve, Para *paras,int m );
    float RunPeakTracking(bool PVFlag,bool CHFlag, float *SampCurve, float *RefCurve, Para *paras);
    void showRealTime();

signals:
  //  void buffer0_begin_collect();
  //  void buffer1_begin_collect();
    void result0_show();
    void result1_show();
    void plotter_start();//@
public slots:
     void handle_spi0();
     void handle_spi1();

 private:
     uint8_t buffer_copy[8012];
     PARA paras_copy;

     float ref_avg_buffer[1000];
     int ref_avg_count;
     bool algo_start;  //for start Pls or Cls
     bool transmit_start;//for start rs232 transmit and screen display;
     bool PV_temp;
     int PV_count;
     // status flag
     uint16_t State;
     uint16_t State1;
     uint16_t State2;
     uint16_t State3;
     uint16_t State4;
     uint16_t State5;
     uint16_t State6;
     uint16_t State7;
     uint16_t State8;
     uint16_t State9;
     uint16_t State10;
     uint16_t State11;
     uint16_t State12;
     uint16_t State13;
     uint16_t State14;
     uint16_t State15;
     float Conc;
     //for peakfind;
     float T;
     float P;
     float Tec;//@
     unsigned int PkTrCount;
   //  unsigned int Lpch_PeakTrack_DeltaAvgIdx;
     float PeakAvg;
     float Peakref;
     float Null;
     float Power;

     QString DataStr;

     bool PV_Flag;
     bool DR_Flag;
     bool DR_Flag_Ch1;

     float F2offset;

     bool mode_flag_copy;
};

#endif // ALGO_H
