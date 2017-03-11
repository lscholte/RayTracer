#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <fstream>
#include "ray.hpp"
#include "surface.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "stb_image_write.h"

using namespace std;

int main()
{
    const float horizontalPixels = 400, verticalPixels = 200;

    CameraOptions cameraOptions;
    cameraOptions.cameraPosition = Vector3(0, 0, 0);
    cameraOptions.lookAt = Vector3(0, 0, -1);
    cameraOptions.fieldOfView = 90;
    cameraOptions.lensRadius = 0;
    cameraOptions.cameraRoll = 0;

    Camera camera = Camera(horizontalPixels, verticalPixels, cameraOptions);

    Scene scene;
    scene.setBackground(Vector3(1,1,1));


    scene.addSurface(new Plane(
                         Vector3(0,1.5,0),
                         Vector3(0,1,0),
                         new Diffuse(Vector3(0.2,0.2,0.2))
                         )
                     );
    scene.addSurface(new Plane(
                         Vector3(-2,0,0),
                         Vector3(1,0,0),
                         new Diffuse(Vector3(1,0.3,0.3))
                         )
                     );
    scene.addSurface(new Plane(
                         Vector3(0,0,-2.0),
                         Vector3(0,0,1),
                         new Diffuse(Vector3(0.3,1,0.3))
                         )
                     );
    scene.addSurface(new Plane(
                         Vector3(2,0,0),
                         Vector3(1,0,0),
                         new Diffuse(Vector3(0.3,0.3,1))
                         )
                     );
    scene.addSurface(new Plane(
                         Vector3(0,-1.5,0),
                         Vector3(0,1,0),
                         new Diffuse(Vector3(0.7,0.7,0.7))
                         )
                     );

//    scene.addSurface((new Sphere(
//                          Vector3(0.5,-0.3,-0.65),
//                          0.4,
//                          new Metal(Vector3(0.8,0.8,0.8), 0))
//                          ));

//    scene.addSurface((new Sphere(
//                          Vector3(-0.5,-0.3,-0.8),
//                          0.4,
//                          new Dielectric(1.5))
//                          ));

    scene.addSurface((new Rectangle(Vector3(0,0,0),
                                   Vector3(0,0,1),
                                   1, 1.5,
                                   new Light(Vector3(1,0.8,0))))
                     ->translate(Vector3(0,0,-1.999))
                     );


    RGBAVector *pixels = camera.captureScene(scene, 100);

//    stbi_write_png("/Users/lscholte/Desktop/test.png", horizontalPixels, verticalPixels, 4, pixels, horizontalPixels * 4);
//    system("open /Users/lscholte/Desktop/test.png");

    stbi_write_png("test.png", horizontalPixels, verticalPixels, 4, pixels, horizontalPixels * 4);
    system("open test.png");

    return 0;
}
