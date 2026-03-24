#pragma once
#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/colour.h>
#include <wx/colordlg.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>
#include "Object3D.hpp"
#include "Matrix.hpp"
#include "SFMLCanvas.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class MainFrame : public wxFrame
{
public:
	MainFrame();

private:
	//init methods
	void buildGUI();
	void setupSizers();
	void bindEvents();


	//gui elements
	wxPanel* controlPanel;
	SFMLCanvas* m_canvas;
	wxSlider* m_sliderX;
	wxSlider* m_sliderY;
	wxSlider* m_sliderZ;
	wxSlider* m_sliderTrX;
	wxSlider* m_sliderTrY;
	wxSlider* m_sliderTrZ;
	wxButton* m_selectFileBtn;
	wxButton* m_leftColorButton;
	wxButton* m_rightColorButton;
	wxButton* m_saveButton;
	
	wxSlider* m_thicknessSlider;
	wxSlider* m_fovSlider;
	wxSlider* m_eyesSlider;
	//wxButton* m_animateBtn;
	wxButton* m_defaultBtn;


	//evt handlers
	void OnExit(wxCloseEvent&);
	void OnSliderChanged(wxCommandEvent&);
	void OnOpenClick(wxCommandEvent&);
	void OnLeftColor(wxCommandEvent&);
	void OnRightColor(wxCommandEvent&);
	void OnSave(wxCommandEvent&);
	//void OnAnimate(wxCommandEvent&);
	void OnDefault(wxCommandEvent&);


	//logic elements
	Object3D* obj = new Object3D();
	wxColour colLeft;
	wxColour colRight;
};