// #include <JustEnoughMod.hpp>

// auto main([[maybe_unused]] int argc, char **argv) -> int {
//   try {
//     // shared_ptr is needed for shared_from_this()
//     std::shared_ptr<JEM::Application> const app = std::make_shared<JEM::Application>();

//     app->init(argv[0]);

//     app->run();
//   } catch (std::exception &e) {
//     JEM::getSystemLogger()->error("Unknown Exception: {}", e.what());
//   }
// }

#include <SDL.h>
#include <cstdio>

int main(int argc, char *argv[]) {
  SDL_SetHint(SDL_HINT_VIDEODRIVER, "wayland,x11");

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("error initializing SDL: %s\n", SDL_GetError());
  }
  SDL_Window *win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
  while (1)
    ;

  return 0;
}
