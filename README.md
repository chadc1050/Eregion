# Eregion
[![CI Status](https://img.shields.io/github/actions/workflow/status/chadc1050/eregion/ci.yml?style=flat)](https://github.com/chadc1050/Eregion/actions)
[![Discord](https://img.shields.io/discord/1296476909739442256.svg?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/eQQTgVFUxM)

[Install OpenGL](https://medium.com/geekculture/a-beginners-guide-to-setup-opengl-in-linux-debian-2bfe02ccd1e)

[Install GLAD](https://gen.glad.sh/)

## Engine
### Hierarchal Structure
- Game: Top level reference to the game and scene manager
  - Scene: Loadable component of the game
    - Entity-Component System (ECS): Manages entity, component relations
      - Entity: A game object
        - Component: A property of an entity
    - Window: Manages viewport
    - Renderer: Integration point between engine and render pipeline
      - Batch Render: Render pipeline

> A note on the BatchRenderer, it would be preferable for there to be an adapter in the form of BatchRenderer<R> where
> R contains all the implementation for the render pipeline. An example being BatchRenderer<SpriteRenderer>.