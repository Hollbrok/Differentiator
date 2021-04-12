#pragma once

#define _CRT_SECURE_NO_WARNINGS

using TYPE = int;
using VALUE = int;

struct Objects {
	
	struct Object* obj = nullptr;
	int number_of_objects = 0;
};

struct Object
{
	TYPE type_of_object;

	VALUE value;
};

enum TYPES
{
	OPERATOR	= 1,
	NUMBER		= 2,
	BRACKET		= 3,
	VARIABLE	= 4,
};

enum VALUES
{
	L_BRACKET_VAL	= 1,
	R_BRACKET_VAL	= 2,

	OP_PLUS_VAL		= 3,
	OP_MIN_VAL		= 4,
	OP_TIMES_VAL	= 5,
	OP_DEL_VAL		= 6,
	OP_POW_VAL		= 7,
};

