use bevy::prelude::*;

pub trait JEMPlugin: Plugin {
    fn test(&self);
}