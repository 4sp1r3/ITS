#include "solution.hh"
#include "problem.hh"

#include <malva/random.hh>

namespace newGA {

#define MAXDECAY 0.5
#define MINDECAY 0.0
#define SIMILARS 0.1

    Solution::Solution(const Problem & pbm) :
    _pbm(pbm),
    _coord(((pbm._maxx - pbm._minx) * rand01()) + pbm._minx,
    ((pbm._maxy - pbm._miny) * rand01()) + pbm._miny) {
    }

    const Problem & Solution::pbm() const {
        return _pbm;
    }

    Solution::Solution(const Solution & sol) :
    _pbm(sol.pbm()) {
        *this = sol;
    }

    double Solution::getpersivedDecay(int nodo) const{
    	double SigEsperada = pbm().getPercibedSignal( len(this->_coord - this->_pbm._nodes[nodo]) ) ;
    	double SigReal = pbm()._signal[nodo];
    	return SigEsperada - SigReal ;
    }

    istream& operator>>(istream& is, Solution & sol) {
        /*
        for (int i = 0; i < sol.pbm().numvar(); i++)
            is >> sol._var[i];
        */
        return is;
    }

    ostream& operator<<(ostream& os, const Solution & sol) {
    	os << "(" << sol._coord[0] << "," << sol._coord[1] << ")";

        for (int i = 0 ; i < sol._pbm._numnodes; i++)
            os << " " << sol.getpersivedDecay(i);

        os << endl;
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
        return *this;
    }

    bool Solution::operator==(const Solution & sol) const {
    	if (sol.pbm() != _pbm)
            return false;
    	if (len(sol._coord - this->_coord) < SIMILARS) return true;
        return false;
    }

    bool Solution::operator!=(const Solution & sol) const {
        return !(*this == sol);
    }

    void Solution::initialize() {
        _coord[0] = (_pbm._maxx - _pbm._minx) * rand01() + _pbm._minx;
        _coord[1] = (_pbm._maxy - _pbm._miny) * rand01() + _pbm._miny;
    }

    bool Solution::operator>(const Solution & sol) const {
        Solution & solution = (Solution&) sol;
        return fitness() > solution.fitness();
    }

    double Solution::fitness() const {
        double fitness = 0.0;
        for (int i = 0; i < _pbm._numnodes; i++) {
            fitness += pow(len(_pbm._nodes[i] - _coord) - _pbm.getPercibedDistance(_pbm._signal[i]) ,2);
        }
        return fitness;
    }

    char* Solution::to_String() const {
        double * values = new double[2+_pbm._numnodes];

        values[0] = _coord[0];
        values[1] = _coord[1];

        return (char*) values;
    }

    void Solution::to_Solution(char * string) {
        double * values = (double *) string;

        _coord[0] = values[0];
        _coord[1] = values[1];

    }

    unsigned int Solution::size() const {
        return sizeof(double) * 2;
    }

    Solution::~Solution() {
    }

}
