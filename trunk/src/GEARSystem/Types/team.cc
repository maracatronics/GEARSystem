/*** GEARSystem - GEARSystemTeam implementation
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Includes the class header
#include <GEARSystem/Types/team.hh>


// Inlcudes Qt library
#include <QtCore/QtCore>

// Inlcudes IO streams
#include <iostream>


// Selects namespace
using namespace GEARSystem;
using std::cerr;
using std::endl;
using std::flush;


/*** Constructor
  ** Description: Creates an invalid team
  ** Recieves:    Nothing
  ***/
GEARSystemTeam::GEARSystemTeam() {
    // Sets as invalid
    setInvalid();

    // Creates invalid types
    _invalidPosition     = new Position();
    _invalidAngle        = new Angle();
    _invalidVelocity     = new Velocity();
    _invalidAngularSpeed = new AngularSpeed();

    // Initializes the players
    _nPlayers = 0;
    _validPlayers.clear();
    _playersPositions.clear();
    _playersOrientations.clear();
    _playersVelocities.clear();
    _playersAngularSpeeds.clear();
    _ballPossessions.clear();

    // Creates the locks
    #ifdef GSTHREADSAFE
    _positionsLock     = new QReadWriteLock();
    _orientationsLock  = new QReadWriteLock();
    _velocitiesLock    = new QReadWriteLock();
    _angularSpeedsLock = new QReadWriteLock();
    _possessionsLock   = new QReadWriteLock();
    #endif
}

/*** Constructor
  ** Description: Creates a team
  ** Recieves:    [teamNumber] The team number
                  [teamName]   The team name
  ***/
GEARSystemTeam::GEARSystemTeam(uint8 teamNumber, QString teamName) {
    // Sets team info
    _number = teamNumber;
    _name   = teamName;
    _valid  = true;

    // Creates invalid types
    _invalidPosition     = new Position();
    _invalidAngle        = new Angle();
    _invalidVelocity     = new Velocity();
    _invalidAngularSpeed = new AngularSpeed();

    // Initializes the players
    _nPlayers = 0;
    _validPlayers.clear();
    _playersPositions.clear();
    _playersOrientations.clear();
    _playersVelocities.clear();
    _playersAngularSpeeds.clear();
    _ballPossessions.clear();
    _kickEnabled.clear();
    _dribbleEnabled.clear();
    _batteryCharge.clear();
    _capacitorCharge.clear();

    // Creates the locks
    #ifdef GSTHREADSAFE
    _positionsLock     = new QReadWriteLock();
    _orientationsLock  = new QReadWriteLock();
    _velocitiesLock    = new QReadWriteLock();
    _angularSpeedsLock = new QReadWriteLock();
    _possessionsLock   = new QReadWriteLock();
    #endif
}


/*** Players handling functions
  ** Description: Handles the team players
  ** Receives:    [playerNum] The player number
  ** Returns:     Nothing
  ***/
void GEARSystemTeam::addPlayer(uint8 playerNum) {
    // Handles the locks
    #ifdef GSTHREADSAFE
    QWriteLocker positionsLocker(_positionsLock);
    QWriteLocker orientationsLocker(_orientationsLock);
    QWriteLocker velocitiesLocker(_velocitiesLock);
    QWriteLocker angularSpeedsLocker(_angularSpeedsLock);
    QWriteLocker possessionsLocker(_possessionsLock);
    // TODO: Fix fault at this point
    #endif

    // Adds the player
    (void) _validPlayers.insert(playerNum, true);
    (void) _playersPositions.insert(playerNum, new Position(false,0,0,0));
    (void) _playersOrientations.insert(playerNum, new Angle(false,0));
    (void) _playersVelocities.insert(playerNum, new Velocity(false,0,0));
    (void) _playersAngularSpeeds.insert(playerNum, new AngularSpeed(false,0));
    (void) _kickEnabled.insert(playerNum, false);
    (void) _dribbleEnabled.insert(playerNum, false);
    (void) _batteryCharge.insert(playerNum, 0);
    (void) _capacitorCharge.insert(playerNum, 0);
    (void) _ballPossessions.insert(playerNum, false);
    _nPlayers++;
}

void GEARSystemTeam::delPlayer(uint8 playerNum) {
    // Handles the locks
    #ifdef GSTHREADSAFE
    QWriteLocker positionsLocker(_positionsLock);
    QWriteLocker orientationsLocker(_orientationsLock);
    QWriteLocker velocitiesLocker(_velocitiesLock);
    QWriteLocker angularSpeedsLocker(_angularSpeedsLock);
    QWriteLocker possessionsLocker(_possessionsLock);
    // TODO: Fix fault at this point
    #endif

    // Deletes the player
    (void) _validPlayers.remove(playerNum);
    (void) delete(_playersPositions[playerNum]);
    (void) delete(_playersOrientations[playerNum]);
    (void) delete(_playersVelocities[playerNum]);
    (void) delete(_playersAngularSpeeds[playerNum]);
    (void) _playersPositions.remove(playerNum);
    (void) _playersOrientations.remove(playerNum);
    (void) _playersVelocities.remove(playerNum);
    (void) _playersAngularSpeeds.remove(playerNum);
    (void) _ballPossessions.remove(playerNum);
    (void) _kickEnabled.remove(playerNum);
    (void) _dribbleEnabled.remove(playerNum);
    (void) _batteryCharge.remove(playerNum);
    (void) _capacitorCharge.remove(playerNum);
    _nPlayers--;
}

QList<uint8> GEARSystemTeam::players() const {
    // Adds the players to the list
    QList<uint8> playersList;
    QHashIterator<uint8,Position*> it(_playersPositions);
    while (it.hasNext()) {
        playersList.append(it.next().key());
    }

    // Returns the list
    return(playersList);
}


/*** GEARSystemTeam info functions
  ** Description: Controls team name and number
  ***/
const QString& GEARSystemTeam::name() const { return(_name); }
uint8 GEARSystemTeam::number() const { return(_number); }
void  GEARSystemTeam::setName(const QString& teamName) { _name = teamName; }
void  GEARSystemTeam::setNumber(uint8 teamNumber) {
    _valid  = true;
    _number = teamNumber;
}


/*** 'setPosition' function
  ** Description: Sets the player position
  ** Receives:    [playerNum]   The player number
                  [thePosition] The player position
  ** Returns:     Nothing
  ***/
void GEARSystemTeam::setPosition(uint8 playerNum, const Position& thePosition) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker positionsLocker(_positionsLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the player position
    if (_validPlayers.value(playerNum)) {
        (void) _playersPositions.value(playerNum)->operator =(thePosition);
    }
    else {
        #ifdef GSDEBUGMSG
        //cerr << ">> GEARSystem: GEARSystemTeam::setPosition(uint8, const Position&): No such Player #" << int(playerNum);
        //cerr << " in GEARSystemTeam #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}

/*** 'setOrientation' function
  ** Description: Sets the player orientation
  ** Receives:    [playerNum]      The player number
                  [theOrientation] The player orientation
  ** Returns:     Nothing
  ***/
void GEARSystemTeam::setOrientation(uint8 playerNum, const Angle& theOrientation) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker orientationsLocker(_orientationsLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the player orientation
    if (_validPlayers.value(playerNum)) {
        (void) _playersOrientations.value(playerNum)->operator =(theOrientation);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::setOrientation(uint8, const Angle&): No such Player #" << int(playerNum);
        cerr << " in GEARSystemTeam #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}

/*** 'setVelocity' function
  ** Description: Sets the player velocity
  ** Receives:    [playerNum] The player number
                  [theVelocity]  The player velocity
  ** Returns:     Nothing
  ***/
void GEARSystemTeam::setVelocity(uint8 playerNum, const Velocity& theVelocity) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker velocitiesLocker(_velocitiesLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the player velocity
    if (_validPlayers.value(playerNum)) {
        (void) _playersVelocities.value(playerNum)->operator =(theVelocity);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::setVelocity(uint8, const Velocity&): No such Player #" << int(playerNum);
        cerr << " in GEARSystemTeam #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}

/*** 'setPlayerBatteryCharge' function
  ** Description: Sets the player battery charge
  ** Receives:    [playerNum]    The player number
                  [charge]       The player battery charge
  ** Returns:     Nothing
  ***/
void GEARSystemTeam::setPlayerBatteryCharge(uint8 playerNum, unsigned char charge){
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker batteriesLocker(_batteriesLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the player speed
    if (_validPlayers.value(playerNum)) {
        (void) _batteryCharge.insert(playerNum, charge);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::setPlayerBattery(uint8, char): No such Player #" << int(playerNum);
        cerr << " in GEARSystemTeam #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}

/*** 'setPlayerCapacitorCharge' function
  ** Description: Sets the player capacitor charge
  ** Receives:    [playerNum]    The player number
                  [charge]       The player capacitor charge
  ** Returns:     Nothing
  ***/
void GEARSystemTeam::setPlayerCapacitorCharge(uint8 playerNum, unsigned char charge){
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker capacitorsLocker(_capacitorsLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the player speed
    if (_validPlayers.value(playerNum)) {
        (void) _capacitorCharge.insert(playerNum, charge);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::setPlayerCapacitorCharge(uint8, char): No such Player #" << int(playerNum);
        cerr << " in GEARSystemTeam #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}

/*** 'setPlayerDribbleStatus' function
  ** Description: Sets the player dribble device status
  ** Receives:    [playerNum]    The player number
                  [charge]       The player dribble device status
  ** Returns:     Nothing
  ***/
void GEARSystemTeam::setPlayerDribbleStatus(uint8 playerNum, bool status){
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker dribblesLocker(_dribblesLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the player speed
    if (_validPlayers.value(playerNum)) {
        (void) _dribbleEnabled.insert(playerNum, status);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::setPlayerDribbleStatus(uint8, bool): No such Player #" << int(playerNum);
        cerr << " in GEARSystemTeam #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}

/*** 'setPlayerKickStatus' function
  ** Description: Sets the player kick device status
  ** Receives:    [playerNum]    The player number
                  [charge]       The player kick device status
  ** Returns:     Nothing
  ***/
void GEARSystemTeam::setPlayerKickStatus(uint8 playerNum, bool status){
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker kicksLocker(_kicksLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the player speed
    if (_validPlayers.value(playerNum)) {
        (void) _kickEnabled.insert(playerNum, status);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::setPlayerKickStatus(uint8, bool): No such Player #" << int(playerNum);
        cerr << " in GEARSystemTeam #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}

/*** 'setAngularSpeed' function
  ** Description: Sets the player angular speed
  ** Receives:    [playerNum]    The player number
                  [theAngularSpeed] The player angular speed
  ** Returns:     Nothing
  ***/
void GEARSystemTeam::setAngularSpeed(uint8 playerNum, const AngularSpeed& theAngularSpeed) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker angularSpeedsLocker(_angularSpeedsLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the player speed
    if (_validPlayers.value(playerNum)) {
        (void) _playersAngularSpeeds.value(playerNum)->operator =(theAngularSpeed);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::setAngularSpeed(uint8, const AngularSpeed&): No such Player #" << int(playerNum);
        cerr << " in GEARSystemTeam #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}

/*** 'setBallPossession' function
  ** Description: Indicates if the player possesses a ball
  ** Receives:    [playerNum]  The player number
                  [possession] 'true' if the player has the ball, 'false' otherwise
  ** Returns:     Nothing
  ***/
void GEARSystemTeam::setBallPossession(uint8 playerNum, bool possession) {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QWriteLocker possessionsLocker(_possessionsLock);
    // TODO: Fix fault at this point
    #endif

    // Sets the flag
    if (_validPlayers.value(playerNum)) {
        (void) _ballPossessions.insert(playerNum, possession);
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::setBallPossession(uint8, bool): No such Player #" << int(playerNum);
        cerr << " in GEARSystemTeam #" << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }
}


/*** Gets functions
  ** Description: Gets the player pose, velocity and angular speed
  ** Receives:    [playerNum] The player number
  ** Returns:     The player position, orientation, velocity, angular speed, battery or capacitor charges, kick or dribble status
  ***/
const Position* GEARSystemTeam::position(uint8 playerNum) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker positionsLocker(_positionsLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the player position
    if (_validPlayers.value(playerNum)) {
        return(_playersPositions.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::position(uint8): No such Player #" << int(playerNum) << " in GEARSystemTeam #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns an invalid position
    return(_invalidPosition);
}

const Angle* GEARSystemTeam::orientation(uint8 playerNum) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker orientationsLocker(_orientationsLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the player orientation
    if (_validPlayers.value(playerNum)) {
        return(_playersOrientations.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::orientation(uint8): No such Player #" << int(playerNum) << " in GEARSystemTeam #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns an invalid angle
    return(_invalidAngle);
}

const Velocity* GEARSystemTeam::velocity(uint8 playerNum) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker velocitiesLocker(_velocitiesLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the player velocity
    if (_validPlayers.value(playerNum)) {
        return(_playersVelocities.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::velocity(uint8): No such Player #" << int(playerNum) << " in GEARSystemTeam #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns an invalid velocity
    return(_invalidVelocity);
}

const AngularSpeed* GEARSystemTeam::angularSpeed(uint8 playerNum) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker angularSpeedsLocker(_angularSpeedsLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the player speed
    if (_validPlayers.value(playerNum)) {
        return(_playersAngularSpeeds.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::angularSpeed(uint8): No such Player #" << int(playerNum) << " in GEARSystemTeam #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns an invalid speed
    return(_invalidAngularSpeed);
}

bool GEARSystemTeam::ballPossession(uint8 playerNum) const {
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker possessionsLocker(_possessionsLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the flag
    if (_validPlayers.value(playerNum)) {
        return(_ballPossessions.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::ballPossession(uint8): No such Player #" << int(playerNum) << " in GEARSystemTeam #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns 'false'
    return(false);
}

bool GEARSystemTeam::kickEnabled(quint8 playerNum) const{
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker kicksLocker(_kicksLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the flag
    if (_validPlayers.value(playerNum)) {
        return(_kickEnabled.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::kickEnabled(uint8): No such Player #" << int(playerNum) << " in GEARSystemTeam #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns 'false'
    return(false);
}

bool GEARSystemTeam::dribbleEnabled(quint8 playerNum) const{
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker dribblesLocker(_dribblesLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the flag
    if (_validPlayers.value(playerNum)) {
        return(_dribbleEnabled.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::dribbleEnabled(uint8): No such Player #" << int(playerNum) << " in GEARSystemTeam #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns 'false'
    return(false);
}

unsigned char GEARSystemTeam::batteryCharge(quint8 playerNum) const{
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker batteriesLocker(_batteriesLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the flag
    if (_validPlayers.value(playerNum)) {
        return(_batteryCharge.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::batteryCharge(uint8): No such Player #" << int(playerNum) << " in GEARSystemTeam #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns '0'
    return(0);
}

unsigned char GEARSystemTeam::capacitorCharge(quint8 playerNum) const{
    // Handles the lock
    #ifdef GSTHREADSAFE
    QReadLocker capacitorsLocker(_capacitorsLock);
    // TODO: Fix fault at this point
    #endif

    // Returns the flag
    if (_validPlayers.value(playerNum)) {
        return(_capacitorCharge.value(playerNum));
    }
    else {
        #ifdef GSDEBUGMSG
        cerr << ">> GEARSystem: GEARSystemTeam::batteryCharge(uint8): No such Player #" << int(playerNum) << " in GEARSystemTeam #";
        cerr << int(_number) << "(" << _name.toStdString() << ")!!" << endl << flush;
        #endif
    }

    // Returns '0'
    return(0);
}

// Info functions
bool GEARSystemTeam::isValid() const { return(_valid); }
void GEARSystemTeam::setInvalid() {
    _valid = false;
    _validPlayers.clear();
}
