#pragma once

//Written by and copyright Zachary Damato
//windInfo.h is part of the zlib submodule

#ifdef ZLIB_USING_CINDER

#include<string>
#include<stdlib.h>
#include<vector>

#include "varTypes.h"

namespace zlib
{
	namespace window
	{
		void setDisplacement(var::coord2 _displacement);
		void incrimentDisplacement(double x, double y);
		void incrimentDisplacement(var::coord2 incriment);

		var::coord2 getDisplacement();				//Returns the displacement on the window in scale units
		var::coord2 getScaledDisplacement();		//Returns the displacement on the window in raw pixels

		void setScaleTotal(double _scaleTotal);
		double getScaleTotal();

		//void setZoom(double _zoom);					//Sets the zoom
		//void incrimentZoom(double _zoom);			//Adds _zoom to zoom

		void update();								//Updates the scaling based on the window size.  Call when the window resizes.

		double scaleX(double coord);
		double scaleY(double coord, bool yFlip = true);
		double unscaleX(double coord);
		double unscaleY(double coord, bool yFlip = true);
		var::coord2 scale(var::coord2 coord, bool yFlip = true);
		var::coord2 unscale(var::coord2 coord, bool yFlip = true);

		var::coord2 getRotation(float degrees, float xCoord, float yCoord, float rotPtX = 0, float rotPtY = 0);	//degrees = the degrees rotation (+ = ccw, - = cw), xCoord = the x coordinate of the point rotated, yCoord = the y coordinate of the point rotated, rotPtX = the x coordinate of the point that the point is rotated around, rotPtY = the y coordinate of the point that the point is rotated around
		var::coord2 getRotation(float degrees, var::coord2 rotationPointCoords, var::coord2 coords, bool debug = false);
	}
}
#endif