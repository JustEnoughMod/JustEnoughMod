# FAQ

## What is JEM exactly?

JEM is a game engine that is packed as an executable. The game it self is loaded as dll and so are any mods/plugins.

This reversed process has some benefits over normal linking:

- Default Plugin/modding support (Since everything is a dynamic plugin)
- Better Plugin performance since it is based on cpp (not an any interpreted language)
- Easier development of official plugin interfaces
- Game engine can just be used for multiple Games
- Game engine swapable or modable (modding of the Game Engine by replacing the executable is not recommended).

There are also some minor drawbacks:

- Bigger Executable size (the whole game engine needs to be packed into the Executable no room for optimizations)
- Version management might be a bit more complicated for normal games, however it is not a lot more complicated than normal official modding support.

## Why JEM?

Besides the stated pros above JEM aims to support following things:

- Platform independent code
- Multithreading by default (ECS)
- Multiplayer support and interfaces
- High performance
- High flexibility
- Easy PLugin system

## What is not going to be supported?

Not much on this side besides web games. The reason is simply the Vulkan only ideology and high optimization for performance and possible support for FSR/DLSS, Raytracing, etc.

## Want to contribute?

JEM is open source and contributions are great. Just fork the project and make sure you installed pre-commit correctly (see Getting started).

## Platform support

JEM does support Windows and Linux, however MacOS is possible but not developed currently due to the lack of tester.

Android and IOS support is planned, however there is a lot of much more important stuff to do.
