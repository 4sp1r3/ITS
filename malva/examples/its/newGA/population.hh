#ifndef INC_newGA
#define INC_newGA
#include "newGAstructures.hh"

skeleton newGA
{

    provides class Population {
    private:
        Rarray<Solution*> _parents; // individuals in population
        Rarray<Solution*> _offsprings; // offsprings of current population
        Rarray<Solution*> _new_parents; // individuals of previous population
        Rarray<struct individual> _fitness_values;
        Rarray<struct individual> _fitness_aux;
        const SetUpParams& _setup;
        unsigned int _upper_cost, _lower_cost; // lower and upper fitness of individuals in population
        unsigned long _evaluations;
        double _average_cost;

    public:
        inline void Evaluate(Solution *sol, struct individual & _f);

        Population(const Problem& pbm, const SetUpParams& setup); // crea un array de objetos population;
        ~Population();

        friend ostream & operator<<(ostream& os, const Population& population);
        friend istream & operator>>(istream& is, Population& population);
        Population & operator=(const Population& pop);
        const SetUpParams& setup() const;
        void initialize();

        // Generate a new pool of individuals in population
        void evolution();

        // interchange solutions between island
        void interchange(const unsigned long current_generation, NetStream& channel);

        // creates a array with fitness of all individuals in population and its position in the population
        void evaluate_parents();

        // creates a array with fitness of all individuals and offsprings in population and its position in the population
        void evaluate_offsprings();

        // selects parents to creates offsprings
        void select_parents();

        // selects individuals for the new population
        void select_offsprings();

        const Rarray<Solution*>& parents() const;
        const Rarray<Solution*>& offsprings() const;
        Rarray<struct individual>& fitness_values();

        unsigned int upper_cost() const;
        unsigned int lower_cost() const;
        unsigned int evaluations() const;
        Solution& solution(const unsigned int index) const;
        double fitness(const unsigned int index) const;

        double best_cost() const;
        double worst_cost() const;
        Solution& best_solution() const;
        Solution& worst_solution() const;
        double average_cost() const;
        double standard_deviation() const;
    };

}

#endif
