#pragma once
#define _USE_MATH_DEFINES

//Written by and copyright Zachary Damato
//varTypes.h is part of the varTypes submodule

//Preprocessor directives for enabling different code sections
//		Directive				Description
//		USING_CINDER			Enables Cinder-exclusive functions (i.e. conversion from internal color type to Cinder's color type)
//		USING_VARTYPES_CHEM		Enables chemistry based variables and functions (Very much incomplete)

#include <string>
#include <vector>

using std::string;
using std::vector;

#ifdef USING_CINDER
#include "cinder\Color.h"
#include "cinder\app\AppNative.h"
#include "cinder/Text.h"
#include "cinder/app/App.h"
#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/ImageIo.h"
#include "cinder/app/window.h"
#include "cinder/gl/gl.h"
#endif
		
//Note: Unless otherwise specified, all angles are assumed to be in degrees

namespace var
{
	class mVector;	//Forward declaration

	class coord2
	{
	public:
		coord2();
		coord2(double X, double Y);
#ifdef USING_CINDER
		coord2(ci::Vec2i coordinate);
		coord2(ci::Vec2f coordinate);
		coord2(ci::Vec2d coordinate);
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

	#ifdef USING_CINDER
		ci::Vec2i toVec2i();
		ci::Vec2f toVec2f();
		ci::Vec2d toVec2d();
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

	#ifdef USING_CINDER
		ci::Vec3f toVec3f();
	#endif
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

	#ifdef USING_CINDER
		ci::Color toColor();			//BEING REMOVED.  use toCinderColor() istead
		ci::Color toCinderColor();		//Returns the color in Cinder's format, without opacity
		ci::ColorA toCinderColorA();	//Returns the color in Cinder's format, with opacity
	#endif
	};

	namespace math
	{
		const double pi = 4 * atan(1);
	}

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

#ifdef USING_VARTYPES_CHEM
	namespace chem
	{
		class element
		{
		public:
			//For all of these functions, if autoFill == true data will attempt to be sourced from the periodic table, and then any remaining information will be attempted to be calculated.  If false, any values not explicitly stated will be left null
			element(bool autoFill = false);		//If autoFill == true, autofills with protons = 1
			element(int _protons, bool autoFill = true);	//Creates a instance with _protons
			element(int _protons, float _neutrons, bool autoFill = true);
			element(int _protons, float _neutrons, int _electrons, bool autoFill = true);
			element(int _protons, float _neutrons, int _electrons, float _atomicMass, bool autoFill = true);
			element(string _symbol, bool autoFill = true);
			element(string _symbol, string _name, bool autoFill = true);
			element(string _symbol, string _name, int _protons, float _neutrons, int _electrons, float _atomicMass);

		private:
			int protons;				//The number of protons in the element
			bool protonsSet = false;	//If the value of protons has been set
			float neutrons;				//The number of neutrons in the element
			bool neutronsSet = false;	//If the value of neutrons has been set
			int electrons;				//The number of electron in (technically around) the element
			bool electronsSet = false;	//If the value of electrons has been set
			string name;				//The name of the element
			bool nameSet = false;		//If the name has been set
			string symbol;				//The atomic symbol of the element
			bool symbolSet = false;		//If the symbol has been set
			float atomicMass;			//The atomic mass of the element
			bool atomicMassSet = false;	//If the value of atomicMass has been set
			float atomicNumber;			//The atomic number of the element (technically the average of the isotopes)
			bool atomicNumberSet = false;	//If the value of atomicNumber has been set
			int charge;					//The charge of the element
			bool chargeSet = false;		//If the value of charge has been set;
			float density;				//The density of the element (at STP, in g/L)
			bool densitySet = false;	//If the value of the density has been set

		public:
			//Setting values
			bool setProtons(int _protons);		//Sets the number of protons in the element
			bool setNeutrons(float _neutrons);	//Sets the number of neutrons in the element
			bool setElectrons(int _electrons);	//Sets the number of electrons in the element
			bool setName(string _name);			//Sets the name of the element
			bool setSymbol(string _symbol);		//Sets the symbol of the element
			bool setAtomicMass(float _atomicMass);	//Sets the atomic mass of the element
			bool setAtomicNumber(float _atomicNumber);	//Sets the atomic number of the element
			bool setCharge(int _charge);		//Sets the charge of the element
			bool setDensity(float _density);	//Sets the density of the element

			//Returning if values are defined.
			bool isProtonsSet();		//Returns if the value of 'protons' is set
			bool isNeutronsSet();		//Returns if the value of 'neutrons' is set
			bool isElectronsSet();		//Returns if the value of 'electrons' is set
			bool isNameSet();			//Returns if the value of 'name' is set
			bool isSymbolSet();			//Returns if the value of 'symbol' is set
			bool isAtomicMassSet();		//Returns if the value of 'atomicMass' is set
			bool isAtomicNumberSet();	//Returns if the value of 'atomicNumber' is set
			bool isChargeSet();			//Returns if the value of 'charge' is set
			bool isDensitySet();		//Returns if the value of 'density' is set

			//Returning values
			int getProtons();			//Returns the number of protons in the element
			float getNeutrons();		//Returns the number of neutrons in the element
			int getElectrons();			//Returns the number of electrons in the element
			string getName();			//Returns the name of the element
			string getSymbol();			//Returns the atomic symbol of the element
			float getAtomicMass();		//Returns the atomic mass of the element
			float getAtomicNumber();	//Returns the atomic number of the element
			int getCharge();			//The charge on the atom.  Not available for atoms with averaged neutrons (Will throw an error if this situation arises).
			float getDensity();			//Returns the density of the element (in Liters)

			//Other
			bool inferValues();			//Attempts to calculate all values possible from included information (i.e. protons from electrons and charge, etc.)
			bool lookupValues();		//Tries to autofill values from the periodic table, if it is loaded.
			string toString(bool multiLine = false);	//Converts all data from the element into a string.
		};

		class compound
		{
		public:
			compound(bool isElement = true);	//If true, initializes as an element.  If false, sets as a vector of compounds.
			compound(element _element);
			compound(element _element, int _subscript);
			compound(element _element, int _subscript, int _amount);
			compound(vector<compound> _segments);
			compound(vector<compound> _segments, int _amount);

		private:
			//Vector<sub> specific values
			bool isSegment;
			vector<compound> segments;

			//Element specific values
			bool isElement;
			element elementVal;		//The element.  The trailing 'Val' is to distinguish it from the element class
			bool elementSet = false;
			int subscript;			//The subscript on the element
			bool subscriptSet = false;	//If the value of 'subscript' has been set
			
			//Shared values
			int amount;				//The amount on the compound (i.e. the 2 in (NO_3)_2 )
			bool amountSet = false;	//If the value of 'amount' has been set
			string name;			//The element's name
			bool nameSet = false;	//If the value of 'name' has been set
			float atomicMass;		//The atomic mass of the segment (taking the subscript into account, but not the amount.)
			bool atomicMassSet = false;	//If the value of 'atomicMass' has been set
			int charge;				//The charge of the compound (taking the subscript into account, but not the amount.)
			bool chargeSet = false;	//If the value of 'charge' has been set
			float mass;				//The mass of the compound (in grams)
			bool massSet = false;	//If the value of 'mass' has been set
			float mols;				//The number of moles of the compound
			bool molsSet = false;	//If the value of 'mols' has been set

		public:
			//Returning type
			bool getIsElement();		//Returns if the type is element
			bool getIsSegment();		//Returns if the type is segment

			//Setting values - Segment specific values
			bool setSegments(vector<compound> _segments);	//Sets the segments
			bool addSegment(compound _segment);		//Adds the segment to the end
			bool removeSegment(int _segmentID);		//Removes the segment at '_segmentID'

			//Setting values - Element specific values
			bool setElement(element _element);	//Sets the element
			bool setSubscript(int _subscript);		//Sets the subscript

			//Setting values - Shared values
			bool setAmount(int _amount);			//Sets the amount
			bool setName(string _name);				//Sets the name
			bool setAtomicMass(float _atomicMass);	//Sets the atomicMass
			bool setCharge(int _charge);			//Sets the charge
			bool setMass(float grams);				//Sets the mass
			bool setMols(float _mols);				//Sets the mols

			//Returning if values are defined
			bool isElementSet();		//Returns if the value of 'element' is set
			bool isSubscriptSet();		//Returns if the value of 'subscript' is set
			bool isAmountSet();			//Returns if the value of 'amount' is set
			bool isNameSet();			//Returns if the value of 'name' is set
			bool isAtomicMassSet();		//Returns if the value of 'atomicMass' is set
			bool isChargeSet();			//Returns if the value of 'charge' is set
			bool isMassSet();			//Returns if the value of 'mass' is set
			bool isMolsSet();			//Returns if the value of 'mols' is set

			//Retreving values - Segment specific values
			vector<compound> getSegments();		//Returns the value segments

			//Retreving values - Element specific values
			element getElement();		//Returns the element
			int getSubscript();			//Returns the subscript

			//Retreving values - Shared values
			int getAmount();			//Returns the amount
			string getName();			//Returns the name
			float getAtomicMass();		//Returns the atomicMass
			int getCharge();			//Returns the charge
			float getMass();			//Returns the mass
			float getMols();			//Returns the mols

			//Data functions
			bool calculateValues();		//claulates every value possible based of existing values
		};
	};
#endif
};