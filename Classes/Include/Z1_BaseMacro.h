#ifndef __Z1_BASEMACRO_H__
#define __Z1_BASEMACRO_H__

#define ZFALSE 0
#define ZTRUE  1

#define Z1_PROCESS_SUCCESS(Condition)		\
do											\
{											\
	if (Condition)							\
	{										\
		printf("[Z1_PROCESS_SUCCESS] ERR '%s' at line %d in %s::%s.", #Condition, __LINE__, __FILE__, __FUNCTION__);	\
		goto Exit0;							\
	}										\
} while (0);

#define Z1_PROCESS_ERROR(Condition)			\
do											\
{											\
	if (!(Condition))						\
	{										\
		goto Exit0;							\
	}										\
} while (0);

#endif // !__Z1_BASEMACRO_H__
