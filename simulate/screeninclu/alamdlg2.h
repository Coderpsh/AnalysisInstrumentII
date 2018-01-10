#ifndef ALAMDLG2_H
#define ALAMDLG2_H
#include"keyboarddlg.h"

#include <QWidget>

//ADD 6.14-0
#include"global.h"

namespace Ui {
class alamDlg2;
}

class alamDlg2 : public QWidget
{
    Q_OBJECT

public:
    explicit alamDlg2(QWidget *parent = 0);
    ~alamDlg2();
    void show_paras(); //add 6.14-1


signals:
    void backCalibrationdlg();
        void down();
        void up();
private slots:
     void showRealTime();

     void backtothis();

     void on_lowerlimitalarmvalueTip_clicked();

     void on_maximumtemperatureTip_clicked();

     void on_minimumtemperatureTip_clicked();

     void on_pageUp_clicked();

     void on_pageDown_clicked();

     void on_AlarmConcMin_change_clicked();

     void on_Tmax_change_clicked();

     void on_Tmin_change_clicked();

     void on_back_clicked();

     //add 6.14-3
     void range_limit_AlarmConcMin(QString);
     void range_limit_Tmax(QString);
     void range_limit_Tmin(QString);

     void on_ok_clicked();

     void on_cancel_clicked();

private:
    Ui::alamDlg2 *ui;
    keyboardDlg*keyboarddlg;
    //add 6.14-4
    QString AlarmConcMinstr;
    QString Tmaxstr;
    QString Tminstr;
};

#endif // ALAMDLG2_H
