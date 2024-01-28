use bevy::prelude::*;
use libloading::Library;

use just_enough_mod_core::{Plugin, PluginRegistrar};

struct Registrar {
    plugins: Vec<Box<dyn Plugin>>,
}

impl PluginRegistrar for Registrar {
    fn register_plugin(&mut self, plugin: Box<dyn Plugin>) {
        self.plugins.push(plugin);
    }
}

fn main() {
    let mut registrar = Registrar {
        plugins: Vec::new(),
    };

    for path in std::env::args_os().skip(1) {
        println!("Loading: {:?}", path);
        // NOTE: You need to do something to ensure you're only loading "safe" code. Out of scope
        // for this code.
        unsafe {
            // In this code, we never close the shared library - if you need to be able to unload the
            // library, that will require more work.
            let lib = Box::leak(Box::new(Library::new(path).unwrap()));
            let func: libloading::Symbol<unsafe extern "C" fn(&mut dyn PluginRegistrar) -> ()> =
                lib.get(b"plugin_entry").unwrap();
            func(&mut registrar);
        }
    }
    
    for plugin in &registrar.plugins {
        plugin.init();
    }

    let mut app = App::new();
    app
    .add_plugins(DefaultPlugins);
    
    for plugin in &registrar.plugins {
       plugin.bevy_init(&mut app);
    }

    app.run();
}