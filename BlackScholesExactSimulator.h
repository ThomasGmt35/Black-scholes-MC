#pragma once
#include "BlackScholesSimulator.h"
class BlackScholesExactSimulator :
    public BlackScholesSimulator
{
public:
	BlackScholesExactSimulator();
	BlackScholesExactSimulator(const BlackScholesModel&,
		long num_steps_,
		double T_);

	~BlackScholesExactSimulator();

	virtual double simulate_one_step(double Scurrent,double dt,  double xsi) const;
};

