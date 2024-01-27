use bevy::prelude::*;
use just_enough_mod_core::{Plugin, PluginRegistrar};

struct JustEnoughModBase;

impl Plugin for JustEnoughModBase {
    fn init(&self) {
        println!("JustEnoughModBase::init")
    }

    fn bevy_init(&self, sched: Option<&mut Schedule>) {
        sched.expect("shoudl be here").add_systems(rotate);
        // app
        // .add_systems(Update, rotate);
    }
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
