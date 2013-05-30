#ifndef INC_newGA_mallba_hh
#define INC_newGA_mallba_hh


#include <iostream>
#include <fstream>
#include <math.h>
#include <values.h>
#include <malva/Rlist.h>
#include <malva/Rarray.h>
#include <malva/Messages.h>
#include <malva/mallba.hh>
#include <malva/States.hh>
#include <malva/random.hh>
#include <malva/time.hh>
#include <malva/netstream.hh>
#include <assert.h>

using namespace std;

#ifndef _INDIVIDUAL_
#define _INDIVIDUAL_

struct individual // index of a individual in the population and its fitness
{
	int    index;
	double fitness;
	double sel_parameter;
	bool   change;
};

/*int lessF(const struct individual &i1,const  struct individual &i2)
{
	return i1.fitness < i2.fitness;
}

int lessS(const struct individual &i1,const  struct individual &i2)
{
	return i1.sel_parameter < i2.sel_parameter;
}

int greaterF(const struct individual &i1,const  struct individual &i2)
{
	return i1.fitness > i2.fitness;
}

int greaterS(const struct individual &i1,const  struct individual &i2)
{
	return i1.sel_parameter > i2.sel_parameter;
}*/
#endif
#endif
