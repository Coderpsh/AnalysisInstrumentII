#ifndef SPECTRUMSELFREGULATEDLG3_H
#define SPECTRUMSELFREGULATEDLG3_H

#include "keyboarddlg.h"

#include <QWidget>

//ADD 6.14-0
#include"global.h"


namespace Ui {
class spectrumSelfRegulateDlg3;
}

class spectrumSelfRegulateDlg3 : public QWidget
{
    Q_OBJECT

public:
    explicit spectrumSelfRegulateDlg3(QWidget *parent = 0);
    ~spectrumSelfRegulateDlg3();
    void show_paras(); //add 6.14-1
signals:
    void backCalibrationdlg();
    void up();
    void down();
private slots:
    void showRealTime();

    void backtothis();//add show_paras 6.14-2

    void on_findpeakmaximumtreperatureTip_clicked();

    void on_findpeakminimumpressureTip_clicked();

    void on_findpeakmaximumpressureTip_clicked();
    void on_back_clicked();

    void on_pageUp_clicked();

    void on_PkTrkTHigh_change_clicked();

    void on_PkTrkPLow_change_clicked();

    void on_PkTrkPHigh_change_clicked();

    void on_pageDown_clicked();

    //add 6.14-3
    void range_limit_PkTrkTHigh(QString);
    void range_limit_PkTrkPLow(QString);
    void range_limit_PkTrkPHigh(QString);



    void on_cancel_clicked();

    void on_ok_clicked();

private:
    Ui::spectrumSelfRegulateDlg3 *ui;
    keyboardDlg*keyboarddlg;

    QString PkTrkTHighstr;
    QString PkTrkPLowstr;
    QString PkTrkPHighstr;
};

#endif // SPECTRUMSELFREGULATEDLG3_H
