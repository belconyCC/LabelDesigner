#pragma once

#include <QString>
#include <QObject>

namespace LabelDesigner {

/**
 * @brief Plugin interface for extending LabelDesigner
 */
class PluginInterface {
public:
    virtual ~PluginInterface() = default;

    /**
     * @brief Initialize plugin
     */
    virtual bool initialize() = 0;

    /**
     * @brief Get plugin name
     */
    virtual QString name() const = 0;

    /**
     * @brief Shutdown plugin
     */
    virtual void shutdown() = 0;
};

#define LabelDesignerPluginInterface_iid "com.belconycc.LabelDesigner.PluginInterface"

Q_DECLARE_INTERFACE(LabelDesigner::PluginInterface, LabelDesignerPluginInterface_iid)

} // namespace LabelDesigner
