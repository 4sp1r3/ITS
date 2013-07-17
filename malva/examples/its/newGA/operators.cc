#include "operators.hh"
#include "solution.hh"
#include "problem.hh"

#include <malva/mallba.hh>

namespace newGA {

    Intra_Operator::Intra_Operator(const unsigned int _number_op) :
    _number_operator(_number_op), probability(NULL) {
    }

    unsigned int Intra_Operator::number_operator() const {
        return _number_operator;
    }

    Intra_Operator * Intra_Operator::create(const unsigned int _number_op) {
        switch (_number_op) {
            case 0:
                return new Crossover;
                break;
            case 1:
                return new Mutation();
                break;
        }
    }

    ostream& operator<<(ostream& os, const Intra_Operator & intra) {
        switch (intra.number_operator()) {
            case 0:
                os << (Crossover&) intra;
                break;
            case 1:
                os << (Mutation&) intra;
                break;
        }
        return os;
    }

    Intra_Operator::~Intra_Operator() {
    }

    //  Crossover:Intra_operator -------------------------------------------------------------

    Crossover::Crossover() :
    Intra_Operator(0) {
        probability = new float[1];
    }

    void Crossover::cross(Solution& sol1, Solution & sol2) const // dadas dos soluciones de la poblacion, las cruza
    {
        Solution ret = Solution(sol1.pbm());
        ret._coord = (sol1._coord + sol2._coord) / 2.0;

        if (sol1.pbm().direction() == maximize) {
            if (sol1 > sol2) {
                if (ret > sol2) sol2 = ret;
            } else {
                if (ret > sol1) sol1 = ret;
            }
        } else {
            if (sol1 > sol2) {
                if (!(ret > sol1)) sol1 = ret;
            } else {
                if (!(ret > sol2)) sol2 = ret;
            }
        }

    }

    void Crossover::execute(Rarray<Solution*>& sols) const {
        for (int i = 0; i + 1 < sols.size(); i = i + 2)
            if (rand01() <= probability[0])
                cross(*sols[i], *sols[i + 1]);
    }

    ostream& operator<<(ostream& os, const Crossover & cross) {
        os << "Crossover." << " Probability: " << cross.probability[0] << endl;
        return os;
    }

    void Crossover::RefreshState(const StateCenter & _sc) const {
        _sc.set_contents_state_variable("_crossover_probability",
                (char *) probability, 1, sizeof (float));
    }

    void Crossover::UpdateFromState(const StateCenter & _sc) {
        unsigned long nbytes, length;
        _sc.get_contents_state_variable("_crossover_probability",
                (char *) probability, nbytes, length);
    }

    void Crossover::setup(char line[MAX_BUFFER]) {
        sscanf(line, " %*d %f ", &probability[0]);
        assert(probability[0] >= 0);
    }

    void Crossover::setup(double p){
    	probability[0] = p;
        assert(probability[0] >= 0);
    }

    Crossover::~Crossover() {
        delete[] probability;
    }

    //  Mutation: Sub_operator -------------------------------------------------------------

    Mutation::Mutation() :
    Intra_Operator(1) {
        probability = new float[1];
    }

#define MAX_MUTATION_XY      1.0
#define MAX_MUTATION_DECAY   0.1

    void Mutation::mutate(Solution & sol) const {
        //mutate (x,y)
        sol._coord[0] += ((rand01() * 2.0) - 1) * MAX_MUTATION_XY;
        sol._coord[1] += ((rand01() * 2.0) - 1) * MAX_MUTATION_XY;

        //mutate decays
        Problem& problem = (Problem&) sol.pbm();
        int num_nodes = problem.getNumNodes();
    }

    void Mutation::execute(Rarray<Solution*>& sols) const {
        for (int i = 0; i < sols.size(); i++)
            if (rand01() <= probability[0])
                mutate(*sols[i]);
    }

    ostream& operator<<(ostream& os, const Mutation & mutation) {
        os << "Mutation." << " Probability: " << mutation.probability[0] << endl;
        return os;
    }

    void Mutation::setup(char line[MAX_BUFFER]) {
        sscanf(line, " %*d %f ", &probability[0]);
        assert(probability[0] >= 0);
    }

    void Mutation::setup(double p){
        probability[0] = p;
        assert(probability[0] >= 0);
    }

    void Mutation::RefreshState(const StateCenter & _sc) const {
        _sc.set_contents_state_variable("_mutation_probability",
                (char *) probability, 2, sizeof (probability));
    }

    void Mutation::UpdateFromState(const StateCenter & _sc) {
        unsigned long nbytes, length;
        _sc.get_contents_state_variable("_mutation_probability",
                (char *) probability, nbytes, length);
    }

    Mutation::~Mutation() {
        delete[] probability;
    }

}
