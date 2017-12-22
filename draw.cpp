#pragma once

//Written by and copyright Zachary Damato
//draw.cpp is part of the zlib submodule

#ifdef USING_CINDER

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

using namespace std;


#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Text.h"
#include "cinder/app/App.h"
#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/ImageIo.h"
#include "cinder/app/window.h"
#include "cinder/Color.h"

using namespace ci;
using namespace ci::app;

#ifdef MODULE_HUD
#include "HUD.h"
#endif

#include "varConv.h"
#include "varTypes.h"
#include "windInfo.h"

using namespace zlib;

namespace zlib
{
	namespace draw
	{
		void drawStaticTexture(gl::Texture _texture, var::coord2 _pointA, var::coord2 _pointB, var::coord2 _rotPt, float _rotation, bool _avgRotation, bool _preScaled, bool ignoreZoom)
		{
			gl::color(Color(1, 1, 1));	//sets the color to (1, 1, 1) so that the texture appears properly.
			if(_avgRotation == true)
			{
				_rotPt = (_pointA + _pointB) / 2;
			}
			if(_preScaled == false)
			{
				_rotPt = window::scale(_rotPt, true);
				_pointA = window::scale(_pointA, true);
				_pointB = window::scale(_pointB, true);
			}
			gl::translate(_rotPt.x, _rotPt.y);
			if(_rotation != 0)
			{
				gl::rotate(-_rotation);
			}
			gl::draw(_texture, Area(_pointA.x - _rotPt.x, _pointA.y - _rotPt.y, _pointB.x - _rotPt.x, _pointB.y - _rotPt.y));
			if(_rotation != 0)
			{
				gl::rotate(_rotation);
			}
			gl::translate((-_rotPt.x), (-_rotPt.y));
		}

		void drawTexture(gl::Texture _texture, var::coord2 _pointA, var::coord2 _pointB, var::coord2 _rotPt, float _rotation, bool _avgRotation, bool _preScaled)
		{
			var::coord2 displacement = (_preScaled) ? window::getScaledDisplacement() : window::getDisplacement();
			drawStaticTexture(_texture, _pointA + displacement, _pointB + displacement, _rotPt + displacement, _rotation, _avgRotation, _preScaled, false);
		}



		void drawStaticRect(var::coord2 pointA, var::coord2 pointB, var::coord2 rotPt, float rotation, bool avgRotation, bool preScaled, var::color_RGB color, bool ignoreZoom)
		{
			//app::console() << localDisplacement.toString() << endl;
			if(avgRotation == true)	//Rotates the rectangle about it's center if true
			{
				rotPt = (pointA + pointB) / 2;
			}
			if(preScaled == false)	//Gets the scaled versions of the coordinates (converting to the absolute coordinates of a pixel, from a coordinate relative to the size of the screen)
			{
				rotPt = window::scale(rotPt, true);
				pointA = window::scale(pointA, true);
				pointB = window::scale(pointB, true);
			}

			if(color.isDefined())
			{
				if(color.isOpacityDefined()) gl::color(color.toCinderColorA());
				else gl::color(color.toCinderColor());
			}

			//app::console() << (localDisplacement + rotPt).toString() << endl;

			gl::translate(rotPt.toVec2f());	//Translates the screen so that the point of rotation is at 0, 0 (pixel coordinates)
			if(rotation != 0)					//Rotates the screen to the specified amount, if the amount is non-zero
			{
				gl::rotate(-rotation);
			}
			gl::drawSolidRect(Rectf(pointA.x - rotPt.x, pointA.y - rotPt.y, pointB.x - rotPt.x, pointB.y - rotPt.y));	//Draws the rectangle
			if(rotation != 0)					//Rotates the screen back so that the screen is now level, leaving the rectangle rotated to the specified angle, if the amount is non-zero
			{
				gl::rotate(rotation);
			}
			//app::console() << (localDisplacement - rotPt).toString() << endl;
			gl::translate(-rotPt.toVec2f());	//Translates the screen back so that the origin is in the correct place again (undoes the above translation)
			//app::console() << "== == == ==" << endl;
		}

		void drawRect(var::coord2 pointA, var::coord2 pointB, var::coord2 rotPt, float rotation, bool avgRotation, bool preScaled, var::color_RGB color)
		{
			var::coord2 displacement = (preScaled) ? window::getScaledDisplacement() : window::getDisplacement();
			drawStaticRect(pointA + displacement, pointB + displacement, rotPt + displacement, rotation, avgRotation, preScaled, color, false);
		}



		void drawStaticStrokedRect(var::coord2 pointA, var::coord2 pointB, var::coord2 rotPt, float rotation, bool avgRotation, bool preScaled, var::color_RGB color)
		{
			if(avgRotation == true)	//Rotates the rectangle about it's center if true
			{
				rotPt = (pointA + pointB) / 2;
			}
			if(preScaled == false)	//Gets the scaled versions of the coordinates (converting to the absolute coordinates of a pixel, from a coordinate relative to the size of the screen)
			{
				rotPt = window::scale(rotPt);
				pointA = window::scale(pointA);
				pointB = window::scale(pointB);
			}
			//Sets the color and opacity, if applicable
			if(color.isDefined())
			{
				if(color.isOpacityDefined()) gl::color(color.toCinderColorA());
				else gl::color(color.toCinderColor());
			}

			gl::translate(rotPt.x, rotPt.y);	//Translates the screen so that the point of rotation is at 0, 0 (pixel coordinates)
			if(rotation != 0)					//Rotates the screen to the specified amount, if the amount is non-zero
			{
				gl::rotate(-rotation);
			}

			gl::drawStrokedRect(Rectf(pointA.x - rotPt.x, pointA.y - rotPt.y, pointB.x - rotPt.x, pointB.y - rotPt.y));	//Draws the rectangle

			if(rotation != 0)					//Rotates the screen back so that the screen is now level, leaving the rectangle rotated to the specified angle, if the amount is non-zero
			{
				gl::rotate(rotation);
			}
			gl::translate((-rotPt.x), (-rotPt.y));	//Translates the screen back so that the origin is in the correct place again (undoes the above translation)
		}

		void drawStrokedRect(var::coord2 pointA, var::coord2 pointB, var::coord2 rotPt, float rotation, bool avgRotation, bool preScaled, var::color_RGB color)
		{
			var::coord2 displacement = (preScaled) ? window::getScaledDisplacement() : window::getDisplacement();
			drawStaticStrokedRect(pointA + displacement, pointB + displacement, rotPt + displacement, rotation, avgRotation, preScaled, color);
		}



		void drawStaticHollowRect(var::coord2 pointA, var::coord2 pointB, var::coord2 lineThickness, var::color_RGB color, var::coord2 rotPt, float rotation, bool avgRotation, bool preScaled, bool ignoreZoom)
		{
			if(avgRotation == true)	//Rotates the rectangle about it's center if true
			{
				rotPt = (pointA + pointB) / 2;
			}
			if(preScaled == false)	//Gets the scaled versions of the coordinates (converting to the absolute coordinates of a pixel, from a coordinate relative to the size of the screen)
			{
				rotPt = window::scale(rotPt, true);
				pointA = window::scale(pointA, true);
				pointB = window::scale(pointB, true);
				lineThickness = window::scale(lineThickness, false);
			}

			if(color.isDefined())
			{
				if(color.isOpacityDefined()) gl::color(color.toCinderColorA());
				else gl::color(color.toCinderColor());
			}

			gl::translate(rotPt.x, rotPt.y);	//Translates the screen so that the point of rotation is at 0, 0 (pixel coordinates)
			if(rotation != 0)					//Rotates the screen to the specified amount, if the amount is non-zero
			{
				gl::rotate(-rotation);
			}

			double top = pointA.y - rotPt.y;
			double right = pointB.x - rotPt.x;
			double bottom = pointB.y - rotPt.y;
			double left = pointA.x - rotPt.x;

			//The top side of the rectangle
			gl::drawSolidRect(Rectf(left, top, right, top + lineThickness.y));

			//The bottom side of the rectangle
			gl::drawSolidRect(Rectf(left, bottom - lineThickness.y, right, bottom));

			//The left side of the rectangle
			gl::drawSolidRect(Rectf(left, top, left + lineThickness.x, bottom));

			//The right side of the rectangle
			gl::drawSolidRect(Rectf(right - lineThickness.x, top, right, bottom));

			if(rotation != 0)					//Rotates the screen back so that the screen is now level, leaving the rectangle rotated to the specified angle, if the amount is non-zero
			{
				gl::rotate(rotation);
			}
			gl::translate((-rotPt.x), (-rotPt.y));	//Translates the screen back so that the origin is in the correct place again (undoes the above translation)
		}

		void drawHollowRect(var::coord2 pointA, var::coord2 pointB, var::coord2 lineThickness, var::color_RGB color, var::coord2 rotPt, float rotation, bool avgRotation = false, bool preScaled = false)
		{
			var::coord2 displacement = (preScaled) ? window::getScaledDisplacement() : window::getDisplacement();
			drawStaticHollowRect(pointA + displacement, pointB + displacement, lineThickness, color, rotPt + displacement, rotation, avgRotation, preScaled, false);
		}



		void drawStaticCircle(var::coord2 position, float radius, bool preScaled, var::color_RGB color)
		{
			if(!preScaled)
			{
				position = window::scale(position);
				radius = window::scaleX(radius);
			}
			if(color.isDefined())
			{
				if(color.isOpacityDefined()) gl::color(color.toCinderColorA());
				else gl::color(color.toCinderColor());
			}

			gl::drawSolidCircle(position.toVec2f(), radius);
		}

		void drawCircle(var::coord2 position, float radius, bool preScaled = false, var::color_RGB color = var::color_RGB())
		{
			var::coord2 displacement = (preScaled) ? window::getScaledDisplacement() : window::getDisplacement();
			drawStaticCircle(position + displacement, radius, preScaled, color);
		}



		void drawStaticStrokedCircle(var::coord2 position, float radius, bool preScaled, var::color_RGB color)
		{
			if(!preScaled)
			{
				position = window::scale(position);
				radius = window::scaleX(radius);
			}
			if(color.isDefined())
			{
				if(color.isOpacityDefined()) gl::color(color.toCinderColorA());
				else gl::color(color.toCinderColor());
			}

			gl::drawStrokedCircle(position.toVec2f(), radius);
		}

		void drawStrokedCircle(var::coord2 position, float radius, bool preScaled, var::color_RGB color)
		{
			var::coord2 displacement = (preScaled) ? window::getScaledDisplacement() : window::getDisplacement();
			drawStaticStrokedCircle(position + displacement, radius, preScaled, color);
		}



		void drawStaticTriangle(var::coord2 position, float width, float height, float rotation, bool preScaled, var::color_RGB color)
		{
			if(preScaled == false)	//If the values aren't pre scaled, scale them
			{
				position = window::scale(position);
				width = window::scaleX(width);
				height = window::scaleX(height);
			}

			if(color.isDefined())
			{
				if(color.isOpacityDefined()) gl::color(color.toCinderColorA());
				else gl::color(color.toCinderColor());
			}

			gl::translate(position.toVec2f());	//Translate the screen so the position the triangle is supposed to be drawn at is the origin
			gl::rotate(-rotation);				//Rotate the screen so that the direction the triangle is supposed to face is pointing up

			gl::drawSolidTriangle(			//Draw the triangle (the triangle is drawn centered on the origin, facing right
				Vec2f((var::coord2(width / 2, 0)).toVec2f()),					//The rightmost point (the tip)
				Vec2f((var::coord2(-width / 2, -height / 2)).toVec2f()),	//The bottom left point (the left base)
				Vec2f((var::coord2(-width / 2, height / 2)).toVec2f())		//The top left point (the right base)
			);

			gl::rotate(rotation);				//Rotate the screen back so that it is properly oriented, and the triangle is facing the correct direction
			gl::translate(position.negated().toVec2f());		//Translate the screen so the origin is back at the correct position
		}

		void drawTriangle(var::coord2 position, float width, float height, float rotation, bool preScaled, var::color_RGB color)
		{
			var::coord2 displacement = (preScaled) ? window::getScaledDisplacement() : window::getDisplacement();
			drawStaticTriangle(position + displacement, width, height, rotation, preScaled, color);
		}



		void drawStaticStrokedTriangle(var::coord2 position, float width, float height, float rotation, bool preScaled, var::color_RGB color)
		{
			if(preScaled == false)	//If the values aren't pre scaled, scale them
			{
				position = window::scale(position);
				width = window::scaleX(width);
				height = window::scaleX(height);
			}

			if(color.isDefined())
			{
				if(color.isOpacityDefined()) gl::color(color.toCinderColorA());
				else gl::color(color.toCinderColor());
			}

			gl::translate(position.toVec2f());	//Translate the screen so the position the triangle is supposed to be drawn at is the origin
			gl::rotate(rotation);				//Rotate the screen so that the direction the triangle is supposed to face is pointing up

			gl::drawStrokedTriangle(			//Draw the triangle (the triangle is drawn centered on the origin, facing right
				Vec2f((var::coord2(width / 2, 0)).toVec2f()),					//The rightmost point (the tip)
				Vec2f((var::coord2(-width / 2, -height / 2)).toVec2f()),	//The bottom left point (the left base)
				Vec2f((var::coord2(-width / 2, height / 2)).toVec2f())		//The top left point (the right base)
			);

			gl::rotate(-rotation);				//Rotate the screen back so that it is properly oriented, and the triangle is facing the correct direction
			gl::translate(position.negated().toVec2f());		//Translate the screen so the origin is back at the correct position
		}

		void drawStrokedTriangle(var::coord2 position, float width, float height, float rotation, bool preScaled, var::color_RGB color)
		{
			var::coord2 displacement = (preScaled) ? window::getScaledDisplacement() : window::getDisplacement();
			drawStaticStrokedTriangle(position + displacement, width, height, rotation, preScaled, color);
		}



		void drawStaticStringCentered(std::string text, var::coord2 position, bool preScaled, int size, var::color_RGB color)
		{
			if(!preScaled) position = window::scale(position);

			if(color.isDefined())
			{
				if(color.isOpacityDefined()) gl::color(color.toCinderColorA());
				else gl::color(color.toCinderColor());
			}

			gl::drawStringCentered(text, position.toVec2f(), color.toCinderColorA(), Font::Font("Times New Roman", size));
		}

		void drawStringCentered(std::string text, var::coord2 position, bool preScaled, int size, var::color_RGB color)
		{
			var::coord2 displacement = (preScaled) ? window::getScaledDisplacement() : window::getDisplacement();
			drawStaticStringCentered(text, position + displacement, preScaled, size, color);
		}



		void drawStaticStringRight(std::string text, var::coord2 position, bool preScaled, int size, var::color_RGB color)
		{
			if(!preScaled) position = window::scale(position);

			if(color.isDefined())
			{
				if(color.isOpacityDefined()) gl::color(color.toCinderColorA());
				else gl::color(color.toCinderColor());
			}

			gl::drawStringRight(text, position.toVec2f(), color.toCinderColorA(), Font::Font("Times New Roman", size));
		}

		void drawStringRight(std::string text, var::coord2 position, bool preScaled, int size, var::color_RGB color)
		{
			var::coord2 displacement = (preScaled) ? window::getScaledDisplacement() : window::getDisplacement();
			drawStaticStringRight(text, position + displacement, preScaled, size, color);
		}


		void drawStaticStringLeft(std::string text, var::coord2 position, bool preScaled, int size, var::color_RGB color)
		{
			if(!preScaled) position = window::scale(position);

			if(color.isDefined())
			{
				if(color.isOpacityDefined()) gl::color(color.toCinderColorA());
				else gl::color(color.toCinderColor());
			}

			gl::drawString(text, position.toVec2f(), color.toCinderColorA(), Font::Font("Times New Roman", size));
		}

		void drawStringLeft(std::string text, var::coord2 position, bool preScaled, int size, var::color_RGB color)
		{
			var::coord2 displacement = (preScaled) ? window::getScaledDisplacement() : window::getDisplacement();
			drawStaticStringLeft(text, position + displacement, preScaled, size, color);
		}
	}
}
#endif