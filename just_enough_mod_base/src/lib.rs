use bevy::prelude::*;
use just_enough_mod_core::JEMPlugin;

pub struct BasePlugin;

impl Plugin for BasePlugin {
    fn build(&self, app: &mut App) {
        app.add_systems(Update, rotate).add_systems(Startup, setup);
    }
}

impl JEMPlugin for BasePlugin {
    fn test(&self) {
        println!("test");
    }
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

#[no_mangle]
pub fn _bevy_create_plugin() -> *mut dyn Plugin {
    return Box::into_raw(Box::new(BasePlugin));
}
