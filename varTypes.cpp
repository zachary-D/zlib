#pragma once

//Written by and copyright Zachary Damato
//varTypes.cpp is part of the varTypes submodule

#include <string>

using namespace std;

#ifdef USING_CINDER
#include "cinder\Color.h"
#include "cinder\app\AppNative.h"
#endif

#ifdef USING_DEBUG
#include "debug.h"
#endif

#include "varTypes.h"
#include "varConv.h"

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
#ifdef USING_CINDER
	coord2::coord2(ci::Vec2i coordinate)
	{
		x = coordinate.x;
		y = coordinate.y;
	}

	coord2::coord2(ci::Vec2f coordinate)
	{
		x = coordinate.x;
		y = coordinate.y;
	}

	coord2::coord2(ci::Vec2d coordinate)
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

#ifdef USING_CINDER
	ci::Vec2i coord2::toVec2i()
	{
		return ci::Vec2i(x, y);
	}

	ci::Vec2f coord2::toVec2f()
	{
		return ci::Vec2f(x, y);
	}

	ci::Vec2d coord2::toVec2d()
	{
		return ci::Vec2d(x, y);
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
			_DEBUG_ERROR("Error determining quadrant.  Coordinates may be improperly defined.  Defaulting to 1");
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
		if(x == other.x && y == other.y && z == other.z) return true;
		else return false;
	}

#ifdef USING_CINDER
	ci::Vec3f coord3::toVec3f()
	{
		return ci::Vec3f(x, y, z);
	}
#endif




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

#ifdef USING_CINDER
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
			_DEBUG_ERROR("Unknown exception.  Returning 0.");
			return 0;
		}

		double line::getSlope()
		{
			if(slope.x != 0) return slope.y / slope.x;
			else
			{
				_DEBUG_ERROR("SLOPE = y / 0");
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
				_DEBUG_ERROR("Bad slope - slope cannot be 0 / 0.  Defaulting to 1.");
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
				_DEBUG_ERROR("Bad input, _lowxBound is equal to _highxBound.  Setting xboudns to false.");
				xBounds = false;
			}
			else
			{
				_DEBUG_ERROR("Unspecified error.  Setting xBounds to false.");
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
				_DEBUG_ERROR("Bad input, _lowyBound is equal to _highyBound.  Setting yboudns to false.");
				yBounds = false;
			}
			else
			{
				_DEBUG_ERROR("Unspecified error.  Setting yBounds to false.");
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
			else _DEBUG_ERROR("Bounds not set!");
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
				_DEBUG_ERROR("No intercept!");
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
	};




#ifdef USING_VARTYPES_CHEM
	namespace chem
	{
		element::element(bool autoFill)
		{
			if (autoFill)
			{
				protons = 1;
				lookupValues();
			}
		}

		element::element(int _protons, bool autoFill)
		{
			setProtons(_protons);
			if (autoFill)
			{
				lookupValues();
				inferValues();
			}
		}

		element::element(int _protons, float _neutrons, bool autoFill)
		{
			setProtons(_protons);
			setNeutrons(_neutrons);
			if (autoFill)
			{
				lookupValues();
				inferValues();
			}
		}

		element::element(int _protons, float _neutrons, int _electrons, bool autoFill)
		{
			setProtons(_protons);
			setNeutrons(_neutrons);
			setElectrons(_electrons);
			if (autoFill)
			{
				lookupValues();
				inferValues();
			}
		}

		element::element(int _protons, float _neutrons, int _electrons, float _atomicMass, bool autoFill)
		{
			setProtons(_protons);
			setNeutrons(_neutrons);
			setElectrons(_electrons);
			setAtomicMass(_atomicMass);
			if (autoFill)
			{
				lookupValues();
				inferValues();
			}
		}

		element::element(string _symbol, bool autoFill)
		{
			setName(symbol);
			if (autoFill)
			{
				lookupValues();
				inferValues();
			}
		}

		element::element(string _symbol, string _name, bool autoFill)
		{
			setName(_name);
			setSymbol(_symbol);
			if (autoFill)
			{
				lookupValues();
				inferValues();
			}
		}

		element::element(string _symbol, string _name, int _protons, float _neutrons, int _electrons, float _atomicMass)
		{
			setName(_name);
			setSymbol(_symbol);
			setProtons(_protons);
			setNeutrons(_neutrons);
			setElectrons(_electrons);
			setAtomicMass(_atomicMass);
		}

		bool element::setProtons(int _protons)
		{
			if (_protons <= 0)
			{
				_DEBUG_ERROR("Bad '_protons': Value cannot <= 0.");
				return false;
			}
			else
			{
				protons = _protons;
				protonsSet = true;
				return true;
			}
		}

		bool element::setNeutrons(float _neutrons)
		{
			if (_neutrons < 0)
			{
				_DEBUG_ERROR("Bad '_neutrons': Value cannot < 0.");
				return false;
			}
			else
			{
				neutrons = _neutrons;
				neutronsSet = true;
				return true;
			}
		}

		bool element::setElectrons(int _electrons)
		{
			if (_electrons < 0)
			{
				_DEBUG_ERROR("Bad '_electrons': Value cannot < 0.");
				return false;
			}
			else
			{
				electrons = _electrons;
				electronsSet = true;
				return true;
			}
		}

		bool element::setName(string _name)
		{
			if (_name.length() == 0)
			{
				_DEBUG_ERROR("Bad '_name': Value cannot be empty.");
				return false;
			}
			else
			{
				name = _name;
				nameSet = true;
				return true;
			}
		}

		bool element::setSymbol(string _symbol)
		{
			if (_symbol.length() <= 0 || _symbol.length() > 3)
			{
				_DEBUG_ERROR("Bad '_symbol': Value cannot <= 0 or > 3.");
				return false;
			}
			else
			{
				symbol = _symbol;
				symbolSet = true;
				return true;
			}
		}

		bool element::setAtomicMass(float _atomicMass)
		{
			if (_atomicMass <= 0)
			{
				_DEBUG_ERROR("Bad '_atomicMass': Value cannot <= 0.");
				return false;
			}
			else
			{
				atomicMass = _atomicMass;
				atomicMassSet = true;
				return true;
			}
		}

		bool element::setAtomicNumber(float _atomicNumber)
		{
			if (_atomicNumber <= 0)
			{
				_DEBUG_ERROR("Bad '_atomicNumber': Value cannot <= 0.");
				return false;
			}
			else if (protonsSet == true && neutronsSet == true)
			{
				if (_atomicNumber != protons + neutrons)
				{
					_DEBUG_ERROR("Bad '_atomicNumber': Value is in conflict with existing 'protons' and 'neutrons' value.");
					return false;
				}
				else
				{
					atomicNumber = _atomicNumber;
					atomicNumberSet = true;
					return true;
				}
			}
			else
			{
				atomicNumber = _atomicNumber;
				atomicNumberSet = true;
				return true;
			}
		}

		bool element::setCharge(int _charge)
		{
			charge = _charge;
			chargeSet = true;
			return true;
		}

		bool element::setDensity(float _density)
		{
			if (_density > 0)
			{
				density = _density;
				densitySet = true;
			}
			else return false;
		}

		bool element::isProtonsSet()
		{
			return protonsSet;
		}

		bool element::isNeutronsSet()
		{
			return neutronsSet;
		}

		bool element::isElectronsSet()
		{
			return electronsSet;
		}

		bool element::isNameSet()
		{
			return nameSet;
		}

		bool element::isSymbolSet()
		{
			return symbolSet;
		}

		bool element::isAtomicMassSet()
		{
			return atomicMassSet;
		}

		bool element::isAtomicNumberSet()
		{
			return atomicNumberSet;
		}

		bool element::isChargeSet()
		{
			return chargeSet;
		}

		bool element::isDensitySet()
		{
			return densitySet;
		}

		int element::getProtons()
		{
			if (protonsSet == false)
			{
				_DEBUG_ERROR("'protons' has not yet been set.\n Returning '1' in the place of 'protons'.  This may result in calculation errors.");
				return 1;
			}
			return protons;
		}

		float element::getNeutrons()
		{
			if (neutronsSet == false)
			{
				_DEBUG_ERROR("'neutrons'has not yet been set.\nReurning '1' in the place of 'neutrons'.  This may result in calculation errors.");
				return 1;
			}
			else return neutrons;
		}

		int element::getElectrons()
		{
			if (electronsSet == false)
			{
				_DEBUG_ERROR("'electrons' has not yet been set?\nReturning '1' in the place of 'electrons'.  This may result in calculation errors.");
				return 1;
			}
			else return electrons;
		}

		string element::getName()
		{
			if (nameSet == false)
			{
				_DEBUG_ERROR("'name' has not yet been set?\nReturning 'Err' in the place of 'name'.  This may result in errors.");
				return "Err";
			}
			else return name;
		}

		string element::getSymbol()
		{
			if (symbolSet == false)
			{
				_DEBUG_ERROR("'symbol' has not yet been set?\nReturning 'Er' in the place off 'name'.  This may result in errors.");
				return "Er";
			}
			else return symbol;
		}

		float element::getAtomicMass()
		{
			if (atomicMassSet == false)
			{
				_DEBUG_ERROR("'atomicMass' has not yet been set?\nReturning 1 in the place of 'atomicMass'.  This may result in calculation errors.");
				return 1;
			}
			else return atomicMass;
		}

		float element::getAtomicNumber()
		{
			if (atomicNumberSet == false)
			{
				_DEBUG_ERROR("'atomicNumber' has not yet been set?\nReturning 1 in the place of 'atomicMass'.  This may result in calculation errors.");
				return 1;
			}
			else return atomicNumber;
		}

		int element::getCharge()
		{
			if (chargeSet == false)
			{
				_DEBUG_ERROR("'charge' has not yet been set?\nReturning 1 in the place of 'charge'.  THis may result in calculation errors.");
				return 1;
			}
			else return charge;
		}

		float element::getDensity()
		{
			if (isDensitySet()) return density;
			else
			{
				_DEBUG_ERROR("'desity' has not been set.\nReturning '1' in the place of 'mass'.  This may result in errors.");
				return 1;
			}
		}

		bool element::inferValues()
		{
			bool change = false;		//If the current cycle has calculated any values
			bool anyChanges = false;	//If there were any changes at all
			do
			{
				change = false;
				if (protonsSet == false)			//Calculating protons
				{
					if (electronsSet == true && chargeSet == true)
					{
						setProtons(charge + electrons);
						change = true;
					}
					else if (atomicNumberSet == true && neutronsSet == true && fmod(neutrons, 1) != 0)
					{
						setProtons(atomicNumber - neutrons);
						change = true;
					}
				}
				if (neutronsSet == false)		//Calculating neutrons
				{
					if (atomicNumberSet == true && protonsSet == true)
					{
						setNeutrons(atomicNumber - protons);
						change = true;
					}
				}
				if (electronsSet == false)		//Calculating electrons
				{
					if (protonsSet == true && chargeSet == true)
					{
						setElectrons(protons - charge);
						change = true;
					}
				}
				if (atomicNumberSet == false)	//Calculating atomicNumber
				{
					if (protonsSet == true && neutronsSet == true)
					{
						setAtomicNumber(protons + neutrons);
						change = true;
					}
				}
				if (chargeSet == false)			//Calculating charge
				{
					if (protonsSet == true && electronsSet == true)
					{
						setCharge(protons - electrons);
						change = true;
					}
				}
				if (change) anyChanges = true;
			} while (change);
			return anyChanges;
		}

		bool element::lookupValues()
		{
			_DEBUG_ERROR("We haven't made the periodic table yet sooooo...");
			return false;
		}

		string element::toString(bool multiLine)
		{
			string separator = " | ";
			if (multiLine) separator = "\n";
			string output = "";

			output.append("Name:");
			if (nameSet) output.append(name);
			else output.append("Not set");
			output.append(separator);

			output.append("Symbol:");
			if (symbolSet) output.append(symbol);
			else output.append("Not set");
			output.append(separator);

			output.append("Protons:");
			if (protonsSet) output.append(conv::toString(getProtons()));
			else output.append("Not set");
			output.append(separator);

			output.append("Neutrons:");
			if (neutronsSet)	output.append(conv::toString(getNeutrons()));
			else output.append("Not set");
			output.append(separator);

			output.append("Electrons:");
			if (electronsSet) output.append(conv::toString(getElectrons()));
			else output.append("Not set");
			output.append(separator);

			output.append("Charge:");
			if (chargeSet) output.append(conv::toString(getCharge()));
			else output.append("Not set");
			output.append(separator);

			output.append("Atomic Mass:");
			if (atomicMassSet) output.append(conv::toString(getAtomicMass()));
			else output.append("Not set");
			output.append(separator);

			output.append("Atomic Number:");
			if (atomicNumberSet) output.append(conv::toString(getAtomicNumber()));
			else output.append("Not set");

			return output;
		}

		compound::compound(bool _isElement)
		{
			isElement = _isElement;
			isSegment = !_isElement;
		}

		compound::compound(element _element)
		{
			setElement(_element);
			isElement = true;
			isSegment = false;
		}

		compound::compound(element _element, int _subscript)
		{
			setElement(_element);
			setSubscript(_subscript);
			isElement = true;
			isSegment = false;
		}

		compound::compound(element _element, int _subscript, int _amount)
		{
			setElement(_element);
			setSubscript(_subscript);
			setAmount(_amount);
			isElement = true;
			isSegment = false;
		}

		compound::compound(vector<compound> _segments)
		{
			setSegments(_segments);
			isSegment = true;
			isElement = false;
		}

		bool compound::getIsElement()
		{
			return isElement;
		}

		bool compound::getIsSegment()
		{
			return isSegment;
		}

		bool compound::setSegments(vector<compound> _segments)
		{
			if (getIsSegment())
			{
				segments = _segments;
				return true;
			}
			else
			{
				_DEBUG_ERROR("Unable to set 'segments', segment is initialized as an element.");
				return false;
			}
		}

		bool compound::addSegment(compound _segment)
		{
			if (getIsSegment())
			{
				segments.push_back(_segment);
				return true;
			}
			else
			{
				_DEBUG_ERROR("Unable to set 'segments', segment is initialized as an element.");
				return false;
			}
		}

		bool compound::removeSegment(int _segmentID)
		{
			if (segments.size() < _segmentID)
			{
				return false;
			}
			else
			{
				segments.erase(segments.begin() + _segmentID);
				return true;
			}
		}

		bool compound::setElement(element _element)
		{
			if (getIsElement())
			{
				elementVal = _element;
				elementSet = true;
				return true;
			}
			else
			{
				_DEBUG_ERROR("Unable to set 'element', compond is initialized as a sub-compound.");
				return false;
			}
		}

		bool compound::setSubscript(int _subscript)
		{
			if (getIsElement())
			{
				if (_subscript <= 0)
				{
					_DEBUG_ERROR("Bad '_subscript': Value cannot <= 0.");
					return false;
				}
				else
				{
					subscript = _subscript;
					subscriptSet = true;
					return true;
				}
			}
			else
			{
				_DEBUG_ERROR("Unable to set 'subscript', segment is initialized as a sub-segment.");
				return false;
			}
		}

		bool compound::setAmount(int _amount)
		{
			if (_amount <= 0)
			{
				_DEBUG_ERROR("Bad '_amount': Value cannot be <= 0.");
				return false;
			}
			else
			{
				amount = _amount;
				amountSet = true;
				return true;
			}
		}

		bool compound::setName(string _name)
		{
			if (_name.length() == 0) return false;
			else
			{
				name = _name;
				nameSet = true;
				return true;
			}
		}

		bool compound::setAtomicMass(float _atomicMass)
		{
			if (_atomicMass <= 0) return false;
			else
			{
				atomicMass = _atomicMass;
				return true;
			}
		}

		bool compound::setCharge(int _charge)
		{
			charge = _charge;
			return false;
		}

		bool compound::setMass(float grams)
		{
			if (grams <= 0) return false;
			else
			{
				mass = grams;
				massSet = true;
			}
		}

		bool compound::setMols(float _mols)
		{
			if (_mols <= 0) return false;
			else
			{
				mols = _mols;
				molsSet = true;
			}
		}

		bool compound::isElementSet()
		{
			return elementSet;
		}

		bool compound::isSubscriptSet()
		{
			return subscriptSet;
		}

		bool compound::isAmountSet()
		{
			return amountSet;
		}

		bool compound::isNameSet()
		{
			return nameSet;
		}

		bool compound::isAtomicMassSet()
		{
			return atomicMassSet;
		}

		bool compound::isChargeSet()
		{
			return chargeSet;
		}

		bool compound::isMassSet()
		{
			return massSet;
		}

		bool compound::isMolsSet()
		{
			return molsSet;
		}

		vector<compound> compound::getSegments()
		{

			return segments;
		}

		element compound::getElement()
		{
			if (isElementSet() == false)
			{
				_DEBUG_ERROR("'elements' has not yet been set.\nReturning a blank element template in the place off 'element'.  This may result in errors.");
				return element();
			}
			else return elementVal;
		}

		int compound::getSubscript()
		{
			if (isSubscriptSet() == false)
			{
				_DEBUG_ERROR("'subscript' has not yet been set.\nReturning '1' in the place of 'subscript'.  This may result in errors.");
				return 1;
			}
			else return subscript;
		}

		int compound::getAmount()
		{
			if (isAmountSet() == false)
			{
				_DEBUG_ERROR("'amount' has not been set.\nReturning '1' in the place of 'amount'.  This may result in errors.");
				return 1;
			}
			else return amount;
		}

		string compound::getName()
		{
			if (isNameSet() == false)
			{
				_DEBUG_ERROR("'amount' has not been set.\nReturning 'Err' in the place of 'name'.  This may result in errors.");
				return "Err";
			}
			else return name;
		}

		float compound::getAtomicMass()
		{
			if (isAtomicMassSet() == false)
			{
				_DEBUG_ERROR("'amount' has not been set.\nReturning '1' in the place of 'atomicMass'.  This may result in errors.");
				return 1;
			}
			else return atomicMass;
		}

		int compound::getCharge()
		{
			if (isChargeSet() == false)
			{
				_DEBUG_ERROR("'charge' has not been set.\nReturning '1' in the place of 'charge'.  This may result in errors.");
				return 1;
			}
			else return charge;
		}
		float compound::getMass()
		{
			if (isMassSet() == false)
			{
				_DEBUG_ERROR("'mass' has not been set.\nReturning '1' in the place of 'mass'.  This may result in errors.");
				return 1;
			}
			else return mass;
		}

		float compound::getMols()
		{
			if (isMolsSet() == false)
			{
				_DEBUG_ERROR("'mols' has not been set.\nReturning '1' in the place of 'mols'.  This may result in errors.");
				return 1;
			}
			else return mols;
		}

		bool compound::calculateValues()
		{
			bool totalChange = false;
			bool localChange = false;
			do
			{
				if (getIsElement())			//Calulating traits that can be found as a sum of element properties
				{
					if (elementVal.inferValues()) localChange = true;
					if (isAtomicMassSet() == false && elementVal.isAtomicMassSet() == true)
					{
						setAtomicMass(elementVal.getAtomicMass());
						localChange = true;
					}
					if (isChargeSet() == false && elementVal.isChargeSet() == true)
					{
						setCharge(elementVal.getCharge());
						localChange = true;

					}
					else if (getIsSegment())		//Calulating traits that can be found as a sum of segment properties
					{
						bool canSetAtomicMass = true;
						bool canSetCharge = true;
						int charge = 0;
						float atomicMass = 0;
						for (int x = 0; x < segments.size(); x++)
						{
							if (segments[x].calculateValues()) localChange = true;
							if (isAtomicMassSet() == false)
							{
								if (segments[x].isAtomicMassSet()) atomicMass += segments[x].getAtomicMass();
								else canSetAtomicMass = false;
							}
							else canSetAtomicMass = false;
							if (isChargeSet() == false)
							{
								if (segments[x].isChargeSet()) charge += segments[x].getCharge();
								else canSetCharge = false;
							}
							else canSetCharge = false;
						}
						if (canSetAtomicMass)
						{
							setAtomicMass(atomicMass);
							localChange = true;
						}
						if (canSetCharge)
						{
							setCharge(charge);
							localChange = true;
						}
					}
					if (isAtomicMassSet() == false)		//Calculating atomic mass
					{
						if (isMolsSet() == true && isMassSet() == true)		//From mass and mols
						{
							if (getMass() / getMols() > 0)		//Verifys that the calculated value is valid
							{
								setAtomicMass(getMass() / getMols());
								localChange = true;
							}
							else _DEBUG_ERROR("Calculated atomic mass is <= 0!  Either the mass or mols is incorrect, if not both!");
						}
					}
					if (isMassSet() == false)		//Calculating mass
					{
						if (isMolsSet() == true && isAtomicMassSet() == true)	//From mols and atomic mass
						{
							if (getMols() * getAtomicMass() > 0)		//Verifys that the calculated value is valid
							{
								setMass(getMols() * getAtomicMass());
								localChange = true;
							}
							else _DEBUG_ERROR("Calculated mass is <= 0!  Either the mols or the atomic mass is incorrect, if not both!");
						}
					}
					if (isMolsSet() == false)		//Calculating mols
					{
						if (isAtomicMassSet() == true && isMassSet() == true)	//From atomicMass and mass
						{
							if (getMass() / getAtomicMass() > 0)		//Verifys that the calculated value is valid
							{
								setMols(getMass() / getAtomicMass());
								localChange == true;
							}
							else _DEBUG_ERROR("Calculated mols is <= 0!  Either the mass or atomic mass is incorrect, if not both!");
						}
					}
					if (localChange) totalChange = true;
				}
				while (localChange);
				return totalChange;
			}
		}
#endif
};