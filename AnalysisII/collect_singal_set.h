#ifndef COLLECT_SINGAL_SET_H
#define COLLECT_SINGAL_SET_H

#include <QObject>

class collect_singal_set : public QObject
{
    Q_OBJECT
public:
    explicit collect_singal_set(QObject *parent = 0);
    void spi0_collect();
    void spi1_collect();


signals:
    void spi0_collect_signal();
    void spi1_collect_signal();

public slots:
};

#endif // COLLECT_SINGAL_SET_H
