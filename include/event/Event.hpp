#ifndef EVENT_EVENT_HPP
#define EVENT_EVENT_HPP

#include <event/Key.hpp>

namespace JEM {
  struct ExitEvent {};

  struct MouseMoveEvent {
      unsigned int windowId;
      unsigned int mouseId;
      int x;
      int y;
      int dx;
      int dy;
  } __attribute__((aligned(32)));

  struct MouseButtonPressedEvent {
      unsigned int windowId;
      unsigned int mouseId;
      Mouse button;
      unsigned int clicks;
      int x;
      int y;
  } __attribute__((aligned(32)));

  struct MouseButtonReleasedEvent {
      unsigned int windowId;
      unsigned int mouseId;
      Mouse button;
      unsigned int clicks;
      int x;
      int y;
  } __attribute__((aligned(32)));

  struct MouseWheelEvent {
      unsigned int windowId;
      unsigned int mouseId;
      MouseWheel direction;
      float x;
      float y;
  } __attribute__((aligned(32)));
} // namespace JEM

#endif
