#include "BlackScholesModel.h"
#include <algorithm>
#include "math.h"
#include <cmath>

using namespace std; 


double N(double x)
{
	// constants
	double a1 = 0.254829592;
	double a2 = -0.284496736;
	double a3 = 1.421413741;
	double a4 = -1.453152027;
	double a5 = 1.061405429;
	double p = 0.3275911;

	// Save the sign of x
	int sign = 1;
	if (x < 0)
		sign = -1;
	x = fabs(x) / sqrt(2.0);

	// A&S formula 7.1.26
	double t = 1.0 / (1.0 + p * x);
	double y = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * exp(-x * x);

	return 0.5 * (1.0 + sign * y);
}

BlackScholesModel::BlackScholesModel()
{
	S0 = 1; 
	mu = 0;
	r = 0;
	sigma = 0.0001; 
}

BlackScholesModel::BlackScholesModel(double S0_, 
	double mu_,
	double r_,
	double sigma_)
{
	S0 = S0_; 
	mu = mu_;
	r = r_;
	sigma = max(sigma_, 0.0000001);
}

double BlackScholesModel::vanilla_european_option_price(double cpflag, double T, double K) const
{
	double price = 0.0;

	double F = 0;
	double stdev = 0;
	double var = 0;
	double d1 = 0;
	double d2 = 0;
	double Nd1 = 0; 
	double Nd2 = 0;
	double DF; 

	F  = S0 * exp(mu * T);
	DF = exp(-r * T);

	stdev = sigma * sqrt(T);
	var = stdev * stdev; 

	d1 = (log(F / K) + 0.5 * var) / stdev; 
	d2 = d1 - stdev; 

	Nd1 = N(d1); 
	Nd2 = N(d2); 

	double call_price = DF* (F * Nd1 - K * Nd2);

	if (cpflag == 1)
		price = call_price;
	else
	{
		double forward_price = DF * (F - K);

		price = call_price - forward_price; 
	}

	return price;
}

double BlackScholesModel::forwardPrice(long lsflag, double T, double K) const
{

	double price = 0.0;

	double F = 0;
	double DF;

	F = S0 * exp(mu * T);
	DF = exp(-r * T);

	double forwardPrice = DF * lsflag * (F - K); 

	return forwardPrice;

}

double BlackScholesModel::down_and_in_barrier_call_option(double T, double K, double H) const
{
	double price = 0; 

	double nu = r - 0.5 * sigma * sigma; 

	double S0adjusted = H * H / S0; 

	BlackScholesModel adjusted_model(S0adjusted,
								     mu,
									 r,
									 sigma); 

	double CBS_adjusted = adjusted_model.vanilla_european_option_price(1, T, K);

	double time_change = 2 * nu / (sigma * sigma); 

	double adjust; 
	
	adjust  = H / S0;

	price = pow(adjust , (time_change)) * CBS_adjusted; 

	return price;
}


double BlackScholesModel::down_and_out_barrier_call_option(double T,
														  double K,
														  double H) const
{
	double down_and_in = down_and_in_barrier_call_option(T, K, H); 

	double Cbs = vanilla_european_option_price(1, T, K);

	double down_and_out = Cbs - down_and_in; 

	return down_and_out; 
}