Solution::Solution(const Problem & pbm) : _pbm(pbm), _var(pbm.numvar()) {
}

const Problem & Solution::pbm() const {
    return _pbm;
}

Solution::Solution(const Solution & sol) : _pbm(sol.pbm()) {
    *this = sol;
}

istream& operator>>(istream& is, Solution & sol) {
    for (int i = 0; i < sol.pbm().numvar(); i++)
        is >> sol._var[i];
    return is;
}

ostream& operator<<(ostream& os, const Solution & sol) {
    for (int i = 0; i < sol.pbm().numvar(); i++)
        os << " " << sol._var[i];
    return os;
}

NetStream& operator <<(NetStream& ns, const Solution & sol) {
    for (int i = 0; i < sol._var.size(); i++)
        ns << sol._var[i];
    return ns;
}

NetStream& operator >>(NetStream& ns, Solution & sol) {
    for (int i = 0; i < sol._var.size(); i++)
        ns >> sol._var[i];
    return ns;
}

Solution & Solution::operator=(const Solution & sol) {
    _var = sol._var;
    return *this;
}

bool Solution::operator==(const Solution & sol) const {
    if (sol.pbm() != _pbm) return false;
    return true;
}

bool Solution::operator!=(const Solution & sol) const {
    return !(*this == sol);
}

void Solution::initialize() {
    for (int i = 0; i < _pbm.numvar(); i++)
        _var[i] = rand_int(0, 1);
}

double Solution::fitness() {
    double fitness = 0.0;
    int acum = 0;

    for (int i = 0; i < _pbm.numclause(); i++) {
        int *rl = _pbm.clause(i);
        acum = 0;
        for (int j = 0; (j < _pbm.lenclause()) && (acum != 1); j++) {
            if (((rl[j] < 0) && (_var[(int) abs(rl[j]) - 1] == 0))
                    || ((rl[j] > 0) && (_var[rl[j] - 1] == 1)))
                acum = 1;
        }
        fitness += acum;
    }
    return fitness;
}

char* Solution::to_String() const {
    return (char *) _var.get_first();
}

void Solution::to_Solution(char *_string_) {
    int *ptr = (int *) _string_;
    for (int i = 0; i < _pbm.numvar(); i++) {
        _var[i] = *ptr;
        ptr++;
    }
}

unsigned int Solution::size() const {
    return (_pbm.numvar() * sizeof (int));
}

int& Solution::var(const int index) {
    return _var[index];
}

Rarray<int>& Solution::array_var() {
    return _var;
}

Solution::~Solution() {
}