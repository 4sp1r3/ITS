#ifndef PROBLEM__HH
#define PROBLEM__HH

#include "newGA.hh"
#include "newGAstructures.hh"

#include "Vec.h"
#include "Vec2.h"

namespace newGA {

    class Problem {
    public:
        Problem();
        ~Problem();

        friend ostream & operator<<(ostream& os, const Problem& pbm);
        friend istream & operator>>(istream& is, Problem& pbm);

        Problem & operator=(const Problem& pbm);
        bool operator==(const Problem& pbm) const;
        bool operator!=(const Problem& pbm) const;

        Direction direction() const;

        inline int getNumNodes() { return _numnodes; };
        inline double getSignal(int i) { return _signal[i]; };
        inline Vec2 * getNodes() {return _nodes;};

        inline double getPercibedDistance(double signal) { return 0; }

        int _numnodes;
        Vec2 * _nodes;
        Vec * _signal;

        double _minx;
        double _miny;
        double _maxx;
        double _maxy;
    };

}

#endif
