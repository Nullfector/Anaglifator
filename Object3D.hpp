#pragma once
#include "Vector4.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <iostream>

class TrenaryNode //nie przejmujcie się tym :3
{
	TrenaryNode* parent;
	Vector4 storedValue;
	TrenaryNode* less, * equal, * more;
public:
	TrenaryNode();
	TrenaryNode(TrenaryNode* p);
	~TrenaryNode();

	void calculateCenter(unsigned int& count, Vector4& c);
	void insertData(const Vector4* toInsert);
	void weNeedToGoDeeper(short c, const Vector4* toInsert);
};

class TrenaryTree //tym też - zachciało mi się pawić z projektem
{
	//jak u was nie działa to wina wszego komputera - u mnie działa :3
	//iks de jednak nie :3
	TrenaryNode* start;
	unsigned int counter;
public:
	Vector4 center;
	TrenaryTree();
	TrenaryTree(TrenaryNode* n);
	~TrenaryTree();

	void insertNewNode(const Vector4* v); //dodaje nowy obiekt do drzewka
	void getCenter(); //oblicza wektor geometrycznego centrum (tak, nazwa jest lekko myląca, no trudno)

	//bool isFilled(); //sprawdza czy drzewo przechowuje już jakieś dane
	void clear(); //usuwa dane z drzewa (wykorzytywana w destruktorze)
};


class Object3D
{
public:
	TrenaryTree domb; //magiczna struktura trzymająca wszystkie wierzchołki oraz wektor centrum geometrycznego tego kształtu
	std::vector<Vector4> edgeing; //tablica krawędzi: edgeing[i]-początek odcinka, edgeing[i+1]-koniec odcinka
	Object3D();//konstruktor
	~Object3D();//bum bum bam bam

	bool getData(std::string filepath, wxWindow* parent); //wkłada krawędzie do krawędzi, zapełnia domb (czyli również tworzy wektor środka geo)
	
	void acknowledgeCenter(Vector4* cent); //przesuwa dane w edgeing zgodnie z wekotorem centrum
};
