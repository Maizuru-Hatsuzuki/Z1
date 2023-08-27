#include "Z1C.h"


void ZCreateArray(LPZARRAY* ppArray, ZARRAYTYPE emType)
{
	LPZARRAY pArrayNode = (LPZARRAY)malloc(sizeof(ZARRAY));
	ASSERT(pArrayNode);

	pArrayNode->emType = ZHEAD;
	pArrayNode->unCount = 0;
	pArrayNode->vpData = NULL;
	pArrayNode->ptNext = NULL;
	pArrayNode->ptHeadNode = pArrayNode;
	pArrayNode->ptTailNode = pArrayNode;
	pArrayNode->ptTailNode->ptNext = pArrayNode->ptHeadNode;

	ZCreateArrayFn(pArrayNode);

	*ppArray = pArrayNode;

	return;
}

void ZCreateArrayNextNode(void* pArray, void* vpData, const int cnSize)
{
	LPZARRAY ptmpArray = (LPZARRAY)pArray;
	LPZARRAY pArrayNode = (LPZARRAY)malloc(sizeof(ZARRAY));
	ASSERT(pArrayNode);
	
	pArrayNode->vpData = (void*)malloc(cnSize);
	memcpy_s(pArrayNode->vpData, cnSize, vpData, cnSize);

	pArrayNode->emType				= ptmpArray->emType;
	pArrayNode->ptHeadNode			= ptmpArray;
	pArrayNode->ptTailNode			= pArrayNode;
	pArrayNode->ptNext				= ptmpArray->ptTailNode->ptNext;
	ptmpArray->ptTailNode->ptNext	= pArrayNode;
	ptmpArray->ptTailNode			= pArrayNode;
	ptmpArray->unCount++;

	ZCreateArrayFn(pArrayNode);

	return;
}

void ZCreateArrayFn(LPZARRAY pArray)
{
	pArray->append = ZCreateArrayNextNode;
	pArray->findPos = ZFindData;

	return;
}

void ZFindData(void* pArray, const int cnPos, void** ppvData)
{
	void* vpRes = NULL;
	int nCount = 0;
	LPZARRAY ptmpArr = ((LPZARRAY)pArray)->ptNext;
	Z1_PROCESS_ERROR(ptmpArr->unCount);

	while (NULL != ptmpArr->ptNext && ptmpArr != ptmpArr->ptHeadNode)
	{
		if (cnPos == nCount)
		{
			vpRes = ptmpArr->vpData;
		}
		ptmpArr = ptmpArr->ptNext;
		nCount++;
	}

Exit0:
	*ppvData = vpRes;
	return;
}

void ZDeleteArray(LPZARRAY pArray)
{
	LPZARRAY ptmpArr = pArray;
	LPZARRAY ptmpNode = NULL;
	ptmpArr = ptmpArr->ptNext;

	Z1_PROCESS_SUCCESS(0 == pArray->unCount);

	while (NULL != ptmpArr->ptNext && ptmpArr != pArray->ptHeadNode)
	{
		ptmpNode = ptmpArr;
		ptmpArr = ptmpArr->ptNext;

		Z1_RELEASE(ptmpNode->vpData);
		Z1_RELEASE(ptmpNode);
	}

Exit0:
	Z1_RELEASE(pArray);
	return;
}

void ZDeleteArrayNode(void* pArray)
{

}