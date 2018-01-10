#ifndef COLLE_H
#define COLLE_H

#include <QObject>
#include "global.h"
class colle : public QObject
{
    Q_OBJECT
public:
    explicit colle(QObject *parent = 0);

signals:
   void buffer0_collect_ok();
   void buffer1_collect_ok();
public slots:
 void buffer0_begin_collect();
 void buffer1_begin_collect();
 void buffer0_getdata();
 void buffer1_getdata();

};

#endif // COLLE_H
