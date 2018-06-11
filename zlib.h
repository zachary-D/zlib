#pragma once

//Written by and copyright Zachary Damato
//zlib.h is part of the zlib submodule

//This file serves as a 'shortcut' to the other headers

//Preprocessor directives for enabling different code sections
//		Directive				Description
//		ZLIB_USING_CINDER		Enables Cinder-exclusive functions (i.e. everything in draw, windInfo, conversion from internal color type to Cinder's color type in varTypes)
//		ZLIB_USING_MODEL		Enables the model section.  (Requires ZLIB_USING_CINDER as a prerequisite)


#include "zlib/cryptography.h"
#include "zlib/draw.h"
#include "zlib/fileIO.h"
#include "zlib/input.h"
#include "zlib/math.h"
#include "zlib/model.h"
#include "zlib/varConv.h"
#include "zlib/varTypes.h"
#include "zlib/windInfo.h"