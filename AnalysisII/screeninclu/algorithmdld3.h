#ifndef ALGORITHMDLD3_H
#define ALGORITHMDLD3_H

#include "keyboarddlg.h"

#include <QWidget>

//ADD 6.14-0
#include"global.h"

namespace Ui {
class algorithmDld3;
}

class algorithmDld3 : public QWidget
{
    Q_OBJECT

public:
    explicit algorithmDld3(QWidget *parent = 0);
    ~algorithmDld3();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void up();
private slots:
    void showRealTime();

    void backtothis();

    void on_PRchooseTip_clicked();

    void on_VRchooseTip_clicked();

    void on_R1chooseTip_clicked();

    void on_R2chooseTip_clicked();

    void on_R3chooseTip_clicked();

    void on_BasechooseTip_clicked();

    void on_back_clicked();

    void on_pageUp_clicked();

    void on_Pruse_change_clicked();

    void on_Vruse_change_clicked();

    void on_R1use_change_clicked();

    void on_R2use_change_clicked();

    void on_R3use_change_clicked();

    void on_Baseuse_change_clicked();

    void range_limit_PRuse(QString);
    void range_limit_R1use(QString);
    void range_limit_R2use(QString);
    void range_limit_R3use(QString);
    void range_limit_Baseuse(QString);
    void range_limit_VRuse(QString);

    void on_ok_clicked();

    void on_cancel_clicked();


private:
    Ui::algorithmDld3 *ui;
    keyboardDlg*keyboarddlg;
    QString PRusestr;
    QString R1usestr;
    QString R2usestr;
    QString R3usestr;
    QString Baseusestr;
    QString VRusestr;


};

#endif // ALGORITHMDLD3_H
