#pragma once

#include <glm/glm.hpp>

class Scene
{
protected:
    glm::mat4 model, view, projection;

public:
    int width;
    int height;

    Scene() : m_animate(true), width(800), height(600) { }
    virtual ~Scene() {}

    void SetDimensions(int w, int h) {
        width = w;
        height = h;
    }

    /**
      Load textures, initialize shaders, etc.
      */
    virtual void InitScene() = 0;

    /**
      This is called prior to every frame.  Use this
      to update your animation.
      */
    virtual void Update(float t) = 0;

    /**
      Draw your scene.
      */
    virtual void Render() = 0;

    /**
      Called when screen is resized
      */
    virtual void Resize(int, int) = 0;

    void Animate(bool value) { m_animate = value; }
    bool Animating() { return m_animate; }

protected:
    bool m_animate;
};
