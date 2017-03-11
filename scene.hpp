#ifndef SCENE_HPP
#define SCENE_HPP

#include "surface.hpp"
#include <vector>

/**
 * Stores a bunch of surfaces
 * @brief The Scene class
 */
class Scene
{
    public:
        Scene();

        std::vector<Surface *> getSurfaces() const;
        void addSurface(Surface *surface);
        Vector3 getBackground() const;
        void setBackground(Vector3 background);

    private:
        std::vector<Surface *> surfaces;
        Vector3 background;
};

#endif // SCENE_HPP
