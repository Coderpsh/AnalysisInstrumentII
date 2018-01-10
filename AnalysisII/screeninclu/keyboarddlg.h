#ifndef KEYBOARDDLG_H
#define KEYBOARDDLG_H

#include <QWidget>

namespace Ui {
class keyboardDlg;
}

class keyboardDlg : public QWidget
{
    Q_OBJECT

public:
    explicit keyboardDlg(QWidget *parent = 0);
    ~keyboardDlg();

private slots:

    void on_num1_clicked();

    void on_num2_clicked();

    void on_num3_clicked();

    void on_num4_clicked();

    void on_num5_clicked();

    void on_num6_clicked();

    void on_num7_clicked();

    void on_num8_clicked();

    void on_num9_clicked();

    void on_charMinus_clicked();

    void on_num0_clicked();

    void on_charDot_clicked();

    void on_cleanInput_clicked();

    void on_cancel_clicked();
    void on_Enter_clicked();



    void on_plus_clicked();

    void on_percent_clicked();

    void on_EXP_clicked();

signals:
    void getInput(QString txt);

private:
    Ui::keyboardDlg *ui;
    QString inputTxt;
};

#endif // KEYBOARDDLG_H
