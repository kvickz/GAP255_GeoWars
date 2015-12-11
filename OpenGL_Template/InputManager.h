//InputManager.h

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Vector2.h"

#include "SDL_joystick.h"
#include "SDL_gamecontroller.h"

class Game;
class Command;
class GameObject;

class InputManager
{
private:
    Game* m_pGame;

    struct KeyboardCommands
    {
        Command* axis_XYZ;
        Command* axis_XYZ_rotation;
        Command* m_shootCommand;

        ~KeyboardCommands();
    };

    struct ControllerCommands
    {
        Command* m_axis_LeftStick;
        Command* m_rightTrigger;

        ControllerCommands();
        ~ControllerCommands();
    };

    KeyboardCommands* m_pKeyboardCommands;
    ControllerCommands* m_pControllerCommands;

    SDL_GameController* m_pController;

    bool m_keyboardActive;
    bool m_controllerActive;

    //TODO: I haven't thought this through completely, probably not necessary
    bool m_WKey_Pressed = false;
    bool m_SKey_Pressed = false;
    bool m_AKey_Pressed = false;
    bool m_DKey_Pressed = false;
    bool m_QKey_Pressed = false;
    bool m_EKey_Pressed = false;
    bool m_RKey_Pressed = false;
    bool m_FKey_Pressed = false;
    bool m_spaceKey_Pressed = false;

    //****************************//
    //      Mouse variables       //
    //****************************//
    //Mouse Buttons
    bool m_leftMouse_Pressed = false;
    bool m_rightMouse_Pressed = false;

    //Input Sensitivity
    const int k_mouseSensitivity;
    bool m_mouseXInverted;
    bool m_mouseYInverted;

    Vector2_i m_currentMousePosition;
    //Last clicked position
    Vector2_i m_lastClickedMousePosition_Left;
    Vector2_i m_lastClickedMousePosition_Right;
    //Offset from last clicked position
    Vector2_i m_mouseDragOffset_Left;
    Vector2_i m_mouseDragOffset_Right;
    //****************************//

    //****************************//
    //****************************//
    bool m_controller_LeftYInverted;

    //****************************//

public:
    InputManager(Game* pGame);
    ~InputManager();

    void Init();
    int HandleEvents();

    void AddPlayer(unsigned int playerIndex, GameObject* pGameObject);

private:
    void ApplyKeyboardInput();
    void ApplyMouseInput();
    void ResetUpdateVariables();
    bool ProcessControllerEvents();
};

#endif // !INPUTMANAGER_H
