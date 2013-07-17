#include "problem.hh"
#include <math.h>

namespace newGA {

// CONSTANTS

#define MAXDISTANCE 30.0

double GHZ = 1000000000;
double mwatts = 0.001;
double speedoflight = 299792458.0;

double frec = 2.442 * GHZ;
double lambda = speedoflight / frec;

double Gt = 5.0; //Ganancia estandar de antenas wifi
double Gr = 5.0; //Ganancia estandar de antenas wifi

double dbm_trans = 20.0; // dbm de transmicion de los routers


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

    /* Dada una dbm te devuelve la potencia en miliwats*/
    double dbm2pot(double dbm){
    	double P0 = 1 * mwatts;

    	double P1 = pow(10 , (dbm / 10.0)) * P0;
    	return P1;
    }

    double pot2dbm(double pot){
    	return 10.0 * (log(pot/ (1 * mwatts)) / log(10.0));
    }

    double Problem::getPercibedDistance(double signal) const {

        double dbm_r = signal;
        double dbm_t = dbm_trans;

        double Pt = dbm2pot(dbm_t);
        double Pr = dbm2pot(dbm_r);

        // Pr = (Gt * Gr * (lambda)^2 * Pt) / (4 * PI * dist)^2
        double dist2 = (Gt * Gr * pow(lambda,2) * Pt) / ( Pr * 16 * pow(M_PI,2) );
        return sqrt(dist2);
    }

    double Problem::getPercibedSignal(const double dist) const {
        double dbm_t = dbm_trans;
        double Pt = dbm2pot(dbm_t);

    	// Pr = (Gt * Gr * (lambda)^2 * Pt) / (4 * PI * dist)^2
    	double Pr = (Gt * Gr * pow(lambda,2) * Pt) / pow(4 * M_PI * dist, 2);
    	return pot2dbm(Pr);
    }

    Problem::~Problem() {
        delete [] _nodes;
    }

}
