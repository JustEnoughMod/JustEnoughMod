use bevy::prelude::*;
use just_enough_mod_core::JEMPlugin;

fn main() {
    let mut app = App::new();

    app.add_plugins(DefaultPlugins);

    for path in std::env::args_os().skip(1) {
        println!("Loading: {:?}", path);

        unsafe {
            app.load_plugin(path);
        }
    }

    app.get_added_plugins::<Box<JEMPlugin>>()[0].test();

    app.run();
}