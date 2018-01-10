#ifndef LDDLG2_H
#define LDDLG2_H

#include <QWidget>

#include "keyboarddlg.h"

//ADD 6.14-0
#include"global.h"

namespace Ui {
class LDDlg2;
}

class LDDlg2 : public QWidget
{
    Q_OBJECT

public:
    explicit LDDlg2(QWidget *parent = 0);
    ~LDDlg2();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void up();

private slots:
    void showRealTime();//Text.able

    void backtothis();

    void on_modulationrangeTip_clicked();

    void on_averageoforiginalspectrumTip_clicked();

    void on_laserclosingtimeTip_clicked();

    void on_modulationfrequencyTip_clicked();

    void on_back_clicked();//Back

    void on_pageUp_clicked();//Prev.Page

    void on_ModRange_change_clicked();//

    void on_SpectrAvg_change_clicked();

    void on_NullWidth_change_clicked();

    void on_ModFreq_change_clicked();
    //add 6.14-3
    void range_limit_ModRange(QString);
    void range_limit_SpectrAvg(QString);
    void range_limit_NullWidth(QString);
    void range_limit_ModFreq(QString);
    void on_ok_clicked();//ok

    void on_cancel_clicked();//cancel



private:
    Ui::LDDlg2 *ui;

   keyboardDlg*keyboarddlg;
   QString ModRangestr;
   QString SpectrAvgstr;
   QString NullWidthstr;
   QString ModFreqstr;
   QString Ldwork_Flagstr;

};

#endif // LDDLG2_H
