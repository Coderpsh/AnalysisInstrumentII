#ifndef ALAMDLG3_H
#define ALAMDLG3_H
#include "keyboarddlg.h"

#include <QWidget>

//ADD 6.14-0
#include"global.h"

namespace Ui {
class alamDlg3;
}

class alamDlg3 : public QWidget
{
    Q_OBJECT

public:
    explicit alamDlg3(QWidget *parent = 0);
    ~alamDlg3();
    void show_paras(); //add 6.14-1


 signals:
    void backCalibrationdlg();
    void down();
    void up();
private slots:
    void showRealTime();

    void backtothis();

    void on_back_clicked();

    void on_pageUp_clicked();

    void on_pageDown_clicked();

    void on_laserpowertoohighTip_clicked();

    void on_laserpowertoolowTip_clicked();

    void on_lasercurrenttoohighTip_clicked();

    void on_lasercurrenttoolowTip_clicked();

    void on_DCHigh_change_clicked();

    void on_DCLow_change_clicked();

    void on_IHigh_change_clicked();

    void on_Ilow_change_clicked();

    void on_FitQual_change_clicked();

    void on_FitQual_Tip_clicked();

    //add 6.14-3
    void range_limit_FitQual(QString);
    void range_limit_DCHigh(QString);
    void range_limit_DCLow(QString);
    void range_limit_IHigh(QString);
    void range_limit_Ilow(QString);

    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::alamDlg3 *ui;
    keyboardDlg*keyboarddlg;
    QString FitQualstr;
    QString DCHighstr;
    QString DCLowstr;
    QString IHighstr;
    QString Ilowstr;

};

#endif // ALAMDLG3_H
