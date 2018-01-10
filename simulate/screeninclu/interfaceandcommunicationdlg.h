#ifndef INTERFACEANDCOMMUNICATIONDLG_H
#define INTERFACEANDCOMMUNICATIONDLG_H

#include "keyboarddlg.h"

#include <QWidget>

//ADD 6.14-0
#include"global.h"

namespace Ui {
class interfaceAndCommunicationDlg;
}

class interfaceAndCommunicationDlg : public QWidget
{
    Q_OBJECT

public:
    explicit interfaceAndCommunicationDlg(QWidget *parent = 0);
    ~interfaceAndCommunicationDlg();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
     void down();

private slots:
    void showRealTime();
    void backtothis();
    void on_pressureunitTip_clicked();

    void on_concentrationunitTip_clicked();

    void on_BaudrateTip_clicked();

    void on_back_clicked();

    void on_Punit_change_clicked();

    void on_ConcUnit_change_clicked();

    void on_BaudRate_change_clicked();

    void on_pageDown_clicked();

    //add 6.14-3
    void range_limit_Punit(QString);
    void range_limit_ConcUnit(QString);
    void range_limit_BaudRate(QString);

    void on_ok_clicked();

    void on_cancel_clicked();



private:
    Ui::interfaceAndCommunicationDlg *ui;
    keyboardDlg*keyboarddlg;
    QString Punitstr;
    QString ConcUnitstr;
    QString BaudRatestr;

};

#endif // INTERFACEANDCOMMUNICATIONDLG_H
