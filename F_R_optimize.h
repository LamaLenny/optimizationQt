#pragma once
#include "FUN_vec.h"
#include "Stop_cr.h"
#include "Opt.h"
//!Class for finding the minimum of a function by direction

class oned_fun : public fun {
public:
	vec x;
	vec p;

	/*!
	*Constructor.
	*/
	oned_fun(double(*pg)(vec), vec& x1, vec& p1) : fun(pg), x(x1), p(p1) {};
	/*!
	*Copy constructor.
	*/
	oned_fun(const fun& g, vec& x1, vec& p1) : fun(g), x(x1), p(p1) {};
	/*!
	*Operator overload ().
	*\return f(x + a*p)
	*/
	double operator()(double a)
	{
		return pf(x + p.multiply_const(a));
	}
	/*!
	*.
	*\return min_(left <= a <= right) f(x + a*p)
	*/
	double lin_search(double left, double right, double eps = 1e-7);
};


//!The class search for a minimum by the Fletcher Reeves method.
class F_R : public Opt{
public:
	F_R() {};
    F_R(const Args& b): Opt(b){};
    ~F_R() override{};
	pair<double, double> intersect(const vec& x, const vec& p) const;
    void calculate(Stop_some& s) override;
};
