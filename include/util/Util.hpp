#pragma once

namespace JEM {
constexpr int atoi(const char *ch) {
  int i = 0;

  while (*ch != '\0') {
    if (*ch < 48 || *ch > 57)
      break;

    i *= 10;
    i += *ch - 48;

    ch++;
  }

  return i;
}

constexpr char *removeAppName(char *path) {
  char *orig = path;

  while (*path != '\0')
    path++;
  while (*path != '/')
    path--;
  path++;
  *path = '\0';

  return orig;
}
} // namespace JEM