#ifndef IDDLG2_H
#define IDDLG2_H

#include "keyboarddlg.h"
#include"global.h"
#include <QWidget>

namespace Ui {
class IDDlg2;
}

class IDDlg2 : public QWidget
{
    Q_OBJECT

public:
    explicit IDDlg2(QWidget *parent = 0);
    ~IDDlg2();
     void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void up();
private slots:
    void showRealTime();

    void backtothis();

    void on_airchamberversionTip_clicked();

    void on_analytesTip_clicked();

    void on_maximunvalueoftherangeTip_clicked();

    void on_back_clicked();

    void on_pageUp_clicked();

    void on_CellModel_change_clicked();

    void on_Analyte_change_clicked();

    void on_RangeMin_change_clicked();

    void on_RangeMax_change_clicked();

    void on_minimunvalueoftherangeTip_clicked();

    void range_limit_CellModel(QString);
    void range_limit_Analyte(QString);
    void range_limit_RangeMin(QString);
    void range_limit_RangeMax(QString);
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::IDDlg2 *ui;
    keyboardDlg*keyboarddlg;

    //add 6.14-5
    QString CellModelstr;
    QString Analytestr;
    QString RangeMinstr;
    QString RangeMaxstr;
};

#endif // IDDLG2_H
