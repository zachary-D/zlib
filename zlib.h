#pragma once

//Written by and copyright Zachary Damato
//zlib.h is part of the zlib submodule

//This file serves as a 'shortcut' to the other headers

//Preprocessor directives for enabling different code sections
//		Directive				Description
//		USING_CINDER			Enables Cinder-exclusive functions (i.e. conversion from internal color type to Cinder's color type)
//		ZLIB_ENABLE_TESTS		Enables functions for testing certain features within the library (either automated tests or tests that validate the state of certain classes (i.e. arrList))


#include "zlib/cryptography.h"
#include "zlib/draw.h"
#include "zlib/fileIO.h"
#include "zlib/input.h"
#include "zlib/math.h"
#include "zlib/model.h"
#include "zlib/varConv.h"
#include "zlib/varTypes.h"
#include "zlib/windInfo.h"