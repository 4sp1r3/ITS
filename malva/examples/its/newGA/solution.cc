#include "solution.hh"
#include "problem.hh"

#include <malva/random.hh>

namespace newGA {

#define MAXDECAY 0.5
#define MINDECAY -0.1

    Solution::Solution(const Problem & pbm) :
    _pbm(pbm),
    _decay(pbm._numnodes),
    _coord(((pbm._maxx - pbm._minx) * rand01()) - pbm._minx,
    ((pbm._maxy - pbm._miny) * rand01()) - pbm._miny) {

        for (int i = 0; i < pbm._numnodes; i++) {
            _decay[i] = (rand01() * (MAXDECAY - MINDECAY)) + MINDECAY;
        }

    }

    const Problem & Solution::pbm() const {
        return _pbm;
    }

    Solution::Solution(const Solution & sol) :
    _pbm(sol.pbm()) {
        *this = sol;
    }

    istream& operator>>(istream& is, Solution & sol) {
        /*
        for (int i = 0; i < sol.pbm().numvar(); i++)
            is >> sol._var[i];
        */
        return is;
    }

    ostream& operator<<(ostream& os, const Solution & sol) {
        /*
        for (int i = 0; i < sol.pbm().numvar(); i++)
            os << " " << sol._var[i];
        */
        return os;
    }

    NetStream& operator <<(NetStream& ns, const Solution & sol) {
        /*
        for (int i = 0; i < sol._var.size(); i++)
            ns << sol._var[i];
        */
        return ns;
    }

    NetStream& operator >>(NetStream& ns, Solution & sol) {
        /*
        for (int i = 0; i < sol._var.size(); i++)
            ns >> sol._var[i];
        */
        return ns;
    }

    Solution & Solution::operator=(const Solution & sol) {
        _coord = sol._coord;
        _decay = sol._decay;
        return *this;
    }

    bool Solution::operator==(const Solution & sol) const {
        if (sol.pbm() != _pbm)
            return false;
        return true;
    }

    bool Solution::operator!=(const Solution & sol) const {
        return !(*this == sol);
    }

    void Solution::initialize() {
        _coord[0] = (_pbm._maxx - _pbm._minx) * rand01() - _pbm._minx;
        _coord[1] = (_pbm._maxy - _pbm._miny) * rand01() - _pbm._miny;
        for (int i = 0; i < _pbm._numnodes; i++) {
            _decay[i] = (rand01() * (MAXDECAY - MINDECAY)) + MINDECAY;
        }
    }

    bool Solution::operator>(const Solution & sol) const {
        Solution & solution = (Solution&) sol;
        return fitness() > solution.fitness();
    }

    double Solution::fitness() const {
        double fitness = 0.0;
        for (int i = 0; i < _pbm._numnodes; i++) {
            fitness += len(_pbm._nodes[i] - _coord) - _pbm.getPercibedDistance(_pbm._signal[i]*(1 - _decay[i]));
        }
        return fitness;
    }

    char* Solution::to_String() const {
        double * values = new double[2+_pbm._numnodes];

        values[0] = _coord[0];
        values[1] = _coord[1];

        for (int i = 0; i < _pbm._numnodes; i++) {
            values[i+2] = _decay[i];
        }

        return (char*) values;
    }

    void Solution::to_Solution(char * string) {
        double * values = (double *) string;

        _coord[0] = values[0];
        _coord[1] = values[1];

        for (int i = 0; i < _pbm._numnodes; i++) {
            _decay[i] = values[i+2];
        }
    }

    unsigned int Solution::size() const {
        return (2+_decay.Elts())*sizeof(double);
    }

    Solution::~Solution() {
    }

}
