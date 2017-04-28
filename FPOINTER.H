#ifndef _FUNCTION_POINTERS_
#define _FUNCTION_POINTERS_

#include "object.h"
#include "event.h"

class   TObject;

typedef void (TObject::*FP_VOID_VOID)(void);
typedef void (TObject::*FP_VOID_TOBJECT)(TObject*);

#endif
