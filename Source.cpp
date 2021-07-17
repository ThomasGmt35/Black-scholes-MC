#include <iostream>
#include <string>
#include <random>
#include "math.h"
#include <algorithm>
#include "BlackScholesModel.h"
#include "ForwardContract.h"
#include "VanillaEuropeanOption.h"
#include "BlackScholesExactSimulator.h"
#include "BlackScholesEulerSimulator.h"

using namespace std;

int main()
{
	double S0 = 107;
	double mu = 0.02;
	double r = mu;
	double sigma = 0.15;

	double T = 1;
	double F = S0 * exp(mu * T);

	double K = F;

	long long_or_short_forward = 1;
	long call_or_put_option = 1;
	double ITM = 1;

	K = ITM * F;

	double price_option_analytical = 0;
	double price_forward_analytical = 0;
	double price_option_numerical = 0;
	double price_forward_numerical = 0;

	long cp = 1;

	long num_step_mc = 10;
	unsigned num_path = 100000;


	// analytical price; 
	BlackScholesModel BS(S0, mu, r, sigma);

	double forward_price_analytical = BS.forwardPrice(long_or_short_forward, T, K);	

	price_forward_analytical = BS.forwardPrice(long_or_short_forward, T, K);
	price_option_analytical = BS.vanilla_european_option_price(cp, T, K);


	ForwardContract aForward(T, K, long_or_short_forward);
	VanillaEuropeanOption aOption(T, K, call_or_put_option);

	// Euler Approximation
	BlackScholesEulerSimulator BSEulerSimulator(BS,
		num_step_mc,
		T);

	// Exact
	BlackScholesExactSimulator BSExactSimulator(BS,
		num_step_mc,
		T);

	// simulation Forward 
	double price_forward_mc_euler = BSEulerSimulator.compute_monte_carlo_price(num_path, aForward);

	// simulation  Forward
	double price_forward_mc_exact = BSExactSimulator.compute_monte_carlo_price(num_path, aForward);

	// simulation Option 
	double price_option_mc_euler = BSEulerSimulator.compute_monte_carlo_price(num_path, aOption);
	
	// simulation  Option
	double price_option_mc_exact = BSExactSimulator.compute_monte_carlo_price(num_path, aOption);


	// Print Results
	cout << "Forward Analytical Price: \n\n";
	cout << price_forward_analytical << "\n\n";

	cout << "Forward MC Price using Euler Scheme: \n\n";
	cout << price_forward_mc_euler << "\n\n";

	cout << "Forward MC Price using Exact Scheme: \n\n";
	cout << price_forward_mc_exact << "\n\n";


	cout << "Option Analytical Price: \n\n";
	cout << price_option_analytical << "\n\n";

	cout << "Option MC Price using Euler Scheme: \n\n";
	cout << price_option_mc_euler << "\n\n";

	cout << "Option MC Price using Exact Scheme: \n\n";
	cout << price_option_mc_exact << "\n\n";


	return 0;
}
