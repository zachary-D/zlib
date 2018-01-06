#pragma once

//Written by and copyright Zachary Damato
//input.cpp is part of the zlib submodule

#define _USE_MATH_DEFINES
#include<iostream>
#include<sstream>
#include<string>
#include<map>

using std::string;
using std::map;

#ifdef USING_CINDER
#include "cinder/app/AppNative.h"
#endif

#include "input.h"

#ifdef USING_CINDER
#include "draw.h"
#include "windInfo.h"
#endif
#include "varTypes.h"
#include "varConv.h"

using namespace zlib;

#ifdef USING_CINDER
using cinder::app::KeyEvent;
#endif
namespace zlib
{
	namespace input
	{
#ifndef USING_CINDER
		string getLine(char forceCase)	//Returns the user input from the console.  'forceCase' accepts 'u' or 'l', and converts the text to either uppercase or lowercase respectively, the text will be returned as lowercase.
		{
			string inp;
			std::getline(std::cin, inp);

			if(forceCase == 'l') conv::toLowercase(inp, true);
			else if(forceCase == 'u') conv::toUppercase(inp, true);
			return inp;
		}

		double getNumInput(string prompt)
		{
			while(true)
			{
				string value;
				cout << prompt << ":";
				getline(cin, value);

				if(conv::isNum(value))
				{
					return conv::toNum(value);
				}
				else
				{
					cout << "I'm sorry, I don't understand \"" << value << "\".  Please enter a numerical value." << endl;
				}
			}
		}
#elif USING_CINDER
		button::button(string _name, var::coord2 _position, var::coord2 _size)
		{
			setName(_name);
			setPosition(_position);
			setSize(_size);
		}

		button::button(string _name, var::coord2 _position, var::coord2 _size, void(*_function) ())
		{
			setName(_name);
			setPosition(_position);
			setSize(_size);
			setFunction(_function);
		}

		void button::setName(string _name)
		{
			name = _name;
		}

		void button::setPosition(var::coord2 _position)
		{
			position = _position;
		}

		void button::setSize(var::coord2 _size)
		{
			//check to make sure size is > 0
			if(!(_size < 0))
			{
				size = _size;
			}
			else _DEBUG_ERROR("Invalid button size!");
		}

		void button::setFunction(void(*function)())
		{
			pressAction = function;
			actionDefined = true;
		}

		void button::setColor(var::color_RGB _color)
		{
			color = _color;
		}

		void button::draw()
		{
			draw::drawStaticRect(getPosition(), getPosition() + getSize(), var::coord2(), 0, false, false, getColor());
			gl::drawStringCentered(
				name,
				window::scale(
					getPosition() + var::coord2(
						getSize().x / 2,
						getSize().y)
					).toVec2f(),
				ColorA(1, 1, 1, 1),
				Font("Arial", 50)
			);
		}

		bool button::executeAction()
		{
			if(actionDefined)
			{
				pressAction();
				return true;
			}
			else return false;
		}

		bool button::checkPressed(var::coord2 _coords, bool _rawCoords)
		{
			if(_rawCoords) _coords = window::scale(_coords);

			if(_coords.isWithin(getPosition(), getPosition() + getSize()))
			{
				executeAction();
				return true;
			}
			else return false;
		}


		buttonList::internalButton::internalButton(var::coord2 * _size, var::coord2 * _listOrigin, int _buttonIndex, void(*_function)(), string _name, var::color_RGB _color)
		{
			size = _size;
			listOrigin = _listOrigin;
			listIndex = _buttonIndex;
			setFunction(_function);
			setName(_name);
			setColor(_color);
		}


		bool buttonList::setButtonSize(var::coord2 _size)
		{
			if(!(_size > 0)) return false;
			else
			{
				buttonSize = _size;
				return true;
			}
		}

		void buttonList::newButton(string _name, void(*_function)(), var::color_RGB _color)
		{
			buttons.push_back(internalButton(&buttonSize, &position, buttons.size() - 1, _function, _name, _color));
		}

		int buttonList::checkPressed(var::coord2 _coords, bool _rawCoord)
		{
			for(int iter = 0; iter < buttons.size(); iter++)
			{
				if(buttons[iter].checkPressed(_coords, _rawCoord)) return iter;
			}
			return -1;
		}

		buttonList::internalButton * buttonList::operator[](int & index)
		{
			if(index >= buttons.size()) _DEBUG_ERROR("\nbuttonList::operator[] | Error:\nRequested index does note exist!");
			return &buttons[index];
		}

		void buttonList::draw()
		{
			for(int iter = 0; iter < buttons.size(); iter++)
			{
				buttons[iter].draw();
			}
		}
#endif
	};

#ifdef USING_CINDER
	namespace keyboard
	{
		std::unordered_map< int, bool> keysPressed;		//A map of whether or not the key (on the keyboard) associated with the key 'int' is pressed or not.  This is only available internally


		void keyDown(KeyEvent event)
		{
			keysPressed[event.getCode()] = true;
		}

		void keyUp(KeyEvent event)
		{
			keysPressed[event.getCode()] = false;
		}


		bool isModifierPressed()
		{
			return isShiftPressed() || isAltPressed() || isCtrlPressed();
		}


		bool isShiftPressed()			//Returns true when either of the shift keys are pressed
		{
			return isLShiftPressed() || isRShiftPressed();
		}

		bool isLShiftPressed()			//Returns true when the left shift is pressed
		{
			return keysPressed[304];
		}

		bool isRShiftPressed()			//Returns true when the right shift is pressed
		{
			return keysPressed[303];

		}


		bool isAltPressed()				//Returns true when either of the alt keys are pressed
		{
			return isLAltPressed() || isRAltPressed();
		}

		bool isLAltPressed()			//Returns true when the left alt is pressed
		{
			return keysPressed[308];
		}

		bool isRAltPressed()			//Returns true when the right alt is pressed
		{
			return keysPressed[307];
		}


		bool isCtrlPressed()			//Returns true when either of the ctrl keys are pressed
		{
			return isLCtrlPressed() || isRCtrlPressed();
		}

		bool isLCtrlPressed()			//Returns true when the left ctrl is pressed
		{
			return keysPressed[306];
		}

		bool isRCtrlPressed()			//Returns true when the right ctrl is pressed
		{
			return keysPressed[305];
		}


		bool isKeyPressed(keys key)
		{
			return keysPressed[key];
		}
	}
#endif
}