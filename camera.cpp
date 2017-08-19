#include "camera.hpp"
#include "material.hpp"
#include <iostream>
#include <fstream>
#include "geometry.hpp"
#include <float.h>
#include <math.h>


//Constructors

CameraOptions::CameraOptions()
{
    cameraPosition = Vector3(0, 0, 0);
    lookAt = Vector3(0, 0, -1);
    fieldOfView = 90;
    lensRadius = 0;
    focusDistance = (cameraPosition-lookAt).getLength();
    cameraRoll = 0;
}

/**
 * @brief Camera Constructs a simple pinhole Camera with no focus blur.
 * The field of view is set to 105 degrees by default. The camera is positioned
 * at (0, 0, 0) and is looking at (0, 0, -1). There is no camera roll.
 * @param x The number of horizontal pixels to capture
 * @param y The number of vertical pixels to capture
 */
Camera::Camera(int x, int y)
    : Camera(x, y, CameraOptions())
{
}

/**
 * @brief Camera Constructs a Camera
 * @param x The number of horizontal pixels to capture
 * @param y The number of vertical pixels to capture
 * @param fov The field of view (in degrees) of the camera
 * @param lensRadius The radius of the camera lense
 * @param focusDistance The distance at which the camera is focused
 * @param position The position of the camera
 * @param lookAt The location at which the camera is looking
 * @param cameraRoll The roll (in degrees) of the camera,
 * measured counterclockwise
 */
Camera::Camera(int x, int y, const CameraOptions &options)
{
    //Convert Field of View and Camera Roll from degrees to radians
    float fovRadians = options.fieldOfView * M_PI/180;
    float cameraRollRadians = options.cameraRoll * M_PI/180;

    float halfHeight = tan(fovRadians/2);
    float halfWidth = float(x/y) * halfHeight;

    lensRadius = options.lensRadius;

    horizontalPixels = x;
    verticalPixels = y;

    position = options.cameraPosition;
    lookAt = options.lookAt;

    Vector3 universalUp = Vector3(0, 1, 0);

    //Constructs an orthognal basis to position/orient the camera.
    //w corresponds to moving forward/backward with respect to lookDirection
    //u corresponds to moving left/right with respect to lookDirection
    //v corresponds to moving up/down with respect to lookDirection
    w = (position-lookAt);
    u = universalUp.cross(w);

    //This will happen if universalUp is in the same direction as lookAt
    //so pick a new universal up and recalculate u
    if (u.isZeroVector())
    {
        universalUp = Vector3(1, 0, 0);
        u = universalUp.cross(w);
    }

    v = w.cross(u);

    //Make the orthogonal basis an orthonormal basis
    w = w.getUnitVector();
    u = u.getUnitVector();
    v = v.getUnitVector();

    //Apply the camera roll. This uses Rodrigues' Rotation Formula
    //to rotate the plane that the v and w vectors lie in around
    //the w vector in a counterclockwise direction
    v = v*cos(cameraRollRadians) +
            w.cross(v)*sin(cameraRollRadians) +
            w*w.dot(v)*(1-cos(cameraRollRadians));
    u = u*cos(cameraRollRadians) +
            w.cross(u)*sin(cameraRollRadians) +
            w*w.dot(u)*(1-cos(cameraRollRadians));

    upperLeftCorner = position -
            halfWidth*options.focusDistance*u +
            halfHeight*options.focusDistance*v -
            options.focusDistance*w;
    horizontal = 2*halfWidth*options.focusDistance*u;
    vertical = 2*halfHeight*options.focusDistance*v;
}

RGBAVector * Camera::captureScene(const Scene &scene, int samplesPerPixel) const
{
    RGBAVector *pixels = new RGBAVector[horizontalPixels * verticalPixels];

#pragma omp parallel for
    for (int j = 0; j < verticalPixels; ++j)
    {
        for (int i = 0; i < horizontalPixels; ++i)
        {
            Vector3 col;
            for (int s = 0; s < samplesPerPixel; ++s)
            {
                //Send out a ray to a random spot somewhere inside the current pixel
                float x = float(i + rand() / ((float) RAND_MAX+1)) / float(horizontalPixels);
                float y = float(j + rand() / ((float) RAND_MAX+1)) / float(verticalPixels);

                Vector3 rd = lensRadius*getRandomPointOnUnitDisc();
                Vector3 offset = u*rd.x + v*rd.y;
                Ray r(position + offset, upperLeftCorner + horizontal*x - vertical*y - position - offset);

                col += traceRay(r, scene, 0);
            }

            //Take the average colour of all the samples for this pixel
            col /= float(samplesPerPixel);

            //Applies a filter which should brighten the image a bit
            col = Vector3(sqrt(col.x), sqrt(col.y), sqrt(col.z));

            //Colours must be converted from range [0, 1] to [0, 255].
            //Using slightly less than 256 eliminates the problem where
            //we have 256*1.0=256, which is outside the valid range.
            col.x = fmin(col.x, 1);
            col.y = fmin(col.y, 1);
            col.z = fmin(col.z, 1);

            col *= 255.99;

            pixels[j*horizontalPixels + i] = RGBAVector(col);
        }
    }
    return pixels;
}

Vector3 Camera::traceRay(const Ray &ray, const Scene &scene, int depth)
{
    HitRecord record;
    bool surfaceHit = false;
    float closestObjectDistance = FLT_MAX;

    //Find the closest object that is hit by the ray
    for (Surface *surface : scene.getSurfaces())
    {
        if (surface->hitWithRay(ray, 0.001, closestObjectDistance, record))
        {
            surfaceHit = true;
            closestObjectDistance = record.t;
        }
    }

    //If an object was hit
    if (surfaceHit)
    {
        Ray scatteredRay;
        Vector3 attenuation;
        Vector3 emitted = record.material->emitted();

        //If this material scatters the ray and this ray has not been scattered a lot
        if (depth < 50 && record.material->scatter(ray, record, attenuation, scatteredRay))
        {
            //Trace the scattered ray
            return emitted + traceRay(scatteredRay, scene, depth+1)*attenuation;
        }
        else
        {
            //There are no more scattered rays, so return the emitted colour of the material
            return emitted;
        }
    }

    //Otherwise draw the background
    return scene.getBackground();
}
