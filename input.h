#pragma once

//Written by and copyright Zachary Damato
//input.h is part of the zlib submodule

#include <string>

using std::string;

#ifdef USING_CINDER
#include "cinder/app/AppNative.h"
#endif

#include "varTypes.h"

using namespace zlib; 

#ifdef USING_CINDER
using cinder::app::KeyEvent;
#endif

namespace zlib
{
	namespace input
	{
#ifndef USING_CINDER
		string getLine(char forceCase = 'n'); 	//Returns the user input from the console.  If forceCase == 'l', the text will be returned as lowercase.  If forceCase == 'u' the text will be returned as uppercase
		double getNumInput(string prompt);
#elif USING_CINDER
		class button
		{
		protected:
			string name = "";

		private:
			var::coord2 position = var::coord2(0, 0);
			var::coord2 size = var::coord2(2, 1);

		protected:
			void(*pressAction)();
			bool actionDefined = false;

			var::color_RGB color;

		public:
			button() {}
			button(string _name, var::coord2 _position, var::coord2 _size);
			button(string _name, var::coord2 _position, var::coord2 _size, void(*_function) ());

			void setName(string _name);
			virtual void setPosition(var::coord2 _position);
			virtual void setSize(var::coord2 _size);
			void setFunction(void(*function)());
			void setColor(var::color_RGB _color);

			string getName() { return name; }
			virtual var::coord2 getPosition() { return position; }
			virtual var::coord2 getSize() { return size; }
			var::color_RGB getColor() { return color; }


			void draw();
			bool executeAction();												//Called when the button is pressed.  Calls the function referred to in 'pressAction'
			bool checkPressed(var::coord2 _coords, bool _rawCoords = true);		//Checks if the button was pressed based off user coords.  if _rawCoords is true, the coordinates will be 'dereferenced' through window::unScale() first.  If true, executeAction() will be called
		};

		class buttonList
		{
			class internalButton : public button
			{
			public:
				internalButton(var::coord2 * _size, var::coord2 * _listOrigin, int _buttonIndex, void(*_function)(), string _name = "undef", var::color_RGB _color = var::color_RGB());
			private:
				var::coord2 * listOrigin;			//A pointer to the origin of the list (the upper-left point)
				var::coord2 * size;					//A pointer to the size of the button
				int listIndex;						//The number of the button in the list (starting with 0 being the first button)

				//Functions overidden to do nothing
				void setPosition() {}
				void setSize() {}

			public:
				//Functions overidden to work in the list
				var::coord2 getPosition() { return *listOrigin - var::coord2(0, size->y * (listIndex - 1)); }
				var::coord2 getSize() { return *size; }
			};

			vector<internalButton> buttons;			//The buttons in the list, from top to bottom
			var::coord2 position;					//The position of the upper-left corner of the first button

			var::coord2 buttonSize;

		public:
			bool setButtonSize(var::coord2 _size);
			void setListPosition(var::coord2 _position) { position = _position; }

			void newButton(string _name, void(*_function)(), var::color_RGB _color = var::color_RGB());				//Creates a new button with '_name', that executes the function '_function', with the color '_color'

			int checkPressed(var::coord2 _coords, bool _rawCoords = true);			//Calls checkPressed() for every button until a button is detected to be pressed, or all are checked

			internalButton * operator[](int & index);

			void draw();
		};

#endif
	};

#ifdef USING_CINDER
	namespace keyboard
	{
		enum keys {		//Just copied from cinder's KeyEvents code, and the capitalization is tweaked
			key_backspace = 8,
			key_tab = 9,
			key_clear = 12,
			key_return = 13,
			key_pause = 19,
			key_escape = 27,
			key_space = 32,
			key_exclaim = 33,
			key_quotedbl = 34,
			key_hash = 35,
			key_dollar = 36,
			key_ampersand = 38,
			key_quote = 39,
			key_leftparen = 40,
			key_rightparen = 41,
			key_asterisk = 42,
			key_plus = 43,
			key_comma = 44,
			key_minus = 45,
			key_period = 46,
			key_slash = 47,
			key_0 = 48,
			key_1 = 49,
			key_2 = 50,
			key_3 = 51,
			key_4 = 52,
			key_5 = 53,
			key_6 = 54,
			key_7 = 55,
			key_8 = 56,
			key_9 = 57,
			key_colon = 58,
			key_semicolon = 59,
			key_less = 60,
			key_equals = 61,
			key_greater = 62,
			key_question = 63,
			key_at = 64,

			key_leftbracket = 91,
			key_backslash = 92,
			key_rightbracket = 93,
			key_caret = 94,
			key_underscore = 95,
			key_backquote = 96,
			key_a = 97,
			key_b = 98,
			key_c = 99,
			key_d = 100,
			key_e = 101,
			key_f = 102,
			key_g = 103,
			key_h = 104,
			key_i = 105,
			key_j = 106,
			key_k = 107,
			key_l = 108,
			key_m = 109,
			key_n = 110,
			key_o = 111,
			key_p = 112,
			key_q = 113,
			key_r = 114,
			key_s = 115,
			key_t = 116,
			key_u = 117,
			key_v = 118,
			key_w = 119,
			key_x = 120,
			key_y = 121,
			key_z = 122,
			key_delete = 127,

			key_KP0 = 256,
			key_KP1 = 257,
			key_KP2 = 258,
			key_KP3 = 259,
			key_KP4 = 260,
			key_KP5 = 261,
			key_KP6 = 262,
			key_KP7 = 263,
			key_KP8 = 264,
			key_KP9 = 265,
			key_KP_period = 266,
			key_KP_divide = 267,
			key_KP_multiply = 268,
			key_KP_minus = 269,
			key_KP_plus = 270,
			key_KP_enter = 271,
			key_KP_equals = 272,

			key_up = 273,
			key_down = 274,
			key_right = 275,
			key_left = 276,
			key_insert = 277,
			key_home = 278,
			key_end = 279,
			key_pageup = 280,
			key_pagedown = 281,

			key_F1 = 282,
			key_F2 = 283,
			key_F3 = 284,
			key_F4 = 285,
			key_F5 = 286,
			key_F6 = 287,
			key_F7 = 288,
			key_F8 = 289,
			key_F9 = 290,
			key_F10 = 291,
			key_F11 = 292,
			key_F12 = 293,
			key_F13 = 294,
			key_F14 = 295,
			key_F15 = 296,

			key_numlock = 300,
			key_capslock = 301,
			key_scrollock = 302,
			key_rShift = 303,
			key_lShift = 304,
			key_rCtrl = 305,
			key_lCrtl = 306,
			key_rAlt = 307,
			key_lAlt = 308,
			key_rMeta = 309,
			key_lMeta = 310,
			key_lWin = 311,			/* Left "Windows" key */
			key_rWin = 312,			/* Right "Windows" key */
			key_COMPOSE = 314,		/* Multi-key compose key */		//What is this?

			key_help = 315,
			key_print = 316,
			key_sysreq = 317,
			key_break = 318,
			key_menu = 319,
			key_power = 320,		/* Power Macintosh power key */
			key_euro = 321,			/* Some european keyboards */
			key_undo = 322,			/* Atari keyboard has Undo */
		};


		void keyDown(KeyEvent event);	//Handles a keyDown event
		void keyUp(KeyEvent event);		//Handles a keyUp event

		bool isModifierPressed();		//Returns true when a modifyer key is pressed

		bool isShiftPressed();			//Returns true when either of the shift keys are pressed
		bool isLShiftPressed();			//Returns true when the left shift is pressed
		bool isRShiftPressed();			//Returns true when the right shift is pressed

		bool isAltPressed();			//Returns true when either of the alt keys are pressed
		bool isLAltPressed();			//Returns true when the left alt is pressed
		bool isRAltPressed();			//Returns true when the right alt is pressed

		bool isCtrlPressed();			//Returns true when either of the ctrl keys are pressed
		bool isLCtrlPressed();			//Returns true when the left ctrl is pressed
		bool isRCtrlPressed();			//Returns true when the right ctrl is pressed

		bool isKeyPressed(keys key);	//Returns true when the key 'key' is pressed
	}
#endif
}