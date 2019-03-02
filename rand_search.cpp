#include "rand_search.h"
#include<iostream>
using namespace std;

vec sim_unif_box(const vec& l,const vec& r)
{
	vec result(l.size());
	for (int i = 0; i < l.size(); ++i)
	{
		result.cord[i] = (r[i] - l[i])*get_01() + l[i];
	}
	return result;
}

vec sim_unif_neibor(const vec& x0, double delta)	//Neighbourhoods of Chebyshev, this is a cube with center at x0 and side 2delta
{
	vec l(x0.size());
	vec r(x0.size());
	for (int i = 0; i < x0.size(); ++i)
	{
		l.cord[i] = x0[i] - delta;
		r.cord[i] = x0[i] + delta;
	}
	return sim_unif_box(l, r);
}

bool in_box(const vec& l,const vec& r,const vec& x)
{
	for (int i = 0; i < x.size(); ++i)
		if (x[i] < l[i] || x[i] > r[i]) return false;
	return true;
}

vec  sim_mixture(const vec& l, const vec& r, const vec& x, double p, double delta)
{
	double alpha = get_01();
	if (alpha >= p) return sim_unif_box(l, r);
	vec res;
	do {
		res = sim_unif_neibor(x, delta);
	} while (!in_box(l, r, res));
	return res;
}

void rs::calculate(Stop_some& s)
{
    a.x_cur = a.x0;
	double delta = 1;
	vec y;
    track.clear();
    track.push_back(a.x_cur);
    answ = a.x_cur;
    fansw = a.f.pf(answ);
    for (a.count = 1, a.count_good = 0; ;++a.count)
    {
		y = sim_mixture(a.left, a.right, a.x_cur, a.p, delta);
        if (a.f.pf(y) < a.f.pf(a.x_cur))
		{
			a.x_cur = y;
			++a.count_good;
		}
		delta = 1 / sqrt(a.count + 1);
        track.push_back(a.x_cur);
        if(s.crit(a))
            break;

	}
    answ = a.x_cur;
    fansw = a.f.pf(answ);
}
