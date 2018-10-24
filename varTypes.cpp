#pragma once

//Written by and copyright Zachary Damato
//varTypes.cpp is part of the zlib submodule

#include <string>
#include <math.h>
#include <cmath>
#include <time.h>

using namespace std;

#ifdef ZLIB_USING_CINDER
#include "cinder/Color.h"
#include "cinder/app/bigAddApp.h"
#endif

#ifdef USING_DEBUG
#include "debug.h"
#endif

#include "math.h"
#include "varTypes.h"
#include "varConv.h"

using namespace zlib;

namespace zlib
{
	namespace var
	{
		coord2::coord2()
		{
			x = 0;
			y = 0;
		}

		coord2::coord2(double X, double Y)
		{
			x = X;
			y = Y;
		}
#ifdef ZLIB_USING_CINDER
		coord2::coord2(glm::highp_vec2 coordinate)
		{
			x = coordinate.x;
			y = coordinate.y;
		}
#endif

		coord2 coord2::operator+(const coord2 & other)
		{
			return coord2(x + other.x, y + other.y);
		}

		coord2 coord2::operator+(mVector & other)
		{
			return (*this) + other.toCoord2();
		}


		coord2 coord2::operator-(const coord2 & other)
		{
			return coord2(x - other.x, y - other.y);
		}

		coord2 coord2::operator-(mVector & other)
		{
			return (*this) - other.toCoord2();
		}


		coord2 coord2::operator*(const coord2 & other)
		{
			return coord2(x * other.x, y * other.y);
		}

		coord2 coord2::operator*(mVector & other)
		{
			return (*this) * other.toCoord2();
		}

		coord2 coord2::operator*(const double & other)
		{
			return coord2(x * other, y * other);
		}


		coord2 coord2::operator/(const coord2 & other)
		{
			return coord2(x / other.x, y / other.y);
		}

		coord2 coord2::operator/(mVector & other)
		{
			return (*this) / other.toCoord2();
		}

		coord2 coord2::operator/(const double & other)
		{
			return coord2(x / other, y / other);
		}


		coord2 coord2::operator+=(const coord2 & other)
		{
			x += other.x;
			y += other.y;
			return coord2(x, y);
		}

		coord2 coord2::operator+=(mVector & other)
		{
			return coord2((*this) += other.toCoord2());
		}


		coord2 coord2::operator-=(const coord2 & other)
		{
			x -= other.x;
			y -= other.y;
			return coord2(x, y);
		}

		coord2 coord2::operator-=(mVector & other)
		{
			return (*this) -= other.toCoord2();
		}


		coord2 coord2::operator*=(const coord2 & other)
		{
			x *= other.x;
			y *= other.y;
			return coord2(x, y);
		}

		coord2 coord2::operator*=(mVector & other)
		{
			return (*this) *= other.toCoord2();
		}

		coord2 coord2::operator*=(const double & other)
		{
			x *= other;
			y *= other;
			return coord2(x, y);
		}


		coord2 coord2::operator/=(const coord2 & other)
		{
			x /= other.x;
			y /= other.y;
			return coord2(x, y);
		}

		coord2 coord2::operator/=(mVector & other)
		{
			return (*this) /= other.toCoord2();
		}

		coord2 coord2::operator/=(const double & other)
		{
			x /= other;
			y /= other;
			return coord2(x, y);
		}


		bool coord2::operator==(const coord2 & other)
		{
			if (x == other.x && y == other.y) return true;
			else return false;
		}


		bool coord2::operator!=(const coord2 & other)
		{
			if (x != other.x || y != other.y) return true;
			else return false;
		}


		bool coord2::operator>(const coord2 & other)
		{
			return (x > other.x) && (y > other.y);
		}

		bool coord2::operator>(const double & other)
		{
			return (x > other) && (y > other);
		}


		bool coord2::operator<(const coord2 & other)
		{
			return (x < other.x) && (y < other.y);
		}

		bool coord2::operator<(const double & other)
		{
			return (x < other) && (y < other);
		}


		bool coord2::operator>=(const coord2 & other)
		{
			return (x >= other.x) && (y >= other.y);
		}

		bool coord2::operator>=(const double & other)
		{
			return (x >= other) && (y >= other);
		}


		bool coord2::operator<=(const coord2 & other)
		{
			return (x <= other.x) && (y <= other.y);
		}

		bool coord2::operator<=(const double & other)
		{
			return (x <= other) && (y <= other);
		}


		coord2 coord2::negatedX()
		{
			return coord2(x * -1, y);
		}

		coord2 coord2::negatedY()
		{
			return coord2(x, y * -1);
		}

		coord2 coord2::negated()
		{
			return coord2(x * -1, y * -1);
		}

		void coord2::negateX()
		{
			x *= -1;
		}

		void coord2::negateY()
		{
			y *= -1;
		}

		void coord2::negate()
		{
			x *= -1;
			y *= -1;
		}

#ifdef ZLIB_USING_CINDER
		glm::highp_vec2 coord2::toGlm()
		{
			return glm::highp_vec2(x, y);
		}
#endif

		string coord2::toString()
		{
			return("x: " + conv::toString(x) + ", y: " + conv::toString(y));
		}

		int coord2::getQuadrant()
		{
			if (x >= 0 && y >= 0) return 1;
			else if (x < 0 && y >= 0) return 2;
			else if (x < 0 && y < 0) return 3;
			else if (x >= 0 && y < 0) return 4;
			else
			{
				throw("Error determining quadrant.  Coordinates may be improperly defined.  Defaulting to 1");
				return 1;
			}
		}

		bool coord2::isWithin(coord2 first, coord2 second)
		{
			double highX = 0;
			double lowX = 0;
			double highY = 0;
			double lowY = 0;

			if (first.x > second.x)
			{
				highX = first.x;
				lowX = second.x;
			}
			else
			{
				lowX = first.x;
				highX = second.x;
			}

			if (first.y > second.y)
			{
				highY = first.y;
				lowY = second.y;
			}
			else
			{
				lowY = first.y;
				highY = second.y;
			}

			return (lowX < x && x < highX) && (lowY < y && y < highY);

		}

		double coord2::getMagnitude()
		{
			return sqrt(pow(x, 2) + pow(y, 2));
		}

		double coord2::getAngle()
		{
			return conv::toDegrees(atan2(y, x));
		}

		double coord2::getAngleRadians()
		{
			return atan2(y, x);
		}

		mVector coord2::toMVector()
		{
			return mVector(*this);
		}

		double coord2::distanceTo(coord2 &point)
		{
			return distanceTo(*this, point);
		}

		double coord2::angleBetween(coord2 &point)
		{
			return angleBetween(*this, point);
		}

		double coord2::distanceTo(coord2 &first, coord2 &second)
		{
			return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
		}

		double coord2::angleBetween(coord2 &first, coord2 &second)
		{
			return conv::toDegrees(atan2(second.y - first.y, second.x - first.x));
		}




		mVector::mVector(double _magnitude, double _angle)
		{
			magnitude = _magnitude;
			angle = _angle;
		}

		mVector::mVector(coord2 coordinate)
		{
			magnitude = coordinate.getMagnitude();
			magnitude = coordinate.getAngle();
		}

		mVector::mVector(coord2 first, coord2 second)
		{
			coord2 diff = second - first;
			*this = mVector(diff);
		}

		mVector mVector::operator* (double & other)
		{
			return mVector(magnitude * other, angle);
		}

		mVector mVector::operator/ (double & other)
		{
			return mVector(magnitude / other, angle);
		}

		coord2 mVector::toCoord2()
		{
			return
				coord2(
					magnitude * cos(conv::toRadians(angle)),
					magnitude * sin(conv::toRadians(angle))
				);
		}




		coord3::coord3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		coord3::coord3(double X, double Y, double Z)
		{
			x = X;
			y = Y;
			z = Z;
		}

		coord3 coord3::operator+(const coord3& other)
		{
			return coord3(x + other.x, y + other.y, z + other.z);
		}

		coord3 coord3::operator-(const coord3& other)
		{
			return coord3(x - other.x, y - other.y, z - other.z);
		}

		coord3 coord3::operator*(const coord3& other)
		{
			return coord3(x * other.x, y * other.y, z * other.z);
		}

		coord3 coord3::operator*(const double& other)
		{
			return coord3(x * other, y * other, z * other);
		}

		coord3 coord3::operator/(const coord3& other)
		{
			return coord3(x / other.x, y / other.y, z / other.z);
		}

		coord3 coord3::operator/(const double& other)
		{
			return coord3(x / other, y / other, z / other);
		}

		bool coord3::operator==(const coord3& other)
		{
			if (x == other.x && y == other.y && z == other.z) return true;
			else return false;
		}

#ifdef ZLIB_USING_CINDER
		
		glm::highp_vec3 coord3::toGlm()
		{
			return glm::highp_vec3(x, y, z);
		}
#endif




		fraction::fraction(bool _autoReduce)
		{
			autoReduce = _autoReduce;
		}

		fraction::fraction(int _numer, int _denom, bool _autoReduce)
		{
			autoReduce = _autoReduce;
			if (_denom == 0) throw varExceptions::fraction_denom0;

			numer = _numer;
			denom = _denom;

			if (autoReduce) reduce();
		}

		void fraction::reduce()
		{
			if (denom < 0)	//Move the negative in the denominator to the numerator
			{
				numer *= -1;
				denom *= -1;
			}

			for (int factor = 2; factor <= numer && factor <= denom; factor++)
			{
				if (numer%factor == 0 && denom%factor == 0)
				{
					numer /= factor;
					denom /= factor;
				}
			}
		}

		fraction fraction::reduce(fraction frac)
		{
			if (frac.denom < 0)	//Move the negative in the denominator to the numerator
			{
				frac.numer *= -1;
				frac.denom *= -1;
			}

			for (int factor = 2; factor <= frac.numer && factor <= frac.denom; factor++)
			{
				if (frac.numer%factor == 0 && frac.denom%factor == 0)
				{
					frac.numer /= factor;
					frac.denom /= factor;
				}
			}
			return frac;
		}

		std::pair<fraction, fraction> fraction::convCommonBase(fraction first, fraction second)
		{
			//If they already have a common denominator
			if (first.denom == second.denom) return std::pair<fraction, fraction>(first, second);

			//Remove any common factors from the denominators
			int base1 = first.denom;
			int base2 = second.denom;
			for (int factor = 2; factor <= base1 && factor <= base2; factor++)
			{
				while (base1 % factor == 0 && base2 % factor == 0)
				{
					base1 /= factor;
					base2 /= factor;
				}
			}

			//Cross multiply using the reduced denominators
			first.numer *= base2;
			first.denom *= base2;

			second.numer *= base1;
			second.denom *= base1;

			return std::pair<fraction, fraction>(first, second);
		}

		fraction fraction::getReciprocal()
		{
			return fraction(denom, numer, autoReduce);
		}

		fraction fraction::operator+(fraction const & other)
		{
			std::pair<fraction, fraction> fPair = convCommonBase(*this, other);
			return fraction(fPair.first.numer + fPair.second.numer, fPair.first.denom, autoReduce);
		}

		fraction fraction::operator-(fraction const & other)
		{
			std::pair<fraction, fraction> fPair = convCommonBase(*this, other);
			return fraction(fPair.first.numer - fPair.second.numer, fPair.first.denom, autoReduce);
		}

		fraction fraction::operator*(fraction const & other)
		{
			return fraction(numer * other.numer, denom * other.denom, autoReduce);
		}

		fraction fraction::operator/(fraction const & other)
		{
			return fraction(numer * other.denom, denom * other.numer, autoReduce);
		}

		void fraction::operator+=(fraction const & other)
		{
			std::pair<fraction, fraction> fPair = convCommonBase(*this, other);
			numer = fPair.first.numer + fPair.second.numer;
			denom = fPair.first.denom;
			if (autoReduce) reduce();
		}

		void fraction::operator-=(fraction const & other)
		{
			std::pair<fraction, fraction> fPair = convCommonBase(*this, other);
			numer = fPair.first.numer - fPair.second.numer;
			denom = fPair.first.denom;
			if (autoReduce) reduce();
		}

		void fraction::operator*=(fraction const & other)
		{
			numer *= other.numer;
			denom *= other.denom;
			if (autoReduce) reduce();
		}

		void fraction::operator/=(fraction const & other)
		{
			numer *= other.denom;
			denom *= other.numer;
			if (autoReduce) reduce();
		}

		bool fraction::operator==(fraction const & other)
		{
			fraction first = reduce(*this);
			fraction second = reduce(other);

			return first.numer == second.numer && first.denom == second.denom;
		}

		bool fraction::operator!=(fraction const & other)
		{
			fraction first = reduce(*this);
			fraction second = reduce(other);

			return first.numer != second.numer || first.denom != second.denom;
		}

		bool fraction::operator<(fraction const & other)
		{
			std::pair<fraction, fraction> fPair = convCommonBase(*this, other);

			return fPair.first.numer < fPair.second.numer;
		}

		bool fraction::operator<=(fraction const & other)
		{
			std::pair<fraction, fraction> fPair = convCommonBase(*this, other);

			return fPair.first.numer <= fPair.second.numer;
		}

		bool fraction::operator>(fraction const & other)
		{
			std::pair<fraction, fraction> fPair = convCommonBase(*this, other);

			return fPair.first.numer > fPair.second.numer;
		}

		bool fraction::operator>=(fraction const & other)
		{
			std::pair<fraction, fraction> fPair = convCommonBase(*this, other);

			return fPair.first.numer >= fPair.second.numer;
		}



		color_RGB::color_RGB()
		{
			R = 1;
			G = 0;
			B = 0;
		}

		color_RGB::color_RGB(double r, double g, double b)
		{
			R = r;
			G = g;
			B = b;
		}

		color_RGB::color_RGB(double r, double g, double b, double a)
		{
			R = r;
			G = g;
			B = b;
			A = a;
		}

		bool color_RGB::operator== (const color_RGB & other)
		{
			return R == other.R && G == other.G && B == other.B && A == other.A;
		}

#ifdef ZLIB_USING_CINDER
		ci::Color color_RGB::toColor()
		{
			return ci::Color(R, G, B);
		}

		ci::Color color_RGB::toCinderColor()
		{
			return ci::Color(R, G, B);
		}

		ci::ColorA color_RGB::toCinderColorA()
		{
			if (0 <= A && A <= 1) return ci::ColorA(R, G, B, A);
			return ci::ColorA(R, G, B, 1);
		}
#endif

		longTime::longTime(tm * t)
		{
			tm_sec = t->tm_sec;
			tm_min = t->tm_min;
			tm_hour = t->tm_hour;
			tm_mday = t->tm_mday;
			tm_mon = t->tm_mon + 1;
			tm_year = t->tm_year + 1900;	//Convert epoch year to actual year
			tm_wday = t->tm_wday;
			tm_yday = t->tm_yday;
			tm_isdst = t->tm_isdst;
		}

		longTime::longTime(time_t t)
		{
			tm * formatted = new tm;
#ifndef __linux__
			localtime_s(formatted, &t);
#else
			formatted = localtime(&t);
#endif
			(*this) = longTime(formatted);
		}

		longTime longTime::now()
		{
			time_t t = time(NULL);
			return longTime(t);
		}

		std::string longTime::getYMD()
		{
			return conv::toString(tm_year) + '-' + conv::toString(tm_mon) + '-' + conv::toString(tm_mday);
		}

		std::string longTime::getHMS()
		{
			auto padIfNeeded = [](unsigned value)
			{
				if(value < 10) return "0";
				else return "";
			};

			return padIfNeeded(tm_hour) + conv::toString(tm_hour) + '-' + padIfNeeded(tm_min) + conv::toString(tm_min) + '-' + padIfNeeded(tm_sec) + conv::toString(tm_sec);
		}

		shortTime::shortTime(int _seconds, int minutes, int hours, int days)
		{
			seconds = _seconds +
				minutes * secondsPerMinute +
				hours * secondsPerHour +
				days * secondsPerDay;
		}

		int shortTime::getTotalSeconds()
		{
			return seconds;
		}

		int shortTime::getSeconds()
		{
			return seconds % secondsPerMinute;
		}

		int shortTime::getMinutes()
		{
			return seconds % secondsPerHour / secondsPerMinute;
		}

		int shortTime::getHours()
		{
			return seconds % secondsPerDay / secondsPerHour;
		}

		int shortTime::getDays()
		{
			return seconds / secondsPerDay;
		}

		string shortTime::toStringDHMS()
		{
			return "Days: " + conv::toString(getDays()) + " " + toStringHMS();
		}

		string shortTime::toStringHMS()
		{
			return "Hours: " + conv::toString(getHours()) + " " + toStringMS();
		}

		string shortTime::toStringMS()
		{
			return "Minutes: " + conv::toString(getMinutes()) + " Seconds: " + conv::toString(getSeconds());
		}

		shortTime shortTime::operator+(shortTime & other)
		{
			return shortTime(getTotalSeconds() + other.getTotalSeconds());
		}

		shortTime shortTime::operator-(shortTime & other)
		{
			return shortTime(getTotalSeconds() - other.getTotalSeconds());
		}

		shortTime shortTime::operator*(shortTime & other)
		{
			return shortTime(getTotalSeconds() * other.getTotalSeconds());
		}

		shortTime shortTime::operator/(shortTime & other)
		{
			return shortTime(getTotalSeconds() / other.getTotalSeconds());
		}

		void shortTime::operator+=(shortTime & other)
		{
			seconds += other.getTotalSeconds();
		}

		void shortTime::operator-=(shortTime & other)
		{
			seconds -= other.getTotalSeconds();
		}

		void shortTime::operator*=(shortTime & other)
		{
			seconds *= other.getTotalSeconds();
		}

		void shortTime::operator/=(shortTime & other)
		{
			seconds /= other.getTotalSeconds();
		}

		bool shortTime::operator==(shortTime & other)
		{
			return seconds == other.getTotalSeconds();
		}

		bool shortTime::operator!=(shortTime & other)
		{
			return seconds != other.getTotalSeconds();
		}

		bool shortTime::operator<(shortTime & other)
		{
			return seconds < other.getTotalSeconds();
		}

		bool shortTime::operator<=(shortTime & other)
		{
			return seconds <= other.getTotalSeconds();
		}

		bool shortTime::operator>(shortTime & other)
		{
			return seconds > other.getTotalSeconds();
		}

		bool shortTime::operator>=(shortTime & other)
		{
			return seconds >= other.getTotalSeconds();
		}

		timePeriod::timePeriod()
		{
			beginning = -1;
			ending = -1;
			clockSet = false;
		}

		timePeriod::timePeriod(zlib::timer & clock)
		{
			//Store the current time as the beginning of the clock first-thing, as it's ovb. time dependent
			beginning = clock.getTime();

			//Store a copy of the clock internally
			this->clock = clock;
			clockSet = true;
		}

		timePeriod::timePeriod(double beginning, double ending)
		{
			//The * pow(10, 9) is to convert from s to ns
			this->beginning = beginning * pow(10, 9);
			this->ending = ending * pow(10, 9);
			clockSet = false;
		}

		timePeriod::timePeriod(string encodedForm, bool noExcept)
		{
			//Proper format is: "b<beginning>e<ending>", when the time values are in ns
			clockSet = false;

			//Set default conditions (For error states)
			beginning = -1;
			ending = -1;

			try
			{
				string bgn = encodedForm.substr(1, encodedForm.find('e') - 1);
				string end = encodedForm.substr(1 + encodedForm.find('e'));
				beginning = conv::toNum(bgn);
				ending = conv::toNum(end);
			}
			catch(std::out_of_range e)
			{
				if(!noExcept) throw timePeriodError::malformedString;
			}
			catch(conv::convertError e)
			{
				if(!noExcept)throw timePeriodError::malformedString;
			}
			
		}

		void timePeriod::begin()
		{
			beginning = clock.getTime();
		}


		void timePeriod::begin(zlib::timer clock)
		{
			//Store the current time as the beginning of the clock first-thing, as it's ovb. time dependent
			beginning = clock.getTime();

			//Set our internal clock to the clock we're given
			this->clock = clock;
			clockSet = true;
		}

		void timePeriod::end()
		{
			ending = clock.getTime();
		}

		string timePeriod::encode()
		{
			return "b" + conv::toString(beginning) + "e" + conv::toString(ending);
		}

		namespace geom	//As in geometry
		{
			line::line(coord2 _slope, coord2 _displacement)
			{
				setSlope(_slope);
				displacement = _displacement;
				xBounds = false;
				yBounds = false;
			}

			line::line(coord2 _slope, coord2 _displacement, double _lowxBound, double _highxBound)
			{
				setSlope(_slope);
				displacement = _displacement;
				setxBounds(_lowxBound, _highxBound);
				yBounds = false;
			}

			line::line(coord2 _slope, coord2 _displacement, double _lowxBound, double _highxBound, double _lowyBound, double _highyBound)
			{
				setSlope(_slope);
				displacement = _displacement;
				setxBounds(_lowxBound, _highxBound);
				setyBounds(_lowyBound, _highyBound);
			}

			line::line(coord2 _slope, double _xDisplacement, double _yDisplacement)
			{
				setSlope(_slope);
				displacement = var::coord2(_xDisplacement, _yDisplacement);
				xBounds = false;
				yBounds = false;
			}

			line::line(coord2 _slope, double _xDisplacement, double _yDisplacement, double _lowxBound, double _highxBound)
			{
				setSlope(_slope);
				displacement = var::coord2(_xDisplacement, _yDisplacement);
				setxBounds(_lowxBound, _highxBound);
				yBounds = false;
			}

			line::line(coord2 _slope, double _xDisplacement, double _yDisplacement, double _lowxBound, double _highxBound, double _lowyBound, double _highyBound)
			{
				setSlope(_slope);
				displacement = var::coord2(_xDisplacement, _yDisplacement);
				setxBounds(_lowxBound, _highxBound);
				setyBounds(_lowyBound, _highyBound);
			}

			line::line(double _slope, coord2 _displacement)
			{
				setSlope(coord2(1, _slope));
				displacement = _displacement;
				xBounds = false;
				yBounds = false;
			}

			line::line(double _slope, coord2 _displacement, double _lowxBound, double _highxBound)
			{
				setSlope(coord2(1, _slope));
				displacement = _displacement;
				setxBounds(_lowxBound, _highxBound);
				yBounds = false;
			}

			line::line(double _slope, coord2 _displacement, double _lowxBound, double _highxBound, double _lowyBound, double _highyBound)
			{
				setSlope(coord2(1, _slope));
				displacement = _displacement;
				setxBounds(_lowxBound, _highxBound);
				setyBounds(_lowyBound, _highyBound);
			}

			line::line(double _slope, double _xDisplacement, double _yDisplacement)
			{
				setSlope(coord2(1, _slope));
				displacement = var::coord2(_xDisplacement, _yDisplacement);
				xBounds = false;
				yBounds = false;
			}

			line::line(double _slope, double _xDisplacement, double _yDisplacement, double _lowxBound, double _highxBound)
			{
				setSlope(coord2(1, _slope));
				displacement = var::coord2(_xDisplacement, _yDisplacement);
				setxBounds(_lowxBound, _highxBound);
				yBounds = false;
			}

			line::line(double _slope, double _xDisplacement, double _yDisplacement, double _lowxBound, double _highxBound, double _lowyBound, double _highyBound)
			{
				setSlope(coord2(1, _slope));
				displacement = var::coord2(_xDisplacement, _yDisplacement);
				setxBounds(_lowxBound, _highxBound);
				setyBounds(_lowyBound, _highyBound);
			}

			int line::getSlopeSign()
			{
				if(slope.x == 0 && slope.y == 0) return 0;
				else if((slope.x >= 0 && slope.y >= 0) || (slope.x <= 0 && slope.y <= 0)) return 1;
				else if((slope.x > 0 && slope.y < 0) || (slope.x < 0 && slope.y > 0)) return -1;
				throw("Unknown exception.  Returning 0.");
				return 0;
			}

			double line::getSlope()
			{
				if(slope.x != 0) return slope.y / slope.x;
				else
				{
					throw("SLOPE = y / 0");
					return slope.y / (10 ^ -20);
				}
			}

			coord2 line::getSlopeCoord2()
			{
				return coord2();
			}

			bool line::setSlope(coord2 _slope)
			{
				if(_slope.x == 0 && _slope.y == 0)
				{
					throw("Bad slope - slope cannot be 0 / 0.  Defaulting to 1.");
					slope = coord2(1, 1);
					return false;
				}
				else
				{
					slope = _slope;
					return true;
				}
			}

			bool line::setxBounds(double _lowxBound, double _highxBound)
			{
				if(_lowxBound < _highxBound)
				{
					lowxBound = _lowxBound;
					highxBound = _highxBound;
					xBounds = true;
				}
				else if(_lowxBound > _highxBound)
				{
					lowxBound = _highxBound;
					highxBound = _lowxBound;
					xBounds = true;
				}
				else if(_lowxBound == _highxBound)
				{
					throw("Bad input, _lowxBound is equal to _highxBound.  Setting xboudns to false.");
					xBounds = false;
				}
				else
				{
					throw("Unspecified error.  Setting xBounds to false.");
					xBounds = false;
				}
				return xBounds;
			}

			bool line::setyBounds(double _lowyBound, double _highyBound)
			{
				if(_lowyBound < _highyBound)
				{
					lowyBound = _lowyBound;
					highyBound = _highyBound;
					yBounds = true;
				}
				else if(_lowyBound > _highyBound)
				{
					lowyBound = _highyBound;
					highyBound = _lowyBound;
					yBounds = true;
				}
				else if(_lowyBound == _highyBound)
				{
					throw("Bad input, _lowyBound is equal to _highyBound.  Setting yboudns to false.");
					yBounds = false;
				}
				else
				{
					throw("Unspecified error.  Setting yBounds to false.");
					yBounds = false;
				}
				return yBounds;
			}

			double line::getY(double _x)
			{
				if(slope.x == 0) return _x;
				else return getSlope() * (_x - displacement.x) + displacement.y;
			}

			vector<double> line::getY(vector<double> _x)
			{
				vector<double> y;
				for(int x = 0; x < _x.size(); x++)
				{
					y.push_back(getY(_x[x]));
				}
				return y;
			}

			double line::getX(double _y)
			{
				if(slope.y == 0) return _y;
				else return (slope.x * (_y - displacement.y) / slope.y) + displacement.x;
			}

			vector<double> line::getX(vector<double> _y)
			{
				vector<double> x;
				for(int y = 0; y < _y.size(); y++)
				{
					x.push_back(getX(_y[y]));
				}
				return x;
			}

			vector<coord2> line::getValuesBetweenBounds(double _interval)
			{
				if(xBounds == true)
				{
					vector<coord2> ret;
					for(double x = lowxBound; x < highxBound; x += _interval)
					{
						double y = getY(x);
						if(yBounds == false || lowyBound <= y && y <= highyBound)
						{
							ret.push_back(var::coord2(x, y));
						}
					}
					if(highxBound != ret[ret.size() - 1].x)
					{
						double y = getY(highxBound);
						if(yBounds == false || lowyBound <= y && y <= highyBound)
						{
							ret.push_back(var::coord2(highxBound, y));
						}
					}
					return ret;
				}
				else throw("Bounds not set!");
			}

			bool line::isCoordWithinBounds(coord2 _pos)
			{
				bool withinBounds = true;
				if(xBounds == true && (lowxBound > _pos.x || _pos.x > highxBound)) withinBounds = false;
				if(yBounds == true && (lowyBound > _pos.y || _pos.y > highyBound)) withinBounds = false;
				return withinBounds;
			}

			bool line::hasIntercept(line _line)
			{
				if(slope.x == 0 && _line.slope.x == 0 && displacement.x == _line.displacement.x) return true;
				else if(slope.y == 0 && _line.slope.y == 0 && displacement.y == _line.displacement.y) return true;
				else if((slope.x == 0 && _line.slope.x != 0) || (_line.slope.x == 0 && slope.x != 0)) return true;
				else if((slope.y == 0 && _line.slope.y != 0) || (_line.slope.y == 0 && slope.y != 0)) return true;
				else if(slope.x != 0 && slope.y != 0 && _line.slope.x != 0 && _line.slope.y != 0) return true;
				else if(slope == _line.slope)
				{
					if(displacement == _line.displacement) return true;
					if(displacement != _line.displacement)
					{
						//Checks if the displacement + the slope * a constant == the displacement of the argument, for x and y, and checks if the constant is the same for both x and y
						if((_line.displacement.x - displacement.x) / slope.x == (_line.displacement.y - displacement.y) / slope.y) return true;
					}
				}
				return false;
			}

			coord2 line::getIntercept(line _line)
			{
				if(hasIntercept(_line) == false)
				{
					throw("No intercept!");
					return coord2(0, 0);
				}
				else
				{
					if(slope.x == 0 && _line.slope.x != 0)
					{
						return coord2(displacement.x, _line.getY(displacement.x));
					}
					else if(_line.slope.x == 0 && slope.x != 0)
					{
						return coord2(_line.displacement.x, getY(_line.displacement.x));
					}
					else if(slope.y == 0 && _line.slope.y != 0)
					{
						return coord2(displacement.y, displacement.y);
					}
					else if(_line.slope.y == 0 && slope.y != 0)
					{
						return coord2(_line.displacement.y, _line.displacement.y);
					}
					else
					{
						double x = (_line.displacement.y - displacement.y + (getSlope() * displacement.x) - (_line.getSlope() * _line.displacement.x)) / (getSlope() - _line.getSlope());
						return var::coord2(x, getY(x));
					}
				}
			}

			bool line::isInterceptWithinBounds(line _line)
			{
				if(hasIntercept(_line) == false) return false;
				else
				{
					coord2 intercept = getIntercept(_line);
					return isCoordWithinBounds(intercept) && _line.isCoordWithinBounds(intercept);
				}
			}

			double line::getLengthBetween(double _x1, double _x2)
			{
				return sqrt(pow((_x1 - _x2), 2) + pow(getY(_x1) - getY(_x2), 2));
			}

			double line::getLengthBetweenBounds()
			{
				if(yBounds == false && xBounds == false) return 0;		//The length would be infinite
				double x_lowy;			//The greater value of x_lowy and x_highy
				double x_highy;			//The lesser value of x_lowy and x_highy
				double lowx, highx;		//The best x and y values that represent the best bounds (basically the innermost boudnaries)
				if(yBounds)
				{
					if(getSlopeSign() > 0)
					{
						x_lowy = getX(lowxBound);
						x_highy = getX(highyBound);
					}
					else if(getSlopeSign() < 0)
					{
						x_lowy = getX(highyBound);
						x_highy = getX(lowyBound);
					}
				}
				if(xBounds == true && yBounds == true)
				{
					if(lowxBound >= x_lowy) lowx = lowxBound;
					else if(lowxBound < x_lowy) lowx = x_lowy;
					else lowx = lowxBound;
				}
				else if(xBounds == false && yBounds == true)
				{
					lowx = x_lowy;
					highx = x_highy;
				}
				else if(yBounds == false)
				{
					lowx = lowxBound;
					highx = highxBound;
				}
				return getLengthBetween(lowx, highx);
				return 0;		//An error value, incase something goes wrong
			}

			double line::getLengthToBounds(double _x, int _direction)
			{
				if(yBounds == false && xBounds == false) return 0;		//The length would be infinite
				double x_lowy;			//The greater value of x_lowy and x_highy
				double x_highy;			//The lesser value of x_lowy and x_highy
				double lowx, highx;		//The best x and y values that represent the best bounds (basically the innermost boudnaries)
				if(yBounds)
				{
					if(getSlopeSign() > 0)
					{
						x_lowy = getX(lowxBound);
						x_highy = getX(highyBound);
					}
					else if(getSlopeSign() < 0)
					{
						x_lowy = getX(highyBound);
						x_highy = getX(lowyBound);
					}
				}
				if(xBounds == true && yBounds == true)
				{
					if(lowxBound >= x_lowy) lowx = lowxBound;
					else if(lowxBound < x_lowy) lowx = x_lowy;
					else lowx = lowxBound;
				}
				else if(xBounds == false && yBounds == true)
				{
					lowx = x_lowy;
					highx = x_highy;
				}
				else if(yBounds == false)
				{
					lowx = lowxBound;
					highx = highxBound;
				}
				if(_direction >= 0) lowx = _x;
				else if(_direction < 0) highx = _x;
				return getLengthBetween(lowx, highx);
				return 0;		//An error value, incase something goes wrong
			}

			coord2 line::getCoordAtLength(coord2 _start, double _length)
			{
				return _start + (slope * (_length / sqrt(pow(slope.x, 2) + pow(slope.y, 2))));
			}




			square::square()
			{}

			square::square(coord2 _upperRight, coord2 _lowerLeft)
			{
				topY = _upperRight.y;
				rightX = _upperRight.x;
				bottomY = _lowerLeft.y;
				leftX = _lowerLeft.x;
			}

			square::square(double _leftX, double _rightX, double _bottomY, double _topY)
			{
				leftX = _leftX;
				rightX = _rightX;
				bottomY = _bottomY;
				topY = _topY;
			}

			coord2 square::getTopLeft()
			{
				return coord2(leftX, topY);
			}

			coord2 square::getTopRight()
			{
				return coord2(rightX, topY);
			}

			coord2 square::getBottomLeft()
			{
				return coord2(leftX, bottomY);
			}

			coord2 square::getBottomRight()
			{
				return coord2(rightX, bottomY);
			}




			circle::circle(coord2 _center, double _radius)
			{
				setCenter(_center);
				setRadius(_radius);
			}

			void circle::calculateQuad(line _line)
			{
				A = pow(_line.getSlope(), 2) + 1;
				B = -2 * (center.x + (_line.displacement.x * pow(_line.getSlope(), 2)) - (_line.displacement.y * _line.getSlope()) + (center.y * _line.getSlope()));
				C = pow(center.x, 2) + (pow(_line.displacement.x, 2) * pow(_line.getSlope(), 2)) - (2 * _line.displacement.x * _line.getSlope() * (_line.displacement.y - center.y)) + pow(_line.displacement.y - center.y, 2) - pow(radius, 2);
			}

			bool circle::setCenter(coord2 _center)
			{
				center = _center;
				return true;
			}

			bool circle::setRadius(double _radius)
			{
				if(_radius > 0)
				{
					radius = _radius;
					return true;
				}
				else radius = 1;
				return false;
			}

			coord2 circle::getCenter()
			{
				return center;
			}

			double circle::getRadius()
			{
				return radius;
			}

			double circle::getCircumference()
			{
				return 2 * math::pi * getRadius();
			}

			double circle::getArea()
			{
				return math::pi * getRadius() * getRadius();
			}

			int circle::getNumIntercepts(line _line)
			{
				calculateQuad(_line);
				discriminant = pow(B, 2) - (4 * A * C);
				if(discriminant < 0) return 0;
				else if(discriminant == 0) return 1;
				else if(discriminant > 0) return 2;
			}

			vector<coord2> circle::getIntercept(line _line)
			{
				switch(getNumIntercepts(_line))
				{
					case 0:
					{
						return vector<coord2>();
						break;
					}
					case 1:
					{
						double x = -B / 2 * A;
						return {coord2(x, _line.getY(x))};
						break;
					}
					case 2:
					{
						double x1 = (-B + sqrt(discriminant)) / (2 * A);
						double x2 = (-B - sqrt(discriminant)) / (2 * A);
						return {coord2(x1, _line.getY(x1)), coord2(x2, _line.getY(x2))};
						break;
					}
				}
			}
		}

	}
}