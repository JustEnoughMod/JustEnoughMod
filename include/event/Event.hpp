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
      double x;
      double y;
  };

  struct KeyPressedEvent {
      Key key;
  };

  struct KeyReleasedEvent {
      Key key;
  };

  struct TextInputEvent {
      unsigned int unicode;
  };
} // namespace JEM

#endif
