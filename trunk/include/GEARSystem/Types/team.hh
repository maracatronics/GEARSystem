/*** GEARSystem - GEARSystemTeam class
  ** GEAR - Grupo de Estudos Avancados em Robotica
  ** Department of Electrical Engineering, University of Sao Paulo
  ** http://www.sel.eesc.usp.br/gear
  ** This file is part of the GEARSystem project
  ***/


// Prevents multiple definitions
#ifndef GSTEAM
#define GSTEAM


// Includes GEARSystem
#include <GEARSystem/namespace.hh>
#include <GEARSystem/Types/types.hh>


// Inlcudes Qt library
#include <QtCore/QtCore>


// Selects namespace
using namespace GEARSystem;


/*** 'GEARSystemTeam' class
  ** Description: This class handles a team
  ** Comments:    This class is reentrant and thread-safe
  ***/
class GEARSystem::GEARSystemTeam {
    private:
        // GEARSystemTeam info
        uint8   _number;
        QString _name;

        // GEARSystemTeam players
        uint8 _nPlayers;
        QHash<uint8,bool>          _validPlayers;
        QHash<uint8,Position*>     _playersPositions;
        QHash<uint8,Angle*>        _playersOrientations;
        QHash<uint8,Velocity*>     _playersVelocities;
        QHash<uint8,AngularSpeed*> _playersAngularSpeeds;
        QHash<uint8,bool>          _ballPossessions;
        QHash<uint8,bool>          _dribbleEnabled;
        QHash<uint8,bool>          _kickEnabled;
        QHash<uint8,unsigned char>          _batteryCharge;
        QHash<uint8,unsigned char>          _capacitorCharge;

        // Info flag
        bool _valid;

        // Invalid types
        Angle*        _invalidAngle;
        AngularSpeed* _invalidAngularSpeed;
        Position*     _invalidPosition;
        Velocity*     _invalidVelocity;

        // Locks
        #ifdef GSTHREADSAFE
        mutable QReadWriteLock* _positionsLock;
        mutable QReadWriteLock* _orientationsLock;
        mutable QReadWriteLock* _velocitiesLock;
        mutable QReadWriteLock* _angularSpeedsLock;
        mutable QReadWriteLock* _possessionsLock;
        mutable QReadWriteLock* _dribblesLock;
        mutable QReadWriteLock* _kicksLock;
        mutable QReadWriteLock* _batteriesLock;
        mutable QReadWriteLock* _capacitorsLock;
        #endif


    public:
        /*** Constructor
          ** Description: Creates an invalid team
          ** Recieves:    Nothing
          ***/
        GEARSystemTeam();

        /*** Constructor
          ** Description: Creates a team
          ** Recieves:    [number] The team number
                          [name]   The team name
          ***/
        GEARSystemTeam(uint8 number, QString name);


    public:
        /*** Players handling functions
          ** Description: Handles the team players
          ** Receives:    [playerNum] The player number
          ** Returns:     Nothing
          ***/
        void addPlayer(uint8 playerNum);
        void delPlayer(uint8 playerNum);
        QList<uint8> players() const;

        /*** GEARSystemTeam info functions
          ** Description: Controls team name and number
          ***/
        const QString& name() const;
        uint8 number() const;
        void  setName(const QString& name);
        void  setNumber(uint8 number);

    public:
        /*** Players RadioSensor functions
         **  Description: Handles the radiosensor functions
         **  Receives:      [playerNum] The player number
         **                 [status] or [charge], the status(bool) or charge(char)
         **  Returns:       Nothing
         ***/

        void setPlayerBatteryCharge(uint8 playerNum, unsigned char charge);
        void setPlayerCapacitorCharge(uint8 playerNum, unsigned char charge);
        void setPlayerDribbleStatus(uint8 playerNum, bool status);
        void setPlayerKickStatus(uint8 playerNum, bool status);


    public:
        /*** Gets functions
          ** Description: Gets the player pose, velocity and angular speed
          ** Receives:    [playerNum] The player number
          ** Returns:     The player position, orientation, velocity or angular speed
          ***/
        const Position*     position(uint8 playerNum)        const;
        const Angle*        orientation(uint8 playerNum)     const;
        const Velocity*     velocity(uint8 playerNum)        const;
        const AngularSpeed* angularSpeed(uint8 playerNum)    const;
        bool                ballPossession(uint8 playerNum)  const;
        unsigned char       batteryCharge(uint8 playerNum)   const;
        unsigned char       capacitorCharge(uint8 playerNum) const;
        bool                kickEnabled(uint8 playerNum)     const;
        bool                dribbleEnabled(uint8 playerNum)  const;

        /*** 'setPosition' function
          ** Description: Sets the player position
          ** Receives:    [playerNum] The player number
                          [position]  The player position
          ** Returns:     Nothing
          ***/
        void setPosition(uint8 playerNum, const Position& position);

        /*** 'setOrientation' function
          ** Description: Sets the player orientation
          ** Receives:    [playerNum]   The player number
                          [orientation] The player orientation
          ** Returns:     Nothing
          ***/
        void setOrientation(uint8 playerNum, const Angle& orientation);

        /*** 'setVelocity' function
          ** Description: Sets the player velocity
          ** Receives:    [playerNum] The player number
                          [velocity]  The player velocity
          ** Returns:     Nothing
          ***/
        void setVelocity(uint8 playerNum, const Velocity& velocity);

        /*** 'setAngularSpeed' function
          ** Description: Sets the player angular speed
          ** Receives:    [playerNum]    The player number
                          [angularSpeed] The player angular speed
          ** Returns:     Nothing
          ***/
        void setAngularSpeed(uint8 playerNum, const AngularSpeed& angularSpeed);

        /*** 'setBallPossession' function
          ** Description: Indicates if the player possesses a ball
          ** Receives:    [playerNum]  The player number
                          [possession] 'true' if the player has the ball, 'false' otherwise
          ** Returns:     Nothing
          ***/
        void setBallPossession(uint8 playerNum, bool possession);

    public:
        /*** 'isValid' function
          ** Description: Verifies if the team is valid
          ** Receives:    Nothing
          ** Returns:     'false' if the team is invalid, 'true' otherwise
          ***/
        bool isValid() const;

        /*** 'setInvalid' function
          ** Description: Sets the team as invalid
          ** Receives:    Nothing
          ** Returns:     Nothing
          ***/
        void setInvalid();
};


#endif
