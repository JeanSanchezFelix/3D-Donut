# Randomly Moving 3D Donut Mesh

This is a fun little project that features a randomly moving donut mesh. It was initially created in a separate repository and later forked to become its own independent project. The implementation is done in C++ using the OpenFrameworks library.

## Installation

To run this project, you'll need to have OpenFrameworks and the necessary dependencies set up on your machine. Follow the instructions below to get started:

1. Clone this repository to your local machine.

   ```bash
   git clone <https://github.com/JeanSanchezFelix/3D-Donut.git>
   ```

2. Install OpenFrameworks by following the instructions provided in the [OpenFrameworks documentation](https://openframeworks.cc/download/).

## Setup

The donut mesh is created using the *ofMesh* class provided by the openFrameworks library. It consists of a torus shape with an outer radius **(radius1)** and an inner radius **(radius2)**. The number of segments in the torus is defined by **numSegments**, and the number of sides for each segment is defined by **numSides**.

The donut mesh is animated by rotating it smoothly and slowly around the X and Y axes. The rotation angles are calculated using "Perlin noise" and are updated in the update() function.

The rotation is achieved using quaternions, and the *ofQuaternion* class is used to create the rotation quaternions for X and Y axes. The previous and current rotations are interpolated using spherical linear interpolation **(slerp)** for smoother rotation.

The rotation is applied to the donut mesh vertices by transforming each vertex using a rotation matrix created from the rotation quaternion. The transformed vertices are then updated in the update() function.

The donut mesh is drawn in wireframe mode in the draw() function using the drawWireframe() method provided by the ofMesh class. The drawing is done within a 3D scene, and the camera is set up to provide the desired perspective.

## Usage

    1. Ensure that you have openFrameworks properly installed.
    2. Clone the repository or download the source code.
    3. Using the terminal, navigate to the project directory.
    4. Run make to build the project.
    5. Run the executable file generated.
    6. Enjoy the randomly moving donut mesh!

This will compile the code, build the project, and launch the application. You should see a window displaying the randomly moving donut mesh.

Feel free to experiment with the code and modify it to create your own variations of the donut mesh. Have fun!

## Screenshot

![Verdadero LOGO donut](https://github.com/JeanSanchezFelix/3D-Donut/assets/109083974/c18d579d-562d-47f6-85f6-a1b42d0fa2e3)

A fun bug while creating said donut.

## Acknowledgments

- The Randomly Moving Donut Mesh project was inspired by [[C Program That Generates 3D Spinning Donut](https://www.youtube.com/watch?v=4pHREcZJ9BQ)].
- Special thanks to user *alptugan* for their study repository on 3D structures [[3D-Studies-with-openFrameworks](https://github.com/alptugan/3D-Studies-with-openFrameworks.git)]
  
  

