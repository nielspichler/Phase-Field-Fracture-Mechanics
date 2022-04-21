#ifndef __COMMON_HEADERDEF__
#define __COMMON_HEADERDEF__


#include <memory>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <ostream>
#include <iomanip>   // for setprecision

#define __BEGIN_TEHPC__ namespace tehpc {
#define __END_TEHPC__  }

#define GET_VARIABLE_NAME(Variable) (#Variable) //macro returns Variable name

using UInt = unsigned int;

#endif /* __COMMON_HEADERDEF__ */
