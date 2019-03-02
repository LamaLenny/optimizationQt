#ifndef PAINTER_H
#define PAINTER_H
#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include "F_R_optimize.h"
#include "rand_search.h"
#include "Stop_cr.h"
#include "FUN_vec.h"

class Painter: public QWidget
{
    Q_OBJECT
public:
    Painter(QWidget *parent = 0);
    ~Painter();
signals:
    void minSignal(QString s);
    void fminSignal(QString s);
    void stepsSignal(QString s);

public slots:
    void changeFunc(int index);
    void changeMethod(bool checked);
    void changeLFBord(double l);
    void changeLSBord(double l);
    void changeRFBord(double r);
    void changeRSBord(double r);
    void changeP(double p);
    void changeNMax(int n);
    void changeNGoodMax(int n);
    void changeEps(double e);
    void stopDifferent(bool checked);
    void stopGrad(bool checked);
    void stopGoodIter(bool checked);
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) override;

    Opt* op;

    Stop_some st1;
    Stop_some st2;
    Stop_some* pst;

    vector<vector<int>> grid;
    int N_grid;
    void gridMake();
    QPointF convertToPic(vec x);

    void trackDraw();
};

#endif // PAINTER_H
