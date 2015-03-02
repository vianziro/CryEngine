#include "StdAfx.h"
#include "sqlFederate.h"
#include "Global2.h"

int vapur = 0;

SQLFederate::SQLFederate()
{
	this -> connect = mysql_init(NULL);
}

SQLFederate::~SQLFederate()
{

}

void SQLFederate::startConnection()
{
	this -> connect = mysql_real_connect(connect,SERVER,USER,PASSWORD,DATABASE,0,NULL,0);
}

void SQLFederate::endConnection()
{
	mysql_close(this -> connect);
}

void SQLFederate::closeHLA()
{
	std::string query = "Delete From Situation";
    const char* constquery = query.c_str();
	mysql_query( this -> connect, constquery );
    query = "Insert Into Situation (Status) Values (0)";
    constquery = query.c_str();
    mysql_query( this -> connect, constquery );
}

void SQLFederate::startHLA()
{
	std::string query = "Delete From Situation";
    const char* constquery = query.c_str();
    mysql_query( this -> connect, constquery );
    query = "Insert Into Situation (Status) Values (1)";
    constquery = query.c_str();
    mysql_query( this -> connect, constquery );
}

vessel SQLFederate::getPosition(float fSimuTime, float fVesselID)
{
    std::string simuTime = ToString(fSimuTime);
    std::string vesselID = ToString(fVesselID);

    MYSQL_RES* res_set;
    MYSQL_ROW row;
    std::string count;

	
    std::string query = "SELECT Count(*) FROM CurrentSimulation Where simuTime=" + simuTime + " and vesselID=" + vesselID;
    const char* constquery = query.c_str();

    mysql_query( this -> connect, constquery );
    res_set = mysql_store_result( this -> connect );
    row = mysql_fetch_row( res_set );
    count = row[0];

    while ( count == "0" )
    {
    //Sleep( 1 );
    mysql_query( this -> connect, constquery );
    res_set = mysql_store_result( this -> connect );
    row = mysql_fetch_row( res_set );
    count = row[0];
    }

	query = "Select xcoordinate, ycoordinate From CurrentSimulation Where simuTime=" + simuTime + " and vesselID=" + vesselID;
    constquery = query.c_str();
    mysql_query( this -> connect, constquery );
    res_set = mysql_store_result( this -> connect );

    std::string xcoordinate, ycoordinate;
	vessel temp;
	temp.vesselID = fVesselID;
	
    while ( ( row = mysql_fetch_row( res_set ) ) != NULL )
    {
        temp.xcoordinate = row[0];
        temp.ycoordinate = row[1];
    }

	return temp;
}

void SQLFederate::setSimulationName(std::string name)
{
	std::string query = "Delete From SimulationName";
    const char* constquery = query.c_str();
    mysql_query( this -> connect, constquery );

    query = "Insert Into SimulationName (name) Values ('" + name + "')";
    constquery = query.c_str();

    mysql_query( this -> connect, constquery );
}

void SQLFederate::setStartingTime(std::string time)
{
	std::string query = "Delete From StartingTime";
    const char* constquery = query.c_str();

    mysql_query( this -> connect, constquery );

    query = "Insert Into StartingTime (time) Values ('" + time + "')";
    constquery = query.c_str();

    mysql_query( this -> connect, constquery );
}

void SQLFederate::setWeather(std::string weather)
{
	std::string query = "Delete From Weather";
    const char* constquery = query.c_str();
    mysql_query( this -> connect, constquery );
    query = "Insert Into Weather (theWeather) Values ('" + weather + "')";
    constquery = query.c_str();
    mysql_query( this -> connect, constquery );
}

void SQLFederate::addVessel(int iEntityID, float fInitialX, float fInitialY, float fEndingX, float fEndingY)
{

	if(vapur < 2)
	{
		std::string entityID = ToString(iEntityID);
		std::string initialX = ToString(fInitialX);
		std::string initialY = ToString(fInitialY);
		std::string endingX = ToString(fEndingX);
		std::string endingY = ToString(fEndingY);

		std::string query = "Insert Into VesselProperties (entityID,model,initialX,initialY,endingX,endingY,port,portTwo) Values ('"+ entityID +"','tanker','"+initialX+"','"+initialY+"','"+endingX+"','"+endingY+"','-','-')";
		const char* constquery = query.c_str();
		vapur++;

		mysql_query( connect, constquery );
	}///////////////////////////////////////yukariyi tanker yaptik sonra degistirin
	else
	{
		std::string entityID = ToString(iEntityID);
		std::string initialX = ToString(fInitialX);
		std::string initialY = ToString(fInitialY);
		std::string endingX = ToString(fEndingX);
		std::string endingY = ToString(fEndingY);

		std::string query = "Insert Into VesselProperties (entityID,model,initialX,initialY,endingX,endingY,port,portTwo) Values ('"+ entityID +"','vapur','"+initialX+"','"+initialY+"','"+endingX+"','"+endingY+"','-','-')";
		const char* constquery = query.c_str();
		vapur++;
		mysql_query( connect, constquery );
	}

	if(vapur == 2)
	{
		startHLA();
		sleep(30);
		counter=1;
	}
}


