#ifndef __HN_HNLogicExport_H__
#define __HN_HNLogicExport_H__

#include "HNPlatformLogic/HNPlatformLogin.h"
#include "HNPlatformLogic/HNPlatformRegist.h"
#include "HNPlatformLogic/HNPlatformRoomList.h"
#include "HNPlatformLogic/HNPlatformGameList.h"
#include "HNPlatformLogic/HNPlatformSpreadManager.h"
#include "HNPlatformLogic/HNPlatformSpreadLogic.h"
#include "HNRoomLogic/HNRoomLogicBase.h"
#include "HNRoomLogic/HNGameLogicBase.h"
#include "HNRoomLogic/HNRoomDeskLogic.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "HNPCStartLogic/HNPCStartLogic.h"
#endif

using namespace HN;

#endif	//__HN_HNLogicExport_H__