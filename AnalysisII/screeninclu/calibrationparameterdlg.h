#ifndef CALIBRATIONPARAMETERDLG_H
#define CALIBRATIONPARAMETERDLG_H

#include "keyboarddlg.h"
#include"global.h"
#include <QWidget>

namespace Ui {
class calibrationParameterDlg;
}

class calibrationParameterDlg : public QWidget
{
    Q_OBJECT

public:
    explicit calibrationParameterDlg(QWidget *parent = 0);
    ~calibrationParameterDlg();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void down();

private slots:
    void showRealTime();

    void backtothis();

    void on_processzeroorderparameterTip_clicked();

    void on_processfirstorderparameterTip_clicked();

    void on_processsecondorderparameterTip_clicked();

    void on_processthirdorderparameterTip_clicked();

    void on_back_clicked();

    void on_pageDown_clicked();

    void on_PCoeff0_change_clicked();

    void on_PCoeff1_change_clicked();

    void on_PCoeff2_change_clicked();

    void on_PCoeff3_change_clicked();
    //add 6.14-3
    void range_limit_PCoeff0(QString);
    void range_limit_PCoeff1(QString);
    void range_limit_PCoeff2(QString);
    void range_limit_PCoeff3(QString);


    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::calibrationParameterDlg *ui;
    keyboardDlg*keyboarddlg;

    //add 6.14-5
    QString PCoeff0str;
    QString PCoeff1str;
    QString PCoeff2str;
    QString PCoeff3str;
};

#endif // CALIBRATIONPARAMETERDLG_H
