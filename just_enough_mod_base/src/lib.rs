use just_enough_mod_core::{Plugin, PluginRegistrar};

struct JustEnoughModBase;

impl Plugin for JustEnoughModBase {
    fn init(&self) {
        println!("JustEnoughModBase::init")
    }
}

#[no_mangle]
pub fn plugin_entry(registrar: &mut dyn PluginRegistrar) {
    registrar.register_plugin(Box::new(JustEnoughModBase));
}