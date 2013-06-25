/*
    File:           Vec2.h
    Function:       Defines a length-2 vector.
    Author(s):      Andrew Willmott
    Copyright:      (c) 1995-2001, Andrew Willmott
 */

#ifndef __Vec2__
#define __Vec2__

#define Assert

// --- Vec2 Class -------------------------------------------------------------

class Vec2 {
public:

    // Constructors

    Vec2();
    Vec2(double x, double y); // (x, y)
    Vec2(const Vec2 &v); // Copy constructor

    // Accessor functions

    double &operator [] (int i);
    const double &operator [] (int i) const;

    int Elts() const {
        return (2);
    };
    double *Ref() const; // Return ptr to data

    // Assignment operators

    Vec2 &operator =(const Vec2 &a);

    Vec2 &operator +=(const Vec2 &a);
    Vec2 &operator -=(const Vec2 &a);
    Vec2 &operator *=(const Vec2 &a);
    Vec2 &operator *=(double s);
    Vec2 &operator /=(const Vec2 &a);
    Vec2 &operator /=(double s);

    // Comparison operators

    bool operator ==(const Vec2 &a) const; // v == a?
    bool operator !=(const Vec2 &a) const; // v != a?

    // Arithmetic operators

    Vec2 operator +(const Vec2 &a) const; // v + a
    Vec2 operator -(const Vec2 &a) const; // v - a
    Vec2 operator -() const; // -v
    Vec2 operator *(const Vec2 &a) const; // v * a (vx * ax, ...)
    Vec2 operator *(double s) const; // v * s
    Vec2 operator /(const Vec2 &a) const; // v / a (vx / ax, ...)
    Vec2 operator /(double s) const; // v / s

    // Initialisers

    Vec2 &MakeZero(); // Zero vector

    Vec2 &Normalise(); // normalise vector

    // Private...

protected:

    double elt[2];
};


// --- Vec operators ----------------------------------------------------------

inline Vec2 operator *(double s, const Vec2 &v); // s * v
inline double dot(const Vec2 &a, const Vec2 &b); // v . a
inline double len(const Vec2 &v); // || v ||
inline double sqrlen(const Vec2 &v); // v . v
inline Vec2 norm(const Vec2 &v); // v / || v ||
inline void normalise(Vec2 &v); // v = norm(v)
inline Vec2 cross(const Vec2 &v); // cross prod.

// --- Inlines ----------------------------------------------------------------

inline double &Vec2::operator [] (int i) {
    //CheckRange(i, 0, 2, "(Vec2::[i]) index out of range");
    return (elt[i]);
}

inline const double &Vec2::operator [] (int i) const {
    //CheckRange(i, 0, 2, "(Vec2::[i]) index out of range");
    return (elt[i]);
}

inline Vec2::Vec2() {
}

inline Vec2::Vec2(double x, double y) {
    elt[0] = x;
    elt[1] = y;
}

inline Vec2::Vec2(const Vec2 &v) {
    elt[0] = v[0];
    elt[1] = v[1];
}

inline double *Vec2::Ref() const {
    return ((double *) elt);
}

inline Vec2 &Vec2::operator =(const Vec2 &v) {
    elt[0] = v[0];
    elt[1] = v[1];

    return (*this);
}

inline Vec2 &Vec2::operator +=(const Vec2 &v) {
    elt[0] += v[0];
    elt[1] += v[1];

    return (*this);
}

inline Vec2 &Vec2::operator -=(const Vec2 &v) {
    elt[0] -= v[0];
    elt[1] -= v[1];

    return (*this);
}

inline Vec2 &Vec2::operator *=(const Vec2 &v) {
    elt[0] *= v[0];
    elt[1] *= v[1];

    return (*this);
}

inline Vec2 &Vec2::operator *=(double s) {
    elt[0] *= s;
    elt[1] *= s;

    return (*this);
}

inline Vec2 &Vec2::operator /=(const Vec2 &v) {
    elt[0] /= v[0];
    elt[1] /= v[1];

    return (*this);
}

inline Vec2 &Vec2::operator /=(double s) {
    elt[0] /= s;
    elt[1] /= s;

    return (*this);
}

inline Vec2 Vec2::operator +(const Vec2 &a) const {
    Vec2 result;

    result[0] = elt[0] + a[0];
    result[1] = elt[1] + a[1];

    return (result);
}

inline Vec2 Vec2::operator -(const Vec2 &a) const {
    Vec2 result;

    result[0] = elt[0] - a[0];
    result[1] = elt[1] - a[1];

    return (result);
}

inline Vec2 Vec2::operator -() const {
    Vec2 result;

    result[0] = -elt[0];
    result[1] = -elt[1];

    return (result);
}

inline Vec2 Vec2::operator *(const Vec2 &a) const {
    Vec2 result;

    result[0] = elt[0] * a[0];
    result[1] = elt[1] * a[1];

    return (result);
}

inline Vec2 Vec2::operator *(double s) const {
    Vec2 result;

    result[0] = elt[0] * s;
    result[1] = elt[1] * s;

    return (result);
}

inline Vec2 operator *(double s, const Vec2 &v) {
    return (v * s);
}

inline Vec2 Vec2::operator /(const Vec2 &a) const {
    Vec2 result;

    result[0] = elt[0] / a[0];
    result[1] = elt[1] / a[1];

    return (result);
}

inline Vec2 Vec2::operator /(double s) const {
    Vec2 result;

    result[0] = elt[0] / s;
    result[1] = elt[1] / s;

    return (result);
}

inline double dot(const Vec2 &a, const Vec2 &b) {
    return (a[0] * b[0] + a[1] * b[1]);
}

inline Vec2 cross(const Vec2 &a) {
    Vec2 result;

    result[0] = a[1];
    result[1] = -a[0];

    return (result);
}

inline double len(const Vec2 &v) {
    return (sqrt(dot(v, v)));
}

inline double sqrlen(const Vec2 &v) {
    return (dot(v, v));
}

inline Vec2 norm(const Vec2 &v) {
    Assert(sqrlen(v) > 0.0, "normalising length-zero vector");
    return (v / len(v));
}

inline void normalise(Vec2 &v) {
    v /= len(v);
}

inline Vec2 &Vec2::Normalise() {
    Assert(sqrlen(*this) > 0.0, "normalising length-zero vector");
    *this /= len(*this);
    return (*this);
}

inline bool Vec2::operator ==(const Vec2 &a) const {
    return (elt[0] == a[0] && elt[1] == a[1]);
}

inline bool Vec2::operator !=(const Vec2 &a) const {
    return (elt[0] != a[0] || elt[1] != a[1]);
}

#endif
