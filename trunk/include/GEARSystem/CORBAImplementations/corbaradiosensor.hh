/*** GEARSystem - CORBA Sensor class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef CORBARADIOSENSOR_HH
#define CORBARADIOSENSOR_HH


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/Types/types.hh>
#include <GEARSystem/worldmap.hh>
#include <GEARSystem/CORBAImplementations/corbainterfaces.hh>


// Includes omniORB 4
#include <omniORB4/CORBA.h>


// Selects namespace
using namespace GEARSystem;
using CORBA::Boolean;
using CORBA::Float;
using CORBA::Octet;
using CORBA::Char;


/*** 'RadioSensor' class
  ** Description: This class implements the Sensor CORBA interface
  ** Comments:
  ***/
class GEARSystem::CORBAImplementations::RadioSensor : public POA_GEARSystem::CORBAInterfaces::RadioSensor {
    private:
        // World map
        WorldMap* _worldMap;


    public:
        /*** Constructor
          ** Description: Creates the sensor
          ** Receives:    [worldMap] The world map the sensor will control
          ***/
        RadioSensor(WorldMap* worldMap);

    public:
        /*** Players parameters functions
          ** Description: Parameters for the teams players
          ** Receives:    [teamNum]   The team number
                          [playerNum] The player number
          ** Returns:     Nothing
          ***/

        virtual void setPlayerBatteryCharge(Octet teamNum, Octet playerNum, Char charge);
        virtual void setPlayerCapacitorCharge(Octet teamNum, Octet playerNum, Char charge);
        virtual void setPlayerDribbleStatus(Octet teamNum, Octet playerNum, bool status);
        virtual void setPlayerKickStatus(Octet teamNum, Octet playerNum, bool status);
};


#endif // CORBARADIOSENSOR_HH
