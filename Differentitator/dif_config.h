#pragma once

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



