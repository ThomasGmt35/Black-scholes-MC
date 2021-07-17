#pragma once
#include "EuropeanPayoff.h"
class ForwardContract :
    public EuropeanPayoff
{
private:

    double T; 
    double K; 
    long lsflag; 



public:

    ForwardContract(); 

    ForwardContract(double T_, 
                    double K_, 
                    long lsflag_);

    
    virtual double evaluate_payoff(double S) const;

  


    ~ForwardContract() {};

};

