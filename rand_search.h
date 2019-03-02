#pragma once
#include "my_vector.h"
#include "com_rand.h"
#include "FUN_vec.h"
#include "Stop_cr.h"
#include "Opt.h"

//!The class search for a minimum by random search.
class rs : public Opt
{
public:
	rs() {};
    rs(const Args& b): Opt(b) {};
    ~rs() override {};
    void calculate(Stop_some& s) override;
};

