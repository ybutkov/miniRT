*This project has been created as part of the 42 curriculum by [skomyshe](https://profile-v3.intra.42.fr/users/skomyshe).* 

# miniRT — minimal ray tracer (42 project)

> Elegant minimal ray tracer implemented in C for the 42 curriculum. This README includes quickstart steps, a compact scene syntax reference, usage examples, development tips, and design notes.

## Table of contents
- Quick start
- Minimal `.rt` example
- Scene syntax (reference)
- Mathematical concepts
- Usage examples
- Project structure
- Limitations & improvements
- Development & troubleshooting
- Resources & AI disclosure

---

## Quick start

Requirements
- Linux (X11) or macOS
- `gcc` / `clang`, `make`
- MiniLibX (platform-specific)

Build and run a sample scene:

```bash
cd miniRT
make
./miniRT scenes/test.rt
```

Tip: iterate with small scenes from `scenes/` to keep render times reasonable.

---

## Minimal `.rt` example

Create `scenes/simple.rt` with the snippet below and run `./miniRT scenes/simple.rt`.

```text
# Ambient
A 0.2 255,255,255

# Camera
C 0,0,-5 0,0,1 70

# Light
L 10,10,-10 0.7 255,255,255

# Sphere
sp 0,0,10 2 255,0,0

# Plane
pl 0,-2,0 0,1,0 200,200,200

# Cylinder
cy 2,0,12 0,1,0 1 4 0,0,255
```

---

## Scene syntax (reference)

- Ambient (A): `A <ratio> <R,G,B>` — ratio `0.0–1.0`, color `0–255` per channel. One ambient allowed.
- Camera (C): `C <pos> <orient> <FOV>` — `orient` must be normalized; one camera allowed.
- Light (L): `L <pos> <brightness> <R,G,B>` — brightness `0.0–1.0`.
- Sphere (sp): `sp <center> <diameter> <R,G,B>`
- Plane (pl): `pl <point> <normal> <R,G,B>` — normal should be normalized.
- Cylinder (cy): `cy <center> <orientation> <diameter> <height> <R,G,B>`

General rules
- Values are separated by spaces. Vectors use `x,y,z` notation.
- Colors use `R,G,B` with integer values `0–255`.
- Lines starting with `#` are comments (useful for annotations).

---

## Mathematical concepts

- Vector operations: add/subtract, dot product, cross product, normalization.
- Ray–sphere, ray–plane, ray–cylinder intersection tests.
- Projection geometry and camera rays.
- Lighting: ambient, diffuse (Lambert), basic specular component.
- Shadow rays (hard shadows).

---

## Usage examples

- Render the `test.rt` scene:

```bash
./miniRT scenes/test.rt
```

- Render a large scene (expected to be slow; used for testing correctness):

```bash
./miniRT scenes/10000_spheres.rt
```

---

## Project structure (important files)

```
miniRT/
├── includes/         # headers (miniRT.h, vectors.h, etc.)
├── src/              # source folders: parsing/, math/, objects/, bvh/, draw_func/
├── scenes/           # sample .rt files and tests
├── libft/            # included libft implementation
├── Makefile
└── README.md
```

---

## Limitations (subject constraints)

- No reflections or refractions
- No textures
- No anti-aliasing
- Hard shadows only
- Only one camera and one ambient light

These constraints follow the miniRT subject; they are intentional and define the scope.

Possible improvements (bonus ideas)
- Multiple lights, specular highlights, reflections/refractions
- Anti-aliasing, texture mapping
- Geometry transforms and instancing
- Scene validation tools and a small `.rt` linter

---

## Development & troubleshooting

- MiniLibX linking on Linux: if linking fails, install X11 dev packages (example):

```bash
sudo apt install libx11-dev libxext-dev libbsd-dev
```

- Parser notes: check `scenes/test_parcer/` for many intentionally valid and invalid input examples.
- Performance: rendering is single-threaded per the subject; consider smaller scenes for local iteration.

---

## Resources

- "Ray Tracing in One Weekend" — Peter Shirley
- Scratchapixel — ray tracing fundamentals
- MiniLibX documentation / 42 intranet subject page
- C programming and linear algebra references

---

## AI usage disclosure

This README was revised with AI assistance to improve wording, layout, and examples. The repository source code itself was not generated or modified by AI during this edit. If you used AI in other parts of the project, please document specifics here.

---

## Contributing

Contributions are welcome (scenes, parser fixes, performance improvements). Open a PR and include test scenes demonstrating the change.

