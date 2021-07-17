#include "BlackScholesSimulator.h"

#include "math.h"

BlackScholesSimulator::BlackScholesSimulator()
{
	
	num_steps = 0; 
	num_spot = 0;
	ti = NULL;
	Si = NULL; 

	default_random_engine agenerator;
	normal_distribution<double> adistribution(0.,1.);

	generator = agenerator; 
	distribution = adistribution; 

	beta = 0.5826;


}

BlackScholesSimulator::BlackScholesSimulator(const BlackScholesModel& model_, 
										     long num_steps_,
											 double T_)
{
	model = model_; 
	num_steps = num_steps_; 
	num_spot = num_steps_ + 1; 
	beta = 0.5826;

	double dt = T_ / num_steps; 

	ti = new double[num_spot];
	Si = new double[num_spot];

	//initialization

	ti[0] = 0.;
	Si[0] = model.get_S0(); 

	for (unsigned i = 1; i < num_spot; i++)
	{
		ti[i] = i * dt;
		Si[i] = 0.;
	}

	default_random_engine agenerator;
	normal_distribution<double> adistribution(0., 1.);

	generator = agenerator;
	distribution = adistribution;
}


BlackScholesSimulator::~BlackScholesSimulator()
{
	delete[] ti; 
	delete[] Si; 
}

void BlackScholesSimulator::simulate_path(default_random_engine & agenerator, normal_distribution<double> & adistribution)
{
	double Scurrent  = Si[0];
	double Snext = 0;
	

	for (unsigned i = 0; i < num_steps; i++)
	{
		double tcurrent = ti[i]; 
		double tnext = ti[i + 1]; 
		double dt = tnext - tcurrent; 

		double xsi = adistribution(agenerator);

		Snext = simulate_one_step(Scurrent,dt,xsi); 

		Si[i+1] = Snext; 

		Scurrent = Snext; 
	}
}

double BlackScholesSimulator::get_payoff(const EuropeanPayoff& payoff) const
{
	double SN = Si[num_spot - 1]; 

	double po = payoff.evaluate_payoff(SN); 

	return po; 
}

double BlackScholesSimulator::check_down_and_in_barrier(double H, const double* path, long num_points) const
{
	double crossed_barrier = 0.0;
	


	for (long i = 0; i < num_points; i++)
	{
		double S_local = path[i]; 

		if (S_local <= H)
		{
			crossed_barrier = 1; 
			break;
		}
	}

	return crossed_barrier; 
}

double BlackScholesSimulator::check_down_and_out_barrier(double H, const double* path, long num_points) const
{
	double crossed_barrier = 1.0;

	for (long i = 0; i < num_points; i++)
	{
		double S_local = path[i];

		if (S_local <= H)
		{
			crossed_barrier = 0;
			break;
		}
	}

	return crossed_barrier;
}

double BlackScholesSimulator::compute_monte_carlo_price(unsigned num_path, const EuropeanPayoff& payoff)
{
	double MC_sum = 0.0;

	default_random_engine agenerator = get_generator();
	normal_distribution<double> adistribution = get_distribution();

	for (unsigned i = 1; i <= num_path; i++)
	{
		simulate_path(agenerator, adistribution);
		double scenario_payoff = get_payoff(payoff);

		MC_sum = MC_sum + scenario_payoff;
	}

	double MC_mean = MC_sum / (double)num_path;

	BlackScholesModel model = get_model();

	double T = ti[num_spot - 1];
	double r = model.get_r();

	double DF = exp(-r * T);

	double MC_price = DF * MC_mean;

	return MC_price;
}

double BlackScholesSimulator::compute_down_in_monte_carlo_price(unsigned num_path, 
		double H, 
	const EuropeanPayoff& payoff, 
	bool adjust_barrier)
{
	double MC_sum = 0.0;

	BlackScholesModel model = get_model();


	default_random_engine agenerator = get_generator();
	normal_distribution<double> adistribution = get_distribution();

	double dt = ti[1] - ti[0]; 
	double crossed_barrier = 0;

	double H_tilda = H;

	double sigma = model.get_sigma(); 

	if(adjust_barrier)
		H_tilda = H * exp(beta * sigma * sqrt(dt));

	for(unsigned i = 1; i <= num_path; i++)
	{
		simulate_path(agenerator, adistribution);

		crossed_barrier = check_down_and_in_barrier(H_tilda, Si, num_spot); 
		double scenario_payoff = get_payoff(payoff);

		scenario_payoff = crossed_barrier * scenario_payoff; 

		MC_sum = MC_sum + scenario_payoff;
	}

	double MC_mean = MC_sum / (double)num_path; 
	
	
	double T = ti[num_spot - 1]; 
	double r = model.get_r(); 

	double DF = exp(-r*T);

	double MC_price = DF * MC_mean; 

	return MC_price; 
}

double BlackScholesSimulator::compute_down_out_monte_carlo_price(unsigned num_path,
	double H,
	const EuropeanPayoff& payoff,
	bool adjust_barrier)
{
	double MC_sum = 0.0;

	BlackScholesModel model = get_model();


	default_random_engine agenerator = get_generator();
	normal_distribution<double> adistribution = get_distribution();

	double dt = ti[1] - ti[0];
	double crossed_barrier = 0;

	double H_tilda = H;

	double sigma = model.get_sigma();

	if (adjust_barrier)
		H_tilda = H * exp(beta * sigma * sqrt(dt));

	for (unsigned i = 1; i <= num_path; i++)
	{
		simulate_path(agenerator, adistribution);

		crossed_barrier = check_down_and_out_barrier(H_tilda, Si, num_spot);
		double scenario_payoff = get_payoff(payoff);

		scenario_payoff = crossed_barrier * scenario_payoff;

		MC_sum = MC_sum + scenario_payoff;
	}

	double MC_mean = MC_sum / (double)num_path;

	double T = ti[num_spot - 1];
	double r = model.get_r();

	double DF = exp(-r * T);

	double MC_price = DF * MC_mean;

	return MC_price;
}
