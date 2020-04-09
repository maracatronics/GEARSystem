/*** GEARSystem - RadioSensor class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSRADIOSENSOR
#define GSRADIOSENSOR


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/Types/types.hh>
#include <GEARSystem/CORBAImplementations/corbainterfaces.hh>


// Includes Qt library
#include <QtCore/QtCore>


// Selects namespace
using namespace GEARSystem;


/*** 'RadioSensor' class
  ** Description: This class encapsulates an implementation of the RadioSensor CORBA interface
  ** Comments:
  ***/
class GEARSystem::RadioSensor {
    private:
        // CORBA Sensor
        CORBAInterfaces::RadioSensor_var _corbaRadioSensor;

        // Connection info
        QString _serverAddress;
        uint32  _serverPort;
        bool    _isConnected;


    public:
        /*** Constructor
          ** Description: Creates the Radiosensor
          ** Receives:    Nothing
          ***/
        RadioSensor();


    public:
        /*** 'connect' function
          ** Description: Connects to the server
          ** Receives:    [address] The server address
                          [port]    The server port
          ** Returns:     'true' if the connection was established, 'false' otherwise
          ***/
        bool connect(const QString& address, uint16 port);

        /*** 'disconnect' function
          ** Description: Disconnects from the server
          ** Receives:    Nothing
          ** Returns:     Nothing
          ***/
        void disconnect();

        /*** 'isConnected' function
          ** Description: Verifies if the Radiosensor is connected to the server
          ** Receives:    Nothing
          ** Returns:     'true' if the connection was established, 'false' otherwise
          ***/
        bool isConnected() const;

         /*** Players parameters functions
          **  Description: Parameters for the teams players
          **  Receives:    [teamNum]   The team number
                           [playerNum] The player number
          ** Returns:     Nothing
          ***/

         void setPlayerBatteryCharge(uint8 teamNum, uint8 playerNum, unsigned char charge);
         void setPlayerCapacitorCharge(uint8 teamNum, uint8 playerNum, unsigned char charge);
         void setPlayerDribbleStatus(uint8 teamNum, uint8 playerNum, bool status);
         void setPlayerKickStatus(uint8 teamNum, uint8 playerNum, bool status);
};


#endif
