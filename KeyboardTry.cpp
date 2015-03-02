#include "StdAfx.h"
#include "KeyboardTry.h"
#include "Global.h"
#include "IEntityClass.h"
#include "IEntitySystem.h"



void KeyboardTry::KeyboardEvent(EHARDWAREKEYBOARDEVENT EHardwareKeyboardEvent)
{
	switch (EHardwareKeyboardEvent)
	{		

		case EHARDWAREKEYBOARDEVENT_LEFT_KEYPRESSED:
			{
				//g_RTSCamera.Rotate(ECAMERAROTATEDIRECTION_LEFT, 0.02);
				g_RTSCamera.Move(ECAMERAMOVEDIRECTION_MOVELEFT, 0.5);
			}
		break;

		
		case EHARDWAREKEYBOARDEVENT_N_KEYRELEASED:
			{
				//g_RTSCamera.Rotate(ECAMERAROTATEDIRECTION_LEFT, 0.02);
				//g_RTSCamera.Move(ECAMERAMOVEDIRECTION_MOVELEFT, 0.5);
				g_IsNPressed=true;
			}
		break;

		case EHARDWAREKEYBOARDEVENT_RIGHT_KEYPRESSED:
			{
				//g_RTSCamera.Rotate(ECAMERAROTATEDIRECTION_RIGHT, 0.02);
				g_RTSCamera.Move(ECAMERAMOVEDIRECTION_MOVERIGHT, 0.5);
			}
		break;

		case EHARDWAREKEYBOARDEVENT_UP_KEYPRESSED:
			{
				//g_RTSCamera.Rotate(ECAMERAROTATEDIRECTION_UP, 0.02);
				g_RTSCamera.Move(ECAMERAMOVEDIRECTION_MOVEFORWARD, 0.5);
			}
		break;

		case EHARDWAREKEYBOARDEVENT_DOWN_KEYPRESSED:
			{
				//g_RTSCamera.Rotate(ECAMERAROTATEDIRECTION_DOWN, 0.02);
				g_RTSCamera.Move(ECAMERAMOVEDIRECTION_MOVEBACKWARDS, 0.5);
			}
		break;
	}
}