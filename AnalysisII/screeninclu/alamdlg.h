#ifndef ALAMDLG_H
#define ALAMDLG_H

#include <QWidget>
#include "keyboarddlg.h"

//ADD 6.14-0
#include"global.h"

namespace Ui {
class alamDlg;
}

class alamDlg : public QWidget
{
    Q_OBJECT

public:
    explicit alamDlg(QWidget *parent = 0);
    ~alamDlg();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void down();
private slots:
    void showRealTime();

    void backtothis();

    void on_alarmprocessionTip_clicked();

    void on_maximumpressureTip_clicked();

    void on_minimumpressureTip_clicked();

    void on_highlimitalarmvalueTip_clicked();

    void on_back_clicked();

    void on_pageDown_clicked();

    void on_Alarm_ch_clicked();

    void on_Pmax_ch_clicked();

    void on_Pmin_ch_clicked();

    void on_AlarmConcMax_ch_clicked();

    void range_limit_Alarm(QString);
    void range_limit_Pmax(QString);
    void range_limit_Pmin(QString);
    void range_limit_AlarmConcMax(QString);


    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::alamDlg *ui;
    keyboardDlg*keyboarddlg;

    //add 6.14-4
    QString Alarmstr;
    QString Pmaxstr;
    QString Pminstr;
    QString AlarmConcMaxstr;



};

#endif // ALAMDLG_H
