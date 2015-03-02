#include "IHardwareMouse.h"
#include "IEntity.h"

#include <fstream>
#include <iostream>


//sekogs
struct MouseTry{

	//Constructor
	MouseTry();
	//Destructor
	~MouseTry();
	
	void MouseEvent(int iX,int iY,EHARDWAREMOUSEEVENT eHardwareMouseEvent, int wheelDelta = 0);
	void StoreEntityIdUnderMouse(unsigned int MouseEntity);
	Vec3 GetRightClick3dPosition();
	void StoreRightClick3dPosition(Vec3 HitPos);
	void StoreLeftClick3dPosition(Vec3 HitPos);
	EntityId GetEntityUnderMouse();


	EntityId m_EntityIdUnderMouse;

	//sekogs deneme
	

	//sekogs deneme



};
