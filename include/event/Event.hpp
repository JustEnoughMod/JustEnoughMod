#ifndef EVENT_EVENT_HPP
#define EVENT_EVENT_HPP

#include <event/Key.hpp>

namespace JEM {
  struct ExitEvent {};

  struct MouseMoveEvent {
      double x;
      double y;
  };

  struct MouseButtonPressedEvent {
      Mouse button;
  };

  struct MouseButtonReleasedEvent {
      Mouse button;
  };

  struct MouseWheelEvent {
      //   float x;
      //   float y;
  };
} // namespace JEM

#endif
