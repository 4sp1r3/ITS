#include "problem.hh"
#include "operators.hh"
#include "setup.hh"
#include "solver.hh"

using namespace newGA;

int main(int argc, char** argv) {
    using skeleton newGA;

    random_seed(time(0));

    if (argc < 4) {
        cerr << endl
                << "Error: number of arguments in the execution call is incorrect !!";
        exit(-1);
    }

    ifstream ifsConfig(argv[1]);
    if (!ifsConfig) {
        cerr << endl << "Error: It's imposible find Configuration file !!";
        exit(-1);
    }

    ifstream ifsInstance(argv[2]);
    if (!ifsInstance) {
        cerr << endl << "Error: It's imposible find Instance Problem File !!";
        exit(-1);
    }

    ofstream ofsResult(argv[3]);
    if (!ofsResult) {
        cerr << endl << "Error: It's imposible find Resultate File !!";
        exit(-1);
    }

    Problem pbm;
    ifsInstance >> pbm;

    Operator_Pool pool(pbm);

    SetUpParams cfg(pool);
    ifsConfig >> cfg;

    int population[] =  { 5 , 15 , 30 };
    int population_size = 3;

    double cross[] = {0.7, 0.80 , 0.90 };
    int cross_size = 3;

    double mutation[] = {0.01, 0.05 , 0.1 };
    int mutation_size = 3;

    for (int ite_population = 0; ite_population < population_size ; ite_population++) {
    	cfg.population_size(population[ite_population]);

    	for (int ite_cross = 0 ; ite_cross < cross_size ; ite_cross++){
    		cfg.pool().intra_operator(0).setup(cross[ite_cross]);

        	for (int ite_mutation = 0 ; ite_mutation < mutation_size ; ite_mutation++){
        	    cfg.pool().intra_operator(1).setup(mutation[ite_mutation]);

        	    random_seed(time(0)+ite_population+ite_cross+ite_mutation);
        	    Solver_Seq solver(pbm, cfg);
        	    solver.run();

        	    if (solver.pid() == 0) {

        	    	float avgBestCost = 0.0;
        	    	for (int i = 1; i <= cfg.independent_runs() ; i++) {
        	    			avgBestCost += solver.browseHistory_getBest_Cost_by_trial(i);
        	    	}
        	    	avgBestCost = avgBestCost / ( (float)cfg.independent_runs() ) ;

        	        solver.show_state();
        	        cout << "Solution: " << solver.global_best_solution() << " ";
                    printf("Fitness: %.4f ", solver.global_best_solution().fitness());
                    printf("FitnessP: %.4f \n", avgBestCost);
        	        ofsResult << solver.userstatistics();
        	    }

        	    printf("FINISH Poblacion = %d , Cross = %.4f , Mutation = %.4f \n\n",
        	    		population[ite_population] , cross[ite_cross] , mutation[ite_mutation]);

        	}

    	}
    }



    return (0);
}
