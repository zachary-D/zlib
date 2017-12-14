#pragma once

//Written by and copyright Zachary Damato
//module.h is part of the zlib submodule

#ifdef USING_CINDER && USING_ZLIB_MODEL

#include<vector>

#include "zlib/model.h"
#include "zlib/varTypes.h"

using namespace zlib;

namespace zlib
{
	namespace model
	{

		class anim_segment
		{
		public:
			anim_segment();
			anim_segment(float rotationRate);
			anim_segment(float rotationTarget, bool useClosestPath, bool useClockwisePath);
			anim_segment(float rotationTarget, bool useClosestPath, bool useClockwisePath, bool isRelativeToParent);

			bool rotChange = false;		//Whether or not the rotation of the rectangle changes
			float rotRate;				//The rate at which the model_segment will be spun
			bool constRate;				//Ignores rotTarget when true, defaults to the preset rotRate
			float rotTarget;			//The target (in degrees) to which the model_segment will spin to
			bool rotClosestPath;		//When true, the model_segment will rotate to its target (defined by 'rotTarget'), in the direction that would result in the shortest movement
			bool rotClockwise;			//When true, the model_segment will rotate clockwise to its target.  When false, the model_segment will rotate counter-clockwise towards its target.  Ignored when 'rotClosestPath' = true
			bool relativeToParent;		//When true: sets to rotate to the angle relative to the parent, When false: sets to rotate when the horiz. axis = 0 degrees

			bool sizeChange = false;	//Whether or not the size of the rectangle changes
			bool constSizeRate = false;	//Ignores point1 & point2 when true, and instead uses point1Rate & point2Rate
			var::coord2 point1;			//The target coordinate for the first coordinate of the model_segment to be resized to 
			var::coord2 point2;			//The target coordinate for the second coordinate of the model_segment to be resized to
			var::coord2 point1Rate;		//The rate at which the model_segment's first coordinate will move each frame
			var::coord2 point2Rate;		//The rate at which the model_sement's first coordinate will move each frame

			bool jointChange = false;		//Whether or not the joints on the segment are changing
			bool constJointChangeRate = false;	//Ignores childJoint and parentJoint when true, and instead uses childRate and parentRate
			var::coord2 parentJoint;		//The target coordinate for the parentJoint of the model_segment to be moved to
			var::coord2 childJoint;			//The target coordinate for the childJoint of the modle_segment to be moved to
			var::coord2 parentJointRate;	//The rate at which the model_segment's parent joint will move each frame
			var::coord2 childJointRate;		//The rate at which the model_segment's parent joint will move each frame

			vector<anim_segment> childrenAbove;
			vector<anim_segment> childrenBelow;

			//void update();
			void createAbove();
			void createAbove(anim_segment child);
			void createBelow();
			void createBelow(anim_segment child);

			void debugTree(int depth);
		};

		class anim_container
		{
		public:
			vector<anim_segment> cycles;
			vector<int> cycle_length;
			int currTime = 0;
			int cycleNum = 0;

			void newCycle();
			void newCycle(anim_segment anim);

			bool doNotLoop = false;		//If true, the animation will be deleted after it finishes

			int getCurrentCycleLength();

			void debugTree();
		};

		class model_segment
		{
		public:
			model_segment();
			model_segment(var::coord2 firstPoint, var::coord2 secondPoint);
			model_segment(var::coord2 firstPoint, var::coord2 secondPoint, var::coord2 joint_Parent, var::coord2 joint_Child);
		public:
			//Both of these coordiantes are stored in the current object, the parentJoint coordinate is stored in the child but measured in relation to the parent
			var::coord2 parentJoint;					//The coordinates on the parent object that aligns with the joint of the current object
			var::coord2 childJoint;						//The coordinates on the current object that aligns with the joint of the parent object

			var::coord2 parentJointRate = var::coord2(0, 0);	//The rate at which the parent joint is moving
			var::coord2 childJointRate = var::coord2(0, 0);		//The rate at which the child joint is moving

			vector<model_segment> childrenBelow;		//The children to be drawn before (behind) the parent
			vector<model_segment> childrenAbove;		//The children to be draw after (on top of) the parent

			int specialBelowSegment = NULL;				//The index ID of the special child segment in the childrenBelow vector, equals null if there isn't one.
			int specialAboveSegment = NULL;				//The index ID of the special child segment in the childrenAbove vector, equals null if there isn't one.

			var::coord2 point1;
			var::coord2 point2;

			var::coord2 point1Rate = var::coord2(0, 0);	//The rate of change for point 1 and point 2, respectivley
			var::coord2 point2Rate = var::coord2(0, 0);

			var::color_RGB color;						//The color of the segment

			float rotation;								//The angle the segment has rotated (From the resting position)
			float baseRotation;							//The angle the segment is rotated to in a 'resting' state

			float rotationRate = 0;						//The amount the 'rotation' var will increase by every time 'update' is run (if it is negative it is the amount 'rotate' will decrease by)

			bool absoluteRotation;						//If true, the segment will ignore the rotation of any of it's parent segments, and will rotate to the angle stored in 'rotation'

			bool debugMode;								//Enables the debug draw mode for this particular segment

			void createBelow();								//Creates a new segment below this one
			void createBelow(model_segment child);			//Creates a new semgnet with 'child' below this one
			void createSpecialBelow();
			void createSpecialBelow(model_segment _child);
			int sizeBelow();								//Returns the number of child elements below this one
			bool eraseBelow(int number);					//Erases the element at position "number" in "childrenBelow"
			bool eraseSpecialChildBelow();					//Erases the model_segment designated as the 'special segment'
			model_segment *getChildBelow(int number);		//Returns a pointer to the model_segment at position "number" in the "childrenBelow" vector
			model_segment *getSpecialChildBelow();			//Returns a pointer to the model_segment designated as the 'special segment'

			void createAbove();								//Creates a new segment above this one
			void createAbove(model_segment child);			//Creates a new segment 
			void createSpecialAbove();
			void createSpecialAbove(model_segment _child);
			int sizeAbove();
			bool eraseAbove(int number);				//Erases the element at position "number" in "childrenAbove"
			bool eraseSpecialChildAbove();				//Erases the model_segment designates as the 'special segment'
			model_segment *getChildAbove(int number);	//Returns a pointer to the model_segment at position "number" in the "childrenAbove" vector
			model_segment *getSpecialChildAbove();		//Returns a pointer to the model_segment designated as the 'special segment'

			gl::Texture segTexture;
			string textureLocation;
			bool isTextured;

			void draw(var::coord2 position, float parentRotation, bool runAnimation);// , vector<anim_segment> *animations);

			bool setTexture(string _filepath);
			bool setTexture(gl::Texture _texture);
			bool hasTexture();
			void setColor(var::color_RGB _color);
			void update();
			void updateAnimation(anim_segment *animations, int cycleLength);

			void debugTree(int depth);
		};

		class model
		{
		public:
			model();

			model_segment root;							//The model_segment that is the 'top level', that all other segments are anchored to
			vector<anim_container> animations;			//The vector 

			bool runAnimations = true;					//Runs animations on the model when true
			void draw(var::coord2 position, float rotation);	//Draws the model at 'position' with roration 'rotation'
			void update();

			void newAnimation();
			void newAnimation(anim_container anim);

			void updateAnimation();
			void updateAnimation(vector<anim_container> *animations);
			void initializeAnimation();
			void initializeAnimation(vector<anim_container> *animations);

			void debugTree();				//Prints a tree diagram of the model via app::console()
		};
	}
}
#endif