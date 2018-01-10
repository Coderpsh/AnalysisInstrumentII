#ifndef VERIFYDLG2_H
#define VERIFYDLG2_H
#include "keyboarddlg.h"

#include <QWidget>
//ADD 6.14-0
#include"global.h"

namespace Ui {
class verifyDlg2;
}

class verifyDlg2 : public QWidget
{
    Q_OBJECT

public:
    explicit verifyDlg2(QWidget *parent = 0);
    ~verifyDlg2();
     void show_paras(); //add 6.14-1
signals:
    void backCalibrationdlg();
    void up();
private slots:
    void on_VCorrection_change_clicked();

    void on_checkingcorrectionTip_clicked();

    void on_SSlope_change_clicked();

    void on_SOffset_change_clicked();

    void on_correctionfactorTip_clicked();

    void on_offsetcorrectionTip_clicked();

    void on_back_clicked();

    void on_pageUp_clicked();

    void backtothis();

    //add 6.14-3
    void range_limit_VCorrection(QString);
    void range_limit_SSlope(QString);
    void range_limit_SOffset(QString);



    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::verifyDlg2 *ui;
    keyboardDlg*keyboarddlg;
    QString VCorrectionstr;
    QString SSlopestr;
    QString SOffsetstr;

};

#endif // VERIFYDLG2_H
