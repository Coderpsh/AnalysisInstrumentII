#ifndef PLOTTERDLG_H
#define PLOTTERDLG_H

#include <QMainWindow>//??

#include <qwt_plot_curve.h>
#include<QTimer>

#include <qwt_scale_draw.h>
#include <qwt_date_scale_draw.h>


namespace Ui {
class plotterDlg;
}

class plotterDlg : public QMainWindow//??
{
    Q_OBJECT

public:
    explicit plotterDlg(QWidget *parent = 0);
    ~plotterDlg();
    void drawing_all();

signals:
    void backMainWindow();

private slots:

     void on_Plot_CH_activated(const QString &arg1);

     void concentration0_show();

     void concentration1_show();

     void graph1();

     void do_showplotterdlg();

     void on_DCavg_btn_clicked();

     void on_Raw2f_btn_clicked();

     void on_F2avg_btn_clicked();

     void on_PR_btn_clicked();

     void on_Fitted_btn_clicked();

     void on_Back_btn_clicked();

private:
    Ui::plotterDlg *ui;

    QwtPlotCurve*curve1;
    QwtPlotCurve*curve2;
    QwtPlotCurve*curve3;
    QwtPlotCurve*curve4;
    QwtPlotCurve*curve5;

};

#endif // PLOTTER_H
