#include "../include/debug.h"

void debug_log(const char* x)
{
    printf("%s\n", x);
}

void debug_log(const std::string& x)
{
    printf("%s\n", x.c_str());
}

