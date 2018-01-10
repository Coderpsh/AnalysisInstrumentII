#ifndef LOGINDLG1_H
#define LOGINDLG1_H
#include "keyboarddlg.h"

#include <QWidget>

namespace Ui {
class Logindlg1;
}

class Logindlg1 : public QWidget
{
    Q_OBJECT

public:
    explicit Logindlg1(QWidget *parent = 0);
    ~Logindlg1();

signals:
      void backMainWindow();
      void ChangeToDebug();


private slots:
    void on_input_clicked();



    void on_password_lineEdit_textChanged(const QString &arg1);

    void on_back_clicked();

private:
    Ui::Logindlg1 *ui;
    keyboardDlg*keyboarddlg;

};

#endif // LOGINDLG1_H
