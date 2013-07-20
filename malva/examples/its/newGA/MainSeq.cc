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
        double * costT = new double[trials];
        double time_promedio = 0.0 ;

        for (int i = 0 ; i < trials ; i++) {
        	timeT[i] = solver.browseHistory_getTime_found_best_by_trial(i+1) / 1000000.0;
        	costT[i] = solver.browseHistory_getBest_Cost_by_trial(i+1);
            printf("Tiempo optimo para trial %d = %.4f\n", i+1 , timeT[i]);
            printf("Mejor fitness para trial %d = %.4f\n", i+1 , costT[i]);
            time_promedio += timeT[i];
        }

        time_promedio /= (double)trials;
        printf("Tpromedio es = %.4f\n" , time_promedio);

        double time_desviacion = 0;
        for (int i = 0 ; i < trials ; i++) {
        	time_desviacion += pow( time_promedio - timeT[i] , 2.0 );
        };
        time_desviacion /= (double)trials;
        time_desviacion = sqrt(time_desviacion);

        printf("Desviacion Tiempo = %.4f\n" , time_desviacion);

        int iteration = solver.iteration_best_found();
        int trial = solver.trial_best_found();

        printf("global se obtubo en Trial=%d , Iteracion=%d\n" , trial, iteration);

        s_stat statics = solver.browseHistory_getIteration(trial, iteration);
        printf("En ese Trial/iteracion el costo promedio=%.4f , desviacion=%.4f\n",
        		statics.average_cost,
        		statics.standard_deviation);


        /* Para grafica  y test normal*/
        double cost_promedio = 0;
        printf("\n ##### TABLA Fitness optimo por trial ######\n");
        printf("\n [ \n");
        for (int i=0 ; i < trials ; ++i) {
        	printf(" %.4f " , costT[i] );
        	if (i != (trials -1) ) printf(" , ");
        	printf("\n");
        	cost_promedio += costT[i];
        }
        printf(" ] \n ");
        cost_promedio /= (double)trials;

        double cost_desv = 0;
        for (int i = 0 ; i < trials ; i++) {
        	cost_desv += pow( cost_promedio - costT[i] , 2.0 );
        };
        cost_desv /= (double)trials;
        cost_desv = sqrt(cost_desv);

        printf("fitnes promedio entre todos los triasls = %.4f\n" , cost_promedio);
        printf("desviacion de fitness entre las triasl = %.4f\n\n", cost_desv);

        /* TABLA DE Fitness en funcion de generacion (para el trial 1)*/
        printf("\n ##### TABLA mejor Fitness en funcion de generacion (para trial1) ######\n");
        printf("\n [ \n");
        for (int i=0 ; i <= cfg.nb_evolution_steps() ; ++i) {
        	double aux = solver.browseHistory_getIteration(1,i).best_cost;
        	printf(" %.4f " , aux );
        	if (i != (cfg.nb_evolution_steps()) ) printf(" , ");
        	printf("\n");
        }
        printf(" ] \n ");


        printf("\n\n");

        /* Para la tabla... */
        printf("\n F=%s Gen=%d fit=%.4f fitpro=%.4f fitdes=%.4f time=%.4f timepro=%.4f timedes=%.4f\n" ,
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
