#ifndef STOP__H
#define STOP__H

#include "newGAstructures.hh"

namespace newGA {

    class Problem;
    class Solver;
    class SetUpParams;

    class StopCondition {
    public:
        StopCondition();
        virtual bool EvaluateCondition(const Problem& pbm, const Solver& solver, const SetUpParams& setup) = 0;
        ~StopCondition();
    };

    class StopITS : public StopCondition {
    public:
        StopITS();
        virtual bool EvaluateCondition(const Problem& pbm, const Solver& solver, const SetUpParams& setup);
        ~StopITS();
    };

    bool terminateQ(const Problem& pbm, const Solver& solver, const SetUpParams & setup);

}

#endif
