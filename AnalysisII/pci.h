#ifndef PCI_H
#define PCI_H

#include <QObject>
#include "global.h"
#include"OperateCP2110.h"

#define BASE_CIC_GAIN (2*65536)
#define BASE_ICIC_GAIN (8*65536)

class pci : public QObject  //for double CP2110
{
    Q_OBJECT
public:
  explicit  pci(QObject *parent = 0);
   ~pci();
  void pci_open(int num); //open one cp2110
  void get_all_parameter();//@
  void set_scanperiod(long a);
  void set_offset(long a);
  void set_frequency(long a);
  void set_amplitude(long a);
  void set_bandwidth(long a);
  void set_phase(long a);
  void set_gain(long a);
  void set_laserscan(float s1,float s2,int point);
  void pci_close();
  void save2flash();
  void laser_open(int a);
  void set_cic_gain(int rate);
  void set_icic_gain(int rate);
  //void set_frequencytry(Para *a);
private:
   OperateCP2110*operation;

};

#endif // PCI_H
