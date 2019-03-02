#pragma once
#include "FUN_vec.h"
#include <string>
#include <vector>
#include "Args.h"

//!Virtual parent class stop criteria
class Stop {
public:
	/*!
	*Is it time to stop the iteration.
	*\return true->stop, false->not stop.
	*/
	virtual bool crit(Args& a) = 0;
	/*!
	*Criterion name
	*/
	virtual const char* name() = 0;
};

//!iteration count is max
/*!
*count >= N_max -> stop
*/
class Stop_N_max : public Stop {
public:
	bool crit(Args& a) override;	
	const char* name() override;
};

//!x_different less then eps
/*!
*||x_cur - x_next|| < eps -> stop
*/
class Stop_x_dif : public Stop {
public:
	bool crit(Args& a) override;	
	const char* name() override;
};

//!f norm is less then eps
/*!
*||f(x_cur)||<eps -> stop (for Fletcher Reeves)
*/
class Stop_grad_norm : public Stop {
public:
	bool crit(Args& a) override;
	const char* name() override;
};

//!good iteration count is max
/*!
*count_good >= N_max_good -> stop (for random search)
*/
class Stop_good_comp : public Stop {
public:
	bool crit(Args& a) override;
	const char* name() override;

};

//!The class containing the vector of pointers to criteria

class Stop_some {
public:
	/*!
	*Vector of pointers to criteria
	*/
	vector<Stop*> ps;
	/*!
	*The name of the criterion that caused the stop.
	*/
	string* reason;
	/*!
	*Constructor. Allocates memory for a and reason. Copies a vector of pointers to criteria.
	*/
	Stop_some():ps(1)
	{
		ps[0] = new Stop_N_max;
		reason = new string;
	};
	/*!
	*Constructor. Allocates memory for a and reason. 
	*/
	Stop_some(vector<Stop*>& pq) : ps(pq)
	{
		reason = new string;
	}
	/*!
	*Destructor. Delete reason and a.
	*/
	~Stop_some()
	{
		delete reason;
		for (int i = 0; i < ps.size(); ++i)
		{
			delete ps[i];
		}
	}
	/*!
	*Is it time to stop the iteration on any of the criteria.
	*/
	bool crit(Args& a);
};
