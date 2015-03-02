#ifndef _SQLFEDERATE_
#define _SQLFEDERATE_

#include "my_global.h"
#include "mysql.h"
#include <iostream>
#include <string>
#include <vector>
#define SERVER "localhost"
#define USER "root"
#define PASSWORD "CamelSoft"
#define DATABASE "CamelShip"

struct vessel
{
	float vesselID;
	std::string xcoordinate;
	std::string ycoordinate;
};

class SQLFederate
{
	public:
		SQLFederate();
		~SQLFederate();
		void startConnection();
		void endConnection();
		void closeHLA();
		void startHLA();
		vessel getPosition(float fSimuTime, float fVesselID);
		void setSimulationName(std::string name);
		void setStartingTime(std::string time);
		void setWeather(std::string weather);
		void addVessel(int iEntityID, float fInitialX, float fInitialY, float fEndingX, float fEndingY);
	private:
		MYSQL *connect;

};

#endif