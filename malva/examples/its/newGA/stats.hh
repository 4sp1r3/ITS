#ifndef STATS__HH
#define STATS__HH

#include "newGAstructures.hh"

namespace newGA {

    class Solver;

    class UserStatistics {
        private:

            struct user_stat {
                unsigned int trial;
                unsigned long nb_evaluation_best_found_trial;
                unsigned long nb_iteration_best_found_trial;
                double best_cost_trial;
                double worst_cost_trial;
                float time_best_found_trial;
                float time_spent_trial;
            };

            Rlist<struct user_stat> result_trials;

        public:
            UserStatistics();
            ~UserStatistics();

            friend ostream & operator<<(ostream& os, const UserStatistics& usertats);

            UserStatistics & operator=(const UserStatistics& userstats);
            void update(const Solver& solver);
            void clear();
    };

    class Statistics {
        private:

            struct stat {
                unsigned int trial;
                unsigned long nb_generation;
                unsigned long nb_evaluation;
                double best_cost;
                double global_best_cost;
                double average_cost;
                double standard_deviation;
            };

            Rlist<struct stat> stats_data;

        public:
            Statistics();
            ~Statistics();

            friend ostream & operator<<(ostream& os, const Statistics& stats);

            Statistics & operator=(const Statistics& stats);
            void update(const Solver& solver);
            void clear();
    };

}

#endif
