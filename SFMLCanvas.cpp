#include "SFMLCanvas.h"


SFMLCanvas::SFMLCanvas(wxWindow* parent, Object3D* obj, wxSlider* sliderX, wxSlider* sliderY)
	: wxPanel(parent), obj(obj), sliderX(sliderX), sliderY(sliderY)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	Bind(wxEVT_PAINT, &SFMLCanvas::OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &SFMLCanvas::OnMouseDown, this);
	Bind(wxEVT_MOTION, &SFMLCanvas::OnMouseMove, this);
	Bind(wxEVT_LEFT_UP, &SFMLCanvas::OnMouseUp, this);
	Bind(wxEVT_SIZE, &SFMLCanvas::OnResize, this);


	timer = new wxTimer(this);
	Bind(wxEVT_TIMER, &SFMLCanvas::OnTimer, this);
	timer->Start(16);

	m_cacheSize = GetClientSize();

	InitSFML();
}

SFMLCanvas::~SFMLCanvas()
{
	if (sfWindow)
		delete sfWindow;
	if (timer) {
		timer->Stop();
		delete timer;
		timer = nullptr;
	}
}


void SFMLCanvas::setRotation(int x, int y, int z) {
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
}

void SFMLCanvas::setTranslation(float x, float y, float z)
{
	m_translationX = x;
	m_translationY = y;
	m_translationZ = z;
}

void SFMLCanvas::setThickness(float t)
{
	this->thickness = t;
}

void SFMLCanvas::setProjParams(float fov, float eyeWidth)
{
	this->fov = fov;
	this->eyeWidth = eyeWidth;
}

void SFMLCanvas::updateColors(wxColour colLeft, wxColour colRight)
{
	this->colLeft.r = colLeft.Red();
	this->colLeft.g = colLeft.Green();
	this->colLeft.b = colLeft.Blue();

	this->colRight.r = colRight.Red();
	this->colRight.g = colRight.Green();
	this->colRight.b = colRight.Blue();
}
/*
void SFMLCanvas::setAnimate(bool isAnimated)
{
	this->isAnimated = isAnimated;
}

bool SFMLCanvas::getAnimate() {
	return isAnimated;
}
*/


void SFMLCanvas::InitSFML()
{
	if (sfWindow) return;

	sf::WindowHandle handle = reinterpret_cast<sf::WindowHandle>(GetHandle());
	sfWindow = new sf::RenderWindow(handle);

	wxSize size = GetClientSize();
	if (size.x > 0 && size.y > 0) {
		sf::View view(sf::FloatRect({ 0.f, 0.f }, { static_cast<float>(size.x), static_cast<float>(size.y) }));
		sfWindow->setView(view);
	}

	std::ignore = sfWindow->setActive(true);

}




void SFMLCanvas::OnResize(wxSizeEvent& evt) {
	m_cacheSize = GetClientSize();

	if (sfWindow && m_cacheSize.x > 0 && m_cacheSize.y > 0) {
		sfWindow->setSize(sf::Vector2u(m_cacheSize.x, m_cacheSize.y));


		sf::View view(sf::FloatRect({ 0.f, 0.f }, { static_cast<float>(m_cacheSize.x), static_cast<float>(m_cacheSize.y) }));
		sfWindow->setView(view);
	}

	Refresh(false);
	evt.Skip();
}


void SFMLCanvas::OnTimer(wxTimerEvent&)
{
	Refresh(false);
}


void SFMLCanvas::OnMouseDown(wxMouseEvent& event)
{
	m_dragging = true;
	m_lastMousePos = event.GetPosition();
}


void SFMLCanvas::OnMouseUp(wxMouseEvent&)
{
	m_dragging = false;
}


void SFMLCanvas::OnMouseMove(wxMouseEvent& event)
{
	if (m_dragging && event.Dragging())
	{
		//przesuwanie myszk¹ pozwala na obrót tylko w osi X i Y
		wxPoint pos = event.GetPosition();
		wxPoint delta = pos - m_lastMousePos;

		m_rotationY -= delta.x * 0.5f;
		m_rotationX += delta.y * 0.5f;

		if (m_rotationX > 90) m_rotationX = 90;
		if (m_rotationX < -90) m_rotationX = -90;


		if (m_rotationY > 360) m_rotationY = 360;
		if (m_rotationY < 0) m_rotationY = 0;

		m_lastMousePos = pos;

		//aktualizacja obrotu na sliderach
		sliderX->SetValue(m_rotationX);
		sliderY->SetValue(m_rotationY);
	}
}

void SFMLCanvas::OnPaint(wxPaintEvent&)
{
	wxPaintDC dc(this);
	if (!IsShown()) return;

	if(!sfWindow)
		InitSFML();

	std::ignore = sfWindow->setActive(true);
	sfWindow->clear(sf::Color(0, 0, 0));
	DrawLine3D(thickness);
	sfWindow->display();
}


void SFMLCanvas::DrawIntoRenderTarget(sf::RenderTarget& target, unsigned int width, unsigned int height, float thickness)
{
	Matrix rotX, rotY, rotZ;

	rotX.setRotX(m_rotationX / 180.0 * M_PI);
	rotY.setRotY(m_rotationY / 180.0 * M_PI);
	rotZ.setRotZ(m_rotationZ / 180.0 * M_PI);
	Matrix TrMatrix;
	TrMatrix.setTranslate(m_translationX, m_translationY, m_translationZ);

	Matrix rotationMatrix = rotX * rotY * rotZ;

	float fwidth = static_cast<float>(width);
	float fheight = static_cast<float>(height);


	for (int side = 0; side < 2; side++) {
		Matrix TrEye;
		sf::Color curr;
		Matrix localTrMatrix = TrMatrix;

		if (side == 0) {//lewe oko - przesuwam obraz o polowe rozstawu w prawo
			TrEye.setTranslate(0.5 * eyeWidth * 100, 0.0, 0.0);
			localTrMatrix = TrEye * localTrMatrix;//skladam przeksztalcenia
			curr = colLeft;
		}
		else if (side == 1) {//prawe oko
			TrEye.setTranslate(-0.5 * eyeWidth * 100, 0.0, 0.0);
			localTrMatrix = TrEye * localTrMatrix;
			curr = colRight;
		}


		for (size_t i = 0; i + 1 < obj->edgeing.size(); i += 2) {

			sf::Vector2f p1 = (localTrMatrix * rotationMatrix * (obj->edgeing[i])).project(fwidth, fheight, fov, 100);
			sf::Vector2f p2 = (localTrMatrix * rotationMatrix * (obj->edgeing[i + 1])).project(fwidth, fheight, fov, 100);



			sf::Vector2f dir = p2 - p1;
			float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

			if (len > 0)
			{
				sf::RectangleShape line(sf::Vector2f(len, thickness));
				line.setPosition(p1);
				line.setFillColor(curr);

				// SFML 3.0 uses sf::degrees(); older SFML accepts float degrees too
				float angle = std::atan2(dir.y, dir.x) * 180.0f / M_PI;
				line.setRotation(sf::degrees(angle));
				target.draw(line);
			}
		}
	}
}



bool SFMLCanvas::SaveToFile(const std::string& path, unsigned int width, unsigned int height)
{
	sf::RenderTexture renderTex(sf::Vector2u{width, height});
	renderTex.clear(sf::Color(0, 0, 0, 255));

	sf::View view(sf::FloatRect({ 0.f, 0.f }, { static_cast<float>(width), static_cast<float>(height) }));
	renderTex.setView(view);

	DrawIntoRenderTarget(renderTex, width, height, thickness);
	renderTex.display();
	sf::Image img = renderTex.getTexture().copyToImage();
	return img.saveToFile(path);
}

void SFMLCanvas::DrawLine3D(float thickness)
{
	Matrix rotX, rotY, rotZ;

	rotX.setRotX(m_rotationX / 180.0 * M_PI);
	rotY.setRotY(m_rotationY / 180.0 * M_PI);
	rotZ.setRotZ(m_rotationZ / 180.0 * M_PI);
	Matrix TrMatrix;
	TrMatrix.setTranslate(m_translationX, m_translationY, m_translationZ);


	Matrix rotationMatrix = rotX * rotY * rotZ;

	float width = static_cast<float>(m_cacheSize.x);
	float height = static_cast<float>(m_cacheSize.y);


	for (int side = 0; side < 2; side++) {
		Matrix TrEye;
		sf::Color curr;
		if (side == 0) {
			TrEye.setTranslate(0.5 * eyeWidth * 100, 0.0, 0.0);
			TrMatrix = TrEye * TrMatrix;
			curr = colLeft;
		}
		else if (side == 1) {
			TrEye.setTranslate(-0.5 * eyeWidth * 100, 0.0, 0.0);
			TrMatrix = TrEye * TrMatrix;
			curr = colRight;
		}


		for (size_t i = 0; i + 1 < obj->edgeing.size(); i += 2) {

			sf::Vector2f p1 = (TrMatrix * rotationMatrix * (obj->edgeing[i])).project(width, height, fov, 100);
			sf::Vector2f p2 = (TrMatrix * rotationMatrix * (obj->edgeing[i + 1])).project(width, height, fov, 100);



			sf::Vector2f dir = p2 - p1;
			float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

			if (len > 0)
			{
				sf::RectangleShape line(sf::Vector2f(len, thickness));
				line.setPosition(p1);
				line.setFillColor(curr);

				float angle = std::atan2(dir.y, dir.x) * 180.0f / M_PI;
				line.setRotation(sf::degrees(angle));

				sfWindow->draw(line);
			}
		}
	}
}