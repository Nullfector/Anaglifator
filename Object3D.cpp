#include <wx/wx.h>
#include "Object3D.hpp"

TrenaryNode::TrenaryNode() :parent(nullptr), less(nullptr), equal(nullptr), more(nullptr) {}

TrenaryNode::TrenaryNode(TrenaryNode* p) :parent(p), less(nullptr), equal(nullptr), more(nullptr) {}

TrenaryNode::~TrenaryNode()
{
	if (less != nullptr)
	{
		delete less;
	}
	if (more != nullptr)
	{
		delete more;
	}
	if (equal != nullptr)
	{
		delete equal;
	}
}

void TrenaryNode::calculateCenter(unsigned int& count, Vector4& c)
{
	++count;
	c.setX(c.getX() + this->storedValue.getX()).setY(c.getY() + this->storedValue.getY()).setZ(c.getZ() + this->storedValue.getZ());
	if (this->less != nullptr) this->less->calculateCenter(count, c);
	if (this->more != nullptr) this->more->calculateCenter(count, c);
	if (this->equal != nullptr) this->equal->calculateCenter(count, c);
}

void TrenaryNode::insertData(const Vector4* toInsert)
{
	this->storedValue = *toInsert;
}

void TrenaryNode::weNeedToGoDeeper(short c, const Vector4* toInsert)
{
	//zachciało mi się być wydajnym do cholery
	//to mogło być ładniej napisane, ale jestem leniwy iks de 
	switch (c)
	{
	case 0:
		if (toInsert->getX() < this->storedValue.getX())
		{
			if (this->less != nullptr)
			{
				this->less->weNeedToGoDeeper(c, toInsert);
				return;
			}
			else
			{
				this->less = new TrenaryNode(this);
				this->less->insertData(toInsert);
				return;
			}
		}
		else if (toInsert->getX() > this->storedValue.getX())
		{
			if (this->more != nullptr)
			{
				this->more->weNeedToGoDeeper(c, toInsert);
				return;
			}
			else
			{
				this->more = new TrenaryNode(this);
				this->more->insertData(toInsert);
				return;
			}
		}
		else if (toInsert->getX() == this->storedValue.getX())
		{
			if (this->equal != nullptr)
			{
				this->equal->weNeedToGoDeeper(c + 1, toInsert); //ok
				return;
			}
			else if (this->storedValue.getY() != toInsert->getY() && this->storedValue.getZ() != toInsert->getZ())
			{
				this->equal = new TrenaryNode(this);
				this->equal->insertData(toInsert);
				return;
			}
			else return; //to oznacza że znaleźliśmy identycznego
		}
		break;

	case 1:
		if (toInsert->getY() < this->storedValue.getY())
		{
			if (this->less != nullptr)
			{
				this->less->weNeedToGoDeeper(c, toInsert);
				return;
			}
			else
			{
				this->less = new TrenaryNode(this);
				this->less->insertData(toInsert);
				return;
			}
		}
		else if (toInsert->getY() > this->storedValue.getY())
		{
			if (this->more != nullptr)
			{
				this->more->weNeedToGoDeeper(c, toInsert);
				return;
			}
			else
			{
				this->more = new TrenaryNode(this);
				this->more->insertData(toInsert);
				return;
			}
		}
		else if (toInsert->getY() == this->storedValue.getY())
		{
			if (this->equal != nullptr)
			{
				this->equal->weNeedToGoDeeper(c + 1, toInsert); //ok
				return;
			}
			else if (this->storedValue.getZ() != toInsert->getZ())
			{
				this->equal = new TrenaryNode(this);
				this->equal->insertData(toInsert);
				return;
			}
			else return; //to oznacza że znaleźliśmy identycznego
		}
		break;

	case 2:
		if (toInsert->getZ() < this->storedValue.getZ())
		{
			if (this->less != nullptr)
			{
				this->less->weNeedToGoDeeper(c, toInsert);
				return;
			}
			else
			{
				this->less = new TrenaryNode(this);
				this->less->insertData(toInsert);
				return;
			}
		}
		else if (toInsert->getZ() > this->storedValue.getZ())
		{
			if (this->more != nullptr)
			{
				this->more->weNeedToGoDeeper(c, toInsert);
				return;
			}
			else
			{
				this->more = new TrenaryNode(this);
				this->more->insertData(toInsert);
				return;
			}
		}
		else if (toInsert->getZ() == this->storedValue.getZ())
		{
			return; //no tutaj to już na pewno
		}
		break;
	}
}

TrenaryTree::TrenaryTree() :start(nullptr), counter(0) {}

TrenaryTree::TrenaryTree(TrenaryNode* n) :start(n), counter(0) {}

//tu jeszcze zmienie
TrenaryTree::~TrenaryTree()
{
	/*if (start != nullptr)
	{
		delete start;
	}*/
	this->clear();
}

void TrenaryTree::insertNewNode(const Vector4* v)
{
	short comp = 0; //po x-ach - 1=y, 2=z
	if (this->start == nullptr)
	{
		this->start = new TrenaryNode();
		this->start->insertData(v);
	}
	else this->start->weNeedToGoDeeper(comp, v);
}

void TrenaryTree::getCenter()
{
	this->counter = 0;
	this->center.setX(0.0).setY(0.0).setZ(0.0);
	if (start != nullptr)
	{
		this->start->calculateCenter(this->counter, this->center);
		this->center.setX(this->center.getX() / this->counter).setY(this->center.getY() / this->counter).setZ(this->center.getZ() / this->counter);
	}
}

//nowe funkcje w trenarytree
//bool TrenaryTree::isFilled() { return this->start; }

void TrenaryTree::clear()
{
	if (start != nullptr)
	{
		delete start;
		start = nullptr;
	}
}

Object3D::Object3D() {}

Object3D::~Object3D() {}

bool Object3D::getData(std::string filepath, wxWindow* parent)
{

	std::ifstream File(filepath);
	int edgeNum = 0;
	int curval = 0;
	double values = 0;
	if (!File.is_open())
	{
		wxMessageBox("Nie znleziono pliku 'wsad.txt'", "Błąd", wxOK | wxICON_INFORMATION, parent);
		return false;
	}

	//tutaj zaczyna się moja edycja tego wszystkiego
	if (!this->edgeing.empty())
	{
		this->domb.clear();
		this->edgeing.clear();
	}

	int c = 0;
	while ((curval = File.get()) >= '0' && curval <= '9')
	{
		edgeNum *= 10;
		edgeNum += (curval - '0');
		values++;
		c++;
	}

	if ((edgeNum > 550 || (curval != '\n')) || c == 0) { wxMessageBox("Zła wartość w pierwszej linijce", "Błąd", wxOK | wxICON_INFORMATION, parent); File.close(); return false; }

	//std::string lineContent;
	double rest;
	bool zm;
	bool neg;
	short amm;

	std::array<double, 6> temp;
	Vector4 f, l;
	for (int i = 0; i < edgeNum; i++)
	{
		if (!(File.get() == '1'))
		{
			wxMessageBox("Pierwszy znak ZAWSZE musi być 1", "Błąd", wxOK | wxICON_INFORMATION, parent);
			File.close();
			return false;
		}
		curval = File.get();
		for (int j = 0; j < 6; j++)
		{
			values = 0;
			rest = 0;
			zm = false;
			neg = false;
			amm = 0;
			if (curval != ' ')
			{
				wxMessageBox("błąd w zapisie!", "Błąd", wxOK | wxICON_INFORMATION, parent);
				File.close();
				return false;
			}
			curval = File.get();
			if (curval == '-') { curval = File.get(); neg = true; }
			else if (curval == '+') { curval = File.get(); }

			if (!(curval >= '0' && curval <= '9')) { wxMessageBox("błąd w zapisie!", "Błąd", wxOK | wxICON_INFORMATION, parent); File.close(); return false; }
			while ((curval >= '0' && curval <= '9') || curval == '.')
			{
				if (curval == '.')
				{
					rest = values;
					values = 0.0;
					zm = true;
					curval = File.get();
				}
				else
				{
					if (zm) amm++;
					values *= 10;
					values += (curval - '0');
					curval = File.get();
				}
			}
			if (zm)
			{
				values /= pow(10, amm);
			}
			rest += values;
			if (neg) rest *= -1;
			//std::cout << rest << " ";
			temp[j] = rest;
		}
		if (curval == '\n' || curval == EOF);
		else while ((curval = File.get()) != '\n' && curval != EOF);
		//std::cout << std::endl;
		f.setX(temp[0]).setY(temp[1]).setZ(temp[2]);
		l.setX(temp[3]).setY(temp[4]).setZ(temp[5]);

		this->edgeing.push_back(f);
		this->domb.insertNewNode(&(this->edgeing.back()));
		this->edgeing.push_back(l);
		this->domb.insertNewNode(&(this->edgeing.back()));
	}
	File.close();
	this->domb.getCenter();
	//NOWE
	this->acknowledgeCenter(&(this->domb.center));
	return true;
}

//nowe w Object3d
void Object3D::acknowledgeCenter(Vector4* cent)
{
	for (Vector4& e : edgeing)
	{
		e.setX(e.getX() - (*cent).getX()).setY(e.getY() - (*cent).getY()).setZ(e.getZ() - (*cent).getZ());
	}
}

