#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "HLog.h"

extern int LogLevel[7];

int main()
{
    hlog(__FILE__, __LINE__, LogLevel[0], 0, "this is a test");
    hlog(__FILE__, __LINE__, LogLevel[1], 1, "this is a test");
    hlog(__FILE__, __LINE__, LogLevel[2], 2, "this is a test");
    hlog(__FILE__, __LINE__, LogLevel[3], 3, "this is a test");
    hlog(__FILE__, __LINE__, LogLevel[4], 4, "this is a test");
    hlog(__FILE__, __LINE__, LogLevel[5], 5, "this is a test");
    hlog(__FILE__, __LINE__, LogLevel[6], 6, "this is a test");
}
