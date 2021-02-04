#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>

class Scene
{
public:

	Scene() : m_animate(true),width(800), height(600){}
	virtual ~Scene() {}

	void SetDimension(int _width, int _height)
	{
		width = _width;
		height = _height;
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

public:
	int width, height;

protected:
	glm::mat4 model, view, projection;

protected:
	bool m_animate = false;
private:

};

#endif
