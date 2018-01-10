#ifndef INTERFACEANDCOMMUNICATIONDLG2_H
#define INTERFACEANDCOMMUNICATIONDLG2_H

#include <QWidget>

#include "keyboarddlg.h"
//ADD 6.14-0
#include"global.h"

namespace Ui {
class interfaceandcommunicationDlg2;
}

class interfaceandcommunicationDlg2 : public QWidget
{
    Q_OBJECT


public:
    explicit interfaceandcommunicationDlg2(QWidget *parent = 0);
    ~interfaceandcommunicationDlg2();
    void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void up();
private slots:
    void showRealTime();

    void backtothis();

    void on_DataFormat_change_clicked();

    void on_DataFormat_Tip_clicked();

    void on_pageUp_clicked();

    void on_back_clicked();

    void range_limit_DataFormat(QString);

    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::interfaceandcommunicationDlg2 *ui;
    keyboardDlg*keyboarddlg;
    QString DataFormatstr;
};

#endif // INTERFACEANDCOMMUNICATIONDLG2_H
