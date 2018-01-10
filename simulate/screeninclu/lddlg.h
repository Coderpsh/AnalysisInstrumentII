#ifndef LDDLG_H
#define LDDLG_H

#include <QWidget>

#include "keyboarddlg.h"

//ADD 6.14-0
#include"global.h"

namespace Ui {
class LDDlg;
}

class LDDlg : public QWidget
{
    Q_OBJECT

public:
    explicit LDDlg(QWidget *parent = 0);
    ~LDDlg();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void down();

private slots:
    void showRealTime();

    void backtothis();

    void on_currentstartingpointTip_clicked();

    void on_scanrangeTip_clicked();

    void on_currenttuningTip_clicked();

    void on_back_clicked();

    void on_pageDown_clicked();

    void on_sweeptimeTip_clicked();

    void on_IStart_change_clicked();

    void on_IRange_change_clicked();

    void on_Ituning_change_clicked();

    void on_ScanTime_change_clicked();

    //add 6.14-3
    void range_limit_IStart(QString);
    void range_limit_IRange(QString);
    void range_limit_Ituning(QString);
    void range_limit_ScanTime(QString);
    //void range_limit_ScanChang(QString);

    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::LDDlg *ui;
    keyboardDlg*keyboarddlg;
    //add 6.14-4
    QString IStartstr;
    QString IRangestr;
    QString Ituningstr;
    QString ScanTimestr;

};

#endif // LDDLG_H
