#include "stats.hh"
#include "solver.hh"
#include "stop.hh"
#include "setup.hh"

namespace newGA {

    UserStatistics::UserStatistics() {
    }

    ostream& operator<<(ostream& os, const UserStatistics & userstat) {
        os << "\n---------------------------------------------------------------" << endl;
        os << "                   STATISTICS OF TRIALS                   	 " << endl;
        os << "------------------------------------------------------------------" << endl;

        for (int i = 0; i < userstat.result_trials.size(); i++) {
            os << endl
                    << userstat.result_trials[i].trial
                    << "\t" << userstat.result_trials[i].best_cost_trial
                    << "\t\t" << userstat.result_trials[i].worst_cost_trial
                    << "\t\t\t" << userstat.result_trials[i].nb_evaluation_best_found_trial
                    << "\t\t\t" << userstat.result_trials[i].nb_iteration_best_found_trial
                    << "\t\t\t" << userstat.result_trials[i].time_best_found_trial
                    << "\t\t" << userstat.result_trials[i].time_spent_trial;
        }
        os << endl << "------------------------------------------------------------------" << endl;
        return os;
    }

    UserStatistics & UserStatistics::operator=(const UserStatistics & userstats) {
        result_trials = userstats.result_trials;
        return (*this);
    }

    Rlist<struct user_stat> * UserStatistics::getlist(){
    	return &this->result_trials;
    }

    void UserStatistics::update(const Solver & solver) {
        if ((solver.pid() != 0) || (solver.end_trial() != true)
                || ((solver.current_iteration() != solver.setup().nb_evolution_steps())
                && !terminateQ(solver.pbm(), solver, solver.setup())))
            return;


        struct user_stat *new_stat;

        if ((new_stat = (struct user_stat *) malloc(sizeof (struct user_stat))) == NULL)
            show_message(7);
        new_stat->trial = solver.current_trial();
        new_stat->nb_evaluation_best_found_trial = solver.evaluations_best_found_in_trial();
        new_stat->nb_iteration_best_found_trial = solver.iteration_best_found_in_trial();
        new_stat->worst_cost_trial = solver.worst_cost_trial();
        new_stat->best_cost_trial = solver.best_cost_trial();
        new_stat->time_best_found_trial = solver.time_best_found_trial();
        new_stat->time_spent_trial = solver.time_spent_trial();

        result_trials.append(*new_stat);
    }

    void UserStatistics::clear() {
        result_trials.remove();
    }

    UserStatistics::~UserStatistics() {
        result_trials.remove();
    }


    // Statistics ------------------------------------------------------

    Statistics::Statistics() {
    }

    ostream& operator<<(ostream& os, const Statistics& stats) {
        os << "\n---------------------------------------------------------------" << endl;
        os << "                   STATISTICS OF CURRENT TRIAL                   " << endl;
        os << "------------------------------------------------------------------" << endl;
        for (int i = 0; i < stats.stats_data.size(); i++) {
            os << endl
                    << " Trial:	" << stats.stats_data[i].trial
                    << " Generation: " << stats.stats_data[i].nb_generation
                    << " Evaluation: " << stats.stats_data[i].nb_evaluation
                    << " Current best cost: " << stats.stats_data[i].best_cost
                    << " Global best cost: " << stats.stats_data[i].global_best_cost
                    << " Avg: " << stats.stats_data[i].average_cost
                    << " Std. Dev.: " << stats.stats_data[i].standard_deviation;
        }

        os << endl << "------------------------------------------------------------------" << endl;
        return os;
    }

    Statistics& Statistics::operator=(const Statistics& stats) {
        stats_data = stats.stats_data;
        return *this;
    }

    Rlist<struct stat> * Statistics::getlist(){
    	return &this->stats_data;
    }

    void Statistics::update(const Solver& solver) {
        struct stat *new_stat = (struct stat *) malloc(sizeof (struct stat));

        new_stat->trial = solver.current_trial();
        new_stat->nb_generation = solver.current_iteration();
        new_stat->nb_evaluation = solver.current_evaluations();
        new_stat->average_cost = solver.current_average_cost();
        new_stat->standard_deviation = solver.current_standard_deviation();
        new_stat->best_cost = solver.current_best_cost();
        new_stat->global_best_cost = solver.global_best_cost();

        stats_data.append(*new_stat);
    }

    void Statistics::clear() {
        stats_data.remove();
    }

    Statistics::~Statistics() {
    }


}
