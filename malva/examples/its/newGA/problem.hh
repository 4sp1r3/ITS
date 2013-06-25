#ifndef PROBLEM__HH
#define PROBLEM__HH

#include "newGAstructures.hh"

#include "Vec.h"
#include "Vec2.h"

namespace newGA {

    class Problem {
    public:
        Problem();
        ~Problem();

        Problem & operator=(const Problem& pbm);
        bool operator==(const Problem& pbm) const;
        bool operator!=(const Problem& pbm) const;
        
        friend istream & operator>>(istream& is, Problem& pbm);

        Direction direction() const;

        inline int getNumNodes() { return _numnodes; };
        inline double getSignal(int i) { return _signal[i]; };
        inline Vec2 * getNodes() {return _nodes;};

        double getPercibedDistance(double signal) const;

        int _numnodes;
        Vec2* _nodes;
        Vec _signal;

        double _minx;
        double _miny;
        double _maxx;
        double _maxy;
    };

}

#endif
