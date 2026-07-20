# Plugin Development Guide

This document explains how to develop plugins for LabelDesigner and how to register them.

Plugin Interface

The plugin interface is defined in `src/plugins/plugin_interface.h`:

```cpp
class PluginInterface {
public:
    virtual ~PluginInterface() = default;
    virtual bool initialize() = 0;
    virtual QString name() const = 0;
    virtual void shutdown() = 0;
};
```

Create a Plugin

- Implement the PluginInterface in your plugin class.
- Example minimal plugin:

```cpp
#include "src/plugins/plugin_interface.h"

class MyPlugin : public QObject, public LabelDesigner::PluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID LabelDesignerPluginInterface_iid)
    Q_INTERFACES(LabelDesigner::PluginInterface)

public:
    bool initialize() override {
        // register actions, menus, or UI extensions
        return true;
    }
    QString name() const override { return "MyPlugin"; }
    void shutdown() override {
        // cleanup
    }
};
```

Registering and Loading Plugins

- PluginManager currently supports registering PluginInterface instances and calling initialize/shutdown.
- To load plugins dynamically (future enhancement), load shared libraries (DLLs on Windows) and use QPluginLoader to instantiate plugin objects and cast to PluginInterface.

Best Practices

- Keep plugin API stable; avoid depending on internal headers unless versioned.
- Use PluginManager to manage plugin lifecycle and ensure proper shutdown before application exit.
- If exposing UI elements, provide actions that can be connected to the main window or to registered toolbars.

Security

- Plugins execute in the same process as the host application; be cautious when loading third-party plugins. Consider implementing a signing or permission model before allowing untrusted plugins.

