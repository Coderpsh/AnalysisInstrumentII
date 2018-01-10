#ifndef PLSDLG_H
#define PLSDLG_H

#include "keyboarddlg.h"

#include <QWidget>

//ADD 6.14-0
#include"global.h"

namespace Ui {
class plsDlg;
}

class plsDlg : public QWidget
{
    Q_OBJECT

public:
    explicit plsDlg(QWidget *parent = 0);
    ~plsDlg();
    void show_paras(); //add 6.14-1


signals:
    void backCalibrationdlg();
private slots:
    void showRealTime();

    void on_errorcontrolprecisionTip_clicked();

    void on_errorcontrolcycleTip_clicked();

    void on_bendnumberTip_clicked();

    void on_largestprinciplecomponentTip_clicked();

    void on_back_clicked();

    void on_erref_change_clicked();

    void on_errcirNum_change_clicked();

    void on_K_change_clicked();

    void on_A_change_clicked();

    void on_PLS_N_change_clicked();

    void on_PLS_N_Tip_clicked();

    //add 6.14-3

    void range_limit_erref(QString);
    void range_limit_errcirNum(QString);
    void range_limit_PLS_K(QString);
    void range_limit_PLS_A(QString);
    void range_limit_PLS_N(QString);

    void on_cancel_clicked();

    void on_moduling_clicked();

private:
    Ui::plsDlg *ui;
    keyboardDlg*keyboarddlg;
    //add 6.14-4
    QString errefstr;
    QString errcirNumstr;
    QString PLS_Kstr;
    QString PLS_Astr;
    QString PLS_Nstr;

};

#endif // PLSDLG_H
