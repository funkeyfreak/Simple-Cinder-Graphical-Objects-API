#ifndef ___DataConstraint___
#define ___DataConstraint___
#include <functional>
#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

#define formula [&]()
#define setFormula(x) setFormulaEx([&]() {return ((x)); })


class Constraint{
public:
	static stack<Constraint *> stk;
	using Formula = function <int()>;
	Formula default_eval = [&](){return value; };
	bool valid;

	Constraint() : eval(default_eval){} //default ctor
	Constraint(int& v) : value(v), eval(default_eval){}
	Constraint(Formula f) : eval(f){} //preferred ctor
	Constraint(Constraint & f) = default; //copy ctor


	Constraint& operator=(int& i){
		set(i);
		return *this;
	};

	operator int(){
		return (int)get();
	};

	int get(){
		if (!stk.empty()){
			this->dependents.push_back(stk.top());
		}
		if (!valid){
			this->valid = false;
			stk.push(this);
			this->value = eval();
			stk.pop();
		}
		return value;
	};

	void set(int new_val){
		value = new_val;
		for (Constraint* dep : dependents){
			if (dep->valid){
				dep->invalidate();
			}
		}
	};

	void invalidate(){
		valid = false;
		for (auto& dep : dependents){
			if (dep->valid){
				dep->invalidate();
			}
			//dependents.clear();
			//break;//constraints broke, added for resetting /*Hotfix*/
		}
		dependents.clear();
	};

	void setFormulaEx(Formula f){
		eval = f;
		invalidate();
	};

private:
	Formula eval;
	int value;
	vector<Constraint *> dependents;
};

stack<Constraint *> Constraint::stk;

#endif // ___DataConstraint___
