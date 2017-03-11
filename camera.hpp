#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "scene.hpp"
#include "rgbvector.hpp"

class CameraOptions
{
    public:
        Vector3 cameraPosition, lookAt;
        float cameraRoll;
        float fieldOfView;
        float lensRadius;
        float focusDistance;

        CameraOptions();
};

class Camera
{
    public:
        Camera(int x, int y);
        Camera(int x, int y, CameraOptions options);

        RGBAVector * captureScene(const Scene scene, const int samplesPerPixel) const;

    private:
        Vector3 position, lookAt;
        Vector3 upperLeftCorner;
        Vector3 horizontal, vertical;
        int horizontalPixels, verticalPixels;
        float lensRadius;
        Vector3 u, v, w;

        static Vector3 traceRay(const Ray ray, Scene scene, int depth);


};

#endif // CAMERA_HPP
