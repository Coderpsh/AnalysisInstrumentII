#ifndef ALGORITHMDLG_H
#define ALGORITHMDLG_H

#include "keyboarddlg.h"

#include <QWidget>

//ADD 6.14-0
#include"global.h"

namespace Ui {
class algorithmDlg;
}

class algorithmDlg : public QWidget
{
    Q_OBJECT

public:
    explicit algorithmDlg(QWidget *parent = 0);
    ~algorithmDlg();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void down();

private slots:
    void showRealTime();

    void backtothis();

    void on_calculationmodelTip_clicked();

    void on_digitalfilteringTip_clicked();

    void on_slidingaveragetimeTip_clicked();

    void on_back_clicked();

    void on_pageDown_clicked();

    void on_Model_change_clicked();

    void on_DFEnable_change_clicked();

    void on_movingaverage_change_clicked();
    //add 6.14-3
    void range_limit_Model(QString);
    void range_limit_DFEnable(QString);
    void range_limit_MovAvg(QString);



    void on_ok_clicked();

    void on_cancel_clicked();


private:
    Ui::algorithmDlg *ui;
    keyboardDlg*keyboarddlg;
    QString Modelstr;
    QString DFEnablestr;
    QString MovAvgstr;

};

#endif // ALGORITHMDLG_H
