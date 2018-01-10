#ifndef PICTURE_SHEETDLG_H
#define PICTURE_SHEETDLG_H

#include <QWidget>

namespace Ui {
class picture_sheetDlg;
}

class picture_sheetDlg : public QWidget
{
    Q_OBJECT

public:
    explicit picture_sheetDlg(QWidget *parent = 0);
    ~picture_sheetDlg();


signals:
    void backMainWindow();

private slots:

    void on_back_clicked();

    void showRealTime();

private:
    Ui::picture_sheetDlg *ui;

};

#endif // PICTURE_SHEETDLG_H
