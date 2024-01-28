use bevy::prelude::*;
use just_enough_mod_core::{Plugin, PluginRegistrar};

struct JustEnoughModBase;

impl Plugin for JustEnoughModBase {
    fn init(&self) {
        println!("JustEnoughModBase::init")
    }

    fn bevy_init(&self, app: &mut App) {
        // app.get_schedule_mut(Update).expect("shoudl be here").add_systems(rotate);
        app
        .add_systems(Update, rotate)
        .add_systems(Startup, setup);

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
pub fn plugin_entry(registrar: &mut dyn PluginRegistrar) {
    registrar.register_plugin(Box::new(JustEnoughModBase));
}
