namespace newGA {

StopCondition_1::StopCondition_1() : StopCondition() {
}

bool StopCondition_1::EvaluateCondition(const Problem& pbm, const Solver& solver, const SetUpParams & setup) {
    return ((int) solver.best_cost_trial() == pbm.numclause());
}

StopCondition_1::~StopCondition_1() {

}

bool terminateQ(const Problem& pbm, const Solver& solver,
        const SetUpParams & setup) {
    StopCondition_1 stop;
    return stop.EvaluateCondition(pbm, solver, setup);
}

}

