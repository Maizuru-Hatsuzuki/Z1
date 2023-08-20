#ifndef __Z1CV_H__
#define __Z1CV_H__


#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "Z1C.h"

#ifdef __cplusplus
extern "C" {
#endif
	ZBOOL ZcGetCVTargetPosition(const char* cszpCVImgPath, const float fThreshold, int* arrnPosRet, ZBOOL* pnRet);
	//ZBOOL ZcafGetCardColor();
#ifdef __cplusplus
}
#endif



#endif // !__Z1CV_H__
