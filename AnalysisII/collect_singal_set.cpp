#include "collect_singal_set.h"

collect_singal_set::collect_singal_set(QObject *parent) : QObject(parent)
{

}

void collect_singal_set::spi0_collect()
{

    spi0_collect_signal();
}
void collect_singal_set::spi1_collect()
{

    spi1_collect_signal();
}
