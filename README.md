## OpenGL Lighting System

### Key Classes

1. **Renderer**
   - Manages the rendering pipeline and switches between lighting techniques.
   - Functions:
     - `initialize()`: Sets up the renderer.
     - `renderFrame(Scene& scene, Camera& camera)`: Renders a frame using the current lighting technique.
     - `setTechnique(ILightTechnique* technique)`: Changes the active lighting technique.
     - `shutdown()`: Cleans up resources.

2. **ILightTechnique (Interface)**
   - Abstract base class for different lighting techniques.
   - Functions (pure virtual):
     - `initialize()`: Setup for the technique.
     - `render(Scene& scene, Camera& camera)`: Performs the actual rendering.
     - `cleanup()`: Cleans up resources.

3. **PhotonMapping (Derived from ILightTechnique)**
   - Implements the Photon Mapping lighting technique.
   - Handles photon emission and light gathering in the scene.

4. **ThreePassTechnique (Derived from ILightTechnique)**
   - Implements a Three-Pass rendering technique, such as G-buffer pass, light pass, and final composition.

5. **Scene**
   - Manages all objects and lights within the 3D world.
   - Functions:
     - `addObject(Object* obj)`: Adds an object to the scene.
     - `getObjects()`: Returns all objects.
     - `getLights()`: Returns all lights.

6. **Object**
   - Represents 3D objects in the scene with associated mesh and materials.
   - Functions:
     - `getMaterial()`: Returns the material used by the object.
     - `setMaterial(Material* mat)`: Assigns a material to the object.

7. **Material**
   - Manages shader programs and textures for rendering.
   - Functions:
     - `bind()`: Binds the material (shader) for rendering.
     - `unbind()`: Unbinds the material.
     - `setUniforms()`: Sets shader uniform variables (e.g., textures, colors).

8. **Light**
   - Represents light sources in the scene.
   - Functions:
     - `setPosition(glm::vec3 pos)`: Sets the light’s position.
     - `setColor(glm::vec3 color)`: Sets the light’s color and intensity.


### How It Works
- **Initialization**: The `Renderer` class is initialized with a specific lighting technique (e.g., Photon Mapping or Three-Pass Technique).
- **Rendering**: On each frame, `Renderer::renderFrame()` is called, passing the scene and camera information to the active lighting technique for rendering.
- **Scene Management**: The `Scene` class holds all 3D objects and lights, which are used by the lighting techniques during rendering.
- **Switching Techniques**: You can dynamically switch between lighting techniques using the `Renderer::setTechnique()` method, allowing for flexible experimentation.
