#include "pci.h"


pci::pci(QObject *parent) : QObject(parent)
{
   operation =new OperateCP2110;
}

pci::~pci()
{
  delete operation;
}

void pci::pci_open(int num)
{
    if(!operation->OpenDevice(num))
         printf("open pci device failed !\n");
    operation->SyncDataStream();
}

void pci::get_all_parameter() //init pci_para
{
  BYTE *regData=new BYTE[70];
  RePci_Flag=operation->ReadRegisters(regData);

  tscanperiod=(long)((regData[8]*256+regData[9])*(2e-3*2048));
  toffset=(long)((regData[14]*256+regData[15])*(100.0/32768));
  tfrequency=(long)((regData[2]*256+regData[3])*(250e3/(double)32768));
  tamplitude=(long)((regData[16]*256+regData[17])*(100.0/32768));
  tbandwidth=(long)(50e3/(regData[6]*256+regData[7]));
  tphase= (long)((regData[4]*256+regData[5])*(360.0/65536));
  tgain=(long)(regData[46]*256+regData[47]);
  tc1=(double)((regData[24]*256+regData[25])/100.0);
  tc2= (double)((regData[26]*256+regData[27])/100.0);;
  tnullpoint=(long)(regData[22]*256+regData[23]);

  //a->nullpoint=(long)(regData[22]*256+regData[23]);
  //a->c1 = (double)((regData[24]*256+regData[25])/100.0);
  //a->c2 = (double)((regData[26]*256+regData[27])/100.0);
  //a->frequency=(long)((regData[2]*256+regData[3])*(250e3/(double)32768));
  //a->phase = (long)((regData[4]*256+regData[5])*(360.0/65536));
  //a->bandwidth=  (long)(50e3/(regData[6]*256+regData[7]));
  //a->scanperiod =(long)((regData[8]*256+regData[9])*(2e-3*2048));
  //a->offset =(long)((regData[14]*256+regData[15])*(100.0/32768));
  //a->amplitude=(long)((regData[16]*256+regData[17])*(100.0/32768));
  //a->gain =(long)(regData[46]*256+regData[47]);8192
}

void pci::set_amplitude(long a)
{
    float b = (a*32768)/(float)100;
    QString c = QString::number(b,'f',0);
    int d = c.toInt();
    operation->Write1_31Register(8,d);
}

void pci::set_bandwidth(long a)//special
{
    float b = 50e3/(float)a;
    QString c = QString::number(b,'f',0);
    int d = c.toInt();
    //printf("BandWidth %d\t",d);
    operation->Write1_31Register(3,d);//50e3/a//30  33  35
  //if(! operation->Write1_31Register(3,b)) //cichu shiyong
     //printf("bandwidth set failed !\n");
     set_cic_gain(d);
     set_icic_gain(d);
}

void pci::set_frequency(long a)
{
    float b = (a*32768)/(float)250e3;
    QString c = QString::number(b,'f',0);
    int d = c.toInt();
    operation->Write1_31Register(1,d);
    if(!operation->Write1_31Register(1,d))
        printf("frequency set failed !\n");
}

void pci::set_gain(long a)//-1
{
    float b = (a*1032)/(float)100;//?
    QString c = QString::number(b,'f',0);
    int d = c.toInt();
    operation->Write1_31Register(23,d);
    //if(!operation->Write1_31Register(23,d))
       // printf("gain2f set failed !\n");

}

void pci::set_offset(long a)
{
    float b = (a*32768)/(float)100;
    QString c = QString::number(b,'f',0);
    int d = c.toInt();
    //printf("offset %d\t",d);
    if(!operation->Write1_31Register(7,d))
         printf("offset set failed !\n");
}

void pci::set_phase(long a)//@
{
    float b = (a*65536)/(float)360;
    QString c = QString::number(b,'f',0);
    int d = c.toInt();
    if(! operation->Write1_31Register(2,d))
       printf("phase set failed !\n");
}

void pci::set_scanperiod(long a)
{
    float b = a/(float)(2e-3*2048);
    QString c = QString::number(b,'f',0);
    int d = c.toInt();
    operation->Write1_31Register(4,d);
}
void pci::set_laserscan(float s1,float s2,int point)
{
      int c1value =(int) (s1*100);
      int c2value =(int) (s2*100);
      operation->Write1_31Register(11,point);
      operation->Write1_31Register(12,c1value);
      operation->Write1_31Register(13,c2value);
      operation->SetRampPointer();
      for(int i=0;i<point;i++)
           { operation->WriteRampTable(0);}
      for(int i = point;i<2048;i++)
      {
         operation->WriteRampTable( (int)(c1value+c2value*((i-point)*1.0/(2048-point)))*(65535*1.0/10000));
      }
}

void pci::pci_close()
{
   operation->CloseDevice();
}


void pci::save2flash()
{
  if( !operation->Sava2Flash())
     printf("save flash failed !\n");//@
  else
       printf("save flash success !\n");//@

}

void pci::laser_open(int a) //1 open
{
    operation->Write1_31Register(5,a);

}
void pci::set_cic_gain(int rate)
{
   uint32_t gain_high ,gain_low,shift=0;
   double ratio ,gain;

   gain = BASE_CIC_GAIN;
   ratio =(double)2000/(double)rate;
   gain = gain * pow(ratio,6);
   while(gain>=0x100000000)
   {
       gain /=65536;
       shift++;
   }
   gain_high =(uint32_t)gain;
   gain_low = gain_high & 0xFFFF;
   gain_high = gain_high >>16;
   operation->Write1_31Register(18,shift);
   operation->Write1_31Register(20,gain_high);
   operation->Write1_31Register(21,gain_low);

}
void pci::set_icic_gain(int rate)
{
    uint32_t gain_high ,gain_low,shift=0;
    double ratio ,gain;

    gain = BASE_ICIC_GAIN;
    ratio =(double)2000/(double)rate;
    gain = gain * pow(ratio,2);
    while(gain>=0x100000000)
    {
        gain /=128;
        shift++;
    }
    gain_high =(uint32_t)gain;
    gain_low = gain_high & 0xFFFF;
    gain_high = gain_high >>16;
    operation->Write1_31Register(24,shift);
    operation->Write1_31Register(26,gain_high);
    operation->Write1_31Register(27,gain_low);

}



