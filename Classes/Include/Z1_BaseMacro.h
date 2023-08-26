#ifndef __Z1_BASEMACRO_H__
#define __Z1_BASEMACRO_H__

#define ZFALSE 0
#define ZTRUE  1
#define MAX_ADBCMD 1024
#define MAX_ZPRINTF 1024
#define MAX_CMDRET 10240

#define ASSERT(Condition) if (!(Condition)) __debugbreak()
#define Z1_RELEASE(p) { if (p) { free(p); (p) = NULL; } }

#define Z1_PROCESS_SUCCESS(Condition)		\
do											\
{											\
	if (Condition)							\
	{										\
		printf("[Z1_PROCESS_SUCCESS] ERR '%s' at line %d in %s::%s.\n", #Condition, __LINE__, __FILE__, __FUNCTION__);	\
		goto Exit0;							\
	}										\
} while (0);

#define Z1_PROCESS_ERROR(Condition)			\
do											\
{											\
	if (!(Condition))						\
	{										\
		printf("[Z1_PROCESS_ERROR] ERR '%s' at line %d in %s::%s.\n", #Condition, __LINE__, __FILE__, __FUNCTION__);	\
		goto Exit0;							\
	}										\
} while (0);


typedef int ZBOOL;

#endif // !__Z1_BASEMACRO_H__
