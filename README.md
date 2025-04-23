# 🕷️ Spider Boss Fight

Spider Boss Fight is a 3D action survival game built using **Godot 4.3** and **GDExtension (C++)**, featuring a procedurally generated terrain and AI-driven spider boss. The player must navigate the map, shoot the spider, and avoid death to survive.

🎥 **[Gameplay Video](https://drive.google.com/file/d/1b7y9dP6LGplK6QVhnZpBBtnF__h0FpFM/view?usp=sharing)**

---

## 🎮 Gameplay Overview

- **Controls**:
  - `W`, `A`, `S`, `D` – Player movement
  - Mouse click or `ui_accept` – Fire projectile
- **Game Logic**:
  - Player dies if hit by spider projectile
  - Player loses if they run out of ammo
  - Spider dies when health reaches zero

---

## 🧱 Core Systems & Scripts

- **Procedural Terrain Generation**
  - `proceduralTerrainGenerator.gd` dynamically generates terrain geometry at runtime.

- **Spider AI Logic**
  - `spiderController.gd`: Governs spider boss behavior including attack, movement, and health.
  - `spider_projectile.tscn`: Scene representing spider’s attack projectile.
  - `spider_hitbox.gd`: Detects collision and manages damage intake.

- **Player Logic**
  - `player.tscn`: Scene including player movement and shooting controls.
  - `playerProjectile.tscn`: Scene instantiated when the player fires.

- **Game Scene**
  - `finalGameSpace.tscn`: Main integrated scene including terrain, spider, player, and environment.

---

## 🛠️ Build & Installation Instructions (macOS)

Pre-requisites:
- [Godot 4.3](https://godotengine.org/)
- [SCons](https://scons.org/)
- Xcode Command Line Tools (`clang`, `make`, etc.)

```bash
# Clone project and setup from root (assignment-5)

rm -rf godot-cpp
git clone -b 4.3 https://github.com/godotengine/godot-cpp
git submodule add -b 4.3 https://github.com/godotengine/godot-cpp
git submodule update --init
scons platform=macos
```

This compiles your native extension, placing `.dylib` in the `bin/` directory.

---

## 📁 Project Structure

```
assignment-5/
├── godot-cpp/                   # GDExtension bindings
├── spiderbossfight/
│   ├── Assets/                  # Game visual assets
│   ├── Audio/                   # Music and sound effects
│   ├── Scenes/                  # All game scenes (*.tscn)
│   │   └── finalGameSpace.tscn  ← Main playable scene
│   ├── Scripts/                 # GDScripts for logic
│   ├── Shaders/                 # Custom shaders
│   └── project.godot            # Entry point for Godot
├── src/                         # C++ source for native modules
├── SConstruct                   # Build script for GDExtension
```

---

## 🚀 Running the Game

1. Open `spiderbossfight/project.godot` in Godot 4.3.
2. Set `Scenes/finalGameSpace.tscn` as your main scene.
3. Press ▶️ to play and test the game.

---

## 🧪 Debugging Tips

- **Spider not moving?** Ensure `spiderController.gd` is properly attached and connected to the scene tree.
- **Projectiles not firing?** Verify input mapping for `ui_accept` and the logic in `player.gd`.
- **Terrain not showing?** Check for runtime errors in `proceduralTerrainGenerator.gd`.

