#ifndef VERIFYDLG_H
#define VERIFYDLG_H

#include <QWidget>

#include "keyboarddlg.h"

//ADD 6.14-0
#include"global.h"

namespace Ui {
class verifyDlg;
}

class verifyDlg : public QWidget
{
    Q_OBJECT

public:
    explicit verifyDlg(QWidget *parent = 0);
    ~verifyDlg();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void down();
private slots:
    void showRealTime();

    void on_checkingswitchtimeTip_clicked();

    void on_checkingconcentrationTip_clicked();

    void on_checkingerrorallowanceTip_clicked();

    void on_back_clicked();

    void on_PurgeTime_change_clicked();

    void on_Vconc_change_clicked();

    void on_VAllowance_change_clicked();

    void on_pageDown_clicked();

    void backtothis();  //add show_paras 6.14-2

    //add 6.14-3
    void range_limit_PurgeTime(QString);
    void range_limit_Vconc(QString);
    void range_limit_VAllowance(QString);



    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::verifyDlg *ui;
    keyboardDlg*keyboarddlg;

    //add 6.14-4
    QString PurgeTimestr;
    QString Vconcstr;
    QString VAllowancestr;



};

#endif // VERIFYDLG_H
