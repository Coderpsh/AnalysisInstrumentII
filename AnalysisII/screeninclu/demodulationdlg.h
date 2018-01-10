#ifndef DEMODULATIONDLG_H
#define DEMODULATIONDLG_H

#include "keyboarddlg.h"
#include "global.h"
#include <QWidget>

namespace Ui {
class demodulationDlg;
}

class demodulationDlg : public QWidget
{
    Q_OBJECT

public:
    explicit demodulationDlg(QWidget *parent = 0);
    ~demodulationDlg();
     void show_paras();

signals:
    void backCalibrationdlg();

private slots:

    void showRealTime();

    void on_phase2fTip_clicked();

    void on_gain2fTip_clicked();

    void on_bias2fTip_clicked();

    void on_BandWidth_clicked();

    void on_back_clicked();

    void on_Phase2f_change_clicked();

    void on_Gain2f_change_clicked();

    void on_Cent2f_change_clicked();

    void on_BandWidth_change_clicked();

    //add 6.14-3
    void range_limit_Phase(QString);
    void range_limit_Gain2f(QString);
    void range_limit_Cent2f(QString);
    void range_limit_BandWidth(QString);



    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::demodulationDlg *ui;
    keyboardDlg*keyboarddlg;
    QString Phasestr;
    QString Gain2fstr;
    QString Cent2fstr;
    QString BandWidthstr;

};

#endif // DEMODULATIONDLG_H
