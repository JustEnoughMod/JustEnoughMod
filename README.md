# JustEnoughMod

JustEnoughMod (JEM) is a Minecraft like Game, but it is supposed to be modded.

## How it works

JustEnoughMod is a Minecraft like game based on mods. Every base component (except the mod loader itself) is just a mod that can be loaded into the game at runtime. This mod/plugin only system allows specifying uniform interfaces between the mods and keep redundancy at a minimal level.

## What should a mod/plugin (not) do

Generally every mod should obviously implement game features and mechanics. However mods can also just be libraries and interfaces for other mods in order to decrease coding effort for the final modder.

Here is a list what mods should not do:

- Implement redundant interfaces (alternative entity loader for example)
- Implement performance fixes
- Implement patches for bugs or other issues

Generally the solution to these problems is just to contribute upstream and fix it on the source! If this is not possible due to no maintenance, just fork the project and start to implement there. However please keep the number of parallel forks at the same time.

## How about mod incompatibilities

Later on we will implement a version system that allows to determine what version is compatible with which plugin. This is currently not possible due to heavy development, so generally just keep everything up to date.

## How to get started with modding

TBD !Currently no example plugin is implemented!
