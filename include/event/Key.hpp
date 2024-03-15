#ifndef EVENT_KEY_HPP
#define EVENT_KEY_HPP

#include <GLFW/glfw3.h>

namespace JEM {

  enum class Mouse {
    Last = GLFW_MOUSE_BUTTON_4,
    Next = GLFW_MOUSE_BUTTON_5,
    Left = GLFW_MOUSE_BUTTON_LEFT,
    Right = GLFW_MOUSE_BUTTON_RIGHT,
    Middle = GLFW_MOUSE_BUTTON_MIDDLE
  };

  constexpr const char *mouseToString(Mouse e) {
    switch (e) {
      case Mouse::Last:
        return "Last";
      case Mouse::Next:
        return "Next";
      case Mouse::Left:
        return "Left";
      case Mouse::Right:
        return "Right";
      case Mouse::Middle:
        return "Middle";
      default:
        return "__ERROR_UNKOWN";
    }
  }

  // enum class Key {
  //   Space = SDL_SCANCODE_SPACE,
  //   Apostrophe = SDL_SCANCODE_APOSTROPHE,
  //   Comma = SDL_SCANCODE_COMMA,
  //   Minus = SDL_SCANCODE_MINUS,
  //   Period = SDL_SCANCODE_PERIOD,
  //   Slash = SDL_SCANCODE_SLASH,
  //   Key0 = SDL_SCANCODE_0,
  //   Key1 = SDL_SCANCODE_1,
  //   Key2 = SDL_SCANCODE_2,
  //   Key3 = SDL_SCANCODE_3,
  //   Key4 = SDL_SCANCODE_4,
  //   Key5 = SDL_SCANCODE_5,
  //   Key6 = SDL_SCANCODE_6,
  //   Key7 = SDL_SCANCODE_7,
  //   Key8 = SDL_SCANCODE_8,
  //   Key9 = SDL_SCANCODE_9,
  //   Semicolon = SDL_SCANCODE_SEMICOLON,
  //   Equal = SDL_SCANCODE_EQUALS,
  //   KeyA = SDL_SCANCODE_A,
  //   KeyB = SDL_SCANCODE_B,
  //   KeyC = SDL_SCANCODE_C,
  //   KeyD = SDL_SCANCODE_D,
  //   KeyE = SDL_SCANCODE_E,
  //   KeyF = SDL_SCANCODE_F,
  //   KeyG = SDL_SCANCODE_G,
  //   KeyH = SDL_SCANCODE_H,
  //   KeyI = SDL_SCANCODE_I,
  //   KeyJ = SDL_SCANCODE_J,
  //   KeyK = SDL_SCANCODE_K,
  //   KeyL = SDL_SCANCODE_L,
  //   KeyM = SDL_SCANCODE_M,
  //   KeyN = SDL_SCANCODE_N,
  //   KeyO = SDL_SCANCODE_O,
  //   KeyP = SDL_SCANCODE_P,
  //   KeyQ = SDL_SCANCODE_Q,
  //   KeyR = SDL_SCANCODE_R,
  //   KeyS = SDL_SCANCODE_S,
  //   KeyT = SDL_SCANCODE_T,
  //   KeyU = SDL_SCANCODE_U,
  //   KeyV = SDL_SCANCODE_V,
  //   KeyW = SDL_SCANCODE_W,
  //   KeyX = SDL_SCANCODE_X,
  //   KeyY = SDL_SCANCODE_Y,
  //   KeyZ = SDL_SCANCODE_Z,
  //   LeftBracket = SDL_SCANCODE_LEFTBRACKET,
  //   Backslash = SDL_SCANCODE_BACKSLASH,
  //   RightBracket = SDL_SCANCODE_RIGHTBRACKET,
  //   GraveAccent = SDL_SCANCODE_GRAVE,
  //   Escape = SDL_SCANCODE_ESCAPE,
  //   Enter = SDL_SCANCODE_RETURN,
  //   Tab = SDL_SCANCODE_TAB,
  //   Backspace = SDL_SCANCODE_BACKSPACE,
  //   Insert = SDL_SCANCODE_INSERT,
  //   Delete = SDL_SCANCODE_DELETE,
  //   Right = SDL_SCANCODE_RIGHT,
  //   Left = SDL_SCANCODE_LEFT,
  //   Down = SDL_SCANCODE_DOWN,
  //   Up = SDL_SCANCODE_UP,
  //   PageUp = SDL_SCANCODE_PAGEUP,
  //   PageDown = SDL_SCANCODE_PAGEDOWN,
  //   Home = SDL_SCANCODE_HOME,
  //   End = SDL_SCANCODE_END,
  //   CapsLock = SDL_SCANCODE_CAPSLOCK,
  //   ScrollLock = SDL_SCANCODE_SCROLLLOCK,
  //   NumLock = SDL_SCANCODE_NUMLOCKCLEAR,
  //   PrintScreen = SDL_SCANCODE_PRINTSCREEN,
  //   Pause = SDL_SCANCODE_PAUSE,
  //   F1 = SDL_SCANCODE_F1,
  //   F2 = SDL_SCANCODE_F2,
  //   F3 = SDL_SCANCODE_F3,
  //   F4 = SDL_SCANCODE_F4,
  //   F5 = SDL_SCANCODE_F5,
  //   F6 = SDL_SCANCODE_F6,
  //   F7 = SDL_SCANCODE_F7,
  //   F8 = SDL_SCANCODE_F8,
  //   F9 = SDL_SCANCODE_F9,
  //   F10 = SDL_SCANCODE_F10,
  //   F11 = SDL_SCANCODE_F11,
  //   F12 = SDL_SCANCODE_F12,
  //   F13 = SDL_SCANCODE_F13,
  //   F14 = SDL_SCANCODE_F14,
  //   F15 = SDL_SCANCODE_F15,
  //   F16 = SDL_SCANCODE_F16,
  //   F17 = SDL_SCANCODE_F17,
  //   F18 = SDL_SCANCODE_F18,
  //   F19 = SDL_SCANCODE_F19,
  //   F20 = SDL_SCANCODE_F20,
  //   F21 = SDL_SCANCODE_F21,
  //   F22 = SDL_SCANCODE_F22,
  //   F23 = SDL_SCANCODE_F23,
  //   F24 = SDL_SCANCODE_F24,
  //   Num0 = SDL_SCANCODE_KP_0,
  //   Num1 = SDL_SCANCODE_KP_1,
  //   Num2 = SDL_SCANCODE_KP_2,
  //   Num3 = SDL_SCANCODE_KP_3,
  //   Num4 = SDL_SCANCODE_KP_4,
  //   Num5 = SDL_SCANCODE_KP_5,
  //   Num6 = SDL_SCANCODE_KP_6,
  //   Num7 = SDL_SCANCODE_KP_7,
  //   Num8 = SDL_SCANCODE_KP_8,
  //   Num9 = SDL_SCANCODE_KP_9,
  //   NumDecimal = SDL_SCANCODE_KP_DECIMAL,
  //   NumDivide = SDL_SCANCODE_KP_DIVIDE,
  //   NumMultiply = SDL_SCANCODE_KP_MULTIPLY,
  //   NumSubtract = SDL_SCANCODE_KP_MINUS,
  //   NumAdd = SDL_SCANCODE_KP_PLUS,
  //   NumEnter = SDL_SCANCODE_KP_ENTER,
  //   NumEqual = SDL_SCANCODE_KP_EQUALS,
  //   LeftShift = SDL_SCANCODE_LSHIFT,
  //   LeftControl = SDL_SCANCODE_LCTRL,
  //   LeftAlt = SDL_SCANCODE_LALT,
  //   LeftSuper = SDL_SCANCODE_LGUI,
  //   RightShift = SDL_SCANCODE_RSHIFT,
  //   RightControl = SDL_SCANCODE_RCTRL,
  //   RightAlt = SDL_SCANCODE_RALT,
  //   RightSuper = SDL_SCANCODE_RGUI,
  //   Menu = SDL_SCANCODE_MENU
  // };
} // namespace JEM

#endif
