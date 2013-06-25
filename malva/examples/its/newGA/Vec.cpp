/*
    File:           Vec.cpp
    Function:       Implements Vec.h
    Author(s):      Andrew Willmott
    Copyright:      (c) 1995-2001, Andrew Willmott
 */

#include "Vec.h"
#include "Vec2.h"

#include <cctype>
#include <cstring>
#include <cstdarg>
#include <iomanip>

// --- Vec Constructors -------------------------------------------------------

Vec::Vec(const Vec &v) {
    Assert(v.data != 0, "(Vec) Can't construct from a null vector");

    elts = v.Elts();
    data = new double[elts];

#ifdef VL_USE_MEMCPY
    memcpy(data, v.Ref(), sizeof (double) * Elts());
#else
    for (int i = 0; i < Elts(); i++)
        data[i] = v[i];
#endif
}

Vec::Vec(const Vec2 &v) : data(v.Ref()), elts(v.Elts()) {
}

Vec::~Vec() {
    if (!IsRef())
        delete[] data;
}

// --- Vec Assignment Operators -----------------------------------------------

Vec &Vec::operator =(const Vec &v) {
    if (!IsRef())
        SetSize(v.Elts());
    else
        Assert(Elts() == v.Elts(), "(Vec::=) Vector sizes don't match");

#ifdef VL_USE_MEMCPY
    memcpy(data, v.data, sizeof (double) * Elts());
#else
    for (int i = 0; i < Elts(); i++)
        data[i] = v[i];
#endif

    return (*this);
}

Vec &Vec::operator =(const Vec2 &v) {
    if (!IsRef())
        SetSize(v.Elts());
    else
        Assert(Elts() == v.Elts(), "(Vec::=) Vector sizes don't match");

    data[0] = v[0];
    data[1] = v[1];

    return (*this);
}

void Vec::SetSize(int ni) {
    Assert(ni > 0, "(Vec::SetSize) Illegal vector size");
    unsigned int n = (unsigned int) ni;

    if (!IsRef()) {
        // Don't doublelocate if we already have enough storage

        if (n <= elts) {
            elts = n;
            return;
        }

        // Otherwise, delete old storage

        delete[] data;

        elts = n;
        data = new double[elts];
    } else
        Assert(false, "(Vec::SetSize) Can't resize a vector reference");
}

// --- Vec In-Place operators -------------------------------------------------

Vec &Vec::operator +=(const Vec &b) {
    Assert(Elts() == b.Elts(), "(Vec::+=) vector sizes don't match");

    int i;

    for (i = 0; i < Elts(); i++)
        data[i] += b[i];

    return (*this);
}

Vec &Vec::operator -=(const Vec &b) {
    Assert(Elts() == b.Elts(), "(Vec::-=) vector sizes don't match");

    int i;

    for (i = 0; i < Elts(); i++)
        data[i] -= b[i];

    return (*this);
}

Vec &Vec::operator *=(const Vec &b) {
    Assert(Elts() == b.Elts(), "(Vec::*=) Vec sizes don't match");

    int i;

    for (i = 0; i < Elts(); i++)
        data[i] *= b[i];

    return (*this);
}

Vec &Vec::operator *=(double s) {
    int i;

    for (i = 0; i < Elts(); i++)
        data[i] *= s;

    return (*this);
}

Vec &Vec::operator /=(const Vec &b) {
    Assert(Elts() == b.Elts(), "(Vec::/=) Vec sizes don't match");

    int i;

    for (i = 0; i < Elts(); i++)
        data[i] /= b[i];

    return (*this);
}

Vec &Vec::operator /=(double s) {
    int i;

    for (i = 0; i < Elts(); i++)
        data[i] /= s;

    return (*this);
}


// --- Vec Comparison Operators -----------------------------------------------

bool operator ==(const Vec &a, const Vec &b) {
    int i;

    for (i = 0; i < a.Elts(); i++)
        if (a[i] != b[i])
            return (0);

    return (1);
}

bool operator !=(const Vec &a, const Vec &b) {
    int i;

    for (i = 0; i < a.Elts(); i++)
        if (a[i] != b[i])
            return (1);

    return (0);
}


// --- Vec Arithmetic Operators -----------------------------------------------

Vec operator +(const Vec &a, const Vec &b) {
    Assert(a.Elts() == b.Elts(), "(Vec::+) Vec sizes don't match");

    Vec result(a.Elts());
    int i;

    for (i = 0; i < a.Elts(); i++)
        result[i] = a[i] + b[i];

    return (result);
}

Vec operator -(const Vec &a, const Vec &b) {
    Assert(a.Elts() == b.Elts(), "(Vec::-) Vec sizes don't match");

    Vec result(a.Elts());
    int i;

    for (i = 0; i < a.Elts(); i++)
        result[i] = a[i] - b[i];

    return (result);
}

Vec operator -(const Vec &v) {
    Vec result(v.Elts());
    int i;

    for (i = 0; i < v.Elts(); i++)
        result[i] = -v[i];

    return (result);
}

Vec operator *(const Vec &a, const Vec &b) {
    Assert(a.Elts() == b.Elts(), "(Vec::*) Vec sizes don't match");

    Vec result(a.Elts());
    int i;

    for (i = 0; i < a.Elts(); i++)
        result[i] = a[i] * b[i];

    return (result);
}

Vec operator *(const Vec &v, double s) {
    Vec result(v.Elts());
    int i;

    for (i = 0; i < v.Elts(); i++)
        result[i] = v[i] * s;

    return (result);
}

Vec operator /(const Vec &a, const Vec &b) {
    Assert(a.Elts() == b.Elts(), "(Vec::/) Vec sizes don't match");

    Vec result(a.Elts());
    int i;

    for (i = 0; i < a.Elts(); i++)
        result[i] = a[i] / b[i];

    return (result);
}

Vec operator /(const Vec &v, double s) {
    Vec result(v.Elts());
    int i;

    for (i = 0; i < v.Elts(); i++)
        result[i] = v[i] / s;

    return (result);
}

double dot(const Vec &a, const Vec &b) {
    Assert(a.Elts() == b.Elts(), "(Vec::dot) Vec sizes don't match");

    double sum = 0;
    int i;

    for (i = 0; i < a.Elts(); i++)
        sum += a[i] * b[i];

    return (sum);
}

Vec operator *(double s, const Vec &v) {
    Vec result(v.Elts());
    int i;

    for (i = 0; i < v.Elts(); i++)
        result[i] = v[i] * s;

    return (result);
}
