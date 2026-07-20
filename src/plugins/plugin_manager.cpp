#include "plugin_manager.h"
#include "plugin_interface.h"
#include <algorithm>

namespace LabelDesigner {

PluginManager::PluginManager() {
}

PluginManager::~PluginManager() {
    shutdownAll();
}

void PluginManager::registerPlugin(PluginInterfacePtr plugin) {
    if (plugin) {
        m_plugins.push_back(plugin);
    }
}

void PluginManager::unregisterPlugin(const QString& name) {
    auto it = std::find_if(m_plugins.begin(), m_plugins.end(),
        [&name](const PluginInterfacePtr& p) { return p && p->name() == name; });
    if (it != m_plugins.end()) {
        (*it)->shutdown();
        m_plugins.erase(it);
    }
}

bool PluginManager::initializeAll() {
    for (auto& p : m_plugins) {
        if (p && !p->initialize()) return false;
    }
    return true;
}

void PluginManager::shutdownAll() {
    for (auto& p : m_plugins) {
        if (p) p->shutdown();
    }
}

std::vector<QString> PluginManager::getPluginNames() const {
    std::vector<QString> names;
    for (const auto& p : m_plugins) {
        if (p) names.push_back(p->name());
    }
    return names;
}

} // namespace LabelDesigner
