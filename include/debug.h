#include <stdio.h>
#include <string>

#ifdef DEBUG
#define DEBUG_LOG(x) debug_log(x)
#else
#define DEBUG_LOG(x)
#endif


void debug_log(const char* x);
void debug_log(const std::string& x);

