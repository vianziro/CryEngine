#include "StdAfx.h"
#include "vapur.h"
#include "sqlFederate.h"
#include "Global.h"
#include "Global2.h"


bool Cvapur::Init( IGameObject *pGameObject ){
		
	SetGameObject(pGameObject);
	GetEntity()->Activate(true);
	return true;

}

void Cvapur::PostInit(IGameObject *pGameObject){

	IMaterial *tempMaterial=gEnv->p3DEngine->GetMaterialManager()->LoadMaterial("Materials/material_layers_default");
	//GetEntity()->
	if(GetEntity()->HasAI()){
		gEnv->pLog->Log("ai var");
	}
	GetEntity()->SetMaterial(tempMaterial);
	entID=GetEntity()->GetId();
	SQLFederate *sqlfed=new SQLFederate();
	sqlfed->startConnection();
	
	
	sqlfed->addVessel(entID,g_RigthClick3dPosition.x,g_RigthClick3dPosition.y,g_LeftClick3dPosition.x,g_LeftClick3dPosition.y);
	//sqlfed->startHLA();
	//
	//sqlfed->startHLA();
	//sleep(30);
	sqlfed->endConnection();
	pGameObject->EnableUpdateSlot(this,0);
	GetEntity()->SetScale(Vec3(4,4,4),0);
	GetEntity()->LoadGeometry(0,"Editor/Objects/speedboat.cgf");
	Quat tempQuat;

	Quat dirQuat=tempQuat.CreateRotationVDir(Vec3(1,1,0).normalize());
	GetEntity()->SetRotation(dirQuat,0);
	SEntityPhysicalizeParams fizik;
	
	//fizik.mass=500;
	fizik.density=10;
	fizik.type=PE_RIGID;
	//fizik.pCar=
	
	GetEntity()->Physicalize(fizik);
	

}

float simutime = 0;

void Cvapur::Update(SEntityUpdateContext& ctx, int updateSlot){
	if(counter==1)
	{
		//sleep(0.0999);
		
		SQLFederate *sqlfed=new SQLFederate();
		vessel temp;
		sqlfed->startConnection();
		Vec3 nextPos;
		temp=sqlfed->getPosition(simutime, GetEntity()->GetId());
		sqlfed->endConnection();
		simutime++;

		double tempx = ::atof(temp.xcoordinate.c_str());
		double tempy = ::atof(temp.ycoordinate.c_str());

		Vec3 curPos=GetEntity()->GetPos();
		nextPos.x = tempx;
		//gEnv->pLog->Log(temp.xcoordinate.c_str());
		nextPos.y = tempy;
		nextPos.z = 26.0;
		GetEntity()->SetPos(nextPos);
		Vec3 temppos=nextPos.sub(curPos);
		temppos.Normalize();
		Quat tempQuat;
		//Matrix34 matrix=Matrix34.CreateRotationXYZ(Ang3(temppos),temppos);
		//tempQuat.
		//GetEntity()->SetRotation(tempQuat.CreateRotationVDir(Vec3(-1,0,0),0));
		GetEntity()->SetRotation(tempQuat.CreateRotationVDir(temppos),0);
		IMaterial *tempMaterial=gEnv->p3DEngine->GetMaterialManager()->LoadMaterial("Materials/material_layers_default");
		//GetEntity()->
		if(GetEntity()->HasAI()){
			gEnv->pLog->Log("ai var");
		}
		GetEntity()->SetMaterial(tempMaterial);
	}
	
}