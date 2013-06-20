Problem::Problem() : _numvar(0), _numclause(0), _clauses(NULL), _lenclause(0) {
}

ostream& operator<<(ostream& os, const Problem & pbm) {
    os << endl << endl << "Number of variables " << pbm._numvar
            << endl << endl << "Number of clauses " << pbm._numclause
            << endl << endl << "Length of clauses " << pbm._lenclause
            << endl << endl
            << " Clauses: " << endl;

    for (int i = 0; i < pbm._numclause; i++) {
        os << "\t clause " << i << "\t ";
        for (int j = 0; j < pbm._lenclause; j++)
            os << pbm._clauses[i][j] << " ";
        os << endl;
    }
    return os;
}

istream& operator>>(istream& is, Problem & pbm) {
    int l;
    int n;
    is >> pbm._numvar >> pbm._numclause >> pbm._lenclause;

    n = pbm._lenclause;
    // read clauses
    pbm._clauses = new int*[pbm._numclause];

    for (int i = 0; i < pbm._numclause; i++) {
        pbm._clauses[i] = new int[n];
        for (int j = 0; j < n; j++) {
            is >> l;
            pbm._clauses[i][j] = l;
        }
        is >> l;
    }

    return is;
}

Problem & Problem::operator=(const Problem & pbm) {
    int n;
    _numvar = pbm.numvar();
    for (int i = 0; i < _numclause; i++)
        delete [] _clauses[i];
    delete [] _clauses;

    _numclause = pbm.numclause();
    n = _lenclause = pbm.lenclause();

    _clauses = new int *[_numclause];

    for (int i = 0; i < pbm._numclause; i++) {
        _clauses[i] = new int [n];
        for (int j = 0; j < n; j++)
            _clauses[i][j] = pbm._clauses[i][j];
    }
    return *this;
}

bool Problem::operator==(const Problem & pbm) const {
    if (_numvar != pbm.numvar()) return false;
    for (int i = 0; i < _numclause; i++)
        for (int j = 0; j < _lenclause; j++)
            if (_clauses[i][j] != pbm._clauses[i][j])
                return false;
    return true;
}

bool Problem::operator!=(const Problem & pbm) const {
    return !(*this == pbm);
}

Direction Problem::direction() const {
    return maximize;
    //return minimize;
}

int Problem::numvar() const {
    return _numvar;
}

int Problem::numclause() const {
    return _numclause;
}

int Problem::lenclause() const {
    return _lenclause;
}

int *Problem::clause(const int i) const {
    return _clauses[i];
}

Problem::~Problem() {
    for (int i = 0; i < _numclause; i++)
        delete [] _clauses[i];

    delete [] _clauses;
}