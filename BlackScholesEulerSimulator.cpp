#include "BlackScholesEulerSimulator.h"
#include "math.h"
#include <random>


BlackScholesEulerSimulator::BlackScholesEulerSimulator():BlackScholesSimulator()
{}

BlackScholesEulerSimulator::BlackScholesEulerSimulator(const BlackScholesModel& model_,
	long num_steps_,
	double T_): BlackScholesSimulator(model_, num_steps_,T_)
{
}

BlackScholesEulerSimulator::~BlackScholesEulerSimulator()
{
}

double BlackScholesEulerSimulator::simulate_one_step(double Scurrent, double dt, double xsi) const
{
	BlackScholesModel model = get_model();
	double mu = model.get_mu();
	double sigma = model.get_sigma(); 

	double Snext = 0; 

	double sqrt_dt = sqrt(dt); 

	double dW = sqrt_dt * xsi; 

	Snext = Scurrent + Scurrent * mu * dt + Scurrent * sigma * dW; 

	return Snext;
}