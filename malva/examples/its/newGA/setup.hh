#ifndef SETUP__H
#define SETUP__H
#include "newGAstructures.hh"
#include "operators.hh"

namespace newGA
{

    provides class SetUpParams {
    private:
        unsigned int _independent_runs;
        unsigned long _nb_evolution_steps;
        unsigned int _population_size; // number of individuals
        unsigned int _population_additional_size; // size of offspring in each generation
        bool _combine; // combines parents and offsprings to select new parents ?
        bool _display_state;

        unsigned long _refresh_global_state;
        bool _synchronized;
        unsigned int _check_asynchronous;

        // selection of parents and offsprings
        mutable unsigned int _select_parents;
        mutable unsigned int _select_offsprings;
        mutable unsigned int _parameter_select_parents;
        mutable unsigned int _parameter_select_offsprings;

        Rlist<unsigned int> _intra_operators;
        Rlist<unsigned int> _inter_operators;

        Operator_Pool& _pool;

    public:
        SetUpParams(Operator_Pool& pool);
        Operator_Pool& pool() const;

        friend ostream & operator<<(ostream& os, const SetUpParams& setup);
        friend istream & operator>>(istream& is, SetUpParams& setup);

        const unsigned int independent_runs() const;
        const unsigned long nb_evolution_steps() const;
        const unsigned int population_size() const;
        const unsigned int population_additional_size() const;
        const bool combine() const;
        const bool display_state() const;
        const unsigned long refresh_global_state() const;
        const bool synchronized() const;
        const unsigned int check_asynchronous() const;

        void independent_runs(const unsigned int val);
        void nb_evolution_steps(const unsigned long val);
        void population_size(const unsigned int val);
        void population_additional_size(const unsigned int val);
        void combine(const bool val);
        void display_state(const bool val);
        void refresh_global_state(const unsigned long val);
        void synchronized(const bool val);
        void check_asynchronous(const unsigned int val);

        // gets the i-th operator of inter-population
        const unsigned int inter_operator_index(const unsigned int index) const;
        const unsigned int inter_operators_size() const;

        // gets the i-th operator of intra-population
        const unsigned int intra_operator_index(const unsigned int index) const;
        const unsigned int intra_operators_size() const;

        const unsigned int select_parents() const;
        const unsigned int select_offsprings() const;
        const unsigned int parameter_select_parents() const;
        const unsigned int parameter_select_offsprings() const;

        void select_parents(const unsigned int val);
        void select_offsprings(const unsigned int val);
        void parameter_select_parents(const unsigned int val);
        void parameter_select_offsprings(const unsigned int val);

        void RefreshState(const StateCenter& _sc) const;
        void UpdateFromState(const StateCenter& _sc) const;

        ~SetUpParams();
    };

}

#endif
