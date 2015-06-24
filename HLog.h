#ifndef _HLOG_H_
#define _HLOG_H_
 //Level类别
#define L_NO 0
#define L_DEBUG 1
#define L_TRACE 2
#define L_INFO 3
#define L_NOTICE 4
#define L_WARNING 5
#define L_FATAL 6

/*
int LogLevel[7] = {L_NO, L_DEBUG, L_TRACE, L_INFO, L_NOTICE, L_WARNING, L_FATAL}; 
//Level的名称
char LogLevelName[7][10] = {"NO", "DEBUG", "TRACE", "INFO", "NOTICE", "WARNING", "FATAL"}; 

*/
void hlog(const char *file, int line, int level, int status, const char *fmt, ...);

#endif
