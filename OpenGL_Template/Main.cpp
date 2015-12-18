//Michael Nevins
//GAP 255 - Geometry Wars Clone Project - FINAL
//11-26-2015
//Main.cpp

#include <vld.h>
#include <SDL.h>
#include "Game.h"

//************************************************************************************** *
//  Program structure
//************************************************************************************** *
//  -Game creates game objects and systems
//  -Game Objects contain components which determine their attributes and logic
//  -When new gameplay or feature is needed, I basically create a new component
//   or component behavior class to control the behavior, or I create a new system
//   for the game, or maybe both if its required.
//
//  -I created 2 game modes which only really change 1 thing, the modes are
//      -standard
//      -survival
//
//  survival mode just makes the enemies invulnerable to your bullets and shows off the physics
//  go into Game.cpp and look above Init() to find the assignment of the gamemode to switch it out
//
//************************************************************************************** *
//  Overview of Game Systems
//************************************************************************************** *
//  -All major game systems are listed in the Core filter in the visual studio solution
//  -Event System:
//      It's basically a modified version of the class demo you made, I use it in a few
//      places. Mainly to track when enemies die or the player dies. Other classes inherit
//      from EventListener to override the OnEvent function.
//  -AssetManager:
//      This loads files from data with the exception of audio for now. So it loads
//      models and materials and keeps track of them for deletion when the program
//      ends. It also makes sure theres no duplication of materials or meshes.
//  -AudioManager:
//      Plays audio, music, manages audio files
//  -CollisionSystem:
//      Calculates when collisions occur and delegates the logic out to Collider components.
//      Collisions are handled using a CollisionResponse class which hook into the GameObject's
//      components to execute the appropriate logic for that class.
//  -FileLoader:
//      Helper class for AssetManager, basically handles the loading and parsing of files.
//  -Game:
//      Skeleton class, it's primary purpose is to act as a communication hub for different
//      systems and as it's built right now a few gameplay logic functions.
//  -InputManager:
//      Handle's all input and window events. Utilizes Command classes to convert user input
//      to game logic.
//  -Renderer:
//      This class initializes the window, is responsible for clearing the screen, swapping buffers.
//  -SpawnManger:
//      This class acts as an interface for Game, it contains a GameObjectFactory which it uses
//      to spawn enemies in the appropriate places on the map. Removes the need for the game
//      class to decide what to spawn where and how. When particles or any game objects are spawned, 
//      this is the class that is called.
//************************************************************************************** *
//  Controls
//************************************************************************************** *
//  On Keyboard:        On Xbox Controller:         Action:
//  -   WASD            -   Left Stick              -   Movement
//  -   Arrow keys      -   Right Stick             -   Shooting
//  -   Left Shift      -   Left Trigger            -   Boost
//
//************************************************************************************** *
//  Gameplay
//************************************************************************************** *
//  The game is a twin stick shooter. The goals depend on the game mode.
//
//  -Standard mode is about shooting as many enemies as possible, points are accrued
//  per enemy killed.
//  
//  -Survival mode is about surviving as long as possible, you can still shoot but
//  your bullets wont kill enemies, only push them away
//
//  There's an ability to boost, it can help you survive a tight spot but can just as easily
//  get you killed if its not used carefully.
//  
//************************************************************************************** *
//  General Comments:
//      So I did most of what I wanted to accomplish for the final, the main thing I didn't get
//      to that I really wanted to was to make more things data driven. The only things that are
//      are the models, audio, and shaders. I do plan on modifying this a bit over the break and
//      adding an ini file or xml files for different enemies.
//
//      A few things in here I feel like are short term solutions, I would definitely like to make
//      the rendering more robust and have Renderer handle the draw calls itself. I think the
//      flickering comes from the fact that the game objects draw themselves, I'll definitely try
//      a different approach to see if that works.
//
//      I also wanted to build in a way to reset after you die but I just ran out of time.
//
//-------------------------------------------------------------------------------------- -
    Game g_game;
//-------------------------------------------------------------------------------------- -
//  Main Function
//-------------------------------------------------------------------------------------- -
int main(int argc, char* argv[])
{
    // INIT APPLICATION
    g_game.Init();

    // MAIN LOOP
    while (g_game.Update() == 1) {}

    // SHUTDOWN APPLICATION
    g_game.Shutdown();

    return 0;
}