#pragma once

#if defined(USING_CINDER) && defined(USING_GRAPHICSSHELL)


using namespace std;

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

#include "zlib/zlib.h"



class shell : public AppNative {
private:
	void setup();
	void mouseDown(MouseEvent event);
	void update();



	void draw();	//The main draw function, called by cinder itself
public:
	void update_Pre() {}	//The update function to be overidden by the user, called before everything else in update()
	void update_Post() {}	//The update function to be overidden by the user, called after everything else in updates()

	void draw_Pre() {}	//The draw function to be overidden by the user, called before everything else in draw()
	void draw_Post() {}	//The draw functoin to be overidden by the user, called after everything else in draw()
};

void shell::setup()
{
}

void shell::mouseDown(MouseEvent event)
{
}

void shell::update()
{
}

void shell::draw()
{
	// clear out the window with black
	gl::clear(Color(0, 0, 0));
}

CINDER_APP_NATIVE(shell, RendererGl)





#endif