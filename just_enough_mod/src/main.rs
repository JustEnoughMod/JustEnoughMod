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
    
    for plugin in registrar.plugins {
        plugin.init();
    }

    App::new()
        .insert_resource(ClearColor(Color::BLACK))
        .add_plugins(DefaultPlugins)
        .add_systems(Startup, setup)
        .add_systems(Update, rotate)
        .run();
}

fn setup(mut commands: Commands, asset_server: Res<AssetServer>) {
    // Camera
    commands.spawn(Camera2dBundle::default());

    // Sprite
    commands.spawn(SpriteBundle {
        texture: asset_server.load("bevy.png"),
        ..default()
    });
}

fn rotate(mut query: Query<&mut Transform, With<Sprite>>, time: Res<Time>) {
    for mut bevy in &mut query {
        bevy.rotate_local_z(-time.delta_seconds());
    }
}