#pragma once
#include "BlackScholesModel.h"
#include "EuropeanPayoff.h"
#include <random>

using namespace std; 

class BlackScholesSimulator
{
private: 

	BlackScholesModel model;
	unsigned num_steps;
	unsigned num_spot; 

	double* ti;
	double* Si; 

	default_random_engine generator;
	normal_distribution<double> distribution;

	double beta; 
public:



	BlackScholesSimulator();
	BlackScholesSimulator(const BlackScholesModel &,
						  long num_steps_,
						  double T_);
	
	virtual ~BlackScholesSimulator();

	virtual double simulate_one_step(double Scurrent, double dt, double xsi) const=0;

	void simulate_path(default_random_engine& agenerator, normal_distribution<double>& adistribution);

	double get_payoff(const EuropeanPayoff& payoff) const; 

	const BlackScholesModel & get_model() const { return model;}
	const default_random_engine & get_generator() const { return generator; }
	const normal_distribution<double> & get_distribution() const { return distribution; }
	
	double compute_monte_carlo_price(unsigned num_path, const EuropeanPayoff & payoff); 

	double compute_down_in_monte_carlo_price(unsigned num_path, double H, const EuropeanPayoff& payoff, bool adjust_barrier);

	double compute_down_out_monte_carlo_price(unsigned num_path, double H, const EuropeanPayoff& payoff, bool adjust_barrier);

	double check_down_and_in_barrier(double H, const double* path, long num_points) const;

	double check_down_and_out_barrier(double H, const double* path, long num_points) const;

};

