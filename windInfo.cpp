#pragma once

//Written by and copyright Zachary Damato
//windInfo.cpp is part of the zlib submodule

#ifdef ZLIB_USING_CINDER
#define _USE_MATH_DEFINES

#include<iostream>
#include<sstream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<algorithm>
#include<windows.h>
#include<vector>
#include<new>

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/app/App.h"
#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/ImageIo.h"
#include "cinder/app/window.h"

#include "var.h"
#include "windInfo.h"

using namespace std;
using namespace ci;
using namespace ci::app;

using namespace zlib;

namespace zlib
{
	namespace window
	{
		double scaleTotal = 100;				//The number of segments that the window is divided into (for scaling)
		double scaleMultiplier = 1;				//The same idea as zoom, but it is applied to all objects, static or not.  It's for scaling to window size
		//double zoom = 1;						//The level of zoom applied to all non-static objects

		float zoomRatio = 1;					//zoomRatio:1 - The ratio of zoom 1 = 1:1(no zoom), 2:1 - stuff is twice as big
		float dispCoordX = 0;
		float dispCoordY = 0;

		const float minZoom = 0.001;	//The minimum value for zoom, set to keep the zoom from getting too low

		enum windowScaleControllerType { scaleByX, scaleByY } windowScaleController;

		var::coord2 displacement(0, 0);				//The distance (in scaled units) between the lower-left point on the screen and the origin on the screen
		var::coord2 scaledDisplacement(0, 0);		//displacement, converted to pixel measurements;

		void setScaleTotal(double _scaleTotal)
		{
			if(_scaleTotal <= 0) throw "_scaleTotal cannot be less than or equal to 0";
			else scaleTotal = _scaleTotal;
		}

		double getScaleTotal() { return scaleTotal; }

		void updateScaledDisplacement()
		{
			scaledDisplacement = window::scale(displacement, false).negatedY();
		}

		void setDisplacement(var::coord2 _displacement)
		{
			displacement = _displacement;
			updateScaledDisplacement();
		}

		void incrimentDisplacement(double x, double y)
		{
			displacement += var::coord2(x, y);
			updateScaledDisplacement();
		}

		void incrimentDisplacement(var::coord2 incriment)
		{
			displacement += incriment;
			updateScaledDisplacement();
		}

		var::coord2 getDisplacement() { return displacement; }
		var::coord2 getScaledDisplacement() { return scaledDisplacement; }


		/*void setZoom(double _zoom)
		{
			//Ensures that the zoom doesn't get extremley low
			if (_zoom > minZoom) zoom = _zoom;
		}

		void incrimentZoom(double incriment)
		{
			//Ensures that the zoom doesn't get extremley low
			if (zoom + incriment > minZoom) zoom += incriment;
		}*/


		void update()
		{
			if(windowScaleController == scaleByX) scaleMultiplier = getWindowWidth() / scaleTotal;
			else if(windowScaleController == scaleByY) scaleMultiplier = getWindowHeight() / scaleTotal;
			else {	//If the axis controlling the scale hasn't been set, default it to X
				windowScaleController = scaleByX;
				scaleMultiplier = getWindowWidth() / scaleTotal;
			}
			updateScaledDisplacement();
		}


		double scaleX(double coord)
		{
			return coord * scaleMultiplier;
		}

		double scaleY(double coord, bool yFlip)
		{
			double ret = coord * scaleMultiplier;
			if(yFlip == true) ret = getWindowHeight() - ret;
			return ret;
		}

		double unscaleX(double coord)
		{
			return coord / scaleMultiplier;
		}

		double unscaleY(double coord, bool yFlip)
		{
			double ret = coord;
			if(yFlip) ret = getWindowHeight() - coord;
			return ret / scaleMultiplier;
		}

		var::coord2 scale(var::coord2 coord, bool yFlip)
		{
			return var::coord2(scaleX(coord.x), scaleY(coord.y, yFlip));
		}

		var::coord2 unscale(var::coord2 coord, bool yFlip)
		{
			return(var::coord2(unscaleX(coord.x), unscaleY(coord.y, yFlip)));
		}

		var::coord2 getRotation(float degrees, float xCoord, float yCoord, float rotPtX, float rotPtY)	//degrees = the degrees rotation (+ = ccw, - = cw), xCoord = the x coordinate of the point rotated, yCoord = the y coordinate of the point rotated, rotPtX = the x coordinate of the point that the point is rotated around, rotPtY = the y coordinate of the point that the point is rotated around
		{
			if(degrees == 0) return var::coord2(xCoord, yCoord);
			float theta = -1 * toDegrees(atan((yCoord - rotPtY) / (xCoord - rotPtX)));
			if(xCoord == rotPtX) theta = 0;
			float thetaPrime = theta - degrees;
			float dist = sqrt(pow(xCoord - rotPtX, 2) + pow(yCoord - rotPtY, 2));
			//app::console() << "dist: " << dist << endl;
			return var::coord2((dist * cos(toRadians(thetaPrime)) + rotPtX), (dist * sin(toRadians(thetaPrime)) + rotPtY));
		}

		var::coord2 getRotation(float degrees, var::coord2 rotationPointCoords, var::coord2 coords, bool debug)
		{
			//if(degrees == 0) return coords;
			if(debug == true) app::console() << "rotPT " << rotationPointCoords.toString() << endl;
			if(debug == true) app::console() << "coords " << coords.toString() << endl;
			float theta = //-1 * 
				toDegrees(atan((coords.y - rotationPointCoords.y) / (coords.x - rotationPointCoords.x)));
			if(debug == true) app::console() << "theta1 " << theta << endl;
			if(coords.x == rotationPointCoords.x)
			{
				if(debug == true) app::console() << "specialC" << endl;
				if(coords.y > rotationPointCoords.y) theta = 90;
				else theta = 270;
			}
			else if(coords.y == rotationPointCoords.y)
			{
				if(debug == true) app::console() << "specialC" << endl;
				if(coords.x > rotationPointCoords.x) theta = 0;
				else theta = 180;
			}
			else
			{
				if(coords.x < rotationPointCoords.x) theta = theta + 180;
				else if(coords.y < rotationPointCoords.y) theta = 360 + theta;
			}
			if(debug == true) app::console() << "theta2 " << theta << endl;
			float thetaPrime = theta - degrees;
			if(debug == true) app::console() << "thetaPrime " << thetaPrime << endl;
			//float dist = sqrt(pow(coords.x - rotationPointCoords.x, 2) + pow(coords.y - rotationPointCoords.y, 2));
			float dist = sqrt(pow(coords.x - rotationPointCoords.x, 2) + pow(coords.y - rotationPointCoords.y, 2));
			if(debug == true) app::console() << "dist: " << dist << endl;
			if(debug == true) app::console() << "ret " << var::coord2((dist * cos(toRadians(thetaPrime))) + rotationPointCoords.x, (dist * sin(toRadians(thetaPrime))) + rotationPointCoords.y).toString() << endl << "-- -- --" << endl;
			if(debug == true) gl::drawStrokedCircle(glm::highp_vec2(
				scaleX((dist * cos(toRadians(thetaPrime))) + rotationPointCoords.x),
				scaleY((dist * sin(toRadians(thetaPrime))) + rotationPointCoords.y)
			)
				, 10, 7);
			//if(debug == true) Sleep(250);
			//Error somewhere to do with dist * cos(...) + rotPtC.x
			return var::coord2(
				(
				dist * cos(
				toRadians(
				thetaPrime
			)
			)
			) + rotationPointCoords.x
				,
				(dist * sin(toRadians(thetaPrime))) + rotationPointCoords.y);
		}
	}
}
#endif