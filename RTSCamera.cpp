#include "StdAfx.h"
#include "RTSCamera.h"
#include "IGameFramework.h"
#include "IEntity.h"
#include "IEntitySystem.h"
#include "Global.h"
#include "IActorSystem.h"
#include "MathUtil.h"
#include <iostream>
#include <fstream>

std::ofstream output;

string RTSCamera::GetLevelName()
{
	m_pGameFrameWork = gEnv->pGame->GetIGameFramework();

	string LevelName = m_pGameFrameWork->GetLevelName();

	return LevelName;
}

void RTSCamera::CreateRTSCamera()
{
			output.open("K:\\output.txt");
			//Assign the IViewSystem to a pointer named m_pIViewSystem
			m_pIViewSystem = gEnv->pGameFramework->GetIViewSystem();

			//Assign the IEntitySystem to a pointer nameed m_pIEntitySystem
			m_pIEntitySystem = gEnv->pSystem->GetIEntitySystem();

			//Assign our camera entity in the game world to a pointer named m_pIEntity
			g_RTSCamera.m_pGameCameraEntity = m_pIEntitySystem->FindEntityByName("GameCamera");

			//m_pScriptTable = g_RTSCamera.m_pGameCameraEntity->GetScriptTable();

			//Get Our GameCamera's EntityId and store it into a variable named m_ViewId
			if(g_RTSCamera.m_pGameCameraEntity!= NULL)
				m_EntityId = g_RTSCamera.m_pGameCameraEntity->GetId();

			//Activate our Game Camera Entity
			//m_pGameCameraEntity->Activate(true);

			//Create a new View and assign it to a pointer named m_pIView
			m_pRTSCameraView = m_pIViewSystem->CreateView();
			
			//Get the View ID of our new camera and assign it to a variable named RTSCameraViewID
			m_RTSCameraViewID = m_pIViewSystem->GetViewId(m_pRTSCameraView);

			//Remove the currently active View
			m_pIViewSystem->RemoveView(m_pIViewSystem->GetActiveViewId());

			//Set our new view as the active one
			m_pIViewSystem->SetActiveView(m_pRTSCameraView);

			//Give Initial values to our camera's view params
			CreateViewParams(m_RTSCameraViewID, m_EntityId, g_RTSCamera.m_pGameCameraEntity);

			//Set View params for our camera
			m_pRTSCameraView->SetCurrentParams(m_CurViewParams);

			//Link Our new view to the game camera entity in our world
			m_pRTSCameraView->LinkTo(g_RTSCamera.m_pGameCameraEntity);

			gEnv->pLog->Log("Created RTSCamera");

			m_RTSCameraExist = true;
}







void RTSCamera::CreateViewParams(unsigned int CameraId, EntityId GameCameraId, IEntity *GameCamera)
{
		m_CurViewParams.position = GameCamera->GetWorldPos();
		m_CurViewParams.rotation = GameCamera->GetWorldRotation();
		m_CurViewParams.nearplane = 0.0f;
		m_CurViewParams.fov = 0.6f;
		m_CurViewParams.viewID = CameraId;
		m_CurViewParams.groundOnly = false;
		m_CurViewParams.shakingRatio = 0.0f;
		m_CurViewParams.currentShakeQuat = IDENTITY;
		m_CurViewParams.currentShakeShift = ZERO;
		m_CurViewParams.idTarget = GameCameraId;
		m_CurViewParams.targetPos = GameCamera->GetWorldPos();
		m_CurViewParams.frameTime = 60.0f;
		m_CurViewParams.angleVel = 0.0f;
		m_CurViewParams.vel = 0.0f;
		m_CurViewParams.dist = 0.0f;
		m_CurViewParams.blend = true;
}










void RTSCamera::Update()
{
	//Movement Logic
	
	if (ShouldMoveForward())
	{
		if (ShouldMoveForwardLeft())
		{
			//Move(ECAMERAMOVEDIRECTION_MOVEFORWARDLEFT, 0.5);
			g_RTSCamera.Rotate(ECAMERAROTATEDIRECTION_UP, 0.02);
		}

		else if (ShouldMoveForwardRight())
		{
			//Move(ECAMERAMOVEDIRECTION_MOVEFORWARDRIGHT, 0.5);
			g_RTSCamera.Rotate(ECAMERAROTATEDIRECTION_UP, 0.02);
		}

		else
		{
			//Move(ECAMERAMOVEDIRECTION_MOVEFORWARD, 0.5);
			g_RTSCamera.Rotate(ECAMERAROTATEDIRECTION_UP, 0.02);
		}
	}

	if (ShouldMoveBackwards())
	{
		if (ShouldMoveBackwardsLeft())
		{
			//Move(ECAMERAMOVEDIRECTION_MOVEBACKWARDSLEFT, 0.5);
			g_RTSCamera.Rotate(ECAMERAROTATEDIRECTION_DOWN, 0.02);
		}

		else if (ShouldMoveBackwardsRight())
		{
			//Move(ECAMERAMOVEDIRECTION_MOVEBACKWARDSRIGHT, 0.5);
			g_RTSCamera.Rotate(ECAMERAROTATEDIRECTION_DOWN, 0.02);
		}

		else
		{
			//Move(ECAMERAMOVEDIRECTION_MOVEBACKWARDS, 0.5);
			g_RTSCamera.Rotate(ECAMERAROTATEDIRECTION_DOWN, 0.02);
		}
	}

	if (ShouldMoveLeft())
	{
		//Move(ECAMERAMOVEDIRECTION_MOVELEFT, 0.5);
		g_RTSCamera.Rotate(ECAMERAROTATEDIRECTION_LEFT, 0.02);
	}

	if (ShouldMoveRight())
	{
		//Move(ECAMERAMOVEDIRECTION_MOVERIGHT, 0.5);
		g_RTSCamera.Rotate(ECAMERAROTATEDIRECTION_RIGHT, 0.02);
	}
}







bool RTSCamera::ShouldMoveForward()
{
	int ScreenHeight = gEnv->pRenderer->GetHeight();
	int ScreenWidth = gEnv->pRenderer->GetWidth();

	float MouseScreenYPos = 0;
	float MouseScreenXPos = 0;

	if (gEnv->pHardwareMouse)
	{
		//gEnv->pHardwareMouse->
		gEnv->pHardwareMouse->GetHardwareMouseClientPosition(&MouseScreenXPos, &MouseScreenYPos);

		if (MouseScreenYPos < ((ScreenHeight - ScreenHeight) + 10))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	else
	{
		return false;
	}
	
}







bool RTSCamera::ShouldMoveBackwards()
{
	int ScreenHeight = gEnv->pRenderer->GetHeight();
	int ScreenWidth = gEnv->pRenderer->GetWidth();

	float MouseScreenYPos = 0;
	float MouseScreenXPos = 0;

	if (gEnv->pHardwareMouse)
	{
		gEnv->pHardwareMouse->GetHardwareMouseClientPosition(&MouseScreenXPos, &MouseScreenYPos);

		if (MouseScreenYPos > (ScreenHeight - 10))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	else
	{
		return false;
	}
}








bool RTSCamera::ShouldMoveLeft()
{
	int ScreenHeight = gEnv->pRenderer->GetHeight();
	int ScreenWidth = gEnv->pRenderer->GetWidth();

	float MouseScreenYPos = 0;
	float MouseScreenXPos = 0;

	if (gEnv->pHardwareMouse)
	{
		gEnv->pHardwareMouse->GetHardwareMouseClientPosition(&MouseScreenXPos, &MouseScreenYPos);

		if (MouseScreenXPos < ((ScreenWidth - ScreenWidth) + 10))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	else
	{
		return false;
	}
}









bool RTSCamera::ShouldMoveRight()
{
	int ScreenHeight = gEnv->pRenderer->GetHeight();
	int ScreenWidth = gEnv->pRenderer->GetWidth();

	float MouseScreenYPos = 0;
	float MouseScreenXPos = 0;

	if (gEnv->pHardwareMouse)
	{
		gEnv->pHardwareMouse->GetHardwareMouseClientPosition(&MouseScreenXPos, &MouseScreenYPos);

		if (MouseScreenXPos > (ScreenWidth - 10))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	else
	{
		return false;
	}
}








bool RTSCamera::ShouldMoveForwardLeft()
{
	int ScreenHeight = gEnv->pRenderer->GetHeight();
	int ScreenWidth = gEnv->pRenderer->GetWidth();

	float MouseScreenYPos = 0;
	float MouseScreenXPos = 0;

	if (gEnv->pHardwareMouse)
	{
		gEnv->pHardwareMouse->GetHardwareMouseClientPosition(&MouseScreenXPos, &MouseScreenYPos);
		//gEnv->pHardwareMouse->GetHardwareMouseClientPosition(&MouseScreenXPos, &MouseScreenYPos);

		if ((MouseScreenYPos < ((ScreenHeight - ScreenHeight) + 10)) && (MouseScreenXPos < ((ScreenWidth - ScreenWidth) + 10)))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	else
	{
		return false;
	}
}







bool RTSCamera::ShouldMoveForwardRight()
{
	int ScreenHeight = gEnv->pRenderer->GetHeight();
	int ScreenWidth = gEnv->pRenderer->GetWidth();

	float MouseScreenYPos = 0;
	float MouseScreenXPos = 0;

	if (gEnv->pHardwareMouse)
	{
		gEnv->pHardwareMouse->GetHardwareMouseClientPosition(&MouseScreenXPos, &MouseScreenYPos);

		if ((MouseScreenYPos < ((ScreenHeight - ScreenHeight) + 10)) && (MouseScreenXPos > (ScreenWidth - 10)))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	else
	{
		return false;
	}
}






bool RTSCamera::ShouldMoveBackwardsLeft()
{
	int ScreenHeight = gEnv->pRenderer->GetHeight();
	int ScreenWidth = gEnv->pRenderer->GetWidth();

	float MouseScreenYPos = 0;
	float MouseScreenXPos = 0;

	if (gEnv->pHardwareMouse)
	{
		gEnv->pHardwareMouse->GetHardwareMouseClientPosition(&MouseScreenXPos, &MouseScreenYPos);

		if ((MouseScreenYPos > (ScreenHeight - 10)) && (MouseScreenXPos < ((ScreenWidth - ScreenWidth) + 10)))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	else
	{
		return false;
	}
}









bool RTSCamera::ShouldMoveBackwardsRight()
{
	int ScreenHeight = gEnv->pRenderer->GetHeight();
	int ScreenWidth = gEnv->pRenderer->GetWidth();

	float MouseScreenYPos = 0;
	float MouseScreenXPos = 0;

	if (gEnv->pHardwareMouse)
	{
		gEnv->pHardwareMouse->GetHardwareMouseClientPosition(&MouseScreenXPos, &MouseScreenYPos);

		if ((MouseScreenYPos > (ScreenHeight - 10)) && (MouseScreenXPos > (ScreenWidth - 10)))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	else
	{
		return false;
	}
}








void RTSCamera::Move(ECAMERAMOVEDIRECTION eCameraMoveDirection, float Speed)
{
	Speed*=4;

	if(g_RTSCamera.m_pGameCameraEntity!=NULL){
		Vec3 CamCurPos = g_RTSCamera.m_pGameCameraEntity->GetPos();
		float tempZ=gEnv->p3DEngine->GetTerrainElevation(CamCurPos.x,CamCurPos.y,false);
		std::string asd = "xpos "+ToString(CamCurPos.x)+" ypos "+ToString(CamCurPos.y)+" zpos "+ToString(tempZ)+"\n";
		char *out =(char*)calloc(asd.size(),sizeof(char));
		for(int i = 0;i<asd.size();i++){
		
			out[i]=asd.at(i);
		}
		/*gEnv->pLog->Log(ToString(CamCurPos.x)+" ypos"+ToString(CamCurPos.y)+" zpos"+ToString(tempZ));*/
		output.write(out,asd.size());
		//output << asd;
	}
	switch (eCameraMoveDirection)
	{

	case ECAMERAMOVEDIRECTION_MOVEFORWARD:
		{
			if (g_RTSCamera.m_pGameCameraEntity)
			{

				Vec3 CamCurPos = g_RTSCamera.m_pGameCameraEntity->GetPos();

				Ang3 CamCurRot = g_RTSCamera.m_pGameCameraEntity->GetWorldAngles();

				Vec3 CamCurVecRot = MathUtil::Ang2DirIgnoreZ(CamCurRot);

				Vec3 FinalPos = CamCurPos + (CamCurVecRot * Speed);

				g_RTSCamera.m_pGameCameraEntity->SetPos(FinalPos);
			}
		}
		break;

		case EHARDWAREKEYBOARDEVENT_N_KEYRELEASED:
		{
				g_IsNPressed=true;
			
		}
		break;


		case ECAMERAMOVEDIRECTION_MOVEBACKWARDS:
		{
			if (g_RTSCamera.m_pGameCameraEntity)
			{
				Vec3 CamCurPos = g_RTSCamera.m_pGameCameraEntity->GetPos();

				Ang3 CamCurRot = g_RTSCamera.m_pGameCameraEntity->GetWorldAngles();

				Vec3 CamCurVecRot = MathUtil::Ang2DirIgnoreZ(CamCurRot);

				Vec3 FinalPos = CamCurPos - (CamCurVecRot * Speed);

				g_RTSCamera.m_pGameCameraEntity->SetPos(FinalPos);
			}
		}
		break;


		case ECAMERAMOVEDIRECTION_MOVELEFT:
		{
			if (g_RTSCamera.m_pGameCameraEntity)
			{
				Vec3 CamCurPos = g_RTSCamera.m_pGameCameraEntity->GetPos();

				Ang3 CamCurRot = g_RTSCamera.m_pGameCameraEntity->GetWorldAngles();

				Vec3 CamCurVecRot = MathUtil::Ang2DirIgnoreZ(CamCurRot - DEG2RAD(Ang3(0,0,90)));

				Vec3 FinalPos = CamCurPos - (CamCurVecRot * Speed);

				g_RTSCamera.m_pGameCameraEntity->SetPos(FinalPos);
			}
		}
		break;


		case ECAMERAMOVEDIRECTION_MOVERIGHT:
		{
			if (g_RTSCamera.m_pGameCameraEntity)
			{
				Vec3 CamCurPos = g_RTSCamera.m_pGameCameraEntity->GetPos();

				Ang3 CamCurRot = g_RTSCamera.m_pGameCameraEntity->GetWorldAngles();

				Vec3 CamCurVecRot = MathUtil::Ang2DirIgnoreZ(CamCurRot + DEG2RAD(Ang3(0,0,90)));

				Vec3 FinalPos = CamCurPos - (CamCurVecRot * Speed);

				g_RTSCamera.m_pGameCameraEntity->SetPos(FinalPos);
			}
		}
		break;

		case ECAMERAMOVEDIRECTION_MOVEFORWARDLEFT:
		{
			if (g_RTSCamera.m_pGameCameraEntity)
			{
				Vec3 CamCurPos = g_RTSCamera.m_pGameCameraEntity->GetPos();

				Ang3 CamCurRot = g_RTSCamera.m_pGameCameraEntity->GetWorldAngles();

				Vec3 CamCurVecRot = MathUtil::Ang2DirIgnoreZ(CamCurRot - DEG2RAD(Ang3(0,0,135)));

				Vec3 FinalPos = CamCurPos - (CamCurVecRot * Speed);

				g_RTSCamera.m_pGameCameraEntity->SetPos(FinalPos);
			}
		}
		break;

		case ECAMERAMOVEDIRECTION_MOVEFORWARDRIGHT:
		{
			if (g_RTSCamera.m_pGameCameraEntity)
			{
				Vec3 CamCurPos = g_RTSCamera.m_pGameCameraEntity->GetPos();

				Ang3 CamCurRot = g_RTSCamera.m_pGameCameraEntity->GetWorldAngles();

				Vec3 CamCurVecRot = MathUtil::Ang2DirIgnoreZ(CamCurRot + DEG2RAD(Ang3(0,0,135)));

				Vec3 FinalPos = CamCurPos - (CamCurVecRot * Speed);

				g_RTSCamera.m_pGameCameraEntity->SetPos(FinalPos);
			}
		}
		break;

		case ECAMERAMOVEDIRECTION_MOVEBACKWARDSLEFT:
		{
			if (g_RTSCamera.m_pGameCameraEntity)
			{
				Vec3 CamCurPos = g_RTSCamera.m_pGameCameraEntity->GetPos();

				Ang3 CamCurRot = g_RTSCamera.m_pGameCameraEntity->GetWorldAngles();

				Vec3 CamCurVecRot = MathUtil::Ang2DirIgnoreZ(CamCurRot - DEG2RAD(Ang3(0,0,45)));

				Vec3 FinalPos = CamCurPos - (CamCurVecRot * Speed);

				g_RTSCamera.m_pGameCameraEntity->SetPos(FinalPos);
			}
		}
		break;

		case ECAMERAMOVEDIRECTION_MOVEBACKWARDSRIGHT:
		{
			if (g_RTSCamera.m_pGameCameraEntity)
			{
				Vec3 CamCurPos = g_RTSCamera.m_pGameCameraEntity->GetPos();

				Ang3 CamCurRot = g_RTSCamera.m_pGameCameraEntity->GetWorldAngles();

				Vec3 CamCurVecRot = MathUtil::Ang2DirIgnoreZ(CamCurRot + DEG2RAD(Ang3(0,0,45)));

				Vec3 FinalPos = CamCurPos - (CamCurVecRot * Speed);

				g_RTSCamera.m_pGameCameraEntity->SetPos(FinalPos);
			}
		}
		break;
	}
}








void RTSCamera::Rotate(ECAMERAROTATEDIRECTION eCameraRotateDirection, float Speed)
{

	switch (eCameraRotateDirection)
	{


	case ECAMERAROTATEDIRECTION_LEFT:
		{
			if (g_RTSCamera.m_pGameCameraEntity)
			{
				Ang3 CamCurRot = g_RTSCamera.m_pGameCameraEntity->GetWorldAngles();

				Ang3 CamAdjRot = CamCurRot + Ang3(0, 0, Speed);

				g_RTSCamera.m_pGameCameraEntity->SetRotation(Quat::CreateRotationXYZ(CamAdjRot));
			}
		}
		break;

	case ECAMERAROTATEDIRECTION_RIGHT:
		{
			if (g_RTSCamera.m_pGameCameraEntity)
			{
				Ang3 CamCurRot = g_RTSCamera.m_pGameCameraEntity->GetWorldAngles();

				Ang3 CamAdjRot = CamCurRot - Ang3(0, 0, Speed);

				g_RTSCamera.m_pGameCameraEntity->SetRotation(Quat::CreateRotationXYZ(CamAdjRot));
			}
		}
		break;

	case ECAMERAROTATEDIRECTION_UP:
		{
			if (g_RTSCamera.m_pGameCameraEntity)
			{
				Ang3 CamCurRot = g_RTSCamera.m_pGameCameraEntity->GetWorldAngles();

				if (CamCurRot.x < DEG2RAD(90))
				{
					Ang3 CamAdjRot = CamCurRot + Ang3(Speed, 0, 0);

					g_RTSCamera.m_pGameCameraEntity->SetRotation(Quat::CreateRotationXYZ(CamAdjRot));
				}
			}
		}
		break;

	case ECAMERAROTATEDIRECTION_DOWN:
		{
			if (g_RTSCamera.m_pGameCameraEntity)
			{
				Ang3 CamCurRot = g_RTSCamera.m_pGameCameraEntity->GetWorldAngles();

				if (CamCurRot.x > DEG2RAD(-90))
				{
					Ang3 CamAdjRot = CamCurRot - Ang3(Speed, 0, 0);

					g_RTSCamera.m_pGameCameraEntity->SetRotation(Quat::CreateRotationXYZ(CamAdjRot));
				}
			}
		}
		break;
	}
}