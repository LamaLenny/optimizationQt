#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    painter = new Painter();
    QGridLayout* Graph = findChild<QGridLayout*>("Graph");
    Q_ASSERT(Graph);
    Graph -> addWidget(painter);

    QObject::connect(painter,&Painter::fminSignal, this, &MainWindow::fminWrite);
    QObject::connect(painter,&Painter::minSignal, this, &MainWindow::minWrite);
    QObject::connect(painter,&Painter::stepsSignal, this, &MainWindow::stepsWrite);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete painter;
}

void MainWindow::on_firstLeftSpin_valueChanged(double arg1)
{
    painter->changeLFBord(arg1);
}

void MainWindow::on_secondLeftSpin_valueChanged(double arg1)
{
    painter->changeLSBord(arg1);
}

void MainWindow::on_firstRightSpin_valueChanged(double arg1)
{
    painter->changeRFBord(arg1);
}

void MainWindow::on_secondRightSpin_valueChanged(double arg1)
{
    painter->changeRSBord(arg1);
}

void MainWindow::on_FuncChoose_currentIndexChanged(int index)
{
    painter->changeFunc(index);
}

void MainWindow::on_meth1_clicked()
{
    painter->changeMethod(true);
}

void MainWindow::on_NMaxSpin_valueChanged(int arg1)
{
    painter->changeNMax(arg1);
}

void MainWindow::on_probSpin_valueChanged(double arg1)
{
    painter->changeP(arg1);
}

void MainWindow::on_epsSpin_valueChanged(double arg1)
{
    painter->changeEps(arg1);
}

void MainWindow::on_meth2_clicked()
{
    painter->changeMethod(false);
}


void MainWindow::on_epsStop_clicked(bool checked)
{
    painter->stopDifferent(checked);
}

void MainWindow::on_gradStop_clicked(bool checked)
{
    painter->stopGrad(checked);
}

void MainWindow::on_goodStop_clicked(bool checked)
{
    painter->stopGoodIter(checked);
}

void MainWindow::on_NGoodSpin_valueChanged(int arg1)
{
    painter->changeNGoodMax(arg1);
}

void MainWindow::minWrite(QString s)
{
    findChild<QLabel*>("minLabel") -> setText(s);
}

void MainWindow::fminWrite(QString s)
{
    findChild<QLabel*>("fminLabel") -> setText(s);
}

void MainWindow::stepsWrite(QString s)
{
    findChild<QLabel*>("stepsLabel") -> setText(s);
}
