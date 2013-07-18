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
            printf("Tiempo optimo para trial %d = %f\n", i+1 , timeT[i]);
            printf("Mejor fitness para trial %d = %f\n", i+1 , costT[i]);
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


        /* Para grafica  y test normal*/
        double cost_promedio = 0;
        printf("\n [ \n");
        for (int i=0 ; i < trials ; ++i) {
        	printf(" %f " , costT[i] );
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

        printf("Costo promedio = %f , costo desviacion = %f\n", cost_promedio , cost_desv);

        /*
         *  Esta parte es para graficar por si no da ok el test de normalidad
         *
         *  */
        int divisiones = trials / 50 ;
        if (divisiones > 5) { // puedo graficar? o es una corrida de pocas trials?
        	printf("Tabla para visualizar la forma de distribucion\n");
        	double * divT = new double[divisiones];
        	for (int i = 0 ; i < divisiones ; i++) {
        		divT[i] = 0.0;
        	};

        	double min_cost = 10000000.0;
        	double max_cost = -10000000.0 ;
            for (int i = 0 ; i < trials ; i++) {
            	if (costT[i] < min_cost) min_cost = costT[i];
            	if (costT[i] > max_cost) max_cost = costT[i];
            };

            double delta = (max_cost - min_cost) / ((double)divisiones) ;

            // populo la tabla divT
            for (int i = 0 ; i < trials ; i++) {
            	for (int j=0 ; j < divisiones ; j++) {
            		double interval_min = min_cost + ((double)j) * delta;
            		double interval_max = interval_min + delta;

            		if ((costT[i] > interval_min) && (costT[i] < interval_max) )
            			divT[j] += 1.0;
            	}
            }

            // escribo la tabla
            printf("[ \n ");
        	for (int i=0 ; i < divisiones ; i++) {
        		double interval_min = min_cost + ((double)i) * delta;
        		double interval_max = interval_min + delta;
        		double interval_med = (interval_min + interval_max) / 2.0 ;

        		printf(" %f  , %f \n" , divT[i]  , interval_med );
        	}
        	printf(" ] \n");

        }

        printf("\n\n");

        /* Para la tabla... */
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
