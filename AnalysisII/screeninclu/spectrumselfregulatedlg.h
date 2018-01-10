#ifndef SPECTRUMSELFREGULATEDLG_H
#define SPECTRUMSELFREGULATEDLG_H

#include "keyboarddlg.h"

//ADD 6.14-0
#include"global.h"

#include <QWidget>

namespace Ui {
class spectrumSelfRegulateDlg;
}

class spectrumSelfRegulateDlg : public QWidget
{
    Q_OBJECT

public:
    explicit spectrumSelfRegulateDlg(QWidget *parent = 0);
    ~spectrumSelfRegulateDlg();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void down();
    void up();

private slots:
    void showRealTime();

        void backtothis();//add show_paras 6.14-2

        void on_findaveragepeakTip_clicked();

        void on_targetpeakTip_clicked();

        void on_startingpointofpeakcalibrationTip_clicked();

        void on_endingpointofpeakcalibrationTip_clicked();

        void on_findpeakstartingpointTip_clicked();

        void on_back_clicked();

        void on_pageDown_clicked();

        void on_PkTrkAvg_change_clicked();

        void on_PkTarget_change_clicked();

        void on_ValPkTrkStart_change_clicked();

        void on_ValPkTrkEnd_change_clicked();

        void on_PkTrkStart_change_clicked();

        void on_pageUp_clicked();

        //add 6.14-3
        void range_limit_PkTrkAvg(QString);
        void range_limit_PkTarget(QString);
        void range_limit_ValPkTrkStart(QString);
        void range_limit_ValPkTrkEnd(QString);
        void range_limit_PkTrkStart(QString);

        void on_cancel_clicked();

        void on_ok_clicked();

private:
    Ui::spectrumSelfRegulateDlg *ui;
    keyboardDlg*keyboarddlg;
    //add 6.14-4
    QString PkTrkAvgstr;
    QString PkTargetstr;
    QString ValPkTrkStartstr;
    QString ValPkTrkEndstr;
    QString PkTrkStartstr;
};

#endif // SPECTRUMSELFREGULATEDLG_H
