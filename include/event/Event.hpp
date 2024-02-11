#pragma once

#include <any>
#include <queue>

#include <SDL.h>

namespace JEM {
    enum class Mouse
    {
        Last   = SDL_BUTTON_X1,
        Next   = SDL_BUTTON_X2,
        Left   = SDL_BUTTON_LEFT,
        Right  = SDL_BUTTON_RIGHT,
        Middle = SDL_BUTTON_MIDDLE
    };

    enum class MouseWheel
    {
        Normal = SDL_MOUSEWHEEL_NORMAL,
        Flipped = SDL_MOUSEWHEEL_FLIPPED
    };

     enum class Key
    {
        Space        = SDL_SCANCODE_SPACE,
        Apostrophe   = SDL_SCANCODE_APOSTROPHE,
        Comma        = SDL_SCANCODE_COMMA,
        Minus        = SDL_SCANCODE_MINUS,
        Period       = SDL_SCANCODE_PERIOD,
        Slash        = SDL_SCANCODE_SLASH,
        Key0         = SDL_SCANCODE_0,
        Key1         = SDL_SCANCODE_1,
        Key2         = SDL_SCANCODE_2,
        Key3         = SDL_SCANCODE_3,
        Key4         = SDL_SCANCODE_4,
        Key5         = SDL_SCANCODE_5,
        Key6         = SDL_SCANCODE_6,
        Key7         = SDL_SCANCODE_7,
        Key8         = SDL_SCANCODE_8,
        Key9         = SDL_SCANCODE_9,
        Semicolon    = SDL_SCANCODE_SEMICOLON,
        Equal        = SDL_SCANCODE_EQUALS,
        KeyA         = SDL_SCANCODE_A,
        KeyB         = SDL_SCANCODE_B,
        KeyC         = SDL_SCANCODE_C,
        KeyD         = SDL_SCANCODE_D,
        KeyE         = SDL_SCANCODE_E,
        KeyF         = SDL_SCANCODE_F,
        KeyG         = SDL_SCANCODE_G,
        KeyH         = SDL_SCANCODE_H,
        KeyI         = SDL_SCANCODE_I,
        KeyJ         = SDL_SCANCODE_J,
        KeyK         = SDL_SCANCODE_K,
        KeyL         = SDL_SCANCODE_L,
        KeyM         = SDL_SCANCODE_M,
        KeyN         = SDL_SCANCODE_N,
        KeyO         = SDL_SCANCODE_O,
        KeyP         = SDL_SCANCODE_P,
        KeyQ         = SDL_SCANCODE_Q,
        KeyR         = SDL_SCANCODE_R,
        KeyS         = SDL_SCANCODE_S,
        KeyT         = SDL_SCANCODE_T,
        KeyU         = SDL_SCANCODE_U,
        KeyV         = SDL_SCANCODE_V,
        KeyW         = SDL_SCANCODE_W,
        KeyX         = SDL_SCANCODE_X,
        KeyY         = SDL_SCANCODE_Y,
        KeyZ         = SDL_SCANCODE_Z,
        LeftBracket  = SDL_SCANCODE_LEFTBRACKET,
        Backslash    = SDL_SCANCODE_BACKSLASH,
        RightBracket = SDL_SCANCODE_RIGHTBRACKET,
        GraveAccent  = SDL_SCANCODE_GRAVE,
        Escape       = SDL_SCANCODE_ESCAPE,
        Enter        = SDL_SCANCODE_RETURN,
        Tab          = SDL_SCANCODE_TAB,
        Backspace    = SDL_SCANCODE_BACKSPACE,
        Insert       = SDL_SCANCODE_INSERT,
        Delete       = SDL_SCANCODE_DELETE,
        Right        = SDL_SCANCODE_RIGHT,
        Left         = SDL_SCANCODE_LEFT,
        Down         = SDL_SCANCODE_DOWN,
        Up           = SDL_SCANCODE_UP,
        PageUp       = SDL_SCANCODE_PAGEUP,
        PageDown     = SDL_SCANCODE_PAGEDOWN,
        Home         = 268,
        End          = 269,
        CapsLock     = 280,
        ScrollLock   = 281,
        NumLock      = 282,
        PrintScreen  = 283,
        Pause        = 284,
        F1           = 290,
        F2           = 291,
        F3           = 292,
        F4           = 293,
        F5           = 294,
        F6           = 295,
        F7           = 296,
        F8           = 297,
        F9           = 298,
        F10          = 299,
        F11          = 300,
        F12          = 301,
        F13          = 302,
        F14          = 303,
        F15          = 304,
        F16          = 305,
        F17          = 306,
        F18          = 307,
        F19          = 308,
        F20          = 309,
        F21          = 310,
        F22          = 311,
        F23          = 312,
        F24          = 313,
        F25          = 314,
        Num0         = 320,
        Num1         = 321,
        Num2         = 322,
        Num3         = 323,
        Num4         = 324,
        Num5         = 325,
        Num6         = 326,
        Num7         = 327,
        Num8         = 328,
        Num9         = 329,
        NumDecimal   = 330,
        NumDivide    = 331,
        NumMultiply  = 332,
        NumSubtract  = 333,
        NumAdd       = 334,
        NumEnter     = 335,
        NumEqual     = 336,
        LeftShift    = 340,
        LeftControl  = 341,
        LeftAlt      = 342,
        LeftSuper    = 343,
        RightShift   = 344,
        RightControl = 345,
        RightAlt     = 346,
        RightSuper   = 347,
        Menu         = 348
    };

    struct ExitEvent {};

    struct MouseMoveEvent {
        unsigned int windowId;
        unsigned int mouseId;
        int x;
        int y;
        int dx;
        int dy;
    };

    struct MouseButtonPressedEvent {
        unsigned int windowId;
        unsigned int mouseId;
        Mouse button;
        unsigned int clicks;
        int x;
        int y;
    };

    struct MouseButtonReleasedEvent {
        unsigned int windowId;
        unsigned int mouseId;
        Mouse button;
        unsigned int clicks;
        int x;
        int y;
    };

    struct MouseWheelEvent {
        unsigned int windowId;
        unsigned int mouseId;
        MouseWheel direction;
        float x;
        float y;
    };
}