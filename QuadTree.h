/*THIS IS A SORTING ALGORITHM THAT PREVENTS FROM EXESSIVE MEMORY
ACCESS

I BELIEVE 
*/

#pragma once
#include<SDL.h>
#include<iostream>

//=========================POINTS ============================================
//============================================================================

struct Point {
private:
	
	float x, y;
public:
	//CONSTRUCTOR  default is 0 everywhere
	Point(float X = 0, float Y = 0);

	float GetX();
	float GetY();

};

//==============================================================================
//==============================================================================
//==============================================================================
//===========================RECTANGLE==========================================
//==============================================================================
//==============================================================================
//==============================================================================


class Rectangle {
private: 
	
	
	float x, y;
	float w, h;


public:


	//CONSTRUCTOR  default is  everywhere
	Rectangle(float X = 0, float Y = 0, float W = 0, float H = 0);
	~Rectangle();
	bool contains(Point p);

	float GetX();
	float GetY();
	float GetW();
	float GetH();

};





//==============================================================================
//==============================================================================
//==============================================================================
//===========================QUADTREE==========================================
//==============================================================================
//==============================================================================
//==============================================================================

class QuadTree {
private:
	int* nbPoints;
	Rectangle* rec;
	bool* divided;
	QuadTree* nw = NULL;
	QuadTree* ne = NULL;
	QuadTree* sw = NULL;
	QuadTree* se = NULL;
	const char* name;

	
	
	
	int capacity;
	Point points[10];
public:
	//CONSTRUCTOR  
	QuadTree(Rectangle rec,int capacity = 2, const char* name = "origin");
	~QuadTree();

	
	void SubDivide();
	void Insert(Point p);
	void Insert(Point p,std::string __VERION);
	void search(Point search[10] ,Point p);
	void draw(SDL_Window* win , SDL_Renderer* ren);

};