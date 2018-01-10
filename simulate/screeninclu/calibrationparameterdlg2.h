#ifndef CALIBRATIONPARAMETERDLG2_H
#define CALIBRATIONPARAMETERDLG2_H
#include "keyboarddlg.h"
#include"global.h"
#include <QWidget>

namespace Ui {
class calibrationParameterDlg2;
}

class calibrationParameterDlg2 : public QWidget
{
    Q_OBJECT

public:
    explicit calibrationParameterDlg2(QWidget *parent = 0);
    ~calibrationParameterDlg2();
   void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void down();
    void up();

private slots:
    void showRealTime();

    void backtothis();

    void on_calibrationzeroorderparameterTip_clicked();

    void on_calibrationfirstorderparameterTip_clicked();

    void on_calibrationsecondorderparameterTip_clicked();

    void on_calibrationthirdorderparameterTip_clicked();

    void on_back_clicked();

    void on_VCoeff0_change_clicked();

    void on_VCoeff1_change_clicked();

    void on_VCoeff2_change_clicked();

    void on_VCoeff3_chamge_clicked();


    void on_pageUp_clicked();

    //add 6.14-3
    void range_limit_VCoeff0(QString);
    void range_limit_VCoeff1(QString);
    void range_limit_VCoeff2(QString);
    void range_limit_VCoeff3(QString);

    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::calibrationParameterDlg2 *ui;
    keyboardDlg*keyboarddlg;

    //add 6.14-5
    QString VCoeff0str;
    QString VCoeff1str;
    QString VCoeff2str;
    QString VCoeff3str;

};

#endif // CALIBRATIONPARAMETERDLG2_H
