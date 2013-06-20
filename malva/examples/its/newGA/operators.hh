#ifndef INC_newGA
#define INC_newGA
#include "newGAstructures.hh"

skeleton newGA
{

    requires class Intra_Operator {
    protected:
        unsigned int _number_operator;
        float *probability;

    public:
        Intra_Operator(const unsigned int _number_op);
        virtual ~Intra_Operator();

        static Intra_Operator *create(const unsigned int _number_op);
        friend ostream & operator<<(ostream& os, const Intra_Operator& intra);

        virtual void execute(Rarray<Solution*>& sols) const = 0;
        virtual void setup(char line[MAX_BUFFER]) = 0;
        unsigned int number_operator() const;

        virtual void RefreshState(const StateCenter& _sc) const = 0;
        virtual void UpdateFromState(const StateCenter& _sc) = 0;
    };

    // Crossover  ----------------------------------------------------------------------------------

    requires class Crossover : public Intra_Operator {
    public:
        Crossover();
        virtual ~Crossover();

        friend ostream & operator <<(ostream& os, const Crossover& cross);

        void cross(Solution &sol1, Solution &sol2) const;
        virtual void execute(Rarray<Solution*>& sols) const;
        virtual void setup(char line[MAX_BUFFER]);

        virtual void RefreshState(const StateCenter& _sc) const;
        virtual void UpdateFromState(const StateCenter& _sc);
    };

    // Mutation ----------------------------------------------------------------------------------

    requires class Mutation : public Intra_Operator {
    public:
        Mutation();
        virtual ~Mutation();

        friend ostream & operator<<(ostream& os, const Mutation& mutation);

        void mutate(Solution& sol) const;
        // applies mutation over all solutions in array sols
        virtual void execute(Rarray<Solution*>& sols) const;
        virtual void setup(char line[MAX_BUFFER]);

        virtual void RefreshState(const StateCenter& _sc) const;
        virtual void UpdateFromState(const StateCenter& _sc);

    };

}

#endif
