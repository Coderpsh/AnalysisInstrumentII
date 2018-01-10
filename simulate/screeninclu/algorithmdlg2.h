#ifndef ALGORITHMDLG2_H
#define ALGORITHMDLG2_H

#include "keyboarddlg.h"

#include <QWidget>

//ADD 6.14-0

#include "global.h"

namespace Ui {
class algorithmDlg2;
}

class algorithmDlg2 : public QWidget
{
    Q_OBJECT

public:
    explicit algorithmDlg2(QWidget *parent = 0);
    ~algorithmDlg2();
     void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void down();
    void up();
private slots:
    void showRealTime();
    void backtothis();

    void on_normalizedstartingpointTip_clicked();

    void on_normalizedendingpointTip_clicked();

    void on_choosedspectrumstartingpointTip_clicked();

    void on_choosedspectrumendingpointTip_clicked();

    void on_back_clicked();

    void on_pageUp_clicked();

    void on_pageDown_clicked();

    void on_DCNormStart_change_clicked();

    void on_DCNormEnd_change_clicked();

    void on_SpectraStart_change_clicked();

    void on_SpectraEnd_change_clicked();
    //add 6.14-3
    void range_limit_DCNormStart(QString);
    void range_limit_DCNormEnd(QString);
    void range_limit_SpectraStart(QString);
    void range_limit_SpectraEnd(QString);


    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::algorithmDlg2 *ui;
    keyboardDlg*keyboarddlg;
    //add 6.14-4
    QString DCNormStartstr;
    QString DCNormEndstr;
    QString SpectraStartstr;
    QString SpectraEndstr;


};

#endif // ALGORITHMDLG2_H
