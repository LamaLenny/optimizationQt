#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "painter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Painter* painter;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_firstLeftSpin_valueChanged(double arg1);

    void on_secondLeftSpin_valueChanged(double arg1);

    void on_firstRightSpin_valueChanged(double arg1);

    void on_secondRightSpin_valueChanged(double arg1);

    void on_FuncChoose_currentIndexChanged(int index);

    void on_meth1_clicked();

    void on_meth2_clicked();

    void on_NMaxSpin_valueChanged(int arg1);

    void on_probSpin_valueChanged(double arg1);

    void on_epsSpin_valueChanged(double arg1);

    void on_epsStop_clicked(bool checked);

    void on_gradStop_clicked(bool checked);

    void on_goodStop_clicked(bool checked);

    void on_NGoodSpin_valueChanged(int arg1);

    void fminWrite(QString s);

    void minWrite(QString s);

    void stepsWrite(QString s);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
