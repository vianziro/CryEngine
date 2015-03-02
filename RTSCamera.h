#ifndef _RTSCamera_
#define _RTSCamera_

#include "IViewSystem.h"
#include "IScriptSystem.h"
#include "ILevelSystem.h"
#include "IHardwareMouse.h"




enum ECAMERAMOVEDIRECTION
{
	ECAMERAMOVEDIRECTION_MOVEFORWARD = 0,
	ECAMERAMOVEDIRECTION_MOVEBACKWARDS,
	ECAMERAMOVEDIRECTION_MOVELEFT,
	ECAMERAMOVEDIRECTION_MOVERIGHT,
	//sekogs
	EHARDWAREKEYBOARDEVENT_N_KEYRELEASED,
	//sekogs
	ECAMERAMOVEDIRECTION_MOVEFORWARDLEFT,
	ECAMERAMOVEDIRECTION_MOVEFORWARDRIGHT,
	ECAMERAMOVEDIRECTION_MOVEBACKWARDSLEFT,
	ECAMERAMOVEDIRECTION_MOVEBACKWARDSRIGHT,
};



enum ECAMERAROTATEDIRECTION
{
	ECAMERAROTATEDIRECTION_UP = 0,
	ECAMERAROTATEDIRECTION_DOWN,
	ECAMERAROTATEDIRECTION_LEFT,
	ECAMERAROTATEDIRECTION_RIGHT,
};



struct RTSCamera
{
	//Constructor
	RTSCamera():
	m_pIViewSystem(0),
	m_pIEntitySystem(0),
	m_EntityId(0),
	m_pGameFrameWork(0),
	m_pRTSCameraView(0),
	m_pGameCameraEntity(0),
	m_RTSCameraViewID(0),
	m_RTSCameraExist(false),
	m_pScriptTable(0)
	{
	}

	//Destructor
	~RTSCamera(){}

	//Member Functions


	//Creates A New CAMERA and sets it as active.  It also calles the "CreateViewParams" Function
	void CreateRTSCamera();

	//Creates The Cameras' View Params
	//
	//THIS IS NEEDED BEFORE WE SET A NEWLY CREATED CAMERA AS THE ACTIVE ONE
	void CreateViewParams(unsigned int CameraId, EntityId GameCameraId, IEntity *GameCamera);

	//Called From MouseEvent Funtion it moves the camera as appropriate
	void Move(ECAMERAMOVEDIRECTION eCameraMoveDirection, float Speed);

	//Called From KeyBoardEvent Funtion it Rotates the camera as appropriate
	void Rotate(ECAMERAROTATEDIRECTION eCameraRotateDirection, float Speed);

	//Calculates if camera should Move Forward
	bool ShouldMoveForward();

	//Calculates if camera should Move Backwards
	bool ShouldMoveBackwards();

	//Calculates if camera should Move Left
	bool ShouldMoveLeft();

	//Calculates if camera should Move Right
	bool ShouldMoveRight();


	bool ShouldMoveForwardLeft();


	bool ShouldMoveForwardRight();


	bool ShouldMoveBackwardsLeft();


	bool ShouldMoveBackwardsRight();

	string GetLevelName();
	
	void Update();

	//Member Variables
	SViewParams m_CurViewParams;
	SViewParams m_NewViewParams;
	IViewSystem *m_pIViewSystem;
	IEntitySystem *m_pIEntitySystem;
	EntityId m_EntityId;
	IGameFramework *m_pGameFrameWork;
	IView *m_pRTSCameraView;
	IEntity *m_pGameCameraEntity;
	uint8 m_RTSCameraViewID;
	bool m_RTSCameraExist;
	IScriptTable *m_pScriptTable;
};

#endif