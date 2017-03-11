#include "scene.hpp"

Scene::Scene()
{
    background = Vector3(0, 0, 0);
}

std::vector<Surface *> Scene::getSurfaces() const
{
    return surfaces;
}

void Scene::addSurface(Surface *surface)
{
    surfaces.push_back(surface);
}

Vector3 Scene::getBackground() const
{
    return this->background;
}

void Scene::setBackground(Vector3 background)
{
    this->background = background;
}

