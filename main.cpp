
#include "ConfigFile.h"


#include "xyz.h"
#include "bfield.h"
#include "walls.h"
#include "system.h"
#include "diffusion.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <vector>
#include <string>


using namespace std;



int main()
{

	// read input into config
	ConfigFile config("input.txt");

	// read integration parameters
	Integration int_params(config);

	// read system parameters
	System system(config);

	// start with random config. 
	system.init_random();

    Diffusion diffusion(system, int_params.Nt);


	// integrate Nt_init time steps
	unsigned int ti;
	cout << "Starting with equilibration ...\n";
	for( ti = 0; ti < int_params.Nt_init; ++ ti) {
		// print progress
		if( (ti%int_params.print_freq) == 0 ) {
			cout << (int_params.Nt_init + int_params.Nt) << '\t';
			cout << ti << endl;
		}
		// make t_unit time steps
		for(unsigned int tti=0; tti < int_params.t_unit; ++tti)	{
			system.step();
		}
	}

	cout << "Ended equilibration. Starting sampling ... \n";

	for(; ti < (int_params.Nt+int_params.Nt_init); ++ti) {
		// print progress 
		if( (ti%int_params.print_freq) == 0 ) {
			cout << (int_params.Nt_init + int_params.Nt) << '\t';
			cout << ti << endl;
		}

		// make t_unit time steps
		for(unsigned int tti = 0;tti<int_params.t_unit;++tti) 
			system.step();
        	
        diffusion.sample(system); 
        int_params.t_unit *= 2;
        
	}


	cout << "Simulation finished.\nNormalizing and writing results ..." << endl;

    diffusion.write("msd.dat");


	return 0;
}



