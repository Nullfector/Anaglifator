#pragma once
#include <wx/wx.h>
#include <wx/timer.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <cmath>
#include <vector>
#include <string>
#include "Object3D.hpp"
#include "Matrix.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class SFMLCanvas : public wxPanel
{
public:
	SFMLCanvas(wxWindow* parent, Object3D* obj, wxSlider* sliderX, wxSlider* sliderY);
	~SFMLCanvas();

	//public logic
	void setRotation(int x, int y, int z);
	void setTranslation(float x, float y, float z);
	void setThickness(float t);
	void setProjParams(float fov, float eyeWidth);
	void updateColors(wxColour colLeft, wxColour colRight);
	//void setAnimate(bool isAnimated);
	//bool getAnimate();
	bool SaveToFile(const std::string& path, unsigned int width = 800, unsigned int height = 600);

private:
	//logic
	void DrawLine3D(float thickness = 2.0f);
	//helper for SaveToFile
	void DrawIntoRenderTarget(sf::RenderTarget& target, unsigned int width, unsigned int height, float thickness);

	Object3D* obj;
	wxSlider* sliderX;
	wxSlider* sliderY;
	float m_rotationX = 0;
	float m_rotationY = 0;
	float m_rotationZ = 0;
	float m_translationX = 0;
	float m_translationY = 0;
	float m_translationZ = 120;
	sf::Color colLeft = sf::Color::Red;
	sf::Color colRight = sf::Color::Cyan;


	float eyeWidth = 0.15f;
	float thickness = 2.0f;
	float fov = 450.0f;


	//bool isAnimated = false;
	
	sf::RenderWindow* sfWindow = nullptr;//here SFML can live
	wxTimer* timer;


	// Mouse interaction
	bool m_dragging = false;
	wxPoint m_lastMousePos;
	sf::Vector2f m_center;

	wxSize m_cacheSize;

	//init
	void InitSFML();


	//handlers
	void OnTimer(wxTimerEvent&);
	void OnMouseDown(wxMouseEvent&);
	void OnMouseUp(wxMouseEvent&);
	void OnMouseMove(wxMouseEvent&);
	void OnPaint(wxPaintEvent&);
	void OnResize(wxSizeEvent&);
};



