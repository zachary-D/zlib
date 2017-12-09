#pragma once

//Written by and copyright Zachary Damato
//varConv.h is part of the varTypes submodule

#include<string>
#include<time.h>

#include "varTypes/varTypes.h"

using namespace std;

namespace conv
{
	string toString(int inp);
	string toString(float inp);
	string toString(double inp);
	string toString(time_t inp);
	string toString(size_t inp);
	string toString(var::coord2 inp, bool multiLine = true);
	string toString(var::color_RGB inp, bool multiLine = true);
	string toString(bool inp);

	string toLowercase(string & inp, bool changeArg = true);	//Coverts 'inp' to lowercase.  USES POINTERS TO CHANGE ARGUMENT VALUES WHEN 'changeArg' IS TRUE
	char toLowercase(char & inp, bool changeArg = false);		//Coverts 'inp' to lowercase.  USES POINTERS TO CHANGE ARGUMENT VALUES WHEN 'changeArg' IS TRUE

	string toUppercase(string & inp, bool changeArg = true);	//Coverts 'inp' to uppercase.  USES POINTERS TO CHANGE ARGUMENT VALUES WHEN 'changeArg' IS TRUE
	char toUppercase(char & inp, bool changeArg = false);		//Coverts 'inp' to uppercase.  USES POINTERS TO CHANGE ARGUMENT VALUES WHEN 'changeArg' IS TRUE

	bool isNum(string inp);
	bool isNum(char inp);
	double toNum(string inp);
	double toNum(char inp);


	bool isBool(string inp);
	bool toBool(string inp);
	bool toBool(double inp);

#ifdef USING_CINDER
	var::coord2 toCoord2(ci::Vec2f coordinate);
#endif

	double toDegrees(double radians);
	double toRadians(double degrees);
}