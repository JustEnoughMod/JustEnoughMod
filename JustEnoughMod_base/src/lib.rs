struct JustEnoughMod_base;

impl JustEnoughMod_core::Plugin for JustEnoughMod_base {
    fn init(&self) {
        println!("JustEnoughMod_base::init")
    }
}

#[no_mangle]
pub fn plugin_entry(registrar: &mut dyn JustEnoughMod_core::PluginRegistrar) {
    registrar.register_plugin(Box::new(JustEnoughMod_base));
}