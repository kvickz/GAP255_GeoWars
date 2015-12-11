//Constants.h

//This file is for storing global constants

#ifndef CONSTANTS_H
#define CONSTANTS_H

//***********************************************
//  TYPE DEFINES
//***********************************************
typedef unsigned int ComponentID;
typedef unsigned int ObjectID;
typedef unsigned int ObjectInstanceID;
typedef unsigned int EventID;
typedef unsigned int EventInstanceID;
typedef signed short AxisValue;

//***********************************************
//  OBJECT IDS
//***********************************************
const ObjectID k_planetID = 1;
const ObjectID k_cameraID = 2;
const ObjectID k_playerID = 3;
const ObjectID k_enemy_1ID = 4;
const ObjectID k_wallID = 10;
const ObjectID k_particleID = 11;
const ObjectID k_bulletID = 12;
//***********************************************

//***********************************************
//  COMPONENT IDS
//***********************************************
const ComponentID k_transformComponentID = 1;
const ComponentID k_renderComponentID = 2;
const ComponentID k_cameraComponentID = 3;
const ComponentID k_characterControllerComponentID = 4;
const ComponentID k_rigidbodyComponentID = 5;
const ComponentID k_enemyAIComponentID = 6;
const ComponentID k_colliderComponentID = 7;
const ComponentID k_characterStatsComponentID = 8;
const ComponentID k_particleComponentID = 9;
const ComponentID k_gunComponentID = 10;
const ComponentID k_bulletComponentID = 11;
//***********************************************

//***********************************************
//  EVENT IDS
//***********************************************
const EventID k_playerDeathEvent = 0;
const EventID k_enemyDeathEvent = 1;
//***********************************************

//***********************************************
//  CONSTANT VALUES
//***********************************************
const int k_maxIntValue = 0x7fffffff;
const int k_maxShortIntValue = 0x7fff;
const AxisValue k_maxStickInputValue = 0x7fff; // 32767;  //1/2 of the max short value
const float k_rad2Deg = 57.295779f; //Converts Radians to Degrees
const float k_deg2Rad = 0.0174532f; //Converts Degrees to Radians
//***********************************************

#endif // !CONSTANTS_H