#include <JustEnoughMod.hpp>

int main([[maybe_unused]] int argc, char **argv) {

  JEM::Application app;

  app.init(argv[0]);

  app.run();

  app.deinit();
}
