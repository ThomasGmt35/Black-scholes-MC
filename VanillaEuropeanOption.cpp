#include "VanillaEuropeanOption.h"
#include <algorithm>

using namespace std;


VanillaEuropeanOption::VanillaEuropeanOption()
{
	K = 0;
	T = 0;
	cpflag = 0;
}

VanillaEuropeanOption::VanillaEuropeanOption(double T_, double K_, long cpflag_)
{
	T = T_;
	K = K_;
	cpflag = cpflag_;
}

double VanillaEuropeanOption::evaluate_payoff(double S) const
{
	double payoff = max(0., cpflag * (S - K));
	
	return payoff;
}
