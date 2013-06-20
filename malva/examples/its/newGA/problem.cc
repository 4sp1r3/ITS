#include "problem.hh"

namespace newGA {

#define MAXDISTANCE 10000.0

Problem::Problem() {
	this->_numnodes = 0;
	this->_nodes = NULL;
	this->_signal = NULL;
	this->_maxx = -MAXDISTANCE;
	this->_maxy = -MAXDISTANCE;
	this->_minx = MAXDISTANCE;
	this->_miny = MAXDISTANCE;
}


istream& Problem::operator>>(istream& is) {
	is >> _numnodes;

    // read nodes
    _nodes = new Vec2[_numnodes];
    _signal = new Vec[_numnodes];

    for (int i = 0; i < _numnodes ; i++) {
        is >> _nodes[i][0];
        if (_nodes[i][0] > maxx) maxx = _nodes[i][0];
        if (_nodes[i][0] < minx) minx = _nodes[i][0];
        is >> _nodes[i][1];
        if (_nodes[i][1] > maxy) maxy = _nodes[i][1];
        if (_nodes[i][1] < miny) miny = _nodes[i][1];
        is >> _signal[i];
   }

    return is;
}


Problem & Problem::operator=(const Problem & pbm) {
    int n;
    _numvar = pbm.numvar();
    for (int i = 0; i < _numclause; i++)
        delete [] _clauses[i];
    delete [] _clauses;

    _numclause = pbm.numclause();
    n = _lenclause = pbm.lenclause();

    _clauses = new int *[_numclause];

    for (int i = 0; i < pbm._numclause; i++) {
        _clauses[i] = new int [n];
        for (int j = 0; j < n; j++)
            _clauses[i][j] = pbm._clauses[i][j];
    }
    return *this;
}

bool Problem::operator==(const Problem & pbm) const {
    if (_numvar != pbm.numvar()) return false;
    for (int i = 0; i < _numclause; i++)
        for (int j = 0; j < _lenclause; j++)
            if (_clauses[i][j] != pbm._clauses[i][j])
                return false;
    return true;
}

bool Problem::operator!=(const Problem & pbm) const {
    return !(*this == pbm);
}

Direction Problem::direction() const {
    //return maximize;
    return minimize;
}

int Problem::numvar() const {
    return _numvar;
}

int Problem::numclause() const {
    return _numclause;
}

int Problem::lenclause() const {
    return _lenclause;
}

int *Problem::clause(const int i) const {
    return _clauses[i];
}

Problem::~Problem() {
    for (int i = 0; i < _numclause; i++)
        delete [] _clauses[i];

    delete [] _clauses;
}

}
