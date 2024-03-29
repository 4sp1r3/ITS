#ifndef SOLUTION__HH
#define SOLUTION__HH

#include "newGAstructures.hh"
#include "Vec2.h"
#include "Vec.h"

namespace newGA {

    class Problem;

    class Solution {
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
        bool operator>(const Solution & sol) const;

        char *to_String() const;
        void to_Solution(char * string);

        void initialize();
        double fitness() const;
        unsigned int size() const;
        double getpersivedDecay(int nodo) const;

        Vec2 _coord;
        const Problem& _pbm;

    };

}

#endif
