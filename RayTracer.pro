TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    geometry.cpp \
    vector3.cpp \
    surface.cpp \
    ray.cpp \
    scene.cpp \
    material.cpp \
    camera.cpp \
    rgbvector.cpp \
    surfaceinstance.cpp

HEADERS += vector3.hpp \
    ray.hpp \
    surface.hpp \
    camera.hpp \
    scene.hpp \
    material.hpp \
    geometry.hpp \
    stb_image_write.h \
    rgbvector.hpp \
    surfaceinstance.hpp
