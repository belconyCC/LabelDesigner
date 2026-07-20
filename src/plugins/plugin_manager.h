#pragma once

#include <QString>
#include <vector>
#include <memory>

namespace LabelDesigner {

class PluginInterface;
using PluginInterfacePtr = std::shared_ptr<PluginInterface>;

/**
 * @brief Simple plugin manager that loads/unloads plugins
 * Currently a stub that holds plugin instances
 */
class PluginManager {
public:
    PluginManager();
    ~PluginManager();

    void registerPlugin(PluginInterfacePtr plugin);
    void unregisterPlugin(const QString& name);

    bool initializeAll();
    void shutdownAll();

    std::vector<QString> getPluginNames() const;

private:
    std::vector<PluginInterfacePtr> m_plugins;
};

} // namespace LabelDesigner
