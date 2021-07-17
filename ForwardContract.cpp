#include "ForwardContract.h"


ForwardContract::ForwardContract()
{
	K = 0;
	T = 0;
	lsflag = 0;
}

ForwardContract::ForwardContract(double T_, double K_, long lsflag_)
{
	T = T_; 
	K = K_;
	lsflag = lsflag_; 
}

double ForwardContract::evaluate_payoff(double S) const
{
	double payoff = lsflag * (S - K); 
	return payoff;
}
