/*** GEARSystem - CORBA Sensor implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/CORBAImplementations/corbaradiosensor.hh>


// Includes omniORB 4
#include <omniORB4/CORBA.h>


// Selects namespace
using namespace GEARSystem;
using CORBA::Boolean;
using CORBA::Float;
using CORBA::Octet;
using CORBA::Char;


/*** Constructor
  ** Description: Creates the sensor
  ** Receives:    [worldMap] The world map the sensor will control
  ***/
CORBAImplementations::RadioSensor::RadioSensor(WorldMap* worldMap) {
    // Sets the world map
    _worldMap = worldMap;
}


/*** Players parameters functions
  ** Description: Parameters for the teams players
  ** Receives:    [teamNum]   The team number
                  [playerNum] The player number
  ** Returns:     Nothing
  ***/

void CORBAImplementations::RadioSensor::setPlayerBatteryCharge(Octet teamNum, Octet playerNum, Char charge){
    _worldMap->setBatteryCharge(teamNum, playerNum, charge);
}

void CORBAImplementations::RadioSensor::setPlayerCapacitorCharge(Octet teamNum, Octet playerNum, Char charge){
    _worldMap->setCapacitorCharge(teamNum, playerNum, charge);
}

void CORBAImplementations::RadioSensor::setPlayerDribbleStatus(Octet teamNum, Octet playerNum, bool status){
    _worldMap->setDribbleEnabled(teamNum, playerNum, status);
}

void CORBAImplementations::RadioSensor::setPlayerKickStatus(Octet teamNum, Octet playerNum, bool status){
    _worldMap->setKickEnabled(teamNum, playerNum, status);
}
