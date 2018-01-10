#ifndef REFERENCECURVEDLG2_H
#define REFERENCECURVEDLG2_H

#include <QWidget>
#include "keyboarddlg.h"

//ADD 6.14-0
#include"global.h"

namespace Ui {
class referenceCurvedlg2;
}

class referenceCurvedlg2 : public QWidget
{
    Q_OBJECT

public:
    explicit referenceCurvedlg2(QWidget *parent = 0);
    ~referenceCurvedlg2();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void down();
    void up();


private slots:
    void showRealTime();
    void backtothis();
    void on_pageDown_clicked();
    void on_component1_change_clicked();
    void on_component2_change_clicked();

    void on_component3_change_clicked();

   void on_component4_change_clicked();

    void on_component1_Tip_clicked();

    void on_component2_Tip_clicked();

    void on_component3_Tip_clicked();

    void on_component4_Tip_clicked();

    void on_pageUp_clicked();

    void on_back_clicked();

    //add 6.14-3
    void range_limit_Comp1(QString);
    void range_limit_Comp2(QString);
    void range_limit_Comp3(QString);
    void range_limit_Comp4(QString);


    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::referenceCurvedlg2 *ui;
    keyboardDlg*keyboarddlg;
    //add 6.14-4
    QString Comp1str;
    QString Comp2str;
    QString Comp3str;
    QString Comp4str;

};

#endif // REFERENCECURVEDLG2_H
