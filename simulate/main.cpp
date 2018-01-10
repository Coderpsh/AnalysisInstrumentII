//#define _GNU_SOURCE
#include "screeninclu/mainwindow.h"
#include <QApplication>
#include <QThread>
#include <QDebug>
#include <QObject>
#include <iostream>
#include "colle.h"
#include"algo.h"
#include"collect_singal_set.h"
#include"global.h"
#include "stm32spi.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include"fileoperate.h"


#define SPI0_SIGIO   60
#define SPI1_SIGIO   61

using namespace std;



colle collect_SPI;
collect_singal_set collect_signals;

//plotterDlg plotterdlg;

extern fileoperate * files;
extern  pci *pci0 ;
extern  pci *pci1 ;

//spi0设备
 struct DeviceInfo spi0={
    //gpio引脚映射
    spi0.num_cov     =58,
    spi0.num_busy   =146,
    spi0.num_cs     =112,
    spi0.num_rest   =147,
    spi0.num_os0    =59,
    spi0.num_os1    =60,
    spi0.num_os2    =61,

    //gpio设备文件描述符
    spi0.fd_cov     =-1,
    spi0.fd_busy    =-1,
    spi0.fd_cs      =-1,
    spi0.fd_rest    =-1,
    spi0.fd_os0     =-1,
    spi0.fd_os1     =-1,
    spi0.fd_os2     =-1,

    //.fd_spi0_hand_sig_H  =-1,
    //.fd_spi0_hand_sig_L  =-1,

    //spi设备文件
    spi0.device     ="/dev/spidev32766.1",
    //spi设备文件描述符
    spi0.fd_spi     =-1,
};
//spi1设备
 struct DeviceInfo spi1={
    //gpio引脚映射
    spi1.num_cov    =153,
    spi1.num_busy   =76,
    spi1.num_cs     =92,
    spi1.num_rest   =75,
    spi1.num_os0    =114,
    spi1.num_os1    =113,
    spi1.num_os2    =154,

    //gpio设备文件描述符
    spi1.fd_cov     =-1,
    spi1.fd_busy    =-1,
    spi1.fd_cs      =-1,
    spi1.fd_rest    =-1,
    spi1.fd_os0     =-1,
    spi1.fd_os1     =-1,
    spi1.fd_os2     =-1,
    //spi设备文件
    spi1.device     ="/dev/spidev32765.0",
    //spi设备文件描述符
    spi1.fd_spi     =-1,
};

//static  int spi0_tick=0;
//static  int spi1_tick=0;
// 打开spi
void open_spi()
{
    gpio_init(&spi0);
    spi_init(&spi0);

    gpio_init(&spi1); // add
    spi_init(&spi1);   // add
}

/*
SPI0 信号函数，接受到信号即从spi读取数据
*/
static void spi0_signal_handler(int signum)
{

   collect_signals.spi0_collect();
   // collect_SPI.buffer0_getdata();

}

/*
SPI1 信号函数，接受到信号即从spi读取数据
*/
static void spi1_signal_handler(int signum)
{
   collect_signals.spi1_collect();
   // collect_SPI.buffer1_getdata();

}

int set_hand_signal()
{
    //注册gpio-->创建gpio目录
    if(gpio_detail_set(spi0_hand_sig_H,OUT)==0)	return 0;
    if(gpio_detail_set(spi0_hand_sig_L,OUT)==0)	return 0;
    if(gpio_detail_set(spi1_hand_sig_H,OUT)==0)	return 0;
    if(gpio_detail_set(spi1_hand_sig_L,OUT)==0)	return 0;
    if(gpio_detail_set(spi0_mode_sig,OUT)==0)	return 0;
    if(gpio_detail_set(spi1_mode_sig,OUT)==0)	return 0;
    if(gpio_detail_set(spi0_data_sig,IN)==0)	return 0;
    if(gpio_detail_set(spi1_data_sig,IN)==0)	return 0;
    //打开gpio设备
    //SPI0 H
    fd_spi0_hand_sig_H = gpio_fd_open(spi0_hand_sig_H);
    if(fd_spi0_hand_sig_H<0){
        printf("open gpio %d error\n",spi0_hand_sig_H);
        return 0;
    }
  // SPI0 L
    fd_spi0_hand_sig_L = gpio_fd_open(spi0_hand_sig_L);
    if(fd_spi0_hand_sig_L<0){
        printf("open gpio %d error\n",spi0_hand_sig_L);
        return 0;
    }
  // SPI1 H
    fd_spi1_hand_sig_H = gpio_fd_open(spi1_hand_sig_H);
    if(fd_spi1_hand_sig_H<0){
        printf("open gpio %d error\n",spi1_hand_sig_H);
        return 0;
    }
  // SPI1 L
    fd_spi1_hand_sig_L = gpio_fd_open(spi1_hand_sig_L);
    if(fd_spi1_hand_sig_L<0){
        printf("open gpio %d error\n",spi1_hand_sig_L);
        return 0;
    }

 //SPI0 Mode SIGNAL
    fd_spi0_mode_sig = gpio_fd_open(spi0_mode_sig);
    if(fd_spi0_mode_sig<0){
        printf("open gpio %d error\n",spi0_mode_sig);
        return 0;
    }
 //SPI1 Mode SIGNAL
     fd_spi1_mode_sig = gpio_fd_open(spi1_mode_sig);
       if(fd_spi1_mode_sig<0){
           printf("open gpio %d error\n",spi1_mode_sig);
           return 0;
       }

//SPI0 DATA SIGNAL
      fd_spi0_data_sig = gpio_fd_open(spi0_data_sig);
        if(fd_spi0_mode_sig<0){
            printf("open gpio %d error\n",spi0_data_sig);
            return 0;
          }

//SPI1 DATA SIGNAL
           fd_spi1_data_sig = gpio_fd_open(spi1_data_sig);
            if(fd_spi1_mode_sig<0){
                 printf("open gpio %d error\n",spi1_data_sig);
                 return 0;
              }
    //gpio引脚电平初始化
    // SPI0
    if(gpio_set_value(fd_spi0_hand_sig_H,H)<0){
        printf("init set value gpio %d error\n",spi0_hand_sig_H);
        return 0;
  }
    if(gpio_set_value(fd_spi0_hand_sig_L,Low)<0){
            printf("init set value gpio %d error\n",spi0_hand_sig_L);
            return 0;
        }

  // SPI1
    if(gpio_set_value(fd_spi1_hand_sig_H,H)<0){
        printf("init set value gpio %d error\n",spi1_hand_sig_H);
        return 0;
     }
    if(gpio_set_value(fd_spi1_hand_sig_L,Low)<0){
                printf("init set value gpio %d error\n",spi1_hand_sig_L);
                return 0;
            }

    //SPI0 Mode init

  if(gpio_set_value(fd_spi0_mode_sig,Low)<0){
        printf("init set value gpio %d error\n",spi0_mode_sig);
        return 0;
  }
    //SPI1 Mode init

    if(gpio_set_value(fd_spi1_mode_sig,Low)<0){
        printf("init set value gpio %d error\n",spi1_mode_sig);
        return 0;
  }

        return 1;
}

void set_mode(int ch,int mode)  //0~run,1-setparas
{
    if(ch==0)
    {
        if(mode==0)
        {
            if(gpio_set_value(fd_spi0_mode_sig,Low)<0)
              printf(" set value gpio %d error\n",spi0_mode_sig);
        }
        else
        {
            if(gpio_set_value(fd_spi0_mode_sig,H)<0)
              printf(" set value gpio %d error\n",spi0_mode_sig);
        }

    }
    else
    {
        if(mode==0)
        {
            if(gpio_set_value(fd_spi1_mode_sig,Low)<0)
              printf(" set value gpio %d error\n",spi1_mode_sig);
        }
        else
        {
            if(gpio_set_value(fd_spi1_mode_sig,H)<0)
              printf(" set value gpio %d error\n",spi1_mode_sig);
        }
    }
}

int get_data_status(int ch)
{
    //int ret =-1;
    if(ch==0)
    {
      if( gpio_get_value(fd_spi0_data_sig)==0)
          return 0;
      else
          return 1;

    }
    else
    {
        if( gpio_get_value(fd_spi1_data_sig)==0)
            return 0;
        else
            return 1;

    }


}

int main(int argc, char *argv[])
{
  // paras_ch0->average=3;
  // paras_ch1->average=3;

    QApplication a(argc, argv);
   MainWindow w;
    w.show();
    /*init paras for ch0 and ch1 , init refcurves_data for ch0 and ch1*/
       files->Ref_read(0);//CH0 data[60][1013] init
       files->Ref_read(1);//CH1 data_CH1[60][1013] init
       files->readfile(0); //init paras for ch0
       files->readfile(1); //init paras for ch1

    qDebug()<<"main thread:"<<QThread::currentThreadId();

    QThread SPI_collect_thread;
    QThread SPI0_handle_thread;
    QThread SPI1_handle_thread;

     //QThread::currentThread()->setPriority(QThread::NormalPriority);
    QThread::currentThread()->setPriority(QThread::HighestPriority);//HighestPriority//NormalPriority

    //  colle collect_buffer0;
    //  colle collect_buffer1;
     algo algo_SPI0;
     algo algo_SPI1;
     algo_SPI0.moveToThread(&SPI0_handle_thread);
     algo_SPI1.moveToThread(&SPI1_handle_thread);
     collect_SPI.moveToThread(&SPI_collect_thread);
//Try
    QObject::connect(&algo_SPI0, SIGNAL(plotter_start()), &w, SLOT(plotter_start()),Qt::QueuedConnection);
    QObject::connect(&collect_SPI, SIGNAL(buffer0_collect_ok()), &algo_SPI0, SLOT(handle_spi0()),Qt::QueuedConnection);//,Qt::QueuedConnection
    QObject::connect(&collect_SPI, SIGNAL(buffer1_collect_ok()), &algo_SPI1, SLOT(handle_spi1()),Qt::QueuedConnection);
    QObject::connect(&collect_signals, SIGNAL(spi0_collect_signal()), &collect_SPI, SLOT(buffer0_getdata()),Qt::QueuedConnection);
    QObject::connect(&collect_signals, SIGNAL(spi1_collect_signal()), &collect_SPI, SLOT(buffer1_getdata()),Qt::QueuedConnection);
  // QObject::connect(&algo_buffer0, SIGNAL(buffer0_begin_collect()), &collect_buffer0, SLOT(buffer0_begin_collect()),Qt::QueuedConnection);
  // QObject::connect(&algo_buffer1, SIGNAL(buffer1_begin_collect()), &collect_buffer1, SLOT(buffer1_begin_collect()),Qt::QueuedConnection);
    QObject::connect(&algo_SPI0, SIGNAL(result0_show()), &w, SLOT(result0_show()),Qt::QueuedConnection);
    QObject::connect(&algo_SPI1, SIGNAL(result1_show()), &w, SLOT(result1_show()),Qt::QueuedConnection);


    SPI_collect_thread.start();
    SPI0_handle_thread.start();
    SPI1_handle_thread.start();
    SPI_collect_thread.setPriority(QThread::HighPriority);//HighestPriority
    SPI0_handle_thread.setPriority(QThread::NormalPriority);
    SPI1_handle_thread.setPriority(QThread::NormalPriority);

//   collect_buffer0.buffer0_getdata();
//   collect_buffer1.buffer1_getdata();

    w.initWindow();

   printf("%d\n",AnaParas_Ch0->SpectrAvg);
   printf("%d\n",AnaParas_Ch1->SpectrAvg);

   printf("\n Test SPI0 AND SPI1 start:\n");
   open_spi();
   int spi0_fd,spi0_oflags;
   int spi1_fd,spi1_oflags;
   spi0_fd=open("/dev/myirqdevspi0",O_RDWR);

   if(spi0_fd<0)
        return 0;
   else
        printf("Open /dev/myirqdevspi0 success !\n");
   signal(SPI0_SIGIO, spi0_signal_handler);    //关联信号和处理函数
   fcntl(spi0_fd, F_SETOWN, getpid());         //设置信号的拥有者进程
   spi0_oflags = fcntl(spi0_fd, F_GETFL); // Set the FD nonblocking
   fcntl(spi0_fd,F_SETSIG,SPI0_SIGIO);
   fcntl(spi0_fd, F_SETFL, spi0_oflags | FASYNC);   //设置异步通知模式

   spi1_fd=open("/dev/myirqdevspi1",O_RDWR);
   if(spi1_fd<0)
          return 0;
   else
          printf("Open /dev/myirqdevspi1 success !\n");

   signal(SPI1_SIGIO, spi1_signal_handler);    //关联信号和处理函数
   fcntl(spi1_fd, F_SETOWN, getpid());         //设置信号的拥有者进程
   spi1_oflags = fcntl(spi1_fd, F_GETFL);
   fcntl(spi1_fd,F_SETSIG,SPI1_SIGIO);  // add
   fcntl(spi1_fd, F_SETFL, spi1_oflags | FASYNC);   //设置异步通知模式
   printf("\n Set hand signal:\n");

   set_hand_signal();   // add
  //pci0->pci_open(0);
  //pci1->pci_open(1);


    return a.exec();
}
//
/*int main()
{
    printf("\n Test SPI0 AND SPI1 start:\n");
    open_spi();

    ////////////////
    int spi0_fd,spi0_oflags;
    int spi1_fd,spi1_oflags;  // adcdata
    //int i=0;

  // open spi0
  spi0_fd=open("/dev/myirqdevspi0",O_RDWR);
    if(spi0_fd<0)
       return 0;
    else
       printf("Open /dev/myirqdevspi0 success !\n");

    signal(SPI0_SIGIO, spi0_signal_handler);    //关联信号和处理函数
    fcntl(spi0_fd, F_SETOWN, getpid());         //设置信号的拥有者进程
    spi0_oflags = fcntl(spi0_fd, F_GETFL); // Set the FD nonblocking

        fcntl(spi0_fd,F_SETSIG,SPI0_SIGIO);  // add

    fcntl(spi0_fd, F_SETFL, spi0_oflags | FASYNC);   //设置异步通知模式

    // open spi1
    spi1_fd=open("/dev/myirqdevspi1",O_RDWR);
    if(spi1_fd<0)
           return 0;
        else
           printf("Open /dev/myirqdevspi1 success !\n");

  signal(SPI1_SIGIO, spi1_signal_handler);    //关联信号和处理函数
    //signal(SIGIO, spi1_signal_handler);

    fcntl(spi1_fd, F_SETOWN, getpid());         //设置信号的拥有者进程
    spi1_oflags = fcntl(spi1_fd, F_GETFL);

    fcntl(spi1_fd,F_SETSIG,SPI1_SIGIO);  // add

    fcntl(spi1_fd, F_SETFL, spi1_oflags | FASYNC);   //设置异步通知模式

  printf("\n Set hand signal:\n");
  set_hand_signal();   // add

  while(1)
       sleep(2) ;

    //关闭spi设备
    close_device(&spi0);
    close_device(&spi1);   // add
    return 0;
}*/














