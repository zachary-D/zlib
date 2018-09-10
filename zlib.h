#pragma once

//Written by and copyright Zachary Damato
//zlib.h is part of the zlib submodule

//This file serves as a 'shortcut' to the other headers

//Preprocessor directives for enabling different code sections
//		Directive				Description
//		ZLIB_USING_CINDER		Enables Cinder-exclusive functions (i.e. everything in draw, windInfo, conversion from internal color type to Cinder's color type in varTypes)
//		ZLIB_USING_MODEL		Enables the model section.  (Requires ZLIB_USING_CINDER as a prerequisite)
//		ZLIB_ENABLE_TESTS		Enables functions for testing certain features within the library (either automated tests or tests that validate the state of certain classes (i.e. arrList))

#include "cryptography.h"
#include "draw.h"
#include "fileIO.h"
#include "general.h"
#include "input.h"
#include "math.h"
#include "model.h"
#include "varConv.h"
#include "varTypes.h"
#include "windInfo.h"