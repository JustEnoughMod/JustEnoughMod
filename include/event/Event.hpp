#pragma once

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
} // namespace JEM
