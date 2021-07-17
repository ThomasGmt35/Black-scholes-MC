#pragma once
class BlackScholesModel
{
private:

	double S0; 
	double mu;
	double r;
	double sigma;

public:

	BlackScholesModel();


	BlackScholesModel(double S0, 
		double mu_,
		double r_,
		double sigma_);

	~BlackScholesModel(){}

	double vanilla_european_option_price(double cpflag,
									     double T, 
									     double K) const; 

	double forwardPrice(long lsflag, 
						double T, 
						double K) const;


	// getters

	double get_S0 () const { return S0; }
	double get_mu() const {return mu;}
	double get_r() const { return r; }
	double get_sigma() const { return sigma;}

	double down_and_in_barrier_call_option(double T,
										   double K,
										   double H) const;


	double down_and_out_barrier_call_option(double T,
		double K,
		double H) const;



};

