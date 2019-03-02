#include "F_R_optimize.h"
#include <cmath>
#include <iostream> 
#include "brent.hpp"
#include <algorithm>

using namespace std;
double oned_fun::lin_search(double left, double right, double eps)
{
	double h = (right - left) / 10;
	double m_f = (*this)(left);
	double m_x = left;
	for (int i = 0; i < 10; ++i)
	{
		//pair<double, double> z = boost::math::tools::brent_find_minima(*this, left, left + h, 20);
		double z = brent::local_min(*this, left, left + h, eps);
		double f_z = (*this)(z);
		if ( f_z < m_f)
		{
			m_f = f_z;
			m_x = z;
		}
		left += h;
	}
	return m_x;
}
pair<double, double> F_R::intersect(const vec& x, const vec& p) const
{
	pair<double, double> result(0, INT_MAX);
	for (int i = 0; i < x.size(); ++i)
	{
		if (p[i] == 0) continue;
		double h1 = (a.left[i] - x[i]) / p[i];
		double h2 = (a.right[i] - x[i]) / p[i];
		if (p[i] < 0)
		{
			std::swap(h1, h2);
		}

		result.first = std::max(result.first, h1);
		result.second = std::min(result.second, h2);
	}
	return result;
}

void F_R::calculate(Stop_some& s)
{
    a.x_cur = a.x0;
	vec grad_cur = a.f.grad(a.x_cur, a.left, a.right, a.eps);
	vec grad_next;
	vec p = grad_cur.multiply_const(-1);
    track.clear();
    track.push_back(a.x_cur);
    answ = a.x_cur;
    fansw = a.f.pf(answ);
    for(a.count = 1;  ; ++(a.count))
    {
		pair<double, double> interval = intersect(a.x_cur, p);
		oned_fun g(a.f, a.x_cur, p);
		double alpha = g.lin_search(interval.first, interval.second, a.eps);
		a.x_prev = a.x_cur;
		a.x_cur = a.x_cur + p.multiply_const(alpha);
		grad_next = a.f.grad(a.x_cur, a.left, a.right, a.eps);
		double beta = grad_next.sq_norm() / grad_cur.sq_norm();
		p = grad_next.multiply_const(-1) + p.multiply_const(beta);
		grad_cur = grad_next;
         bool t = s.crit(a);
         track.push_back(a.x_cur);
        if (s.crit(a))
            break;
	}
    answ = a.x_cur;
    fansw = a.f.pf(answ);
}

