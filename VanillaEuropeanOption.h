#pragma once
#include "EuropeanPayoff.h"
class VanillaEuropeanOption :
    public EuropeanPayoff
{
private:

    double T;
    double K;
    long cpflag;

public:

    VanillaEuropeanOption();

    VanillaEuropeanOption(double T_,
        double K_,
        long cpflag);


    virtual double evaluate_payoff(double S) const;



    ~VanillaEuropeanOption() {};

};

