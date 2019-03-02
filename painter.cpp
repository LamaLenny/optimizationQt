#include "painter.h"
#include <QPainter>
#include <QString>

double f1(vec x)
{
    return ((1 - x[0])*(1 - x[0]) + 100 * (x[1] - x[0] * x[0])*(x[1] - x[0] * x[0]));
}
double f2(vec x)
{
    return(x[0]*x[0] + x[1]*x[1]);
}


Painter::Painter(QWidget *parent): QWidget(parent), N_grid(100),
    op(nullptr)
{
    op = new F_R();
    op->a.f = &f1;
    op->a.p = 0.7;
    op->a.eps = 1e-5;
    op->a.N_max = 1000;
    op->a.N_good_max = 100;

    op->a.left.cord.reserve(2);
    op->a.right.cord.reserve(2);

    op->a.left.cord.push_back(-2);
    op->a.left.cord.push_back(-2);

    op->a.right.cord.push_back(2);
    op->a.right.cord.push_back(2);

    op->a.x0 = (op->a.left + op->a.right).multiply_const(0.5);

    st1.ps.push_back(new Stop_x_dif);
    st1.ps.push_back(new Stop_grad_norm);

    st2.ps.push_back(new Stop_good_comp);

    pst = &st1;

    setMouseTracking(true);
}

Painter::~Painter()
{
    pst = nullptr;
    delete op;
}

void Painter::gridMake()
{
    vector<std::vector<double>> field;
    double value;
    double x_min = op->a.left.cord[0];
    double y_min = op->a.left.cord[1];
    double x_max = op->a.right.cord[0];
    double y_max = op->a.right.cord[1];

    QSize s = size();
    int width=s.width();
    int height=s.height();

    double step_x = (x_max - x_min) / width;
    double step_y = (y_max - y_min) / height;
    vector<double> t({x_min, y_max});
    double min_v = op->a.f.pf(t);
    double max_v = op->a.f.pf(t);
    vector<double> col(height);
    for (int i = 0; i < width; ++i)
    {
        col.clear();
        for (int j = 0; j < height; ++j)
        {
            vector<double> h({x_min + i*step_x, y_max-j*step_y});
            value = op->a.f.pf(h);
            if (min_v > value)
                min_v = value;
            else if (max_v < value)
                max_v = value;
            col.push_back(value);
        }
        field.push_back(col);
    }

    grid = vector<vector<int>>(width);
    for (int i = 0; i < width; ++i)
    {
        grid[i] = vector<int>(height);
        for(int j = 0; j < height; ++j)
            grid[i][j] = N_grid*(log((field[i][j] - min_v) + 1)/log(max_v - min_v+1));
    }
 }
void Painter::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPen pen;
    p.drawEllipse(10, 10, 5, 5);
    QSize s = size();
    int width=s.width();
    int height=s.height();
    gridMake();
    for (int i = 0; i < width; ++i)
    {
        for (int j=0;j<height;++j)
        {
            pen.setColor(QColor(255-std::min(grid[i][j]*4, 255), 0, 255));
            p.setPen(pen);
            p.drawPoint(i, j);
        }
    }

   pen.setColor(QColor(0, 0, 0));
   trackDraw();
}

QPointF Painter::convertToPic(vec x)
{
    QSize s = size();
    int width=s.width();
    int height=s.height();
    return QPointF((x[0] - op->a.left[0]) / (op->a.right[0] - op->a.left[0]) * width,
            (1-(x[1] - op->a.left[1])/ (op->a.right[1]-op->a.left[1])) * height);
}


void Painter::mousePressEvent(QMouseEvent *event)
{
        int x = event->x();
        int y = event->y();

        QSize s = size();
        int width = s.width();
        int height = s.height();

        double step_x = (op->a.right[0] - op->a.left[0]) / width;
        double step_y = (op->a.right[1] - op->a.left[1]) / height;
            op->a.x0.cord[0] = op->a.left[0] + x * step_x;
            op->a.x0.cord[1] = op->a.right[1] - y * step_y;
        op->calculate(*pst);

        emit minSignal(QString::number(op->answ[0]) + ", " + QString::number(op->answ[1]));
        emit fminSignal(QString::number(op->fansw));
        emit stepsSignal(QString::number(op->a.count));

        repaint();
}

void Painter::trackDraw()
{
    if (op->track.size() == 0)
        return;
    QPainter p(this);
    if (op->track.size() == 1)
    {
        p.setPen(QColor(0,255,0));
        p.setBrush(QColor(0,255,0));
        p.drawEllipse(convertToPic(op->track[0]),3,3);
        return;
    }
    p.setPen(QColor(255, 255, 255));
    p.setBrush(QColor(255, 255, 255));
    p.drawEllipse(convertToPic(op->track[0]),3,3);
    int size = op->track.size();

    for(int i = 1; i < size - 1; ++i)
    {
        p.drawLine(convertToPic(op->track[i - 1]),
                convertToPic(op->track[i]));
        p.drawEllipse(convertToPic(op->track[i]),3,3);
    }

    p.setPen(QColor(0,255,0));
    p.setBrush(QColor(0,255,0));
    p.drawLine(convertToPic(op->track[size - 2]),
            convertToPic(op->track[size - 1]));
    p.drawEllipse(convertToPic(op->track[size - 1]),3,3);
}

void Painter::changeLFBord(double l)
{
    op->a.left.cord[0] = l;
}

void Painter::changeLSBord(double l)
{
    op->a.left.cord[1] = l;
}

void Painter::changeRFBord(double r)
{
    op->a.right.cord[0] = r;
}

void Painter::changeRSBord(double r)
{
    op->a.right.cord[1] = r;
}

void Painter::changeFunc(int index){
    switch(index)
    {
        case 0: op->a.f.pf = &f1;
            break;
        case 1: op->a.f.pf = &f2;
            break;
    }
    op->track.clear();
    repaint();
}

void Painter::changeMethod(bool checked)
{
    Args b(op->a); 
    delete op;
    if(checked)
    {
        op = new F_R(b);
        pst = &st1;
    }
    else
    {

        op = new rs(b);
        pst = &st2;
    }

}

void Painter::changeNMax(int n)
{
    op->a.N_max = n;
}

void Painter::changeP(double p)
{
    op->a.p = p;
}

void Painter::changeEps(double ep)
{
    op->a.eps = ep;
}

void Painter::stopDifferent(bool clicked)
{
    if(!clicked)
    {
        delete st1.ps[1];
        st1.ps[1] = nullptr;
    }
    else
    {
        st1.ps[1] = new Stop_grad_norm;
    }
}

void Painter::stopGrad(bool clicked)
{
    if(!clicked)
    {
        delete st1.ps[2];
        st1.ps[2] = nullptr;
    }
    else
    {
        st1.ps[2] = new Stop_grad_norm;
    }
}

void Painter::stopGoodIter(bool clicked)
{
    if(!clicked)
    {
        delete st2.ps[1];
        st2.ps[1] = nullptr;
    }
    else st2.ps[2] = new Stop_x_dif;

}

void Painter::changeNGoodMax(int n)
{
    op->a.N_good_max = n;
}








