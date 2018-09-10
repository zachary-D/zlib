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

		typedef struct tm longTime;		//A time represented as second/minute/hour/day/month/year, from time.h

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


		//An element in a linked list, containing a single value, and pointers to the elements before and after it
		template<class T>
		struct link
		{
			link();
			link(T _data);
			link(T _Data, link * _previous, link * _next);

			T data;
			link * next;
			link * previous;

			inline bool isFirst();
			inline bool isLast();
		};

		//The function definitions and such for the link class are inlcuded here because: templates + compilers = pain.  (they throw a fit otherwise. yay!)

		template<class T>
		link<T>::link()
		{
			next = NULL;
			previous = NULL;
		}

		template<class T>
		link<T>::link(T _data)
		{
			data = _data;
			next = NULL;
			previous = NULL;
		}

		template<class T>
		link<T>::link(T _data, link * _previous, link * _next)
		{
			data = _data;
			next = _next;
			previous = _previous;
		}

		template<class T>
		inline bool link<T>::isFirst()
		{
			return previous == NULL;
		}

		template<class T>
		inline bool link<T>::isLast()
		{
			return next == NULL;
		}


		//A simple linked list, with position-tracking in both directions
		template<class T>
		struct linkedList
		{
			static enum
			{
				badIndex,
				badPointer,
				iter_listEnd,
				iter_badPointer,
			};

			linkedList();
			
			link<T> * first;
			link<T> * last;

			unsigned size;

			void push(T value);
			void insert(T value, unsigned index);
			void erase(unsigned index);
			T & access(unsigned index);

			link<T> * iterateToElement(unsigned index);

			T & operator[](unsigned index);
		};

		template<class T>
		linkedList<T>::linkedList()
		{
			size = 0;
			first = NULL;
			last = NULL;
		}

		template<class T>
		void linkedList<T>::push(T value)
		{
			if (size == 0)
			//If no other elements exist
			{
				first = new link<T>(value, NULL, NULL);
				last = first;
				size = 1;
				return;
			}
			else
			//If at least one element already exists
			{
				//Create the new value on the end of the chain
				last->next = new link<T>(value, last, NULL);

				//Change the pointer to the last element to the new element created
				last = last->next;
				size++;
				return;
			}
		}

		template<class T>
		void linkedList<T>::insert(T value, unsigned index)
		{
			if(index > size) throw badIndex;

			if(size == 0)
			{	//If we're adding to and empty list
				first = new link<T>(value, NULL, NULL);
				last = first;
				size = 1;
				return;
			}
			if(index == 0)
			{	//If we're adding an element at the beginning

				//Allocate space for the new element, and set the appropriate trackers
				first = new link<T>(value, NULL, first);

				//Looks ugly AF, but backlinks the second link to the new first link
				first->next->previous = first;

				size++;
				return;
			}
			else
			{	//If we're adding an element anywhere else

				//Get a reference to the element we're inserting after
				link<T> * previous = iterateToElement(index - 1);

				link<T> * after = NULL;

				if(!previous->isLast())
				{	//If there is an elment after the elemet we're adding, store a reference to the element that will be after the one we are inserting

					after = previous->next;
				}

				//Insert the element
				previous->next = new link<T>(value, previous, after);

				if(after != NULL)
				{	//Link the element after it backwards, if it exists

					after->previous = previous->next;
				}
				//If no element exists after this one, then this is the last element (duh). The 'last' pointer needs to be updated as such.
				else
				{
					last = previous->next;
				}

				size++;
			}
		}

		template<class T>
		void linkedList<T>::erase(unsigned index)
		{
			if(index >= size) throw badIndex;

			//Get the element we're deleting
			link<T> * target = iterateToElement(index);

			//Get pointers to the links before and after the element we're deleting
			link<T> * _prev = target->previous;
			link<T> * _next = target->next;

			// "Stitch" the elements before and after the element together

			//If the element before the target isn't null, link it to the element after the target
			if(_prev != NULL) _prev->next = _next;
			//If the element before the target is null, then the target must be the 'first' pointer.  As such, we must set the 'first' pointer to the element after the target
			else first = _next;

			//If the element after the target isn't null, link it to the element before the target (link backwards)
			if(_next != NULL) _next->previous = _prev;
			//If the element after the target is null, then the target must be the 'last' pointer.  As such, we must set the 'last' pointer to the element before the target
			else last = _prev;

			//Remove the target from memory
			delete target;

			//Deincriment the size tracker
			size--;
		}

		template<class T>
		T & linkedList<T>::access(unsigned index)
		{
			return iterateToElement(index)->data;
		}

		template<class T>
		link<T> * linkedList<T>::iterateToElement(unsigned index)
		{
			if (index > size) throw badIndex;

			link<T> * current = first;

			//Iterate to reach the correct element in the list
			for (unsigned i = 0; i < index; i++)
			{
				if (current->isLast()) throw badPointer;
				current = current->next;
			}

			return current;
		}

		template<class T>
		T & linkedList<T>::operator[](unsigned index)
		{
			return access(index);
		}


		//A linked list along with a vector containing a reference to each element
		template<class T>
		struct arrList : linkedList<T>
		{
			arrList();
			
			vector<link<T>*> links;		//Pointers to each link in the list

			void push(T value);						//Add 'value' to the end of the list
			void insert(T value, unsigned index);	//Insert 'value' at 'index'
			void erase(unsigned index);				//Erase the elment at 'index'
			T & access(unsigned index);				//Return a reference to the element at 'index'

			T & operator[](unsigned index);	//Just a wrapper for access, no different than the parent class, but it had to be explicitly defined to prevent bugs (linkedLIst::access() would end up being called instead of arrList::access(), etc.)
		};

		template<class T>
		arrList<T>::arrList()
		{
			size = 0;
			first = NULL;
			last = NULL;
		}

		template<class T>
		void arrList<T>::push(T value)
		{
			if (size == 0)
			{	//If no other elements exist

				//Allocate the first element
				first = new link<T>(value, NULL, NULL);
				
				//Set the last to the first
				last = first;
				
				//Add a pointer to the new link to the vector, and set the size tracker
				links.push_back(first);
				size = 1;

				return;
			}
			else
			{	//If at least one element exists

				//Create the new link
				last->next = new link<T>(value, last, NULL);
				
				//Update the 'last element' pointer
				last = last->next;

				//Add the link to the tracking vector
				links.push_back(last);

				//Incriment the size tracker of the list
				size++;

				return;
			}
			
		}

		template<class T>
		void arrList<T>::insert(T value, unsigned index)
		{
			if(index > size) throw badIndex;

			if(size == 0)
			{	//If we're adding to and empty list
				first = new link<T>(value, NULL, NULL);
				last = first;
				size = 1;
				links.push_back(first);
				return;
			}
			if (index == 0)
			{	//If we're adding an element at the beginning
				
				//Allocate space for the new element, and set the appropriate trackers
				first = new link<T>(value, NULL, first);

				//Looks ugly AF, but backlinks the second link to the new first link
				first->next->previous = first;
				
				//Add the pointer to the tracker and incriment the size tracker
				links.insert(links.begin() + index, first);
				size++;
				return;
			}
			else
			{	//If we're adding an element anywhere else

				//Get a reference to the element we're inserting after
				link<T> * previous = links[index - 1];

				link<T> * after = NULL;

				if (!previous->isLast())
				{	//If there is an elment after the elemet we're adding, store a reference to the element that will be after the one we are inserting
					
					after = previous->next;
				}
				
				//Insert the element
				previous->next = new link<T>(value, previous, after);

				if (after != NULL)
				{	//Link the element after it backwards, if it exists
					
					after->previous = previous->next;
				}
				//If no element exists after this one, then this is the last element (duh). The 'last' pointer needs to be updated as such.
				else
				{
					last = previous->next;
				}

				links.insert(links.begin() + index, previous->next);
				size++;
			}
		}

		template<class T>
		void arrList<T>::erase(unsigned index)
		{
			if(index >= size) throw badIndex;

			//Get the element we're deleting
			link<T> * target = links[index];

			//Get pointers to the links before and after the element we're deleting
			link<T> * _prev = target->previous;
			link<T> * _next = target->next;

			// "Stitch" the elements before and after the element together

			//If the element before the target isn't null, link it to the element after the target
			if(_prev != NULL) _prev->next = _next;
			//If the element before the target is null, then the target must be the 'first' pointer.  As such, we must set the 'first' pointer to the element after the target
			else first = _next;

			//If the element after the target isn't null, link it to the element before the target (link backwards)
			if(_next != NULL) _next->previous = _prev;
			//If the element after the target is null, then the target must be the 'last' pointer.  As such, we must set the 'last' pointer to the element before the target
			else last = _prev;

			//Remove the target from memory
			delete target;
			
			//Remove the target from the links vector
			links.erase(links.begin() + index);

			//Deincriment the size tracker
			size--;
		}

		template<class T>
		T & arrList<T>::access(unsigned index)
		{
			if(index >= size) throw badIndex;
			return links[index]->data;
		}

		template<class T>
		T & arrList<T>::operator[](unsigned index)
		{
			return access(index);
		}


#ifdef ZLIB_ENABLE_TESTS
		template<class T>
		void validateLinkedListStructure(var::linkedList<T> & list)
		{
			enum errs
			{
				check1,
				check2,
				check3,
				check4,
				check5,
				check6,
				check7,
				check8,
				check9
			};

			//Checks:
			//Check 1 - The 'first' element is known (unless size = 0)
			//Check 2 - The 'last' element is known (unless size = 0)
			//Check 3 - There are no elements before 'first' (skip if size = 0)
			//Check 4 - There are no elements after 'last' (skip if size = 0)
			//Check 5 - The list proceeds continuously from 'first' to 'last'
			//Check 6 - The list proceeds continuously from 'first' to 'last' in 'size' elements
			//Check 7 - The list proceeds continuously from 'last' to 'first'
			//Check 8 - The list proceeds continuously from 'last' to 'first' in 'size' elements
			//Check 9 - Each element links to the element before it properly
			
			//Check 1
			if(list.first == NULL && list.size != 0) throw check1;

			//Check 2
			if(list.last == NULL && list.size != 0) throw check2;

			//if size == 0, we can't do any more checks
			if(list.size == 0) return;
			
			//Check3
			if(list.first->previous != NULL) throw check3;

			//Check 4
			if(list.last->next != NULL) throw check4;

			//Checks 5 & 6
			{
				link<T> * curr = list.first;
				unsigned count = 1;	//If first exists, there is at least 1 element
				
				while(curr != list.last)
				{
					curr = curr->next;
					if(curr == NULL) throw check5;
					count++;
				}

				if(list.size != count) throw check6;
			}

			//Checks 7 & 8
			{
				link<T> * curr = list.last;
				unsigned count = 1;	//If first exists, there is at least 1 element

				while(curr != list.first)
				{
					curr = curr->previous;
					if(curr == NULL) throw check7;
					count++;
				}

				if(list.size != count) throw check8;
			}

			//Check 9
			{
				link<T> * curr = list.first;
				link<T> * prev = curr->previous;

				while(curr != list.last)
				{
					if(curr->previous != prev) throw check9;
					prev = curr;
					curr = curr->next;
				}
			}
		}

		//Checks the arrList to make sure everything is as it should be
		template<class T>
		void validateArrListStructure(var::arrList<T> & list)
		{
			enum class errs
			{
				check1,				//General failure on check 1
				check2,				//General failure on check 2
				check3,				//General failure on check 3
				check3_forward,		//An element in the list has no element after it (in check 3)
				check3_backlink,	//An element in the list does not backlink properly (in check 3)
				check4,				//General failure on check 4
				check5,				//General failure on check 5
				check6,				//General failure on check 6
				check7,				//General failure on check 7
				check8,				//General failure on check 8
				check9,				//General failure on check 9
			};

			//Checks: (Assuming the list contains at least 1 element; tested using list.size)
			//1) Checks that the element at list.first has nothing before it
			//2) Checks that the element at list.last has nothing after it
			//3) Checks that the list is continuous, forwards and backwards (makes sure that every element links forward and backward correctly)
			//4) Checks that list.size matches the number of elements in the list
			//5) Checks that list.access(n) correctly accesses the n'th element of the list  (Can only check the values at each index, not the elements specifically.  Use unique values for best results.)
			//6) Checks that each element only occurs in the list once

			//Checks 2 - If the list contains no elements

			//7) Checks that the first pointer is NULL
			//8) Checks that the last pointer is NULL
			//9) Checks that the size of the list.links array is 0

			//When the checks fail they are thrown as exceptions.... this probably wasn't a great idea, but what's done is done  (until it's redone, that is)

			if(list.size != 0)
			{
				//Check 1
				if(list.first->previous != NULL) throw errs::check1;

				//Check 2
				if(list.last->next != NULL) throw errs::check2;

				//Checks 3, 4, 5, and 6
				var::link<T> * curr = list.first;	//The current element
				var::link<T> * last = curr;		//The last element

				int count = 0;	//Tracks the number of elements in the list

								//Unless the first element is NULL, we need to include it in the count
				if(list.first != NULL) count++;

				vector< var::link<T> * > vec;		//Contains pointers to each element in the list
													//Add the first element to the vector
				if(curr != NULL) vec.push_back(curr);

				//Check 3 (And prep for checks 4 and 5)
				//Loop until we reach the end of the list
				while(curr != list.last)
				{
					if(curr->next == NULL) throw errs::check3_forward;
					curr = curr->next;

					if(curr->previous != last) throw errs::check3_backlink;

					last = curr;
					count++;
					vec.push_back(curr);
				}

				//Check 4
				if(list.size != count) throw errs::check4;

				//Check 5
				for(int i = 0; i < count; i++)
				{
					if(vec[i]->data != list[i]) throw errs::check5;
				}

				//Check 6
				for(int check = 0; check < count; check++)
				{
					for(int against = 0; against < count; against++)
					{
						if(check == against) continue;

						if(vec[check] == vec[against]) throw errs::check6;
					}
				}
			}
			else
			{
				//Check 7
				if(list.first != NULL) throw errs::check7;

				//Check 8
				if(list.last != NULL) throw errs::check8;

				//Check 9
				if(list.links.size() != 0) throw errs::check9;

				//This part was a lot nicer to code than checks 3->6....
			}
		}
#endif

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