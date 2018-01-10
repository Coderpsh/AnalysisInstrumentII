#ifndef REFERENCECURVEDLG_H
#define REFERENCECURVEDLG_H

#include <QWidget>
#include "keyboarddlg.h"
#include "global.h"

namespace Ui {
class referenceCurvedlg;
}

class referenceCurvedlg : public QWidget
{
    Q_OBJECT

public:
    explicit referenceCurvedlg(QWidget *parent = 0);
    ~referenceCurvedlg();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void down();

private slots:

    void showRealTime();
    void backtothis(); //add show_paras 6.14-2
    void on_CalDate_change_clicked();

    void on_RefCurvAvg_change_clicked();

    void on_ProRCon_change_clicked();

    void on_ValRCon_change_clicked();

    void on_RefInd_change_clicked();

    void on_CalDate_Tip_clicked();

    void on_RefCurvAvg_Tip_clicked();

    void on_RefInd_Tip_clicked();

    void on_ProRCon_Tip_clicked();

    void on_ValRCon_Tip_clicked();

    void on_pageDown_clicked();

    void on_back_clicked();

    //add 6.14-3
    void range_limit_CalDate(QString);
    void range_limit_RefCurvAvg(QString);
    void range_limit_ProRCon(QString);
    void range_limit_ValRCon(QString);
    void range_limit_RefInd(QString);

    //add 6.14-5
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::referenceCurvedlg *ui;
    keyboardDlg*keyboarddlg;
    //add 6.14-5
    QString CalDatestr;
    QString RefCurvAvgstr;
    QString RefIndstr;
    QString ProRConstr;
    QString ValRConstr;

};

#endif // REFERENCECURVEDLG_H
