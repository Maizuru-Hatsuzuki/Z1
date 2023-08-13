#ifndef __Z1_LOG_H__
#define __Z1_LOG_H__

#define LOGLEVEL_INFO	1
#define LOGLEVEL_WARING 2
#define LOGLEVEL_ERROR	3
#define LOGLEVEL_DEBUG	4

void Z1Printf(const short csFlags, const char* cszpText, ...);

#define Z1PRINTF_INFO(cszpText, ...)	Z1Printf(LOGLEVEL_INFO, cszpText, ##__VA_ARGS__)
#define Z1PRINTF_WARING(cszpText, ...)	Z1Printf(LOGLEVEL_WARING, cszpText, ##__VA_ARGS__);
#define Z1PRINTF_ERROR(cszpText, ...)	Z1Printf(LOGLEVEL_ERROR, cszpText, ##__VA_ARGS__);
#define Z1PRINTF_DEBUG(cszpText, ...)	Z1Printf(LOGLEVEL_DEBUG, cszpText, ##__VA_ARGS__);

#endif // !__Z1_LOG_H__
