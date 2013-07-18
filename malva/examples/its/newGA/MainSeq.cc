#include "problem.hh"
#include "operators.hh"
#include "setup.hh"
#include "solver.hh"

using namespace newGA;

int main(int argc, char** argv) {
    using skeleton newGA;

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

    random_seed(time(0));

    Solver_Seq solver(pbm, cfg);
    solver.run();

    if (solver.pid() == 0) {
        solver.show_state();
        cout << "Solution: " << solver.global_best_solution()
             << "Fitness: " << solver.global_best_solution().fitness() << endl;
        ofsResult << solver.userstatistics();

        //solver.statistics()


        int trials = cfg.independent_runs();
        double * timeT = new double[trials];
        double time_promedio = 0.0 ;

        for (int i = 0 ; i < trials ; i++) {
        	timeT[i] = solver.browseHistory_getTime_found_best_by_trial(i+1) / 1000000.0;
            printf("Tiempo optimo para trial %d = %f\n", i+1 , timeT[i]);
            time_promedio += timeT[i];
        }

        time_promedio /= (double)trials;
        printf("Tpromedio es = %f\n" , time_promedio);

        double time_desviacion = 0;
        for (int i = 0 ; i < trials ; i++) {
        	time_desviacion += pow( time_promedio - timeT[i] , 2.0 );
        };
        time_desviacion /= (double)trials;
        time_desviacion = sqrt(time_desviacion);

        printf("Desviacion Tiempo = %f\n" , time_desviacion);

        int iteration = solver.iteration_best_found();
        int trial = solver.trial_best_found();

        printf("global se obtubo en Trial=%d , Iteracion=%d\n" , trial, iteration);

        s_stat statics = solver.browseHistory_getIteration(trial, iteration);
        printf("En ese Trial/iteracion el costo promedio=%f , desviacion=%f\n",
        		statics.average_cost,
        		statics.standard_deviation);



        printf("\n F=%s Gen=%d fit=%f fitpro=%f fitdes=%f time=%f timepro=%f timedes=%f\n" ,
        		argv[2] ,
        		iteration ,
        		solver.global_best_solution().fitness() ,
        		statics.average_cost,
        		statics.standard_deviation,
        		timeT[trial-1],
        		time_promedio,
        		time_desviacion);




    }

    return (0);
}
