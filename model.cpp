#pragma once

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

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Text.h"
#include "cinder/app/App.h"
#include "cinder/Font.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/ImageIo.h"
#include "cinder/app/window.h"

using namespace std;
using namespace ci;
using namespace ci::app;

#include "draw/draw.h"
#include "model/model.h"
#include "varTypes/varConv.h"
#include "varTypes/varTypes.h"
#include "draw/windInfo.h"

using namespace window;

anim_segment::anim_segment()
{
	//isEmpty = true;
	rotRate = 0;
	constRate = false; 
	rotTarget = 0;
	rotClosestPath = true;
	rotClockwise = false;
	relativeToParent = true;
}

anim_segment::anim_segment(float rotationRate)
{
	//isEmpty = false;
	rotRate = rotationRate;
	constRate = true;
	rotTarget = 0;
	rotClosestPath = true;
	rotClockwise = false;
	relativeToParent = true;
}

anim_segment::anim_segment(float rotationTarget, bool useClosesetPath, bool useClockwisePath)
{
	//isEmpty = false;
	rotRate = 0;
	constRate = false;
	rotTarget = rotationTarget;
	rotClosestPath = useClosesetPath;
	rotClockwise = useClockwisePath;
	relativeToParent = true;
}

anim_segment::anim_segment(float rotationTarget, bool useClosesetPath, bool useClockwisePath, bool isRelativeToParent)
{
	//isEmpty = false;
	rotRate = 0;
	constRate = false;
	rotTarget = rotationTarget;
	rotClosestPath = useClosesetPath;
	rotClockwise = useClockwisePath;
	relativeToParent = isRelativeToParent;
}

void anim_segment::createAbove()
{
	childrenAbove.push_back(anim_segment());
}

void anim_segment::createAbove(anim_segment child)
{
	childrenAbove.push_back(child);
}

void anim_segment::createBelow()
{
	childrenBelow.push_back(anim_segment());
}

void anim_segment::createBelow(anim_segment child)
{
	childrenBelow.push_back(child);
}

void anim_segment::debugTree(int depth)
{
	if(childrenBelow.size() > 0)
	{
		for(int x = 0; x < depth; x++)
		{
			app::console() << "  ";
		}
		app::console() << "childrenBelow" << endl;
		for(int x = 0; x < depth; x++)
		{
			app::console() << "  ";
		}
		app::console() << "{" << endl;
		for(int x = 0; x < childrenBelow.size(); x++)
		{
			childrenBelow[x].debugTree(depth + 1);
		}
		for(int x = 0; x < depth; x++)
		{
			app::console() << "  ";
		}
		app::console() << "}" << endl;
	}
	for(int x = 0; x < depth; x++)
	{
		app::console() << "  ";
	}
	app::console() << "[rotRate]" << endl;
	for(int x = 0; x < depth; x++)
	{
		app::console() << "  ";
	}
	app::console() << "[ " + conv::toString(rotRate) + " ]" << endl;
	if(childrenAbove.size() > 0)
	{
		for(int x = 0; x < depth; x++)
		{
			app::console() << "  ";
		}
		app::console() << "childrenAbove" << endl;
		for(int x = 0; x < depth; x++)
		{
			app::console() << "  ";
		}
		app::console() << "{" << endl;
		for(int x = 0; x < childrenAbove.size(); x++)
		{
			//app::console() << "c";
			childrenAbove[x].debugTree(depth + 1);
		}
		for(int x = 0; x < depth; x++)
		{
			app::console() << "  ";
		}
		app::console() << "}" << endl;
	}
}

void anim_container::newCycle()
{
	//app::console();
	cycles.push_back(anim_segment());
	cycle_length.push_back(10);
}

void anim_container::newCycle(anim_segment anim)
{
	cycles.push_back(anim);
	cycle_length.push_back(10);
}

int anim_container::getCurrentCycleLength()
{
	return cycle_length[cycleNum];
}

void anim_container::debugTree()
{
	app::console() << "  cycle container" << endl;
	for(int x = 0; x < cycles.size(); x++)
	{
		app::console() << "  {[" << x << "]" << endl;
		cycles[x].debugTree(2);
		app::console() << "  }" << endl;
	}
}

model_segment::model_segment()
{
	point1 = var::coord2(-1, -1);
	point2 = var::coord2(1, 1);
	color = var::color_RGB(0, 1, 0);
	parentJoint = var::coord2(0, 0);
	childJoint = var::coord2(0, 0);
	rotation = 0;
	baseRotation = 0;
	rotationRate = 0;
	absoluteRotation = false;
	debugMode = false;
	isTextured = false;
}

model_segment::model_segment(var::coord2 firstPoint, var::coord2 secondPoint)
{
	point1 = firstPoint;
	point2 = secondPoint;
	color = var::color_RGB(0, 1, 0);
	parentJoint = var::coord2(0, 0);
	childJoint = var::coord2(0, 0);
	rotation = 0;
	baseRotation = 0;
	rotationRate = 0;
	absoluteRotation = false;
	debugMode = false;
	isTextured = false;
}

model_segment::model_segment(var::coord2 firstPoint, var::coord2 secondPoint, var::coord2 joint_Parent, var::coord2 joint_Child)
{
	point1 = firstPoint;
	point2 = secondPoint;
	parentJoint = joint_Parent;
	childJoint = joint_Child;
	color = var::color_RGB(0, 1, 0);
	rotation = 0;
	baseRotation = 0;
	rotationRate = 0;
	absoluteRotation = false;
	debugMode = false;
	isTextured = false;
}

void model_segment::createBelow()
{
	childrenBelow.push_back(model_segment());
}

void model_segment::createBelow(model_segment child)
{
	childrenBelow.push_back(child);
}

void model_segment::createSpecialBelow()
{
	if(specialBelowSegment != NULL)
	{
		eraseBelow(specialBelowSegment);
	}
	createBelow();
	specialBelowSegment = sizeBelow() - 1;
}

void model_segment::createSpecialBelow(model_segment _child)
{
	if(specialBelowSegment != NULL)
	{
		eraseBelow(specialBelowSegment);
	}
	createBelow(_child);
	specialBelowSegment = sizeBelow() - 1;
}

int model_segment::sizeBelow()
{
	return childrenBelow.size();
}

bool model_segment::eraseBelow(int number)
{
	assert(number > sizeBelow());
	if(number > sizeBelow()) return false;
	else
	{
		childrenBelow.erase(childrenBelow.begin() + number);
		return true;
	}
}

bool model_segment::eraseSpecialChildBelow()
{
	if(specialBelowSegment != NULL)
	{
		eraseBelow(specialBelowSegment);
		specialBelowSegment == NULL;
		return true;
	}
	else return false;
}

model_segment *model_segment::getChildBelow(int number)
{
	assert(!(number > sizeBelow()));
	if(number > sizeBelow())
	{
		_DEBUG_ERROR("Returned NULL!");
		return NULL;
	}
	else return &childrenBelow[number];
}

model_segment* model_segment::getSpecialChildBelow()
{
	return getChildBelow(specialBelowSegment);
}

void model_segment::createAbove()
{
	childrenAbove.push_back(model_segment());
}

void model_segment::createAbove(model_segment child)
{
	childrenAbove.push_back(child);
}

void model_segment::createSpecialAbove()
{
	if(specialAboveSegment != NULL)
	{
		eraseAbove(specialAboveSegment);
	}
	createAbove();
	specialAboveSegment = sizeAbove() - 1;
}

void model_segment::createSpecialAbove(model_segment _child)
{
	if(specialAboveSegment != NULL)
	{
		eraseAbove(specialAboveSegment);
	}
	createAbove(_child);
	specialAboveSegment = sizeAbove() - 1;
}

int model_segment::sizeAbove()
{
	return childrenAbove.size();
}

bool model_segment::eraseAbove(int number)
{
	assert(number > sizeAbove());
	if(number > sizeAbove()) return false;
	else
	{
		childrenBelow.erase(childrenAbove.begin() + number);
		return true;
	}
}

bool model_segment::eraseSpecialChildAbove()
{
	if(specialAboveSegment != NULL)
	{
		eraseAbove(specialAboveSegment);
		specialAboveSegment == NULL;
		return true;
	}
	else return false;
}

model_segment *model_segment::getChildAbove(int number)
{
	assert(!(number > sizeAbove()));
	if(number > sizeAbove())
	{
		_DEBUG_ERROR("Returned NULL!");
		return NULL;
	}
	else return &childrenAbove[number];
}

model_segment* model_segment::getSpecialChildAbove()
{
	return getChildAbove(specialAboveSegment);
}

void model_segment::draw(var::coord2 position, float parentRotation, bool runAnimation)//, vector<anim_segment> *animations)
{
	if(absoluteRotation == true) parentRotation = 0;
	for(int x = 0; x < childrenBelow.size(); x++)
	{
		childrenBelow[x].draw(getRotation((rotation + parentRotation + baseRotation) * -1, position, position + childrenBelow[x].parentJoint - childJoint, childrenBelow[x].debugMode), rotation + baseRotation + parentRotation, runAnimation);
	}
	gl::color(color.toColor());
	if(isTextured)
	{
		draw::drawTexture(segTexture, position + point1 - childJoint, position + point2 - childJoint, position, rotation + baseRotation + parentRotation);
	}
	else draw::drawRect(position + point1 - childJoint, position + point2 - childJoint, position, rotation + baseRotation + parentRotation);
	for(int x = 0; x < childrenAbove.size(); x++)
	{
		childrenAbove[x].draw(getRotation((rotation + parentRotation + baseRotation) * -1, position, position + childrenAbove[x].parentJoint - childJoint, childrenAbove[x].debugMode), rotation + baseRotation + parentRotation, runAnimation);
	}
	if(runAnimation == true)
	{
		if(absoluteRotation == false) rotation += rotationRate;
		point1 += point1Rate;
		point2 += point2Rate;
		childJoint += childJointRate;
		parentJoint += parentJointRate;
	}
}

bool model_segment::setTexture(string _filepath)
{
	setTexture(loadImage(loadAsset(_filepath)));
	return false;
}

bool model_segment::setTexture(gl::Texture _texture)
{
	segTexture = _texture;
	isTextured = true;
	return true;
}

bool model_segment::hasTexture()
{
	return isTextured;
}

void model_segment::setColor(var::color_RGB _color)
{
	color = _color;
}

void model_segment::update()
{
	//Model rotation
	if(rotation < 0) rotation += 360;
	else if(rotation >= 360) rotation -= 360;
	for(int x = 0; x < childrenBelow.size(); x++)
	{
		childrenBelow[x].update();
	}
	for(int x = 0; x < childrenAbove.size(); x++)
	{
		childrenAbove[x].update();
	}

	if(point1Rate != var::coord2(0, 0) || point2Rate != var::coord2(0, 0))
	{
		int a = 0;
	}

	//Coordinate translation
	point1 += point1Rate;
	point2 += point2Rate;
}

void model_segment::updateAnimation(anim_segment *animations, int cycleLength)
{
	//Rotation
	if(animations->rotChange == true)
	{
		if(animations->relativeToParent == false)
		{
			absoluteRotation = true;
			rotation = animations->rotTarget;
		}
		else if(animations->constRate == false)
		{
			absoluteRotation = false;
			float rot = 0;	//The angle that the part will need to rotate to reach its target
			float currentRot = rotation;// -baseRotation + parentRotation;
			while(currentRot >= 360) currentRot -= 360;
			while(currentRot < 0) currentRot += 360;
			if(animations->rotClosestPath == true)
			{
				rot = animations->rotTarget - currentRot;
				while(rot > 180) rot -= 360;
				while(rot < -180) rot += 360;
			}
			else if(animations->rotClockwise == true)
			{
				rot = currentRot - animations->rotTarget;
			}
			else
			{
				rot = animations->rotTarget - currentRot;
			}
			if(cycleLength != 0) animations->rotRate = rot / cycleLength;
			else animations->rotRate = rot;
		}
		rotationRate = animations->rotRate;
	}

	//Sizing
	if(animations->sizeChange == true)
	{
		if(animations->constSizeRate == true)
		{
			point1Rate = animations->point1Rate;
			point2Rate = animations->point2Rate;
		}
		else if(cycleLength != 0)
		{
			point1Rate = (animations->point1 - point1) / cycleLength;
			point2Rate = (animations->point2 - point2) / cycleLength;
		}
		else
		{
			point1Rate = (animations->point1 - point1);
			point2Rate = (animations->point2 - point2);
		}
	}

	//Joint location
	if (animations->jointChange == true)
	{
		if (animations->constJointChangeRate == true)
		{
			parentJointRate = animations->parentJointRate;
			childJointRate = animations->childJointRate;
		}
		else if (cycleLength != 0)
		{
			parentJointRate = (animations->parentJoint - parentJoint) / cycleLength;
			childJointRate = (animations->childJoint - childJoint) / cycleLength;
		}
		else
		{
			parentJointRate = (animations->parentJoint - parentJoint);
			childJointRate = (animations->childJoint - childJoint);
		}
	}

	for(int x = 0; x < animations->childrenBelow.size() && x < childrenBelow.size(); x++)
	{
		childrenBelow[x].updateAnimation(&(animations->childrenBelow[x]), cycleLength);
	}
	for(int x = 0; x < animations->childrenAbove.size()	&& x < childrenAbove.size(); x++)
	{
		childrenAbove[x].updateAnimation(&(animations->childrenAbove[x]), cycleLength);
	}
}

void model_segment::debugTree(int depth)
{
	if(childrenBelow.size() > 0)
	{
		for(int x = 0; x < depth; x++)
		{
			app::console() << "  ";
		}
		app::console() << "childrenBelow" << endl;
		for(int x = 0; x < depth; x++)
		{
			app::console() << "  ";
		}
		app::console() << "{" << endl;
		for(int x = 0; x < childrenBelow.size(); x++)
		{
			//app::console() << "a";
			childrenBelow[x].debugTree(depth + 1);
		}
		for(int x = 0; x < depth; x++)
		{
			app::console() << "  ";
		}
		app::console() << "}" << endl;
	}
	for(int x = 0; x < depth; x++)
	{
		app::console() << "  ";
	}
	app::console() << "[p1, p2, cJ, pJ]" << endl;
	for(int x = 0; x < depth; x++)
	{
		app::console() << "  ";
	}
	app::console() << "[ " + point1.toString() + "  | " + point2.toString() + " | " + childJoint.toString() + " | " + parentJoint.toString() + " ]" << endl;
	if(childrenAbove.size() > 0)
	{
		for(int x = 0; x < depth; x++)
		{
			app::console() << "  ";
		}
		app::console() << "childrenAbove" << endl;
		for(int x = 0; x < depth; x++)
		{
			app::console() << "  ";
		}
		app::console() << "{" << endl;
		for(int x = 0; x < childrenAbove.size(); x++)
		{
			//app::console() << "c";
			childrenAbove[x].debugTree(depth + 1);
		}
		for(int x = 0; x < depth; x++)
		{
			app::console() << "  ";
		}
		app::console() << "}" << endl;
	}
}

model::model()
{
	root = model_segment();
	root.point1 = var::coord2(0,0);
	root.point2 = var::coord2(1, 1);
	root.color = var::color_RGB(0, 0, 1);
	root.parentJoint = var::coord2(0, 0);
	root.childJoint = var::coord2(0, 0);
	root.rotation = 0;
	root.baseRotation = 0;
	root.isTextured = false;
	root.rotationRate = 0;
	//$$
}

void model::draw(var::coord2 position, float rotation)
{
	root.draw(root.parentJoint + position, rotation, runAnimations);
	if(runAnimations == true)			//When true, runs through animations
	{
		for(int x = 0; x < animations.size(); x++)		//Loops through every animation
		{
			animations[x].currTime++;					//Incriments the time counter
			while(animations[x].cycle_length.size() <= animations[x].cycleNum) animations[x].cycle_length.push_back(10);	//If the cycle length for this cycle hasn't been set, fill the blanks in with 10 for a default value
			if(animations[x].currTime >= animations[x].cycle_length[animations[x].cycleNum])		//If the time counter has exceeded the time limit for the animation, move on to the next cycle in the animation
			{
				animations[x].cycleNum++;			//Sets the cycle number to the next cycle
				animations[x].currTime = 0;			//Resets the time counter
				if(animations[x].cycleNum >= animations[x].cycles.size())		//If the cycle counter has exceeded the number of cycles
				{
					animations[x].cycleNum = 0;
					if(animations[x].doNotLoop == true)					//If this animation should not loop
					{
						animations.erase(animations.begin() + x);		//Delete it
						x--;
					}
				}
				updateAnimation();
			}
		}
	}

}

void model::update()
{
	root.update();
}

void model::newAnimation()
{
	animations.push_back(anim_container());
	//animations[animations.size() - 1].newCycle();
}

void model::newAnimation(anim_container anim)
{
	animations.push_back(anim);
}

void model::updateAnimation()
{
	for(int x = 0; x < animations.size(); x++)
	{
		if(animations[x].cycles.size() > 0 && animations[x].cycles.size() > animations[x].cycleNum) root.updateAnimation(&animations[x].cycles[animations[x].cycleNum], animations[x].cycle_length[animations[x].cycleNum] - animations[x].currTime);
	}
}

void model::updateAnimation(vector<anim_container> *animations)
{
	for(int x = 0; x < animations->size(); x++)
	{
		if((*animations)[x].cycles.size() > 0 && (*animations)[x].cycles.size() > (*animations)[x].cycleNum) root.updateAnimation(&(*animations)[x].cycles[(*animations)[x].cycleNum], (*animations)[x].cycle_length[(*animations)[x].cycleNum]);
	}
}

void model::initializeAnimation()
{
	for(int x = 0; x < animations.size(); x++)
	{
		root.updateAnimation(&animations[x].cycles[animations[x].cycleNum], animations[x].cycle_length[animations[x].cycleNum] - animations[x].currTime);
	}
}

void model::initializeAnimation(vector<anim_container> *animations)
{
	for(int x = 0; x < animations->size(); x++)
	{
		root.updateAnimation(&(*animations)[x].cycles[(*animations)[x].cycleNum], (*animations)[x].cycle_length[(*animations)[x].cycleNum]);
	}
}

void model::debugTree()
{
	app::console() << "root container" << endl;
	app::console() << "{" << endl;
	root.debugTree(1);
	app::console() << "}" << endl;
	app::console() << "Animation container" << endl;
	app::console() << "{" << endl;
	for(int x = 0; x < animations.size(); x++)
	{
		animations[x].debugTree();
		for(int y = 0; y < animations[x].cycle_length.size(); y++)
		{
			app::console() << "cycle: " << y << " time: " << animations[x].cycle_length[y] << endl;
		}
	}
	app::console() << "}" << endl;
}