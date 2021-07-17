#include "BlackScholesExactSimulator.h"
#include "math.h"
#include <random>


BlackScholesExactSimulator::BlackScholesExactSimulator():BlackScholesSimulator()
{}

BlackScholesExactSimulator::BlackScholesExactSimulator(const BlackScholesModel& model_,
	long num_steps_,
	double T_): BlackScholesSimulator(model_, num_steps_,T_)
{
}

BlackScholesExactSimulator::~BlackScholesExactSimulator()
{
}

double BlackScholesExactSimulator::simulate_one_step(double Scurrent, double dt, double xsi) const
{
	BlackScholesModel model = get_model();
	double mu = model.get_mu();
	double sigma = model.get_sigma(); 

	double Snext = 0; 

	double sqrt_dt = sqrt(dt); 

	double dW = sqrt_dt * xsi; 

	double dvar = (mu - (sigma * sigma / 2)) * dt;

	Snext = Scurrent * exp(dvar + dW * sigma);

	return Snext;
}