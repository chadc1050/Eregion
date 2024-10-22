# Eregion
![CI Status](https://img.shields.io/github/actions/workflow/status/chadc1050/eregion/ci.yml?style=flat)
<object id="discord-badge" data="https://img.shields.io/discord/1296476909739442256?style=flat&link=https%3A%2F%2Fdiscord.gg%2FeQQTgVFUxM"></object>

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