#ifndef _TEVENT_
#define _TEVENT_

#include "object.h"

class   TObject;

typedef void (*TEvent)(TObject*, void* auxData);

#endif