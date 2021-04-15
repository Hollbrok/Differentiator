#pragma once


#include <stdio.h>
#include <cstdio>
#include <windows.h>
//#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stddef.h>
#include <string> 
#include <stdlib.h>


const int NUMBER_OF_VARIABLES = 10;
const int MAX_NAME_SIZE = 10;

using TYPE = int;
using VALUE = int;

class tree_elements;
class tree;

struct Objects {

	struct Object* obj = nullptr;

	char* variables_names[NUMBER_OF_VARIABLES] = {};

	int number_of_objects = 0;
};

struct Object
{
	TYPE type_of_object;

	VALUE value;
};


enum TYPES
{
	OPERATOR = 1,
	NUMBER = 2,
	BRACKET = 3,
	VARIABLE = 4,
};

enum BRACKET_VALUES
{
	L_BRACKET_VAL = 1,
	R_BRACKET_VAL = 2,
};

enum OPERATORS_VALUES
{
	OP_PLUS_VAL = 3,
	OP_MIN_VAL = 4,
	OP_TIMES_VAL = 5,
	OP_DEL_VAL = 6,
	OP_POW_VAL = 7,
};

/* Debug memory allocation support */
#ifndef NDEBUG 
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h> 

#define SetDbgMemHooks()                                           \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))      

static class __Dummy
{
public:
	/* Class constructor */
	__Dummy(VOID)
	{
		SetDbgMemHooks();
	} /* End of '__Dummy' constructor */
} __ooppss;
#endif /* _DEBUG */ 

#ifndef NDEBUG
#  ifdef _CRTDBG_MAP_ALLOC 
#    define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#  endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */


#define NDEBUG
#ifndef NDEBUG
#define VERIFICATION                                                           \
{                                                                              \
  if (verification()) {                                                        \
    fprintf(stderr, "LINE: %d\nFILE:%s\nFUNC:%s"__LINE__, __FILE__, __func__); \
    assert(0);                                                                 \
  }                                                                            \
}                                                                               
#else
#define VERIFICATION ;
#endif /* _DEBUG */