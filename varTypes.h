#pragma once
#define _USE_MATH_DEFINES

//Written by and copyright Zachary Damato
//varTypes.h is part of the zlib submodule

//Preprocessor directives for enabling different code sections
//		Directive				Description
//		ZLIB_USING_CINDER			Enables Cinder-exclusive functions (i.e. conversion from internal color type to Cinder's color type)

#include <string>
#include <vector>

using std::string;
using std::vector;

#ifdef ZLIB_USING_CINDER
#include "cinder\Color.h"
#include "cinder\app\App.h"
#include "cinder/Text.h"
#include "cinder/app/App.h"
#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/ImageIo.h"
#include "cinder/app/window.h"
#include "cinder/gl/gl.h"
#endif
		
namespace zlib {} //This is here so we can set the using namespace below, so that if we need to include another file from zlib the zlib namespace will already be assumed

using namespace zlib;

//Note: Unless otherwise specified, all angles are assumed to be in degrees
namespace zlib
{
	namespace var
	{
		enum class varExceptions
		{
			fraction_denom0,	//The denominator is 0.  This is a math no-no (divide by 0)
		};

		class mVector;	//Forward declaration

		//2-axis coordinate
		class coord2
		{
		public:
			coord2();
			coord2(double X, double Y);
#ifdef ZLIB_USING_CINDER
			coord2(glm::highp_vec2 coordinate);
#endif

			coord2 operator+(const coord2 & other);
			coord2 operator+(mVector & other);

			coord2 operator-(const coord2 & other);
			coord2 operator-(mVector & other);

			coord2 operator*(const coord2 & other);
			coord2 operator*(mVector & other);
			coord2 operator*(const double & other);

			coord2 operator/(const coord2 & other);
			coord2 operator/(mVector & other);
			coord2 operator/(const double & other);

			coord2 operator+=(const coord2 & other);
			coord2 operator+=(mVector & other);

			coord2 operator-=(const coord2 & other);
			coord2 operator-=(mVector & other);

			coord2 operator*=(const coord2 & other);
			coord2 operator*=(mVector & other);
			coord2 operator*=(const double & other);

			coord2 operator/=(const coord2 & other);
			coord2 operator/=(mVector & other);
			coord2 operator/=(const double & other);


			//When being compared to another coordinate pair, the X and Y pairs BOTH must satisfy the comparison individually
			//When being compared to a number, both the X and Y values must satisfy the comparison to the number
			bool operator==(const coord2 & other);

			bool operator!=(const coord2 & other);

			bool operator>(const coord2 & other);
			bool operator>(const double & other);

			bool operator<(const coord2 & other);
			bool operator<(const double & other);

			bool operator>=(const coord2 & other);
			bool operator>=(const double & other);

			bool operator<=(const coord2 & other);
			bool operator<=(const double & other);

			double x, y;

			//These function DO NOT affect this object
			coord2 negatedX();		//Return the object with x negated
			coord2 negatedY();		//Return the object with y negated
			coord2 negated();		//Return the object with both x and y negated

			//These functions DO affect this object
			void negateX();			//Negate x
			void negateY();			//Negate y
			void negate();			//Negate x and y

#ifdef ZLIB_USING_CINDER
			glm::highp_vec2 toGlm();
#endif
			string toString();
			int getQuadrant();
			bool isWithin(coord2 first, coord2 second);

			double getMagnitude();		//Returns the magnitude of the coordinate as if it were a vector
			double getAngle();			//Returns the angle formed by the x+ axis proceeding CCW until it intersects the hypotenuse of the triangle representing this coordinate (In degrees)
			double getAngleRadians();	//getAngle(), but in radians.

			mVector toMVector();		//Converts the coordinates to a vector, with 0,0 as the center

			double distanceTo(coord2 &point);		//Returns the distance between this coord and 'point'
			double angleBetween(coord2 &point);			//Returns the angle measured CCW between the x+ axis and the line from this coord to 'point'

			static double distanceTo(coord2 &first, coord2 &second);	//Returns the distance between to points
			static double angleBetween(coord2 &first, coord2 &second);		//Returns the angle of a line from 'first' to 'second' (the angle being the angle CCW from Y=0, x+)
		};

		//2-axis vector
		class mVector	//The math version of a vector, not the infinite-array version
		{
		public:
			mVector() {}
			mVector(double _magnitude, double _angle);
			mVector(coord2 coordinate);						//Creates a vector based from the origin to 'coordinate'
			mVector(coord2 first, coord2 second);			//Creates a vector from 'first' to 'second'

			mVector operator* (double &other);
			mVector operator/ (double &other);

			double magnitude;
			double angle;

			coord2 toCoord2();			//Converts the vector to coordinates
		};

		//3-axis coordiante
		class coord3
		{
		public:
			coord3();
			coord3(double X, double Y, double Z);

			coord3 operator+(const coord3 & other);
			coord3 operator-(const coord3 & other);
			coord3 operator*(const coord3 & other);
			coord3 operator*(const double & other);
			coord3 operator/(const coord3 & other);
			coord3 operator/(const double & other);
			bool operator==(const coord3 & other);

			double x;
			double y;
			double z;

#ifdef ZLIB_USING_CINDER
			glm::highp_vec3 toGlm();
#endif
		};

		//A fraction
		struct fraction
		{
			fraction(bool _autoReduce = true);
			//fraction(float value); commented bc float should automatically convert to double
			//fraction(double value, bool _autoReduce = true);		//To be added at a later date
			fraction(int _numer, int _denom = 1, bool _autoReduce = true);

			int numer = 0;		//The numerator
			int denom = 0;		//The denominator

			bool autoReduce = true;		//If the fraction should be reduced when possible (2/4 -> 1/2)

			void reduce();
			fraction static reduce(fraction frac);
			std::pair<fraction, fraction> static convCommonBase(fraction first, fraction second);	//Returns first and second, converted so that they have a common denominator
			double toDouble() { return double(numer) / denom; }

			fraction getReciprocal();

			fraction operator+(fraction const & other);
			fraction operator-(fraction const & other);
			fraction operator*(fraction const & other);
			fraction operator/(fraction const & other);
			
			void operator+=(fraction const & other);
			void operator-=(fraction const & other);
			void operator*=(fraction const & other);
			void operator/=(fraction const & other);

			bool operator==(fraction const & other);
			bool operator!=(fraction const & other);
			bool operator<(fraction const & other);
			bool operator<=(fraction const & other);
			bool operator>(fraction const & other);
			bool operator>=(fraction const & other);



		};

		class color_RGB
		{
		public:
			color_RGB();
			color_RGB(double r, double g, double b);
			color_RGB(double r, double g, double b, double a);

			bool operator == (const color_RGB & other);

			double R = -1;
			double G = -1;
			double B = -1;
			double A = -1;

			bool isDefined() { return R != -1 && G != -1 && B != -1; }			//True when the color is defined (not checking the opacity)
			bool isOpacityDefined() { return  A != -1; }						//True when the opacity is defined
			bool areAllDefined() { return isDefined() && isOpacityDefined(); }	//True when the opacity and color is

#ifdef ZLIB_USING_CINDER
			ci::Color toColor();			//BEING REMOVED.  use toCinderColor() istead
			ci::Color toCinderColor();		//Returns the color in Cinder's format, without opacity
			ci::ColorA toCinderColorA();	//Returns the color in Cinder's format, with opacity
#endif
		};

		//typedef struct tm longTime;		//A time represented as second/minute/hour/day/month/year, from time.h

		struct longTime : tm
		{
			//Todo: rewrite this so that we use our own variables so we can define them differently (AKA reasonably)
			longTime() {}
			longTime(tm * t);

			static longTime now();

			std::string getYMD();
			std::string getHMS();
		};
		
		struct shortTime
		{
			shortTime() {}
			shortTime(int _seconds, int minutes = 0, int hours = 0, int days = 0);

		private:
			int seconds;

		public:
			int getTotalSeconds();
			
			int getSeconds();
			int getMinutes();
			int getHours();
			int getDays();

			string toStringDHMS();
			string toStringHMS();
			string toStringMS();

			static const int secondsPerMinute = 60;
			static const int minutesPerHour = 60;
			static const int hoursPerDay = 24;

			static const int secondsPerHour = secondsPerMinute * minutesPerHour;
			static const int secondsPerDay = secondsPerHour * hoursPerDay;

			shortTime operator+(shortTime & other);
			shortTime operator-(shortTime & other);
			shortTime operator*(shortTime & other);
			shortTime operator/(shortTime & other);

			void operator+=(shortTime & other);
			void operator-=(shortTime & other);
			void operator*=(shortTime & other);
			void operator/=(shortTime & other);

			bool operator==(shortTime & other);
			bool operator!=(shortTime & other);
			bool operator<(shortTime & other);
			bool operator<=(shortTime & other);
			bool operator>(shortTime & other);
			bool operator>=(shortTime & other);
		};

		enum day {
			monday,
			tuesday,
			wednesday,
			thursday,
			friday
		};

		enum month {
			january = 1,
			february = 2,
			march = 3,
			april = 4,
			may = 5,
			june = 6,
			july = 7,
			august = 8,
			september = 9,
			october = 10,
			november = 11,
			december = 12,
		};

		namespace geom	//As in geometry
		{
			class line
			{
			public:
				line(coord2 _slope = var::coord2(1, 1), coord2 _displacement = var::coord2(0, 0));
				line(coord2 _slope, coord2 _displacement, double _lowxBound, double _highxBound);
				line(coord2 _slope, coord2 _displacement, double _lowxBound, double _highxBound, double _lowyBound, double _highyBound);

				line(coord2 _slope, double _xDisplacement, double _yDisplacement);
				line(coord2 _slope, double _xDisplacement, double _yDisplacement, double _lowxBound, double _highxBound);
				line(coord2 _slope, double _xDisplacement, double _yDisplacement, double _lowxBound, double _highxBound, double _lowyBound, double _highyBound);

				line(double _slope, coord2 _displacement = var::coord2(0, 0));
				line(double _slope, coord2 _displacement, double _lowxBound, double _highxBound);
				line(double _slope, coord2 _displacement, double _lowxBound, double _highxBound, double _lowyBound, double _highyBound);

				line(double _slope, double _xDisplacement, double _yDisplacement);
				line(double _slope, double _xDisplacement, double _yDisplacement, double _lowxBound, double _highxBound);
				line(double _slope, double _xDisplacement, double _yDisplacement, double _lowxBound, double _highxBound, double _lowyBound, double _highyBound);

				coord2 slope;			//The slope of the line.  Duh.
				coord2 displacement;	//The displacement of the line from where it would be if it was calculated using only the slope
				bool xBounds;		//If the line has x boundaries
				double lowxBound;	//The lower x boundary of the line segment
				double highxBound;	//The upper x boundary of the line segment
				bool yBounds;		//If the line has y boundaries
				double lowyBound;	//The lower y boundary of the line segment
				double highyBound;	//The upper y boundary of the line segment

				int getSlopeSign();			//Returns 1 or -1, based on the sign of the slope (positive slope = 1, negative slope = -1).  Returns 0 if slope hasn't been set, or is 0, 0.  Horizontal or vertical lines are also considered positive.
				double getSlope();	//Returns the slope of the line, as a double (slope.y / slope.x)
				coord2 getSlopeCoord2();	//Returns the slope of the line, in x and y components

				bool setSlope(coord2 _slope);	//Sets the slope and preforms basic input validation
				bool setxBounds(double _lowxBound, double _highxBound);
				bool setyBounds(double _lowyBound, double _highyBound);

				double getY(double _x);		//Returns the y coordinate associated with _x (ignoring the bounds)
				vector<double> getY(vector<double> _x);		//Returns the y coordinates associated with the set of values in _x (ignoring the bounds)

				double getX(double _y);		//Returns the x coordinate associated with _y (ignoring the bounds)
				vector<double> getX(vector<double> _y);		//Returns the x coordinates associated with the set of values in _y (ignoring the bounds)

				vector<coord2> getValuesBetweenBounds(double _interval = 1);		//Returns a set of y values associated with x values, starting at 'lowBound' and increasing by '_interval', up until (and including) 'highBound'

				bool isCoordWithinBounds(coord2 _pos);		//Returns whether or not '_pos' is within the bounds of a segment. If no bounds are set, the point is within those bounds.

				bool hasIntercept(line _line);
				coord2 getIntercept(line _line);
				bool isInterceptWithinBounds(line _line);

				double getLengthBetween(double _x1, double _x2);		//Returns the length of the segment between _x1 and _x2, ignoring the bounds.
				double getLengthBetweenBounds();						//Returns the distance (length) of the line segment between the set bounds.  If the lines are infinite (no bounds are set, no y bounds and a vertical line, etc.), 0 is returned. 
				double getLengthToBounds(double _x, int _direction = 0);		//Returns the length of the line segment from _x to the boundary in _direction (only the sign of the argument is used.  1 would evalute the same as 10000).  If _direction is 0 (or not set) 1 is assumed.

				coord2 getCoordAtLength(coord2 _start, double _length);	//Returns the coordinate _length along the line from _start.  If _length is positive the coord to the right will be returned, if negative the coord to the left will be returned.

			};


			class square
			{
			public:
				square();
				square(coord2 _upperRight, coord2 _lowerLeft);
				square(double _leftX, double _rightX, double _bottomY, double _topY);

				double leftX = 0;	//The X coordinate of every point along the left side of the square
				double rightX = 0;	//The X coordinate of every point along the right side of the square
				double bottomY = 0;	//The Y coordinate of every point along the bottom of the square
				double topY = 0;		//The Y coordinate of every point along the top of the square

				coord2 getTopLeft();
				coord2 getTopRight();
				coord2 getBottomLeft();
				coord2 getBottomRight();
			};


			class circle
			{
			public:
				circle(coord2 _center, double _radius = 1);

				coord2 center;
				double radius;
			private:
				double A;
				double B;
				double C;
				double discriminant;

				void calculateQuad(line _line);
			public:

				bool setCenter(coord2 _center);
				bool setRadius(double _radius);

				coord2 getCenter();
				double getRadius();

				double getCircumference();
				double getArea();

				int getNumIntercepts(line _line);				//returns the number of intercept points the circle and the line passed to the function have.  (returns 0 if none, duh)
				vector<coord2> getIntercept(line _line);	//Returns the intercept point(s) of the circle and the line passed to the function, if any
			};
		};

	};
}