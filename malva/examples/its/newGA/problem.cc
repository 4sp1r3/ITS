#include "problem.hh"

namespace newGA {

#define MAXDISTANCE 30.0

    Problem::Problem() {
        this->_numnodes = 0;
        this->_nodes = NULL;
        this->_maxx = -MAXDISTANCE;
        this->_maxy = -MAXDISTANCE;
        this->_minx = MAXDISTANCE;
        this->_miny = MAXDISTANCE;
    }

    istream & operator>>(istream& is, Problem& pbm) {
        is >> pbm._numnodes;

        // read nodes
        pbm._nodes = new Vec2[pbm._numnodes];
        pbm._signal = Vec(pbm._numnodes);

        for (int i = 0; i < pbm._numnodes; i++) {
            is >> pbm._nodes[i][0];
            if (pbm._nodes[i][0] > pbm._maxx) pbm._maxx = pbm._nodes[i][0];
            if (pbm._nodes[i][0] < pbm._minx) pbm._minx = pbm._nodes[i][0];
            is >> pbm._nodes[i][1];
            if (pbm._nodes[i][1] > pbm._maxy) pbm._maxy = pbm._nodes[i][1];
            if (pbm._nodes[i][1] < pbm._miny) pbm._miny = pbm._nodes[i][1];
            is >> pbm._signal[i];
        }

        return is;
    }

    Problem & Problem::operator=(const Problem & pbm) {
        _numnodes = pbm._numnodes;

        _nodes = new Vec2[pbm._numnodes];
        for (int i = 0; i < pbm._numnodes; i++) {
            _nodes[i] = pbm._nodes[i];
        }

        _signal = pbm._signal;

        _minx = pbm._minx;
        _miny = pbm._miny;
        _maxx = pbm._maxx;
        _maxy = pbm._maxy;

        return *this;
    }

    bool Problem::operator==(const Problem & pbm) const {
        if (_numnodes != pbm._numnodes) {
            return false;
        }

        for (int i = 0; i < pbm._numnodes; i++) {
            if (_nodes[i] != pbm._nodes[i]) {
                return false;
            }
        }

        return _signal == pbm._signal;
    }

    bool Problem::operator!=(const Problem & pbm) const {
        return !(*this == pbm);
    }

    Direction Problem::direction() const {
        //return maximize;
        return minimize;
    }

    double Problem::getPercibedDistance(double signal) const {
        return 0.0;
    }
    
    Problem::~Problem() {
        delete [] _nodes;
    }

}
