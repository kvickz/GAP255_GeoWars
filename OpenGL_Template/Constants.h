//Constants.h

//This file is for storing global constants

#ifndef CONSTANTS_H
#define CONSTANTS_H

//***********************************************
//  TYPE DEFINES
//***********************************************
typedef unsigned int ComponentID;
typedef unsigned int ObjectID;

//***********************************************
//  OBJECT IDS
//***********************************************
const ObjectID k_planetID = 1;
const ObjectID k_cameraID = 2;
const ObjectID k_playerID = 3;
const ObjectID k_enemy_1ID = 4;
const ObjectID k_wallID = 10;
//***********************************************

//***********************************************
//  COMPONENT IDS
//***********************************************
const ComponentID k_transformComponentID = 1;
const ComponentID k_renderComponentID = 2;
const ComponentID k_cameraComponentID = 3;
const ComponentID k_characterControllerComponentID = 4;
const ComponentID k_rigidbodyComponentID = 5;
const ComponentID k_EnemyAIComponentID = 6;
const ComponentID k_ColliderComponentID = 7;
const ComponentID k_CharacterStatsComponentID = 8;
//***********************************************

//***********************************************
//  CONSTANT VALUES
//***********************************************
const int k_maxIntValue = 0x7fffffff;
const float k_rad2Deg = 57.295779f; //Converts Radians to Degrees
const float k_deg2Rad = 0.0174532f; //Converts Degrees to Radians
//***********************************************

#endif // !CONSTANTS_H