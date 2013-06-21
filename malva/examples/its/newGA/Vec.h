/*
    File:           Vec.h

    Function:       Defines a generic resizeable vector.

    Author(s):      Andrew Willmott

    Copyright:      (c) 1995-2001, Andrew Willmott
 */

#ifndef __Vec__
#define __Vec__

class Vec2;
class Vec3;
class Vec4;

#define Assert


// --- Vec Class --------------------------------------------------------------

class Vec
{
public:

    // Constructors

                Vec();                          // Null vector
    explicit    Vec(int n);                     // n-element vector
                Vec(int n, double elt0, ...);   // e.g. Vec(3, 1.1, 2.0, 3.4)
                Vec(int n, double *data);         // Vector reference
                Vec(const Vec &v);              // Copy constructor
                Vec(const Vec2 &v);             // reference to a Vec2
                Vec(const Vec3 &v);             // reference to a Vec3
                Vec(const Vec4 &v);             // reference to a Vec4
               ~Vec();                          // Destructor

    // Accessor functions

    int         Elts() const;

    double        &operator [] (int i);
    double        operator [] (int i) const;

    void        SetSize(int n);                 // Resize the vector
    double        *Ref() const;                   // Return pointer to data

    // Assignment operators

    Vec         &operator =  (const Vec &v);    // v = a etc.

    // In-Place operators

    Vec         &operator += (const Vec &v);
    Vec         &operator -= (const Vec &v);
    Vec         &operator *= (const Vec &v);
    Vec         &operator *= (double s);
    Vec         &operator /= (const Vec &v);
    Vec         &operator /= (double s);

    //  Vector initialisers

    Vec         &MakeZero();


    Vec         &Normalise();                   // Normalise vector
    Vec         &Clamp(double fuzz);
    Vec         &Clamp();



    // Private...

protected:

    double        *data;
    unsigned int        elts;
};


// --- Vec Comparison Operators -----------------------------------------------

bool            operator == (const Vec &a, const Vec &b);
bool            operator != (const Vec &a, const Vec &b);


// --- Vec Arithmetic Operators -----------------------------------------------

Vec             operator + (const Vec &a, const Vec &b);
Vec             operator - (const Vec &a, const Vec &b);
Vec             operator - (const Vec &v);
Vec             operator * (const Vec &a, const Vec &b);
Vec             operator * (const Vec &v, double s);
Vec             operator / (const Vec &a, const Vec &b);
Vec             operator / (const Vec &v, double s);
Vec             operator * (double s, const Vec &v);

double            dot(const Vec &a, const Vec &b);// v . a
inline double     len(const Vec &v);              // || v ||
inline double     sqrlen(const Vec &v);           // v . v
inline Vec      norm(const Vec &v);             // v / || v ||
inline void     normalise(Vec &v);              // v = norm(v)

Vec             clamped(const Vec &v, double fuzz);
Vec             clamped(const Vec &v);


// --- Vec Input & Output -----------------------------------------------------

std::ostream         &operator << (std::ostream &s, const Vec &v);
std::istream         &operator >> (std::istream &s, Vec &v);


// --- Sub-vector functions ---------------------------------------------------

inline Vec      sub(const Vec &v, int start, int length);
inline Vec      first(const Vec &v, int length);
inline Vec      last(const Vec &v, int length);


// --- Vec inlines ------------------------------------------------------------

inline Vec::Vec() : data(0), elts(0)
{
}

inline Vec::Vec(int n) : elts(n)
{
    Assert(n > 0,"(Vec) illegal vector size");

    data = new double[n];
}

inline Vec::Vec(int n, double *data) : data(data), elts(n)
{
}

inline int Vec::Elts() const
{
    return(elts);
}

inline double &Vec::operator [] (int i)
{
 //   CheckRange(i, 0, Elts(), "Vec::[i]");

    return(data[i]);
}

inline double Vec::operator [] (int i) const
{
   // CheckRange(i, 0, Elts(), "Vec::[i]");

    return(data[i]);
}

inline double *Vec::Ref() const
{
    return(data);
}



inline double len(const Vec &v)
{
    return(sqrt(dot(v, v)));
}

inline double sqrlen(const Vec &v)
{
    return(dot(v, v));
}

inline Vec norm(const Vec &v)
{
    Assert(sqrlen(v) > 0.0, "normalising length-zero vector");
    return(v / len(v));
}

inline void normalise(Vec &v)
{
    v /= len(v);
}

inline Vec sub(const Vec &v, int start, int length)
{
    Assert(start >= 0 && length > 0 && start + length <= v.Elts(),
        "(sub(Vec)) illegal subset of vector");

    return(Vec(length, v.Ref() + start));
}

inline Vec first(const Vec &v, int length)
{
    Assert(length > 0 && length <= v.Elts(),
        "(first(Vec)) illegal subset of vector");

    return(Vec(length, v.Ref()));
}

inline Vec last(const Vec &v, int length)
{
    Assert(length > 0 && length <= v.Elts(),
        "(last(Vec)) illegal subset of vector");

    return(Vec(length, v.Ref() + v.Elts() - length));
}

inline Vec &Vec::Normalise()
{
    Assert(sqrlen(*this) > 0.0, "normalising length-zero vector");
    *this /= len(*this);
    return(*this);
}


#endif

