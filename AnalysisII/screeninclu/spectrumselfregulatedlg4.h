#ifndef SPECTRUMSELFREGULATEDLG4_H
#define SPECTRUMSELFREGULATEDLG4_H
#include "keyboarddlg.h"

#include <QWidget>

//ADD 6.14-0
#include"global.h"

namespace Ui {
class spectrumselfregulateDlg4;
}

class spectrumselfregulateDlg4 : public QWidget
{
    Q_OBJECT

public:
    explicit spectrumselfregulateDlg4(QWidget *parent = 0);
    ~spectrumselfregulateDlg4();
    void show_paras(); //add 6.14-1


signals:
    void backCalibrationdlg();
    void up();

private slots:
    void on_PkTrkHgtMin_change_clicked();

    void on_PkTrkHgtMax_change_clicked();

    void on_PkWdith_change_clicked();

    void on_findpeakminimumheightTip_clicked();

    void on_findpeakmaximumheightTip_clicked();

    void on_findpeakfittingwindowTip_clicked();

    void on_back_clicked();

    void on_pageUp_clicked();

    void backtothis();//add show_paras 6.14-2

    //add 6.14-3
    void range_limit_PkTrkHgtMin(QString);
    void range_limit_PkTrkHgtMax(QString);
    void range_limit_PkWdith(QString);


    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::spectrumselfregulateDlg4 *ui;
    keyboardDlg*keyboarddlg;
    //add 6.14-4
    QString PkTrkHgtMinstr;
    QString PkTrkHgtMaxstr;
    QString PkWdithstr;

};

#endif // SPECTRUMSELFREGULATEDLG4_H
