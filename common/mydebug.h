
#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdio.h>
#include <iostream>

#ifndef LOG_LEVEL_E
#define LOG_LEVEL_E 12
#endif

#ifndef LOG_LEVEL_I
#define LOG_LEVEL_I 14
#endif

#ifndef LOG_LEVEL_D
#define LOG_LEVEL_D 15
#endif

#ifndef LOG_LEVEL
#error LOG_LEVEL DEFINE required.
#endif

#ifndef LOG_FILE
#error -DLOG_FILE=stdout or -DLOG_FILE=[your_path] required.
#endif

#define kprintf(fmt, ...)  fprintf(LOG_FILE, fmt, ##__VA_ARGS__)
#define kkprintf(fmt, ...)  fprintf(LOG_FILE, "[%s \"line %d\"] : " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define kputs(str) puts(str)
#define kputchar(c) putchar(c)

#if (LOG_LEVEL >= LOG_LEVEL_E)
#if __linux__
#define LOGEE(fmt, ...) kkprintf(fmt, ##__VA_ARGS__)
#else
#define LOGEE(fmt, ...) do{ HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, LOG_LEVEL_E); kkprintf(fmt,##__VA_ARGS__);  SetConsoleTextAttribute(hConsole, 15); }while(0)
#endif /*linux*/
#else
#define LOGEE(fmt, ...) do{}while(0)
#endif /*LOG_LEVEL */

#if (LOG_LEVEL >= LOG_LEVEL_I)
#if __linux__
#define LOGII(fmt, ...) kkprintf(fmt, ##__VA_ARGS__)
#else
#define LOGII(fmt, ...) do{ HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, LOG_LEVEL_I); kkprintf(fmt,##__VA_ARGS__);  SetConsoleTextAttribute(hConsole, 15); }while(0)
#endif /*linux*/
#else
#define LOGII(fmt, ...) do{}while(0)
#endif /*LOG_LEVEL */

#if (LOG_LEVEL >= LOG_LEVEL_D)
#if __linux__
#define LOGDD(fmt, ...) kkprintf(fmt, ##__VA_ARGS__)
#else
#define LOGDD(fmt, ...) do{ HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, LOG_LEVEL_D); kkprintf(fmt,##__VA_ARGS__);  SetConsoleTextAttribute(hConsole, 15); }while(0)
#endif /*linux*/
#else
#define LOGDD(fmt, ...) do{}while(0)
#endif /*LOG_LEVEL */

#if (LOG_LEVEL >= LOG_LEVEL_E)
#if __linux__
#define LOGE(fmt, ...) kprintf(fmt, ##__VA_ARGS__)
#else
#define LOGE(fmt, ...) do{ HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, LOG_LEVEL_E); kprintf(fmt,##__VA_ARGS__);  SetConsoleTextAttribute(hConsole, 15); }while(0)
#endif /*linux*/
#else
#define LOGE(fmt, ...) do{}while(0)
#endif /*LOG_LEVEL */

#if (LOG_LEVEL >= LOG_LEVEL_I)
#if __linux__
#define LOGI(fmt, ...) kprintf(fmt, ##__VA_ARGS__)
#else
#define LOGI(fmt, ...) do{ HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, LOG_LEVEL_I); kprintf(fmt,##__VA_ARGS__);  SetConsoleTextAttribute(hConsole, 15); }while(0)
#endif /*linux*/
#else
#define LOGI(fmt, ...) do{}while(0)
#endif /*LOG_LEVEL */

#if (LOG_LEVEL >= LOG_LEVEL_D)
#if __linux__
#define LOGD(fmt, ...) kprintf(fmt, ##__VA_ARGS__)
#else
#define LOGD(fmt, ...) do{ HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, LOG_LEVEL_D); kprintf(fmt,##__VA_ARGS__);  SetConsoleTextAttribute(hConsole, 15); }while(0)
#endif /*linux*/
#else
#define LOGD(fmt, ...) do{}while(0)
#endif /*LOG_LEVEL */

#endif /* DEBUG_H_ */
