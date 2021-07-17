#pragma once
#include "BlackScholesSimulator.h"
class BlackScholesEulerSimulator :
    public BlackScholesSimulator
{
public:
	BlackScholesEulerSimulator();
	BlackScholesEulerSimulator(const BlackScholesModel&,
		long num_steps_,
		double T_);

	~BlackScholesEulerSimulator();

	virtual double simulate_one_step(double Scurrent,double dt,  double xsi) const;
};

