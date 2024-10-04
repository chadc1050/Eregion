# Eregion

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

## Styles 

### GLSL
[GLSL File Extension Docs](https://www.khronos.org/opengles/sdk/tools/Reference-Compiler/)

| File Type               | Extension |
| ----------------------- | --------- |
| Vertex                  | .vert     |
| Tessellation Control    | .tesc     |
| Tessellation Evaluation | .tese     |
| Geometry                | .geom     |
| Fragment                | .frag     |
| Compute                 | .comp     |

### C++
TIGER_STYLE.md style guide added to styles dir, "Wu Tang Clan aint nothing to f with". Originates from the TigerBeetle financial database development team, focusing on reliability and security first, perf second, and dev experience third. This style seems very appealing and is inspired by development practices from NASA and MIT proof based development practices.

[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

Googles style guide has some really good concepts especially for multi-thousand developer oriented coding styles. This is fairly strict and very comprehensive to ensure consistency across many projects, teams, and generations of developers. 