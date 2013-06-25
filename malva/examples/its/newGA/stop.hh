#ifndef STOP__H
#define STOP__H

#include "newGA.hh"
#include "newGAstructures.hh"

namespace newGA {

    class StopCondition {
    public:
        StopCondition();
        virtual bool EvaluateCondition(const Problem& pbm, const Solver& solver, const SetUpParams& setup) = 0;
        ~StopCondition();
    };

    class StopCondition_1 : public StopCondition {
    public:
        StopCondition_1();
        virtual bool EvaluateCondition(const Problem& pbm, const Solver& solver, const SetUpParams& setup);
        ~StopCondition_1();
    };


    bool terminateQ(const Problem& pbm, const Solver& solver,
            const SetUpParams & setup);

}

#endif
