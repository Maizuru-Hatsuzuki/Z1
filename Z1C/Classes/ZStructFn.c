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

void ZCreateArrayNextNode(void* pArray, void* vpData)
{
	LPZARRAY ptmpArray = (LPZARRAY)pArray;
	LPZARRAY pArrayNode = (LPZARRAY)malloc(sizeof(ZARRAY));
	ASSERT(pArrayNode);

	pArrayNode->emType				= ptmpArray->emType;
	pArrayNode->vpData				= vpData;
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

	return;
}