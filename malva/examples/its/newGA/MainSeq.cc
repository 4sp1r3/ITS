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

    Solver_Seq solver(pbm, cfg);
    solver.run();

    if (solver.pid() == 0) {
        solver.show_state();
        cout << "Solution: " << solver.global_best_solution()
             << "Fitness: " << solver.global_best_solution().fitness() << endl;
        ofsResult << solver.userstatistics();
    }

    return (0);
}
