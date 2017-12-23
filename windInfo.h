#pragma once

//Written by and copyright Zachary Damato
//windInfo.h is part of the zlib submodule

#ifdef USING_CINDER

#include<string>
#include<stdlib.h>
#include<vector>

#include "varTypes.h"
namespace zlib
{
	namespace window
	{
		class windowObject
		{
			double scaleTotal = 100;				//The number of segments that the window is divided into (for scaling)
			double scaleMultiplier = 1;				//The same idea as zoom, but it is applied to all objects, static or not.  It's for scaling to window size
			//double zoom = 1;						//The level of zoom applied to all non-static objects

			float zoomRatio = 1;					//zoomRatio:1 - The ratio of zoom 1 = 1:1(no zoom), 2:1 - stuff is twice as big
			float dispCoordX = 0;
			float dispCoordY = 0;

			const float minZoom = 0.001;	//The minimum value for zoom, set to keep the zoom from getting too low

			enum windowScaleControllerType { scaleByX, scaleByY } windowScaleController;

		
			var::coord2 displacement = var::coord2(0, 0);				//The distance (in scaled units) between the lower-left point on the screen and the origin on the screen
			var::coord2 scaledDisplacement = var::coord2(0, 0);		//displacement, converted to pixel measurements;

			void updateScaledDisplacement();

		public:
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
		};
	}
}
#endif