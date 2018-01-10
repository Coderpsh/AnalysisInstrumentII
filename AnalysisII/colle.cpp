#include "colle.h"
#include <iostream>
#include <QThread>
#include"global.h"
#include "stm32spi.h"

using namespace std;


colle::colle(QObject *parent) : QObject(parent)
{

}

void colle::buffer0_getdata()
{
   spi0_transmit_flag=1;
  // uint32_t*p32buf_temp; //temp for test;
   int len = 8012;
  //init rbuf
  for(int i=0;i<len;i++)
  {
   spi0_rbuf[i]=0;
   spi0_tbuf[i]=i%100;
  }
  spi0_tbuf[11] = AnaParas_Ch0->SpectrAvg;
 // while(spi0_copy_flag);  //wait for copy end;
  spi_write_tr(&spi0,spi0_tbuf,spi0_rbuf,len);
 // p32buf_temp=(uint32_t *)spi0_rbuf;
 // printf("%d ",p32buf_temp[1]);
  //printf("\n");
  for(int i=0;i<100;i++)
  {
    i =i;
  }
 if(get_data_status(0)==0)    //data right
   {
     spi0_transmit_flag=0;//can copy;
     buffer0_collect_ok();
   }
//  cout<<"SPI0 collect thread :" <<QThread::currentThreadId()<<endl;
}

void colle::buffer1_getdata()
{
   spi1_transmit_flag=1;
  //  uint32_t*p32buf_temp; //temp for test;
    int len = 8012;
   //init rbuf
   for(int i=0;i<len;i++)
   {
    spi1_rbuf[i]=0;
    spi1_tbuf[i]=i%100;
   }
   spi1_tbuf[11] = AnaParas_Ch1->SpectrAvg;
  // while(spi1_copy_flag);
   spi_write_tr(&spi1,spi1_tbuf,spi1_rbuf,len);
 //  p32buf_temp=(uint32_t *)spi1_rbuf;
  // printf("%d ",p32buf_temp[2]);
 //  printf("\n");
   for(int i=0;i<100;i++)
   {
     i =i;
   } //delay
   if(get_data_status(1)==0)
   {
     spi1_transmit_flag=0;//can copy;
     buffer1_collect_ok();
   }

 //   cout<<"SPI1 collect thread :" <<QThread::currentThreadId()<<endl;
}


void colle::buffer0_begin_collect()
{
   buffer0_getdata();
}

void colle::buffer1_begin_collect()
{
   buffer1_getdata();
}



