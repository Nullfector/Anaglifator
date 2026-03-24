#include "MainFrame.h"


MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Projekt Anaglify",
	wxDefaultPosition, wxSize(800, 730)), 
	colLeft(200, 0, 0, 255), 
	colRight(0, 0, 200, 255)
{
	buildGUI();
	setupSizers();
	bindEvents();
	Centre();
}

void MainFrame::buildGUI() {
	controlPanel = new wxPanel(this);

	m_sliderX = new wxSlider(controlPanel, wxID_ANY, 0, -90, 90,
		wxDefaultPosition, wxSize(110, -1));

	m_sliderY = new wxSlider(controlPanel, wxID_ANY, 0, 0, 360,
		wxDefaultPosition, wxSize(110, -1));

	m_sliderZ = new wxSlider(controlPanel, wxID_ANY, 0, 0, 360,
		wxDefaultPosition, wxSize(110, -1));

	m_sliderTrX = new wxSlider(controlPanel, wxID_ANY, 0, -500, 500, wxDefaultPosition, wxSize(110, -1));
	m_sliderTrY = new wxSlider(controlPanel, wxID_ANY, 0, -500, 500, wxDefaultPosition, wxSize(110, -1));
	m_sliderTrZ = new wxSlider(controlPanel, wxID_ANY, 175, -100, 500, wxDefaultPosition, wxSize(110, -1));

	m_thicknessSlider = new wxSlider(controlPanel, wxID_ANY, 2, 0, 10, wxDefaultPosition, wxSize(110, -1));
	m_fovSlider = new wxSlider(controlPanel, wxID_ANY, 22, 1, 100, wxDefaultPosition, wxSize(110, -1));
	m_eyesSlider = new wxSlider(controlPanel, wxID_ANY, 15, 0, 100, wxDefaultPosition, wxSize(110, -1));

	m_selectFileBtn = new wxButton(controlPanel, wxID_ANY, "Wybierz plik");

	m_leftColorButton = new wxButton(controlPanel, wxID_ANY, "Lewy kolor");
	m_rightColorButton = new wxButton(controlPanel, wxID_ANY, "Prawy kolor");

	m_saveButton = new wxButton(controlPanel, wxID_ANY, "Zapisz obraz");

	//m_animateBtn = new wxButton(controlPanel, wxID_ANY, "Animuj");
	m_defaultBtn = new wxButton(controlPanel, wxID_ANY, "Domyœlne");

	m_canvas = new SFMLCanvas(this, obj, m_sliderX, m_sliderY);
	m_canvas->updateColors(colLeft, colRight);
}



void MainFrame::setupSizers() {
	wxBoxSizer* controlSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* XSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* XRotSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* XTrSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* YSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* YRotSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* YTrSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* ZSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* ZRotSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* ZTrSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* OtherSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* ThSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* FovSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* EyesSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* colorButtonSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* otherButtonSizer = new wxBoxSizer(wxVERTICAL);
	
	controlSizer->AddSpacer(10);

	XSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "X"));
	XRotSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Rot:"));
	XRotSizer->Add(m_sliderX, 0, wxALL, 5);
	XTrSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Tr:"));
	XTrSizer->Add(m_sliderTrX, 0, wxALL, 5);
	XSizer->Add(XRotSizer, wxSizerFlags().CenterHorizontal());
	XSizer->Add(XTrSizer, wxSizerFlags().CenterHorizontal());
	controlSizer->Add(XSizer, wxSizerFlags().CenterVertical());

	YSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Y:"));
	YRotSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Rot:"));
	YRotSizer->Add(m_sliderY, 0, wxALL, 5);
	YTrSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Tr:"));
	YTrSizer->Add(m_sliderTrY, 0, wxALL, 5);
	YSizer->Add(YRotSizer, wxSizerFlags().CenterHorizontal());
	YSizer->Add(YTrSizer, wxSizerFlags().CenterHorizontal());
	controlSizer->Add(YSizer, wxSizerFlags().CenterVertical());

	ZSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Z:"));
	ZRotSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Rot:"));
	ZRotSizer->Add(m_sliderZ, 0, wxALL, 5);
	ZTrSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Tr:"));
	ZTrSizer->Add(m_sliderTrZ, 0, wxALL, 5);
	ZSizer->Add(ZRotSizer, wxSizerFlags().CenterHorizontal());
	ZSizer->Add(ZTrSizer, wxSizerFlags().CenterHorizontal());
	controlSizer->Add(ZSizer, wxSizerFlags().CenterVertical());

	ThSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Th:"));
	ThSizer->Add(m_thicknessSlider, 0, wxALL, 5);
	FovSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Fov:"));
	FovSizer->Add(m_fovSlider, 0, wxALL, 5);
	EyesSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Eyes:"));
	EyesSizer->Add(m_eyesSlider, 0, wxALL, 5);
	OtherSizer->Add(ThSizer, wxSizerFlags().CenterHorizontal());
	OtherSizer->Add(FovSizer, wxSizerFlags().CenterHorizontal());
	OtherSizer->Add(EyesSizer, wxSizerFlags().CenterHorizontal());
	controlSizer->Add(OtherSizer, wxSizerFlags().CenterVertical());


	controlSizer->AddSpacer(2);

	colorButtonSizer->Add(m_leftColorButton);
	colorButtonSizer->AddSpacer(5);
	colorButtonSizer->Add(m_rightColorButton);
	colorButtonSizer->AddSpacer(5);
	colorButtonSizer->Add(m_defaultBtn);
	controlSizer->Add(colorButtonSizer, wxSizerFlags().CenterVertical());

	controlSizer->AddSpacer(2);

	otherButtonSizer->Add(m_selectFileBtn);
	otherButtonSizer->AddSpacer(5);
	otherButtonSizer->Add(m_saveButton);
	otherButtonSizer->AddSpacer(5);
	//otherButtonSizer->Add(m_animateBtn);
	controlSizer->Add(otherButtonSizer, wxSizerFlags().CenterVertical());

	controlPanel->SetSizer(controlSizer);
	controlPanel->SetMinSize(wxSize(-1, 130));

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(m_canvas, 1, wxEXPAND);
	mainSizer->Add(controlPanel, 0, wxEXPAND);
	
	m_canvas->SetMinSize(wxSize(800, 600));
	
	this->SetSizer(mainSizer);
	this->Layout();
}


void MainFrame::bindEvents() {
	m_sliderX->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChanged, this);
	m_sliderY->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChanged, this);
	m_sliderZ->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChanged, this);
	m_sliderTrX->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChanged, this);
	m_sliderTrY->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChanged, this);
	m_sliderTrZ->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChanged, this);
	m_thicknessSlider->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChanged, this);
	m_fovSlider->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChanged, this);
	m_eyesSlider->Bind(wxEVT_SLIDER, &MainFrame::OnSliderChanged, this);
	m_selectFileBtn->Bind(wxEVT_BUTTON, &MainFrame::OnOpenClick, this);
	m_leftColorButton->Bind(wxEVT_BUTTON, &MainFrame::OnLeftColor, this);
	m_rightColorButton->Bind(wxEVT_BUTTON, &MainFrame::OnRightColor, this);
	m_saveButton->Bind(wxEVT_BUTTON, &MainFrame::OnSave, this);
	//m_animateBtn->Bind(wxEVT_BUTTON, &MainFrame::OnAnimate, this);
	m_defaultBtn->Bind(wxEVT_BUTTON, &MainFrame::OnDefault, this);
}


void MainFrame::OnSave(wxCommandEvent& evt) {
	wxFileDialog saveFileDialog(this, _("Zapisz obraz"), "", "",
		"Pliki PNG (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_CANCEL) return;

	wxString wxpath = saveFileDialog.GetPath();
	std::string path = std::string(wxpath.mb_str());

	if (!m_canvas->SaveToFile(path, 800, 600)) {
		wxMessageBox("Nie uda³o  siê zapisaæ obrazu", "B³¹d", wxOK | wxICON_ERROR, this);
	}
}


void MainFrame::OnOpenClick(wxCommandEvent& evt) {
	wxFileDialog openFileDialog(
		this,
		"Wybierz plik",
		"",
		"",
		"Pliki txt (*.txt)|*.txt",
		wxFD_OPEN | wxFD_FILE_MUST_EXIST
	);

	if (openFileDialog.ShowModal() == wxID_OK)
	{
		wxString filePath = openFileDialog.GetPath();
		this->obj->getData(std::string(filePath.mb_str()), this);
	}

	
}

void MainFrame::OnLeftColor(wxCommandEvent& evt)
{
	wxColourData data;
	data.SetColour(colLeft);
	wxColourDialog dialog(this, &data);

	if (dialog.ShowModal() == wxID_OK)
	{
		wxColourData retData = dialog.GetColourData();
		colLeft = retData.GetColour();
		m_canvas->updateColors(colLeft, colRight);
	}
}

void MainFrame::OnRightColor(wxCommandEvent& evt)
{
	wxColourData data;
	data.SetColour(colRight);
	wxColourDialog dialog(this, &data);

	if (dialog.ShowModal() == wxID_OK)
	{
		wxColourData retData = dialog.GetColourData();
		colRight = retData.GetColour();
		m_canvas->updateColors(colLeft, colRight);
	}
}



void MainFrame::OnExit(wxCloseEvent& evt)
{
	evt.Skip();
}

//void MainFrame::OnAnimate(wxCommandEvent& evt) {
//	m_canvas->setAnimate(!m_canvas->getAnimate());
//}

void MainFrame::OnDefault(wxCommandEvent&)
{
	m_sliderX->SetValue(0);
	m_sliderTrX->SetValue(0);
	m_sliderY->SetValue(0);
	m_sliderTrY->SetValue(0);
	m_sliderZ->SetValue(0);
	m_sliderTrZ->SetValue(120);

	m_thicknessSlider->SetValue(2);
	m_fovSlider->SetValue(26);
	m_eyesSlider->SetValue(15);

	m_canvas->setRotation(0.0f, 0.0f, 0.0f);
	m_canvas->setTranslation(0.0f, 0.0f, 120.0f);
	m_canvas->setThickness(2.0f);
	m_canvas->setProjParams(450.0f, 0.15f);

}

void MainFrame::OnSliderChanged(wxCommandEvent& evt) {
	float x = (float)m_sliderX->GetValue();
	float y = (float)m_sliderY->GetValue();
	float z = (float)m_sliderZ->GetValue();

	float trX = (float)m_sliderTrX->GetValue();
	float trY = (float)m_sliderTrY->GetValue();
	float trZ = (float)m_sliderTrZ->GetValue();

	float th = (float)m_thicknessSlider->GetValue();
	float fov = 10000.0f / (float)m_fovSlider->GetValue();
	float eyeWidth = (float)m_eyesSlider->GetValue();
	eyeWidth = eyeWidth / 100.0f;

	m_canvas->setRotation(x, y, z);
	m_canvas->setTranslation(trX, trY, trZ);
	m_canvas->setThickness(th);
	m_canvas->setProjParams(fov, eyeWidth);
}