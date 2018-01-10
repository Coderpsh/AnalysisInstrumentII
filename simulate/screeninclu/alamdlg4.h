#ifndef ALAMDLG4_H
#define ALAMDLG4_H
#include "keyboarddlg.h"

#include <QWidget>

//ADD 6.14-0
#include"global.h"

namespace Ui {
class alamDlg4;
}

class alamDlg4 : public QWidget
{
    Q_OBJECT

public:
    explicit alamDlg4(QWidget *parent = 0);
    ~alamDlg4();
    void show_paras(); //add 6.14-1
signals:
    void backCalibrationdlg();
    void up();
private slots:
    void showRealTime();

    void backtothis();

    void on_temperaturedifferencelimitedrestartTip_clicked();

    void on_spectralsaturationthresholdTip_clicked();

    void on_darkcurrenttoolow_clicked();

    void on_darkcurrenttoohighTip_clicked();

    void on_back_clicked();

    void on_pageUp_clicked();

    void on_Tlimit_change_clicked();

    void on_TwoFSat_change_clicked();

    void on_NullHigh_change_clicked();

    void on_NullLow_change_clicked();

    //add 6.14-3
    void range_limit_wait(QString);
    void range_limit_TwoFSat(QString);
    void range_limit_NullHigh(QString);
    void range_limit_NullLow(QString);


    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::alamDlg4 *ui;
    keyboardDlg*keyboarddlg;

    QString waitstr;
    QString TwoFSatstr;
    QString NullHighstr;
    QString NullLowstr;


};

#endif // ALAMDLG4_H
