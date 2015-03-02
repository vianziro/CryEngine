#include "StdAfx.h"
#include "MouseTry.h"
//#include "RTSCamera.h"
//#include "sqlFederate.h"
//#include "my_global.h"
//#include "mysql.h"
#include "Actor.h"
#include "Global.h"
#include "Global2.h"
#include "N:\oyun\CryENGINE_PC_v3_4_3_5047_freeSDK\Code\Game\GameDll\Nodes\G2FlowBaseNode.h"


//SQLFederate *sqlfed = new SQLFederate();

MouseTry::MouseTry(void)
{
}


MouseTry::~MouseTry(void)
{
}

void MouseTry::MouseEvent(int iX,int iY,EHARDWAREMOUSEEVENT eHardwareMouseEvent, int wheelDelta)
{
	IEntity *pEntity;
	Vec3 HitPosition;
	MouseTry MouseTry;
	RTSCamera RTScam;
	//string LevelName=RTSCamera.GetLevelName();
	string LevelName=RTScam.GetLevelName();
	if(LevelName!="")
	{
		switch(eHardwareMouseEvent)
		{

		case HARDWAREMOUSEEVENT_LBUTTONDOWN:
			{
				gEnv->pLog->Log("left button clicked");
				//gEnv->pHardwareMouse->

				break;
		
			}

		case HARDWAREMOUSEEVENT_RBUTTONDOWN:
			{
				gEnv->pLog->Log("rights button clicked");
				break;
			}
	
		case HARDWAREMOUSEEVENT_RBUTTONUP:
			{
				
				//Vec3 HitPosition;
				gEnv->pLog->Log("right button released");
				EntityId tempEntity=MouseTry.GetEntityUnderMouse();
				//MouseTry.StoreEntityIdUnderMouse(tempEntity);
				if(tempEntity==NULL){

					Vec3 HitPosition=MouseTry.GetRightClick3dPosition();				
					
			
					HitPosition.z=26;
					MouseTry.StoreRightClick3dPosition(HitPosition);

				}
				else{

					MouseTry.StoreEntityIdUnderMouse(tempEntity);
					
				
				}
				g_LeftClicked=false;
				g_RightClicked=true;
				

				break;
			}

		case HARDWAREMOUSEEVENT_LBUTTONUP:
			{
					//if(g_EntityIdUnderMouse!=NULL){

						//yeni

						SEntitySpawnParams tempParam;
										
					
						int temp=(int)HitPosition.x;
					
					
						tempParam.sName="vapur";
						tempParam.vScale=Vec3(1,1,1);
					
						
						Vec3 nextPos=MouseTry.GetRightClick3dPosition();
						nextPos.z=26;
						MouseTry.StoreLeftClick3dPosition(nextPos);
						
						tempParam.vPosition=g_RigthClick3dPosition;
						tempParam.nFlags = ENTITY_FLAG_NO_SAVE | ENTITY_FLAG_SPAWNED;
						tempParam.pClass=gEnv->pEntitySystem->GetClassRegistry()->FindClass("vapur");

						
						IEntity *e1 = gEnv->pEntitySystem->SpawnEntity(tempParam, true);



					//}
				g_RightClicked=false;
				g_LeftClicked=true;
				break;

			}
		default:
			break;
		}
	}


}
void MouseTry::StoreRightClick3dPosition(Vec3 temppos)
{
	gEnv->pLog->Log("Destination:  %f,  %f,  %f", temppos.x, temppos.y, temppos.z);
	g_RigthClick3dPosition=temppos;
}
void MouseTry::StoreLeftClick3dPosition(Vec3 temppos)
{
	gEnv->pLog->Log("Destination:  %f,  %f,  %f", temppos.x, temppos.y, temppos.z);
	g_LeftClick3dPosition=temppos;
}

void MouseTry::StoreEntityIdUnderMouse(unsigned int tempid)
{
	g_EntityIdUnderMouse=tempid;

}

EntityId MouseTry::GetEntityUnderMouse()
{
		static ray_hit hit;
	float x, y, xMouse, yMouse, zMouse = 0.0f;
	if(!gEnv->pHardwareMouse || !gEnv->pRenderer || !gEnv->p3DEngine || !gEnv->pSystem 
                                || !gEnv->pEntitySystem || !gEnv->pGame->GetIGameFramework())
		return 0;
 
	IActor *pClientActor = gEnv->pGame->GetIGameFramework()->GetClientActor();
 
	if (!pClientActor)
		return 0;
 
	gEnv->pHardwareMouse->GetHardwareMouseClientPosition(&x,&y);
	y = gEnv->pRenderer->GetHeight() - y;
 
	gEnv->pRenderer->UnProjectFromScreen(x, y, 0.0f,&xMouse,&yMouse,&zMouse);

	static const unsigned int flags = rwi_stop_at_pierceable|rwi_colltype_any;
 
	float  fRange = gEnv->p3DEngine->GetMaxViewDistance();
	Vec3  vCamPos = gEnv->pSystem->GetViewCamera().GetPosition();
	Vec3     vDir = (Vec3(xMouse,yMouse,zMouse) - vCamPos).GetNormalizedSafe();
 
	IPhysicalEntity *pPhysicalEnt = pClientActor->GetEntity() ? pClientActor->GetEntity()->GetPhysics() : NULL;
 
	if(!pPhysicalEnt)
		return 0;
 
	if (gEnv->pPhysicalWorld && gEnv->pPhysicalWorld->RayWorldIntersection(vCamPos, vDir * fRange, ent_all, flags, &hit, 1, pPhysicalEnt))
	{
			if (IEntity *pEntity = gEnv->pEntitySystem->GetEntityFromPhysics(hit.pCollider))
			{
				return pEntity->GetId();
			}	
	}	
 
	return 0;

}

Vec3 MouseTry::GetRightClick3dPosition()
{
	
	static ray_hit hit;
	float x, y, xMouse, yMouse, zMouse = 0.0f;
	if(!gEnv->pHardwareMouse || !gEnv->pRenderer || !gEnv->p3DEngine || !gEnv->pSystem 
                                || !gEnv->pEntitySystem || !gEnv->pGame->GetIGameFramework())
		return ZERO;
 
	IActor *pClientActor = gEnv->pGame->GetIGameFramework()->GetClientActor();
 
	/*if (!pClientActor)
		return ZERO;*/
 
	gEnv->pHardwareMouse->GetHardwareMouseClientPosition(&x,&y);
	y = gEnv->pRenderer->GetHeight() - y;
 
	gEnv->pRenderer->UnProjectFromScreen(x, y, 0.0f,&xMouse,&yMouse,&zMouse);
 
	static const unsigned int flags = rwi_stop_at_pierceable|rwi_colltype_any;
 
	float  fRange = gEnv->p3DEngine->GetMaxViewDistance();
	Vec3  vCamPos = gEnv->pSystem->GetViewCamera().GetPosition();
	Vec3     vDir = (Vec3(xMouse,yMouse,zMouse) - vCamPos).GetNormalizedSafe();
 
	IPhysicalEntity *pPhysicalEnt = pClientActor->GetEntity() ? pClientActor->GetEntity()->GetPhysics() : NULL;
 
	/*if(!pPhysicalEnt)
		return ZERO;*/
 
	if (gEnv->pPhysicalWorld && gEnv->pPhysicalWorld->RayWorldIntersection(vCamPos, vDir * fRange, ent_terrain, flags, &hit, 1, pPhysicalEnt))
	{
			//if (IEntity *pEntity = gEnv->pEntitySystem->GetEntityFromPhysics(hit.pCollider))
			//{
				//Rayhit hit Position
				return hit.pt;
			//}	
	}	
 
	return ZERO;
}
