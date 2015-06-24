#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "HLog.h"

#define LOG_FILE "hlog"
#define LOG_MAX_STRING_LEN 10240

int LogLevel[7] = {L_NO, L_DEBUG, L_TRACE, L_INFO, L_NOTICE, L_WARNING, L_FATAL}; 
//Level的名称
char LogLevelName[7][10] = {"NO", "DEBUG", "TRACE", "INFO", "NOTICE", "WARNING", "FATAL"}; 

static int getCurTime(char * strTime)
{
   struct tm* tmTime = NULL;
   size_t timeLen = 0;
   time_t tTime = 0;

   tTime = time(NULL);
   tmTime = localtime(&tTime);
   timeLen = strftime(strTime, 33, "%Y.%m.%d %H:%M:%S", tmTime);

   return timeLen;
}

static int openFile(FILE **pf)
{
    char fileName[1024];
    memset(fileName, 0, sizeof(fileName));
#ifdef WIN32
    sprintf("d:\\log\\%s", LOG_FILE);
#else
    sprintf(fileName, "%s/log/%s", getenv("HOME"), LOG_FILE);
#endif
    *pf = fopen(fileName, "a");
    if(*pf == NULL)
    {
        return -1;
    }
    return 0;
}

static void hcore(const char *file, int line, int level, int status, const char *fmt, va_list args)
{
    //记录日志str
    char str[LOG_MAX_STRING_LEN];
    int strLen = 0;
    char tmpStr[64];
    int tmpStrLen = 0;
    FILE *pf = NULL;

    //初始化
    memset(str, 0, LOG_MAX_STRING_LEN);
    memset(tmpStr, 0, 64);

    //加入Log时间
    tmpStrLen = getCurTime(tmpStr);
    tmpStrLen = sprintf(str, "[%s] ", tmpStr);
    strLen += tmpStrLen;

    //加入Log等级
    tmpStrLen = sprintf(str+strLen, "[%s] ", LogLevelName[level]);
    strLen += tmpStrLen;

    //加入Log状态
    if(status != 0)
    {
        tmpStrLen = sprintf(str+strLen, "[ERROR is %d] ", status); 
    }
    else
    {
        tmpStrLen = sprintf(str+strLen, "[SUCCESS] ");
    }
    strLen += tmpStrLen;

    //加入Log信息
    tmpStrLen = vsprintf(str+strLen, fmt, args);
    strLen += tmpStrLen;

    //加入Log发生文件
    tmpStrLen = sprintf(str+strLen, " [%s]", file);
    strLen += tmpStrLen;

    //加入Log发生行数
    tmpStrLen = sprintf(str+strLen, " [%d]\n", line);
    strLen += tmpStrLen;

    //打开Log文件
    int ret = openFile(&pf);
    if(ret == -1)
    {
        printf("open file error \n"); 
        return;
    }

    //写入Log文件
    fwrite(str, strLen, 1, pf);
    //fputs(str, pf);
    fclose(pf);

    return;
}

void hlog(const char *file, int line, int level, int status, const char *fmt, ...)
{
    va_list args;
    if(level == L_NO)
    {
        return;
    }

    //调用core打Log
    va_start(args, fmt);
    hcore(file, line, level, status, fmt, args);
    va_end(args);

    return;
}

void hdebug(const char *file, int line, const char *fmt, ...)
{
    hlog(file, line, LogLevel[1], 1, fmt);
}

void htrace(const char *file, int line, const char *fmt, ...)
{
    hlog(file, line, LogLevel[2], 2, fmt);
}

void hinfo(const char *file, int line, const char *fmt, ...)
{
    hlog(file, line, LogLevel[3], 3, fmt);
}

void hnotice(const char *file, int line, const char *fmt, ...)
{
    hlog(file, line, LogLevel[4], 4, fmt);
}

void hwarning(const char *file, int line, const char *fmt, ...)
{
    hlog(file, line, LogLevel[5], 5, fmt);
}

void hfatal(const char *file, int line, const char *fmt, ...)
{
    hlog(file, line, LogLevel[6], 6, fmt);
}
