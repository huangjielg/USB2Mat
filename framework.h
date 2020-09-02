#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"
#define  _WTL_USE_CSTRING
	
//#define _ATL_FREE_THREADED
#define _ATL_APARTMENT_THREADED
//#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将是显式的


#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "resource.h"
#include <atlbase.h>
#include <atlapp.h>
#include <atlwin.h>
#include <atlcom.h>
#include <atlctl.h>



#include <atlframe.h>
#include <atlgdi.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlddx.h>
#include <atlstr.h>
#include <atlfile.h>