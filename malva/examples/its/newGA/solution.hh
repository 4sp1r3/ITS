#ifndef SOLUTION__HH
#define SOLUTION__HH

#include "newGAstructures.hh"
#include "problem.hh"
#include "Vec2.h"


skeleton newGA
{

    requires class Solution {
    public:
        Solution(const Problem& pbm);
        Solution(const Solution& sol);
        ~Solution();

        friend ostream & operator<<(ostream& os, const Solution& sol);
        friend istream & operator>>(istream& is, Solution& sol);
        friend NetStream & operator <<(NetStream& ns, const Solution& sol);
        friend NetStream & operator >>(NetStream& ns, Solution& sol);

        const Problem& pbm() const;

        Solution & operator=(const Solution& sol);
        bool operator==(const Solution& sol) const;
        bool operator!=(const Solution& sol) const;

        char *to_String() const;
        void to_Solution(char *_cadena_);

        void initialize();
        double fitness();
        unsigned int size() const;

        inline Vec2 & getCoord() { return _coord; };
        inline Vec & getDecay() { return _decay; };

 //   private:
        Vec2 _coord;
        Vec _decay;
        const Problem& _pbm;

    };

}

#endif
