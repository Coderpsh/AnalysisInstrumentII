#ifndef FILEOPERATE_H
#define FILEOPERATE_H

#include <QObject>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "global.h"

using namespace std;

class fileoperate : public QObject
{
    Q_OBJECT
public:
    explicit fileoperate(QObject *parent = 0);
    ~fileoperate();


signals:

public slots:
     void writefile(int CH);
     void readfile(int CH);
     void Ref_write(int CH);
     void Ref_read(int CH);
     void Ref_send(bool Ref_transmit,int CH);//@
     void AnaParas_send(int CH);//@

private:
  fstream file;
  FILE * fp;

};

#endif // FILEOPERATE_H
