#ifndef SOLVER__HH
#define SOLVER__HH
#include "newGAstructures.hh"
#include "stats.hh"

skeleton newGA
{
	// Si se definen más de 5 nuevos operadores por parte del usuario, se debe cambiar esta constante.
	#define MAX_OP_USER 5

    provides class Solver {
    protected:
        const Problem& problem;
        const SetUpParams& params;
        UserStatistics _userstat;
        Statistics _stat;
        Population current_population;
        StateCenter _sc;

        double best_cost;
        double worst_cost;
        Solution best_solution;
        double average_cost;
        double standard_deviation;
        float total_time_spent;
        float time_spent_in_trial;
        float start_trial;
        float start_global;

        bool _end_trial;

        State_Vble _current_trial;
        State_Vble _current_iteration;
        State_Vble _current_evaluations;

        State_Vble _current_best_solution;
        State_Vble _current_best_cost;
        State_Vble _current_worst_cost;
        State_Vble _current_average_cost;
        State_Vble _current_standard_deviation;
        State_Vble _current_time_spent;

        State_Vble _best_solution_trial;
        State_Vble _best_cost_trial;
        State_Vble _worst_cost_trial;
        State_Vble _iteration_best_found_in_trial;
        State_Vble _evaluations_best_found_in_trial;
        State_Vble _time_best_found_trial;
        State_Vble _time_spent_trial;

        State_Vble _trial_best_found;
        State_Vble _iteration_best_found;
        State_Vble _evaluations_best_found;
        State_Vble _global_best_solution;
        State_Vble _global_best_cost;
        State_Vble _global_worst_cost;
        State_Vble _time_best_found;

        State_Vble _crossover_probability; // probability of applying the operator over population
        State_Vble _mutation_probability; // probability of applying the operator over population
        State_Vble _user_op_probability[MAX_OP_USER]; // probabilities of user operators
        State_Vble _migration_rate;
        State_Vble _migration_size;
        State_Vble _migration_selection_1;
        State_Vble _migration_selection_2;
        State_Vble _migration_selection_conf_1;
        State_Vble _migration_selection_conf_2;
        State_Vble _select_parents;
        State_Vble _select_offsprings;
        State_Vble _parameter_select_parents;
        State_Vble _parameter_select_offsprings;

        State_Vble _display_state;


    public:
        Solver(const Problem& pbm, const SetUpParams& setup);
        virtual ~Solver();

        virtual int pid() const;
        bool end_trial() const;
        void end_trial(bool et);

        // Execution methods -----------------------------------------------------------------------

        // Full execution
        virtual void run() = 0;
        virtual void run(const unsigned long int nb_generations) = 0;
        virtual void run(const Population& pop, const unsigned long int nb_generations) = 0;

        //Partial execution
        virtual void StartUp() = 0;
        virtual void StartUp(const Population& pop) = 0;

        virtual void DoStep() = 0;

        // Statistics handling ----------------------------------------------------------------------

        Statistics& statistics();
        UserStatistics& userstatistics();
        Population& population();
        const SetUpParams& setup() const;
        const Problem& pbm() const;

        // State handling ---------------------------------------------------------------------------

        void RefreshState();
        void RefreshCfgState();
        void UpdateFromState();
        void UpdateFromCfgState();
        StateCenter* GetState();

        unsigned int current_trial() const;
        unsigned long current_iteration() const;
        unsigned long current_evaluations() const;
        Solution current_best_solution() const;
        double current_best_cost() const;
        double current_worst_cost() const;
        double current_average_cost() const;
        double current_standard_deviation() const;
        float current_time_spent() const;
        Solution best_solution_trial() const;
        double best_cost_trial() const;
        double worst_cost_trial() const;
        unsigned int iteration_best_found_in_trial() const;
        unsigned int evaluations_best_found_in_trial() const;
        float time_best_found_trial() const;
        float time_spent_trial() const;
        unsigned int trial_best_found() const;
        unsigned int iteration_best_found() const;
        unsigned int evaluations_best_found() const;
        Solution global_best_solution() const;
        double global_best_cost() const;
        double global_worst_cost() const;
        float time_best_found() const;
        int display_state() const;

        float *crossover_probability() const;
        float *mutation_probability() const;
        float *user_op_probability(const int index) const;
        unsigned int migration_rate() const;
        unsigned int migration_size() const;
        unsigned int migration_selection_1() const;
        unsigned int migration_selection_2() const;
        unsigned int migration_selection_conf_1() const;
        unsigned int migration_selection_conf_2() const;
        unsigned int select_parents() const;
        unsigned int select_offprings() const;
        unsigned int parameter_select_parents() const;
        unsigned int parameter_select_offsprings() const;

        void current_trial(const unsigned int value);
        void current_iteration(const unsigned long value);
        void current_evaluations(const unsigned long value);
        void current_best_solution(const Solution& sol);
        void current_best_cost(const double value);
        void current_worst_cost(const double value);
        void current_average_cost(const double value);
        void current_standard_deviation(const double value);
        void current_time_spent(const float value);
        void best_solution_trial(const Solution& sol);
        void best_cost_trial(const double value);
        void worst_cost_trial(const double value);
        void iteration_best_found_in_trial(const unsigned int value);
        void evaluations_best_found_in_trial(const unsigned int value);
        void time_best_found_trial(const float value);
        void time_spent_trial(const float value);
        void trial_best_found(const unsigned int value);
        void iteration_best_found(const unsigned int value);
        void evaluations_best_found(const unsigned int value);
        void global_best_solution(const Solution& sol);
        void global_best_cost(const double value);
        void global_worst_cost(const double value);
        void time_best_found(const float value);
        void display_state(const int value);

        void crossover_probability(const float *probability);
        void mutation_probability(const float *probability);
        void user_op_probability(const int index, const float *probability);
        void migration_rate(const unsigned int rate);
        void migration_size(const unsigned int size);
        void migration_selection_1(const unsigned int seleciton_1);
        void migration_selection_2(const unsigned int selection_2);
        void migration_selection_conf_1(const unsigned int selection_conf_1);
        void migration_selection_conf_2(const unsigned int selection_conf_2);
        void select_parents(const unsigned int selection);
        void select_offsprings(const unsigned int selection);
        void parameter_select_parents(const unsigned int value);
        void parameter_select_offsprings(const unsigned int value);

        void show_state() const;
        void KeepHistory(const Solution& best_sol, const double best_cost, const double worst_cost, const float time_spent_trial, const float total_time_spent);
    };

    provides class Solver_Seq : public Solver {
    public:
        Solver_Seq(const Problem& pbm, const SetUpParams& setup);
        virtual ~Solver_Seq();

        // Execution methods -----------------------------------------------------------------------

        // Full execution
        virtual void run();
        virtual void run(const unsigned long int nb_generations);
        virtual void run(const Population& pop, const unsigned long int nb_generations);

        //Partial execution
        virtual void StartUp();
        virtual void StartUp(const Population& pop);

        virtual void DoStep();
    };

    provides class Solver_Lan : public Solver {
    private:
        NetStream _netstream;
        int mypid;

        int receive_local_state();

        unsigned int _current_trial;
        unsigned long _current_iteration;
        unsigned long _current_evaluations;
        double _best_cost_trial;
        Solution _best_solution_trial;
        double _worst_cost_trial;
        float _time_best_found_in_trial;
        unsigned long _iteration_best_found_in_trial;
        unsigned long _evaluations_best_found_in_trial;

        // Termination phase //
        bool final_phase;
        int acum_evaluations;
        int acum_iterations;

    public:
        Solver_Lan(const Problem& pbm, const SetUpParams& setup, int argc, char **argv);
        virtual ~Solver_Lan();
        virtual int pid() const;
        NetStream& netstream();

        // Execution methods -----------------------------------------------------------------------

        // Full execution
        virtual void run();
        virtual void run(const unsigned long int nb_generations);
        virtual void run(const Population& pop, const unsigned long int nb_generations);

        //Partial execution
        virtual void StartUp();
        virtual void StartUp(const Population& pop);

        virtual void DoStep();

        //Communication
        void send_local_state_to(int _mypid);
        void check_for_refresh_global_state();
        void reset();
    };

    provides class Solver_Wan : public Solver {
    private:
        NetStream _netstream;
        int mypid;

        int receive_local_state();

        unsigned int _current_trial;
        unsigned long _current_iteration;
        unsigned long _current_evaluations;
        double _best_cost_trial;
        Solution _best_solution_trial;
        double _worst_cost_trial;
        float _time_best_found_in_trial;
        unsigned long _iteration_best_found_in_trial;
        unsigned long _evaluations_best_found_in_trial;
        unsigned long __best_found_in_trial;

        // Termination phase //
        bool final_phase;
        int acum_evaluations;
        int acum_iterations;

    public:
        Solver_Wan(const Problem& pbm, const SetUpParams& setup, int argc, char **argv);
        virtual ~Solver_Wan();
        virtual int pid() const;
        NetStream& netstream();

        // Execution methods -----------------------------------------------------------------------

        // Full execution
        virtual void run();
        virtual void run(const unsigned long int nb_generations);
        virtual void run(const Population& pop, const unsigned long int nb_generations);

        //Partial execution
        virtual void StartUp();
        virtual void StartUp(const Population& pop);

        virtual void DoStep();

        //Communication
        void send_local_state_to(int _mypid);
        void check_for_refresh_global_state();
        void reset();
    };

}

#endif
