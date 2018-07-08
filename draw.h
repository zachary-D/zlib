#pragma once;

//Written by and copyright Zachary Damato
//draw.h is part of the zlib submodule

#ifdef ZLIB_USING_CINDER

#include <string> 

#include "cinder/gl/Texture.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "cinder/Text.h"
#include "cinder/app/App.h"
#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/ImageIo.h"
#include "cinder/app/window.h"

using namespace ci;
using namespace ci::app;

#include "varTypes.h"

using namespace zlib;

//All static functions ignore window::getDisplacement, all functions without static take it into account

namespace zlib
{
	namespace draw
	{
		namespace config
		{
			//The font and font size used by text boxes, by default
			extern string font;
			extern int fontSize;
		}

		void drawStaticTexture(gl::Texture2dRef _texture, var::coord2 _pointA, var::coord2 _pointB, var::coord2 _rotPt, float _rotation, bool _avgRotation = false, bool _preScaled = false, bool ignoreZoom = true);											//Draws a texture, ignoring window::displacement and window::zoom
		void drawTexture(gl::Texture2dRef _texture, var::coord2 _pointA, var::coord2 _pointB, var::coord2 _rotPt, float _rotation, bool _avgRotation = false, bool _preScaled = false);																			//Draws a texture

		void drawStaticRect(var::coord2 pointA, var::coord2 pointB, var::coord2 rotPt = var::coord2(), float rotation = 0, bool avgRotation = false, bool preScaled = false, var::color_RGB color = var::color_RGB(-1, -1, -1), bool ignoreZoom = true);	//Draws a rectangle, ignoring window::displacement and window::zoom
		void drawRect(var::coord2 pointA, var::coord2 pointB, var::coord2 rotPt = var::coord2(), float rotation = 0, bool avgRotation = false, bool preScaled = false, var::color_RGB color = var::color_RGB(-1, -1, -1));													//Draws a rectangle

																																																																			//void drawRect(float x1, float y1, float x2, float y2, float rotPtX, float rotPtY, float rotation = 45, bool avgRotation = false, bool preScaled = false, float R = -1, float G = -1, float B = -1, float opacity = -1);
		//void drawRect(var::coord2 pointA, var::coord2 pointB, var::coord2 rotPt, float rotation = 45, bool avgRotation = false, bool preScaled = false, float R = -1, float G = -1, float B = -1, float opacity = -1);

		void drawStaticStrokedRect(var::coord2 pointA, var::coord2 pointB, var::coord2 rotPt = var::coord2(0, 0), float rotation = 0.0f, bool avgRotation = false, bool preScaled = false, var::color_RGB color = var::color_RGB());				//Draws a stroked rect
		void drawStrokedRect(var::coord2 pointA, var::coord2 pointB, var::coord2 rotPt = var::coord2(0, 0), float rotation = 0.0f, bool avgRotation = false, bool preScaled = false, var::color_RGB color = var::color_RGB());

		void drawStaticHollowRect(var::coord2 pointA, var::coord2 pointB, var::coord2 lineThickness = var::coord2(0.25, 0.25), var::color_RGB color = var::color_RGB(), var::coord2 rotPt = var::coord2(0, 0), float rotation = 0.0f, bool avgRotation = false, bool preScaled = false, bool ignoreZoom = true);
		void drawHollowRect(var::coord2 pointA, var::coord2 pointB, var::coord2 lineThickness = var::coord2(0.25, 0.25), var::color_RGB color = var::color_RGB(), var::coord2 rotPt = var::coord2(0, 0), float rotation = 0.0f, bool avgRotation = false, bool preScaled = false);

		void drawStaticCircle(var::coord2 position, float radius, bool preScaled = false, var::color_RGB color = var::color_RGB());
		void drawCircle(var::coord2 position, float radius, bool preScaled = false, var::color_RGB color = var::color_RGB());

		void drawStaticStrokedCircle(var::coord2 position, float radius, bool preScaled = false, var::color_RGB color = var::color_RGB());
		void drawStrokedCircle(var::coord2 position, float radius, bool preScaled = false, var::color_RGB color = var::color_RGB());

		void drawStaticTriangle(var::coord2 position, float width, float height, float rotation = 0, bool preScaled = false, var::color_RGB color = var::color_RGB());
		void drawTriangle(var::coord2 position, float width, float height, float rotation = 0, bool preScaled = false, var::color_RGB color = var::color_RGB());

		void drawStaticStrokedTriangle(var::coord2 position, float width, float height, float rotation = 0, bool preScaled = false, var::color_RGB color = var::color_RGB());
		void drawStrokedTriangle(var::coord2 position, float width, float height, float rotation = 0, bool preScaled = false, var::color_RGB color = var::color_RGB());

		//Draws a string 'text' at 'position' (centered on top middle), with font size 'size' in color 'color'
		void drawStaticStringCentered(std::string text, var::coord2 position, bool preScaled = false, int size = 14, var::color_RGB color = var::color_RGB());
		//Draw a string 'text' at 'position' (centered on top middle), with font size 'size' in color 'color'
		void drawStringCentered(std::string text, var::coord2 position, bool preScaled = false, int size = 14, var::color_RGB color = var::color_RGB());

		//Draws a string 'text' at 'position' (centered on the top right), with font size 'size' in color 'color'
		void drawStaticStringRight(std::string text, var::coord2 position, bool preScaled = false, int size = 14, var::color_RGB color = var::color_RGB());
		//Draw a string 'text' at 'position' (centered on the top right), with font size 'size' in color 'color'
		void drawStringRight(std::string text, var::coord2 position, bool preScaled = false, int size = 14, var::color_RGB color = var::color_RGB());

		//Draws a string 'text' at 'position' (centered on the top left), with font size 'size' in color 'color'
		void drawStaticStringLeft(std::string text, var::coord2 position, bool preScaled = false, int size = 14, var::color_RGB color = var::color_RGB());
		//Draws a string 'text' at 'position' (centered on the top left), with font size 'size' in color 'color'
		void drawStringLeft(std::string text, var::coord2 position, bool preScaled = false, int size = 14, var::color_RGB color = var::color_RGB());

		//Manages drawing text boxes.  The text box is drawn either when draw() is called, or when the class goes out of scope
		class tBoxWrapper
		{
		public:
			tBoxWrapper();

			std::string text = "";
			Font textFont = Font(config::font, config::fontSize);
			TextBox::Alignment alignment = TextBox::LEFT;	//Which side the text is aligned to
			var::coord2 size = var::coord2(200, 200);
			var::color_RGB bgColor = var::color_RGB(1, 1, 1);	//bgColor = backGroundColor
			var::color_RGB color = var::color_RGB(0, 0, 0);

			void update();
			void draw(var::coord2 position);
			
		private:
			gl::Texture2dRef texture;
		};

		void drawTextBox(string text, var::coord2 pointA, var::coord2 pointB);

		void drawTextBox(string text, var::coord2 pointA, var::coord2 pointB, Font font);
	}
}
#endif