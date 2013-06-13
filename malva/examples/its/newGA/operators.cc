
Intra_Operator::Intra_Operator(const unsigned int _number_op) : _number_operator(_number_op), probability(NULL) {
}

unsigned int Intra_Operator::number_operator() const {
    return _number_operator;
}

Intra_Operator * Intra_Operator::create(const unsigned int _number_op) {
    switch (_number_op) {
        case 0: return new Crossover;
            break;
        case 1: return new Mutation();
            break;
    }
}

ostream& operator<<(ostream& os, const Intra_Operator & intra) {
    switch (intra.number_operator()) {
        case 0: os << (Crossover&) intra;
            break;
        case 1: os << (Mutation&) intra;
            break;
    }
    return os;
}

Intra_Operator::~Intra_Operator() {
}

//  Crossover:Intra_operator -------------------------------------------------------------

Crossover::Crossover() : Intra_Operator(0) {
    probability = new float[1];
}

void Crossover::cross(Solution& sol1, Solution & sol2) const // dadas dos soluciones de la poblacion, las cruza
{
    int i = 0;
    Rarray<int> aux(sol1.pbm().numvar());
    aux = sol2.array_var();

    int limit = rand_int((sol1.pbm().numvar() / 2) + 1, sol1.pbm().numvar() - 1);
    int limit2 = rand_int(0, limit - 1);

    for (i = 0; i < limit2; i++)
        sol2.var(i) = sol1.var(i);
    for (i = 0; i < limit2; i++)
        sol1.var(i) = aux[i];
    for (i = limit; i < sol1.pbm().numvar(); i++)
        sol2.var(i) = sol1.var(i);
    for (i = limit; i < sol1.pbm().numvar(); i++)
        sol1.var(i) = aux[i];
}

void Crossover::execute(Rarray<Solution*>& sols) const {
    for (int i = 0; i + 1 < sols.size(); i = i + 2)
        if (rand01() <= probability[0]) cross(*sols[i], *sols[i + 1]);
}

ostream& operator<<(ostream& os, const Crossover & cross) {
    os << "Crossover." << " Probability: "
            << cross.probability[0]
            << endl;
    return os;
}

void Crossover::RefreshState(const StateCenter & _sc) const {
    _sc.set_contents_state_variable("_crossover_probability", (char *) probability, 1, sizeof (float));
}

void Crossover::UpdateFromState(const StateCenter & _sc) {
    unsigned long nbytes, length;
    _sc.get_contents_state_variable("_crossover_probability", (char *) probability, nbytes, length);
}

void Crossover::setup(char line[MAX_BUFFER]) {
    int op;
    sscanf(line, " %d %f ", &op, &probability[0]);
    assert(probability[0] >= 0);
}

Crossover::~Crossover() {
    delete [] probability;
}

//  Mutation: Sub_operator -------------------------------------------------------------

Mutation::Mutation() : Intra_Operator(1) {
    probability = new float[2];
}

void Mutation::mutate(Solution & sol) const {
    for (int i = 0; i < sol.pbm().numvar(); i++) {
        if (rand01() <= probability[1]) {
            if (sol.var(i) == 1) sol.var(i) = 0;
            else sol.var(i) = 1;
        }
    }
}

void Mutation::execute(Rarray<Solution*>& sols) const {
    for (int i = 0; i < sols.size(); i++)
        if (rand01() <= probability[0]) mutate(*sols[i]);
}

ostream& operator<<(ostream& os, const Mutation & mutation) {
    os << "Mutation." << " Probability: " << mutation.probability[0]
            << " Probability1: " << mutation.probability[1]
            << endl;
    return os;
}

void Mutation::setup(char line[MAX_BUFFER]) {
    int op;
    sscanf(line, " %d %f %f ", &op, &probability[0], &probability[1]);
    assert(probability[0] >= 0);
    assert(probability[1] >= 0);
}

void Mutation::RefreshState(const StateCenter & _sc) const {
    _sc.set_contents_state_variable("_mutation_probability", (char *) probability, 2, sizeof (probability));
}

void Mutation::UpdateFromState(const StateCenter & _sc) {
    unsigned long nbytes, length;
    _sc.get_contents_state_variable("_mutation_probability", (char *) probability, nbytes, length);
}

Mutation::~Mutation() {
    delete [] probability;
}