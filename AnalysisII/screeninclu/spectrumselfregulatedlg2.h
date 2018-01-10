#ifndef SPECTRUMSELFREGULATEDLG2_H
#define SPECTRUMSELFREGULATEDLG2_H

#include "keyboarddlg.h"

#include <QWidget>

//ADD 6.14-0
#include"global.h"


namespace Ui {
class spectrumSelfRegulateDlg2;
}

class spectrumSelfRegulateDlg2 : public QWidget
{
    Q_OBJECT

public:
    explicit spectrumSelfRegulateDlg2(QWidget *parent = 0);
    ~spectrumSelfRegulateDlg2();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void down();
    void up();

private slots:
    void showRealTime();

    void backtothis();  //add show_paras 6.14-2

    void on_endpointoffindingpeakTip_clicked();

    void on_peakshiftlimitTip_clicked();

    void on_findpeakmaximunmagnitude_clicked();

    void on_findpeakminimummagnitudeTip_clicked();

    void on_findpeakminimumtemperatureTip_clicked();

    void on_back_clicked();

    void on_pageDown_clicked();

    void on_PkTrkEnd_change_clicked();

    void on_PkShiftLmt_change_clicked();

    void on_PkTrkIdxMax_change_clicked();

    void on_PkTrkIdxMin_change_clicked();

    void on_PkTrkTLow_change_clicked();

    void on_pageUp_clicked();
    //add 6.14-3
    void range_limit_PkTrkEnd(QString);
    void range_limit_PkShiftLmt(QString);
    void range_limit_PkTrkIdxMax(QString);
    void range_limit_PkTrkIdxMin(QString);
    void range_limit_PkTrkTLow(QString);

    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::spectrumSelfRegulateDlg2 *ui;
    keyboardDlg*keyboarddlg;
    //add 6.14-4
    QString PkTrkEndstr;
    QString PkShiftLmtstr;
    QString PkTrkIdxMaxstr;
    QString PkTrkIdxMinstr;
    QString PkTrkTLowstr;


};

#endif // SPECTRUMSELFREGULATEDLG2_H
