# Eregion
[![CI Status](https://img.shields.io/github/actions/workflow/status/chadc1050/eregion/ci.yml?style=flat)](https://github.com/chadc1050/Eregion/actions)
[![Discord](https://img.shields.io/discord/1296476909739442256.svg?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/eQQTgVFUxM)

## Engine
Eregion is designed to be a functional style game engine, inspired by [Bevy's]() plugin architecture. 

### Roadmap
- Rendering Pipelines for:
  - Sprites 
  - Text/Font
  - Line
  - Particles
  - Debug
- Audio:
  - Ambient
  - Music
  - Triggered
- Lighting / Materials
- Overacrching state management
- Queryable Entity Component System that is injectable into mechanism system.
- Shader language seemless interoperability.
- Scriptable input for end to end simulation testing.
- Data streams for easily outputting game state to train AI models, and 
- Interoperability via Plugin with [Universal Scene Descpription (USD)](https://openusd.org/release/index.html) as save files to allow for blender scenes to be easily load and offloaded in and out of the engine.
