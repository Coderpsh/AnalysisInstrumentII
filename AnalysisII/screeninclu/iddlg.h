#ifndef IDDLG_H
#define IDDLG_H

#include "keyboarddlg.h"
#include"global.h"
#include <QWidget>

namespace Ui {
class IDDlg;
}

class IDDlg : public QWidget
{
    Q_OBJECT

public:
    explicit IDDlg(QWidget *parent = 0);
    ~IDDlg();
  void show_paras(); //add 6.14-1

signals:
    void backCalibrationdlg();
    void down();

private slots:
    void backtothis();

    void on_analyzerSNTip_clicked();

    void on_analyzerserialnumberTip_clicked();

    void on_softwareversionTip_clicked();

    void on_airchamberSHTip_clicked();

    void on_back_clicked();

    void on_pageDown_clicked();

    void showRealTime();

    void on_AnaSN_change_clicked();

    void on_AnaModel_change_clicked();

    void on_FWRev_change_clicked();

    void on_CellSN_change_clicked();

    //add 6.14-3
    void range_limit_AnaSN(QString);
    void range_limit_AnaModel(QString);
    void range_limit_FWRev(QString);
    void range_limit_CellSN(QString);

    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::IDDlg *ui;
    keyboardDlg*keyboarddlg;
    //add 6.14-5
    QString AnaSNstr;
    QString AnaModelstr;
    QString FWRevstr;
    QString CellSNstr;
};

#endif // IDDLG_H
