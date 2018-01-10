#ifndef SPECTRUMSELFREGULATEDLG1_H
#define SPECTRUMSELFREGULATEDLG1_H

#include "keyboarddlg.h"
//ADD 6.14-0
#include"global.h"

#include <QWidget>

namespace Ui {
class spectrumselfregulateDlg1;
}

class spectrumselfregulateDlg1 : public QWidget
{
    Q_OBJECT

public:
    explicit spectrumselfregulateDlg1(QWidget *parent = 0);
    ~spectrumselfregulateDlg1();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void down();

private slots:
    void showRealTime();
    void backtothis();
    void on_PkTrk_change_clicked();

    void on_PkTrk_Tip_clicked();

    void on_back_clicked();

    void on_pageDown_clicked();
    //add 6.14-3
    void range_limit_PkTrk(QString);


    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::spectrumselfregulateDlg1 *ui;
    keyboardDlg*keyboarddlg;
    QString PkTrkstr;


};

#endif // SPECTRUMSELFREGULATEDLG1_H
