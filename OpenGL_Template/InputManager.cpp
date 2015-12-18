//InputManager.cpp

#include "InputManager.h"

#include "Game.h"
#include "GameObject.h"

#include "CameraMoveCommand.h"
#include "CameraRotateCommand.h"
#include "MovePlayerCommand.h"
#include "ShootCommand.h"
#include "BoostCommand.h"

#include "Constants.h"
#include "Macros.h"

#include <SDL.h>
#include <Windows.h>
#include <Xinput.h>

//-------------------------------------------------------------------------------------- -
//  Input Manager Constructor
//-------------------------------------------------------------------------------------- -
InputManager::InputManager(Game* pGame)
    :m_pGame(pGame)
    , k_mouseSensitivity(100000)
    , m_pKeyboardCommands(nullptr)
    , m_pControllerCommands(nullptr)
    , m_mouseXInverted(false)
    , m_mouseYInverted(false)
    , m_controllerActive(false)
    , m_keyboardActive(true)
    , m_controller_LeftYInverted(false)
{
    //If a controller exists, create controller bindings
    if (SDL_NumJoysticks() > 0)
    {
        m_pController = SDL_GameControllerOpen(0);
        m_controllerActive = true;
    }
}

//-------------------------------------------------------------------------------------- -
//  Input Manager Initialization Function
//-------------------------------------------------------------------------------------- -
void InputManager::Init()
{
    if (m_keyboardActive)
        m_pKeyboardCommands = new KeyboardCommands();

    if (m_controllerActive)
        m_pControllerCommands = new ControllerCommands();
}

//-------------------------------------------------------------------------------------- -
//  Input Manager Destructor
//-------------------------------------------------------------------------------------- -
InputManager::~InputManager()
{
    m_pGame = nullptr;

    delete m_pKeyboardCommands;
    m_pKeyboardCommands = nullptr;

    delete m_pControllerCommands;
    m_pControllerCommands = nullptr;
}

//-------------------------------------------------------------------------------------- -
//  Keyboard Commands Destructor
//      -Cleans up Keyboard Command Objects
//-------------------------------------------------------------------------------------- -
InputManager::KeyboardCommands::~KeyboardCommands()
{
    delete m_axis_XYZ;
    //delete axis_XYZ_rotation;
    delete m_arrowKeys;
    delete m_leftShift;
}

//****************************************************************************************
//-------------------------------------------------------------------------------------- -
//  Controller Commands Constructor
//      -Cleans up Controller Command Objects
//-------------------------------------------------------------------------------------- -
InputManager::ControllerCommands::ControllerCommands()
{
    m_axis_LeftStick = nullptr;
    m_axis_RightStick = nullptr;
    m_rightTrigger = nullptr;
    m_leftTriggerPress = nullptr;
}
//-------------------------------------------------------------------------------------- -
//  Controller Commands Destructor
//      -Cleans up Controller Command Objects
//-------------------------------------------------------------------------------------- -
InputManager::ControllerCommands::~ControllerCommands()
{
    delete m_axis_LeftStick;
    delete m_rightTrigger;
    delete m_leftTriggerPress;
}
//****************************************************************************************
//-------------------------------------------------------------------------------------- -
//  Add Player Function
//      -Adds a user control to a gameobject if it has the appropriate component
//      -Currently only singleplayer supported
//      -Only working component right now is CameraComponent
//-------------------------------------------------------------------------------------- -
void InputManager::AddPlayer(unsigned int playerIndex, GameObject* pGameObject)
{
    Init();

    //[???] Why doesn't this work with a static_cast like in my GameObject::GetComponent?
    //CameraComponent* pCamComponent = pGameObject->GetComponentReinterpret<CameraComponent>(k_cameraComponentID);
    //m_pKeyboardCommands->axis_XYZ_rotation = new CameraRotateCommand(pGameObject, pCamComponent);

    //KEYBOARD BINDINGS
    if (m_keyboardActive)
    {
        m_pKeyboardCommands->m_axis_XYZ = new MovePlayerCommand(pGameObject);
        m_pKeyboardCommands->m_arrowKeys = new ShootCommand(pGameObject);
        m_pKeyboardCommands->m_axis_XYZ_rotation = m_pKeyboardCommands->m_arrowKeys;
        m_pKeyboardCommands->m_leftShift = new BoostCommand(pGameObject);
    }

    //CONTROLLER BINDINGS
    if (m_controllerActive)
    {
        m_pControllerCommands->m_axis_LeftStick = new MovePlayerCommand(pGameObject);
        m_pControllerCommands->m_rightTrigger = new ShootCommand(pGameObject);
        m_pControllerCommands->m_leftTriggerPress = new BoostCommand(pGameObject);
        m_pControllerCommands->m_axis_RightStick = m_pControllerCommands->m_rightTrigger;
    }
}

//-------------------------------------------------------------------------------------- -
//  Handle Events Function
//      -Encapsulates the handling of events
//      -Returns 0 or FALSE for quitting
//-------------------------------------------------------------------------------------- -
int InputManager::HandleEvents()
{
    //TODO: This is kind of janky, maybe make more elegant
    if (m_keyboardActive)
    {
        ResetUpdateVariables();
    }
    

    SDL_Event appEvent;
    while (SDL_PollEvent(&appEvent))
    {
        //-------------------------
        // WINDOW EVENT HANDLING
        //-------------------------
        if (appEvent.type == SDL_QUIT || appEvent.key.keysym.sym == SDLK_ESCAPE)
            return 0;   //QUIT

        //-------------------------
        // KEY HANDLING
        //-------------------------
        //KEY DOWN EVENTS
        if (appEvent.type == SDL_KEYDOWN)
        {
            //W key
            if (appEvent.key.keysym.sym == SDLK_w)
            {
                m_WKey_Pressed = true;
            }

            //S key
            if (appEvent.key.keysym.sym == SDLK_s)
            {
                m_SKey_Pressed = true;
            }

            //A key
            if (appEvent.key.keysym.sym == SDLK_a)
            {
                m_AKey_Pressed = true;
            }

            //D key
            if (appEvent.key.keysym.sym == SDLK_d)
            {
                m_DKey_Pressed = true;
            }

            //Q key
            if (appEvent.key.keysym.sym == SDLK_q)
            {
                m_QKey_Pressed = true;
            }

            //E key
            if (appEvent.key.keysym.sym == SDLK_e)
            {
                m_EKey_Pressed = true;
            }

            //R key
            if (appEvent.key.keysym.sym == SDLK_r)
            {
                m_RKey_Pressed = true;
            }

            //F key
            if (appEvent.key.keysym.sym == SDLK_f)
            {
                m_FKey_Pressed = true;
            }

            //SPACE BAR
            if (appEvent.key.keysym.sym == SDLK_SPACE)
            {
                m_spaceKey_Pressed = true;
            }

            //UP ARROW
            if (appEvent.key.keysym.sym == SDLK_UP)
            {
                m_upKey_Pressed = true;
            }

            //DOWN ARROW
            if (appEvent.key.keysym.sym == SDLK_DOWN)
            {
                m_downKey_Pressed = true;
            }

            //LEFT ARROW
            if (appEvent.key.keysym.sym == SDLK_LEFT)
            {
                m_leftKey_Pressed = true;
            }

            //RIGHT ARROW
            if (appEvent.key.keysym.sym == SDLK_RIGHT)
            {
                m_rightKey_Pressed = true;
            }

            //LEFT SHIFT
            if (appEvent.key.keysym.sym == SDLK_LSHIFT)
            {
                m_leftShiftKey_Pressed = true;
            }
        }

        //KEY UP EVENTS
        if (appEvent.type == SDL_KEYUP)
        {
            //W key
            if (appEvent.key.keysym.sym == SDLK_w)
            {
                m_WKey_Pressed = false;
            }

            //S key
            if (appEvent.key.keysym.sym == SDLK_s)
            {
                m_SKey_Pressed = false;
            }

            //A key
            if (appEvent.key.keysym.sym == SDLK_a)
            {
                m_AKey_Pressed = false;
            }

            //D key
            if (appEvent.key.keysym.sym == SDLK_d)
            {
                m_DKey_Pressed = false;
            }

            //Q key
            if (appEvent.key.keysym.sym == SDLK_q)
            {
                m_QKey_Pressed = false;
            }

            //E key
            if (appEvent.key.keysym.sym == SDLK_e)
            {
                m_EKey_Pressed = false;
            }

            //R key
            if (appEvent.key.keysym.sym == SDLK_r)
            {
                m_RKey_Pressed = false;
            }

            //F key
            if (appEvent.key.keysym.sym == SDLK_f)
            {
                m_FKey_Pressed = false;
            }

            //SPACE BAR
            if (appEvent.key.keysym.sym == SDLK_SPACE)
            {
                m_spaceKey_Pressed = false;
            }

            //UP ARROW
            if (appEvent.key.keysym.sym == SDLK_UP)
            {
                m_upKey_Pressed = false;
            }

            //DOWN ARROW
            if (appEvent.key.keysym.sym == SDLK_DOWN)
            {
                m_downKey_Pressed = false;
            }

            //LEFT ARROW
            if (appEvent.key.keysym.sym == SDLK_LEFT)
            {
                m_leftKey_Pressed = false;
            }

            //RIGHT ARROW
            if (appEvent.key.keysym.sym == SDLK_RIGHT)
            {
                m_rightKey_Pressed = false;
            }

            //LEFT SHIFT
            if (appEvent.key.keysym.sym == SDLK_LSHIFT)
            {
                m_leftShiftKey_Pressed = false;
            }
        }
        //-------------------------
        // END OF KEY HANDLING
        //-------------------------

        //-------------------------
        // MOUSE EVENTS
        //-------------------------

        if (appEvent.type == SDL_MOUSEBUTTONDOWN)
        {
            if (appEvent.button.button == SDL_BUTTON_LEFT)
            {
                //Store the last clicked position for mouse drags
                m_lastClickedMousePosition_Left.x = appEvent.button.x;
                m_lastClickedMousePosition_Left.y = appEvent.button.y;

                m_leftMouse_Pressed = true;
            }
            else if (appEvent.button.button == SDL_BUTTON_RIGHT)
            {
                m_lastClickedMousePosition_Right.x = appEvent.button.x;
                m_lastClickedMousePosition_Right.y = appEvent.button.y;

                m_rightMouse_Pressed = true;
            }
        }

        if (appEvent.type == SDL_MOUSEBUTTONUP)
        {
            if (appEvent.button.button == SDL_BUTTON_LEFT)
            {
                m_leftMouse_Pressed = false;
            }
            else if (appEvent.button.button == SDL_BUTTON_RIGHT)
            {
                m_rightMouse_Pressed = false;
            }
        }

        //Gathers mouse x and y
        m_currentMousePosition.x = appEvent.button.x;
        m_currentMousePosition.y = appEvent.button.y;

    }

    //CONTROLLER PROCESSING
    if (m_controllerActive)
    {
        //If user hits start, exit
        if (!ProcessControllerEvents())
            return false;
    }

    //Applies held down key logic
    if (m_keyboardActive)
    {
        ApplyKeyboardInput();
        m_pKeyboardCommands->m_axis_XYZ->Execute();
    }
    
    ApplyMouseInput();

    //Execute Command Objects
    //m_pKeyboardCommands->axis_XYZ_rotation->Execute();

    return 1;   //SUCCESS
}

//-------------------------------------------------------------------------------------- -
//  Apply Controller Input
//      -This applies the logic from an attached controller
//-------------------------------------------------------------------------------------- -
bool InputManager::ProcessControllerEvents()
{
    /*
    //A Button
    if (SDL_GameControllerGetButton(m_ppControllers[playerIndex], SDL_CONTROLLER_BUTTON_A))
    {
        m_pControllerCommandStructs[playerIndex].controllerButton_A->Execute();
    }

    //Right Shoulder
    if (SDL_GameControllerGetButton(m_ppControllers[playerIndex], SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
    {
        m_pControllerCommandStructs[playerIndex].controllerButton_RightShoulder->Execute();
    }

    //Left Shoulder
    if (SDL_GameControllerGetButton(m_ppControllers[playerIndex], SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
    {
        m_pControllerCommandStructs[playerIndex].controllerButton_LeftShoulder->Execute();
    }
    */

    const short int k_triggerDeadZone = 1000;

    //Left Trigger
    if (SDL_GameControllerGetAxis(m_pController, SDL_CONTROLLER_AXIS_TRIGGERLEFT) > k_triggerDeadZone)
    {
        m_pControllerCommands->m_leftTriggerPress->Execute();
    }

    //Right Trigger
    if (SDL_GameControllerGetAxis(m_pController, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > k_triggerDeadZone)
    {
        m_pControllerCommands->m_rightTrigger->Execute();
    }

    //START BUTTON
    if (SDL_GameControllerGetButton(m_pController, SDL_CONTROLLER_BUTTON_START))
    {
        return false;	//TODO: Maybe try to eventually replace this with a pause menu
    }

    //Left Stick Movement
    AxisValue xInputValue_LeftStick = SDL_GameControllerGetAxis(m_pController, SDL_CONTROLLER_AXIS_LEFTX);
    AxisValue yInputValue_LeftStick = SDL_GameControllerGetAxis(m_pController, SDL_CONTROLLER_AXIS_LEFTY);
    //Right Stick Movement
    AxisValue xInputValue_RightStick = SDL_GameControllerGetAxis(m_pController, SDL_CONTROLLER_AXIS_RIGHTX);
    AxisValue yInputValue_RightStick = SDL_GameControllerGetAxis(m_pController, SDL_CONTROLLER_AXIS_RIGHTY);

    //TODO: There's probably a more elegant way to do this
    if (m_controller_LeftYInverted)
        yInputValue_LeftStick *= -1;

    m_pControllerCommands->m_axis_LeftStick->SetAxisXValue(xInputValue_LeftStick);
    m_pControllerCommands->m_axis_LeftStick->SetAxisYValue(-yInputValue_LeftStick);
    m_pControllerCommands->m_axis_LeftStick->Execute();

    m_pControllerCommands->m_axis_RightStick->SetAxisXValue(xInputValue_RightStick);
    m_pControllerCommands->m_axis_RightStick->SetAxisYValue(-yInputValue_RightStick);
    m_pControllerCommands->m_axis_RightStick->Execute();
    
    return true;
}

//-------------------------------------------------------------------------------------- -
//  Apply Keyboard Input
//      -This applies the logic from held down keys
//-------------------------------------------------------------------------------------- -
void InputManager::ApplyKeyboardInput()
{
    // A KEY
    if (m_AKey_Pressed)
    {
        m_pKeyboardCommands->m_axis_XYZ->SetAxisXValue(-k_maxStickInputValue);
    }

    // D KEY
    if (m_DKey_Pressed)
    {
        m_pKeyboardCommands->m_axis_XYZ->SetAxisXValue(k_maxStickInputValue);
    }

    // Q KEY
    if (m_QKey_Pressed)
    {
        
    }

    // E KEY
    if (m_EKey_Pressed)
    {
        
    }

    // W KEY
    if (m_WKey_Pressed)
    {
        m_pKeyboardCommands->m_axis_XYZ->SetAxisYValue(k_maxStickInputValue);
    }

    // S KEY
    if (m_SKey_Pressed)
    {
        m_pKeyboardCommands->m_axis_XYZ->SetAxisYValue(-k_maxStickInputValue);
    }

    // R KEY
    if (m_RKey_Pressed)
    {
        m_pKeyboardCommands->m_axis_XYZ_rotation->SetAxisXValue(k_maxStickInputValue);
    }

    // F KEY
    if (m_FKey_Pressed)
    {
        m_pKeyboardCommands->m_axis_XYZ_rotation->SetAxisXValue(-k_maxStickInputValue);
    }

    //SPACE BAR
    if (m_spaceKey_Pressed)
    {
        
    }

    //LEFT SHIFT
    if (m_leftShiftKey_Pressed)
    {
        m_pKeyboardCommands->m_leftShift->Execute();
    }

    //UP ARROW
    if (m_upKey_Pressed)
    {
        m_arrowKey_Pressed = true;
        m_pKeyboardCommands->m_arrowKeys->SetAxisYValue(k_maxStickInputValue);
    }

    //DOWN ARROW
    if (m_downKey_Pressed)
    {
        m_arrowKey_Pressed = true;
        m_pKeyboardCommands->m_arrowKeys->SetAxisYValue(-k_maxStickInputValue);
    }

    //LEFT ARROW
    if (m_leftKey_Pressed)
    {
        m_arrowKey_Pressed = true;
        m_pKeyboardCommands->m_arrowKeys->SetAxisXValue(-k_maxStickInputValue);
    }

    //RIGHT ARROW
    if (m_rightKey_Pressed)
    {
        m_arrowKey_Pressed = true;
        m_pKeyboardCommands->m_arrowKeys->SetAxisXValue(k_maxStickInputValue);
    }

    //If any arrow key has been pressed this update
    if (m_arrowKey_Pressed)
    {
        m_pKeyboardCommands->m_arrowKeys->Execute();
    }
}

//-------------------------------------------------------------------------------------- -
//  Apply Keyboard Input
//      -This applies the logic from held down keys
//-------------------------------------------------------------------------------------- -
#include "Utility.h"

void InputManager::ApplyMouseInput()
{
    if (m_leftMouse_Pressed)
    {
        //
    }

    if (m_rightMouse_Pressed)
    {
        //Calculate offset
        m_mouseDragOffset_Right.x = m_currentMousePosition.x - m_lastClickedMousePosition_Right.x;
        m_mouseDragOffset_Right.y = m_currentMousePosition.y - m_lastClickedMousePosition_Right.y;

        //Multiply by mouse sensitivity
        int xRotation = -k_mouseSensitivity * m_mouseDragOffset_Right.y;
        int yRotation = -k_mouseSensitivity * m_mouseDragOffset_Right.x;

        //Check if user wants inverted controls
        if (m_mouseXInverted)
            yRotation *= -1;

        if (m_mouseYInverted)
            xRotation *= -1;

        //Clamp the rotation value
        Utility::Clamp(xRotation, INT_MIN, INT_MAX);
        Utility::Clamp(yRotation, INT_MIN, INT_MAX);

        //Vertical Rotation
        //m_pKeyboardCommands->axis_XYZ_rotation->SetAxisXValue(xRotation);
        //Horizontal Rotation
        //m_pKeyboardCommands->axis_XYZ_rotation->SetAxisYValue(yRotation);
    }
}

//-------------------------------------------------------------------------------------- -
//  Reset Update Variables
//      -This will reset anything that needs to be reset at the beginning of each
//       game loop update.
//      -An example of this would be resetting keyboard axis to zero
//-------------------------------------------------------------------------------------- -
void InputManager::ResetUpdateVariables()
{
    //Default axes to zero
    m_pKeyboardCommands->m_axis_XYZ->ResetAxisValues();
    m_pKeyboardCommands->m_axis_XYZ_rotation->ResetAxisValues();

    m_arrowKey_Pressed = false;
}