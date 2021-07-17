#pragma once
class EuropeanPayoff
{
private: 

public:

	EuropeanPayoff() {};
	virtual ~EuropeanPayoff() {};

	virtual double evaluate_payoff(double S) const=0; 


};

