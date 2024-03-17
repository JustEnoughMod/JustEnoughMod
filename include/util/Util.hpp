#ifndef UTIL_UTIL_HPP
#define UTIL_UTIL_HPP

namespace JEM {
  constexpr auto atoi(const char *ch) -> int {
    int i = 0;

    while (*ch != '\0') {
      if (*ch < 48 || *ch > 57) {
        break;
      }

      i *= 10;
      i += *ch - 48;

      ++ch;
    }

    return i;
  }

  constexpr auto removeAppName(char *path) -> char * {
    char *orig = path;

    while (*path != '\0') {
      ++path;
    }
    while (*path != '/') {
      --path;
    }
    ++path;
    *path = '\0';

    return orig;
  }
} // namespace JEM

#endif
