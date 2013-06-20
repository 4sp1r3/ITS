#ifndef INC_newGA
#define INC_newGA
#include "newGAstructures.hh"

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

        int& var(const int index);
        Rarray<int>& array_var();

    private:
        Rarray<int> _var;
        const Problem& _pbm;
    };

}

#endif
