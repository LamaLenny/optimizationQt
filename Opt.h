#pragma once
#include "FUN_vec.h"
#include "Stop_cr.h"

class Opt
{
public:
	
	Args a;
	vec answ;
        double fansw;
        Opt() : a(1000), track(0) {};
        Opt(const Args& b) : a(b) {};

        virtual ~Opt(){};
        virtual void calculate(Stop_some& s) = 0;
        vector<vec> track;

};

