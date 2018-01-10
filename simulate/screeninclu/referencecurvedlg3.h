#ifndef REFERENCECURVEDLG3_H
#define REFERENCECURVEDLG3_H

#include <QWidget>

#include "keyboarddlg.h"

//ADD 6.14-0
#include"global.h"

namespace Ui {
class referencecurvedlg3;
}

class referencecurvedlg3 : public QWidget
{
    Q_OBJECT

public:
    explicit referencecurvedlg3(QWidget *parent = 0);
    ~referencecurvedlg3();
    void show_paras(); //add 6.14-1


signals:
    void backCalibrationdlg();
    void up();


private slots:

    void showRealTime();
    void backtothis();  //add show_paras 6.14-2
    void on_component5_change_clicked();

    void on_component6_change_clicked();

    void on_component7_change_clicked();

    void on_component8_change_clicked();

    void on_component5_Tip_clicked();

    void on_component6_Tip_clicked();

    void on_component7_Tip_clicked();

    void on_component8_Tip_clicked();

    void on_pageUp_clicked();

    void on_back_clicked();

    //add 6.14-3
    void range_limit_Comp5(QString);
    void range_limit_Comp6(QString);
    void range_limit_Comp7(QString);
    void range_limit_Comp8(QString);

    //add 6.14-5
    void on_ok_clicked();

    void on_cancel_clicked();

    void on_save_clicked();

private:
    Ui::referencecurvedlg3 *ui;
     keyboardDlg*keyboarddlg;
     //add 6.14-4
     QString Comp5str;
     QString Comp6str;
     QString Comp7str;
     QString Comp8str;


};

#endif // REFERENCECURVEDLG3_H
