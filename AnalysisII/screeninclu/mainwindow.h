#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "calibrationdlg.h"
#include "picture_sheetdlg.h"
#include "plotterdlg.h"//@
#include "keyboarddlg.h"
#include"logindlg.h"
#include "logindlg1.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initWindow();


signals:
    void showch();
    void showplotterdlg();

private slots:


    void showRealTime();

    void backMainWindow();

    void on_pro_valButton_clicked();

    void on_run_debugButton_clicked();

    void on_picture_sheetButton_clicked();

    void on_calibration_btn_clicked();

    void on_comboBox_activated(const QString &arg1);

    void result0_show();

    void result1_show();

    void ChangeToDebug();

    void plotter_start();


private:
    Ui::MainWindow *ui;
    calibrationDlg *calibration;
    picture_sheetDlg *pic_sheet;//
    plotterDlg *plotterdlg;//@ 创建对象
    keyboardDlg *keyboard;
    LoginDlg*logindlg;
    Logindlg1*logindlg1;

};

#endif // MAINWINDOW_H
