/*** GEARSystem - Sensor implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/radiosensor.hh>


// Includes IO streams
#include <iostream>

// Includes Qt library
#include <QtCore/QtCore>

// Includes omniORB 4
#include <omniORB4/CORBA.h>


// Selects namespace
using namespace GEARSystem;
using std::cerr;
using std::endl;
using std::flush;


/*** Constructor
  ** Description: Creates the sensor
  ** Receives:    Nothing
  ***/
RadioSensor::RadioSensor() {
    // Initializes the variables
    _corbaRadioSensor = NULL;
    _isConnected = false;
    _serverPort  = 0;
    _serverAddress.clear();
}


/*** 'connect' function
  ** Description: Connects to the server
  ** Receives:    [address] The server address
                  [port]    The server port
  ** Returns:     'true' if the connection was established, 'false' otherwise
  ***/
bool RadioSensor::connect(const QString& address, uint16 port) {
    try {
        // Creates the ORB
        int argc = 0;
        CORBA::ORB_var orb = CORBA::ORB_init(argc, NULL);
        if (CORBA::is_nil(orb)) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: RadioSensor::connect(const QString&, uint16): Could not initialize ORB!!" << endl << flush;
            #endif

            return(false);
        }

        // Sets the CORBA RadioSensor address
        QString radioSensorAddr("corbaname::");
        radioSensorAddr.append(address);
        if (port != 0) {
            radioSensorAddr.append(":");
            radioSensorAddr.append(QString("%1").arg(port));
        }
        radioSensorAddr.append("#GEARSystem.RadioSensor");

        // Gets the CORBA Sensor reference
        CORBA::Object_var corbaObject = orb->string_to_object(radioSensorAddr.toStdString().c_str());
        if (CORBA::is_nil(corbaObject)) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: RadioSensor::connect(const QString&, uint16): Could not connect ";
            cerr << "to the server at " << address.toStdString() << ":" << port << "!!" << endl << flush;
            #endif

            return(false);
        }

        // Narrows it to the encapsulated object
        _corbaRadioSensor = CORBAInterfaces::RadioSensor::_narrow(corbaObject);
        if (CORBA::is_nil(_corbaRadioSensor)) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: RadioSensor::connect(const QString&, uint16): Could not connect ";
            cerr << "to the server at " << address.toStdString() << ":" << port << "!!" << endl << flush;
            #endif

            return(false);
        }

        // Sets as connected
        _serverAddress = address;
        _serverPort    = port;
        _isConnected   = true;
    }

    // Handles CORBA exceptions
    catch (const CORBA::Exception& exception) {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: RadioSensor::connect(const QString&, uint16): Caught CORBA exception: ";
        cerr << exception._name() << "!!" << endl << flush;
        #endif

        return(false);
    }

    // Returns 'true' if everything went OK
    return(true);
}

/*** 'disconnect' function
  ** Description: Disconnects from the server
  ** Receives:    Nothing
  ** Returns:     Nothing
  ***/
void RadioSensor::disconnect() {
    // Sets as disconnected
    _serverAddress.clear();
    _serverPort  = 0;
    _isConnected = false;
}

/*** 'isConnected' function
  ** Description: Verifies if the sensor is connected to the server
  ** Receives:    Nothing
  ** Returns:     'true' if the connection was established, 'false' otherwise
  ***/
bool RadioSensor::isConnected() const { return(_isConnected); }

/*** 'setPlayerKickStatus' function
  ** Description: Indicates if the player enabled kick
  ** Receives:    [teamNum]    The team number
                  [playerNum]  The player number
                  [possession] 'true' if the player enabled kick, 'false' otherwise
  ** Returns:     Nothing
  ***/

void RadioSensor::setPlayerKickStatus(quint8 teamNum, quint8 playerNum, bool status) {
    // Sets the flag
    if (isConnected()) {
        try {
            _corbaRadioSensor->setPlayerKickStatus(teamNum, playerNum, status);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setPlayerKickStatus(uint8, uint8, bool): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setPlayerKickStatus(uint8, uint8, bool): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

/*** 'setPlayerDribbleStatus' function
  ** Description: Indicates if the player enabled dribble
  ** Receives:    [teamNum]    The team number
                  [playerNum]  The player number
                  [possession] 'true' if the player enabled dribble, 'false' otherwise
  ** Returns:     Nothing
  ***/

void RadioSensor::setPlayerDribbleStatus(quint8 teamNum, quint8 playerNum, bool status) {
    // Sets the flag
    if (isConnected()) {
        try {
            _corbaRadioSensor->setPlayerDribbleStatus(teamNum, playerNum, status);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setPlayerDribbleStatus(uint8, uint8, bool): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setPlayerDribbleStatus(uint8, uint8, bool): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}

/*** 'setPlayerBatteryCharge' function
  ** Description: Indicates the player battery charge value
  ** Receives:    [teamNum]    The team number
                  [playerNum]  The player number
                  [charge]     The value of charge
  ** Returns:     Nothing
  ***/

void RadioSensor::setPlayerBatteryCharge(quint8 teamNum, quint8 playerNum, unsigned char charge) {
    // Sets the flag
    if (isConnected()) {
        try {
            _corbaRadioSensor->setPlayerBatteryCharge(teamNum, playerNum, charge);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setPlayerBatteryCharge(uint8, uint8, unsigned char): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setPlayerBatteryCharge(uint8, uint8, unsigned char): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}


/*** 'setPlayerCapacitorCharge' function
  ** Description: Indicates the player capacitor charge value
  ** Receives:    [teamNum]    The team number
                  [playerNum]  The player number
                  [charge]     The value of charge
  ** Returns:     Nothing
  ***/

void RadioSensor::setPlayerCapacitorCharge(quint8 teamNum, quint8 playerNum, unsigned char charge) {
    // Sets the flag
    if (isConnected()) {
        try {
            _corbaRadioSensor->setPlayerCapacitorCharge(teamNum, playerNum, charge);
        }

        // Handles CORBA exceptions
        catch (const CORBA::Exception& exception) {
            #ifdef GSDEBUGMSG
            cerr << ">> GEARSystem: Sensor::setPlayerCapacitorCharge(uint8, uint8, unsigned  char): ";
            cerr << "Caught CORBA exception: " << exception._name() << "!!" << endl << flush;
            #endif
        }
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: Sensor::setPlayerCapacitorCharge(uint8, uint8, unsigned char): ";
        cerr << "The sensor is not connected!!" << endl << flush;
        #endif
    }
}
