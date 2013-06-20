#ifndef INC_newGA
#define INC_newGA
#include "newGAstructures.hh"

skeleton newGA
{

    requires class Problem {
    public:
        Problem();
        ~Problem();

        friend ostream & operator<<(ostream& os, const Problem& pbm);
        friend istream & operator>>(istream& is, Problem& pbm);

        Problem & operator=(const Problem& pbm);
        bool operator==(const Problem& pbm) const;
        bool operator!=(const Problem& pbm) const;

        Direction direction() const;

        int numvar() const;
        int numclause() const;
        int lenclause() const;
        int *clause(const int i) const;

    private:
        int _numvar;
        int _numclause;
        int _lenclause;
        int ** _clauses;
    };

}

#endif
