#include "Z1CV.h"


using namespace std;
using namespace cv;


ZBOOL ZcGetCVTargetPosition(const char* cszpCVImgPath, const float fThreshold, int* arrnPosRet, ZBOOL* pnRet)
{
	ZBOOL nRet = ZFALSE;
	double dMinVal = 0.f;
	double dMaxVal = 0.f;
	Point tMinLoc = {};
	Point tMaxVal = {};
	char arrszCVImgPath[MAX_PATH] = { 0 };
	sprintf_s(arrszCVImgPath, MAX_PATH, "%s\\%s.png", ROOTPATH_CVIMG_BGO, cszpCVImgPath);

	Mat mRes;
	Mat mCvTemplate = imread(arrszCVImgPath);
	Mat mCvSrcImg = imread(ROOTPATH_CVIMG_TARGET);
	int nCvSrcW = mCvTemplate.cols / 2;
	int nCvSrcH = mCvTemplate.rows / 2;

	matchTemplate(mCvSrcImg, mCvTemplate, mRes, TM_CCORR_NORMED);
	minMaxLoc(mRes, &dMinVal, &dMaxVal, &tMinLoc, &tMaxVal);

	if (fThreshold <= dMaxVal)
	{
		arrnPosRet[0] = tMaxVal.x + nCvSrcW;
		arrnPosRet[1] = tMaxVal.y + nCvSrcH;
		*pnRet = ZTRUE;
	}
	else
	{
		*pnRet = ZFALSE;
	}

	nRet = ZTRUE;
Exit0:
	return nRet;
}