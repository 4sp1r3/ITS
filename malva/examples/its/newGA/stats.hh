#ifndef STATS__HH
#define STATS__HH

#include "newGAstructures.hh"

namespace newGA {

    class Solver;

    struct user_stat {
        unsigned int trial;
        unsigned long nb_evaluation_best_found_trial;
        unsigned long nb_iteration_best_found_trial;
        double best_cost_trial;
        double worst_cost_trial;
        float time_best_found_trial;
        float time_spent_trial;
    };

    typedef user_stat s_user_stat;

    class UserStatistics {
        private:

            Rlist<struct user_stat> result_trials;

        public:
            UserStatistics();
            ~UserStatistics();

            friend ostream & operator<<(ostream& os, const UserStatistics& usertats);

            Rlist<struct user_stat> * getlist();

            UserStatistics & operator=(const UserStatistics& userstats);
            void update(const Solver& solver);
            void clear();
    };

    struct stat {
        unsigned int trial;
        unsigned long nb_generation;
        unsigned long nb_evaluation;
        double best_cost;
        double global_best_cost;
        double average_cost;
        double standard_deviation;
    };

    typedef struct stat s_stat;

    class Statistics {
    	public:

            Rlist<struct stat> stats_data;

        //public:
            Statistics();
            ~Statistics();

            friend ostream & operator<<(ostream& os, const Statistics& stats);

            Rlist<struct stat> * getlist();

            Statistics & operator=(const Statistics& stats);
            void update(const Solver& solver);
            void clear();
    };

}

#endif
