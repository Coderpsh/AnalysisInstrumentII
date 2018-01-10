#ifndef LOGINDLG_H
#define LOGINDLG_H
#include "keyboarddlg.h"

#include <QWidget>

namespace Ui {
class LoginDlg;
}

class LoginDlg : public QWidget
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = 0);
    ~LoginDlg();

signals:
    void backcalibrationdlg();

   void  tocalibration();
    void backMainWindow();

private slots:
    void on_input_clicked();

    void on_passward_lineEdit_textChanged(const QString &arg1);

    void on_back_clicked();



private:
    Ui::LoginDlg *ui;
    keyboardDlg*keyboarddlg;
};

#endif // LOGINDLG_H
