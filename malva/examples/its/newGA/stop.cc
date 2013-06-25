#include "stop.hh"
#include "solution.hh"
#include "setup.hh"
#include "solver.hh"

namespace newGA {

    StopITS::StopITS() : StopCondition() {
    }

    bool StopITS::EvaluateCondition(const Problem& pbm, const Solver& solver, const SetUpParams & setup) {
        if (solver.current_best_solution().fitness() < setup.fitness_treshold()) {
            return true;
        }
        return false;
    }

    StopITS::~StopITS() {

    }

    bool terminateQ(const Problem& pbm, const Solver& solver,
            const SetUpParams & setup) {
        StopITS stop;
        return stop.EvaluateCondition(pbm, solver, setup);
    }

}
