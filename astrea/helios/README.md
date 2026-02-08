# Helios - Earth Visualization

An Electron app that displays a 3D model of Earth with realistic lighting from the Sun and a starfield background using Three.js.

## Features

- 🌍 Interactive 3D Earth sphere with realistic textures
- ☁️ Cloud layer with transparency
- 🌃 City lights visible on the night side
- ⭐ Dynamic starfield with 10,000 stars
- 🌫️ Atmospheric glow effect
- ☀️ Directional Sun lighting (distant light source)
- 🎮 OrbitControls for interactive camera movement

## Controls

- **Left Click + Drag**: Rotate the camera around Earth
- **Right Click + Drag**: Pan the camera
- **Scroll Wheel**: Zoom in and out

## Running the App

```bash
npm start
```

For development with DevTools:
```bash
npm start -- --dev
```

## Technical Details

This app uses Three.js with WebGL for 3D rendering. For WSL compatibility, it uses ANGLE with SwiftShader software rendering as a fallback when hardware acceleration is unavailable.

### Earth Model
- Sphere geometry with 64x64 segments for smooth curvature
- Texture mapping using `earthmap.jpg`
- Cloud layer with transparency
- Emissive map for city lights at night
- Phong material for realistic lighting

### Lighting
- Directional light simulating the Sun
- Ambient light for subtle global illumination
- Hemisphere light for atmospheric effects

### Rendering
- WebGL via Three.js
- ACES Filmic tone mapping for realistic colors
- Shader-based atmospheric glow

## Files

- `main.js` - Electron main process with WebGL configuration
- `index.html` - Three.js scene with Earth visualization
- `images/` - Earth texture, clouds, city lights, and star sprites
- `package.json` - Dependencies and scripts

## Requirements

- Node.js
- npm
- Electron (installed as dependency)
- Three.js (installed as dependency)
