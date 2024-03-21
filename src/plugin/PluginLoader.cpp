#include <plugin/PluginLoader.hpp>

void JEM::Plugin::PluginLoader::loadFile(const std::string &path, const std::string &name) {
  auto lib = std::make_shared<dylib>(path.c_str(), name.c_str(), false);

  auto createPlugin = lib->get_function<Plugin *()>("_createPlugin");

  auto plugin = std::shared_ptr<Plugin>(createPlugin());

  plugin->load();

  m_dylibVec.push_back(lib);
  m_pluginVec.push_back(plugin);
}

void JEM::Plugin::PluginLoader::loadFolder(const std::string &path) {
  for (const auto &dirEntry : std::filesystem::directory_iterator(path)) {
    loadFile(dirEntry.path().parent_path(), dirEntry.path().filename());
  }
}
