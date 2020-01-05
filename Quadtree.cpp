#include"QuadTree.h"

//============================================================================
//===============================POINTS ======================================
Point::Point(float x, float y) {

	this->x = x;
	this->y = y;
}

float Point::GetX() {
	return this->x;
}
float Point::GetY() {
	return this->y;
}
//==============================================================================
//===========================RECTANGLE==========================================

Rectangle::Rectangle(float x, float y, float w, float h) {	
	this->x = new float;
	*this->x = x;
	this->y = new float;
	*this->y = y;
	this->w = new float;
	*this->w = w;
	this->h = new float;
	*this->h = h;
}


Rectangle::~Rectangle() {

}

float Rectangle::GetX() {

	return *this->x;
}
float Rectangle::GetY() {
	return *this->y;
}
float Rectangle::GetW() {
	return *this->w;
}
float Rectangle::GetH() {
	return *this->h;
}

bool Rectangle::contains(Point p) {

	float x = this->GetX();
	float y = this->GetY();
	float w = this->GetW();
	float h = this->GetH();

	if (    p.GetX()   >   x  &&
		    p.GetX()   <   x+w&&
		    p.GetY()   >   y  &&
		    p.GetY()   <   y+h) {
		return true;
	}
	return false;
}
//==============================================================================
//===========================QUADTREE==========================================

QuadTree::QuadTree(Rectangle rec, int capacity ,const char* name ) {
	this->rec = new Rectangle();
	*this->rec = rec;
	this->capacity = capacity;
	this->nbPoints =  new int ;
	*this->nbPoints = 0;
	this->divided = new bool;
	*this->divided = false;
	this->name = name;
}
QuadTree::~QuadTree() {
	
	delete this->nbPoints;
	delete this->divided;

	delete this->ne;
	delete this->se;
	delete this->nw;
	delete this->sw;

	delete this->rec;
	
	
}

void QuadTree::SubDivide() {
	if (*this->nbPoints < this->capacity) {		
		//std::cout << "added" << std::endl;
		return;
	}
	else {
		//std::cout << "dividing "<< this->name<< std::endl;
		float x = this->rec->GetX();
		float y = this->rec->GetY();
		float w = this->rec->GetW();
		float h = this->rec->GetH();
		
		Rectangle northwest(x , y ,w/2 ,h/2);
		nw = new QuadTree(northwest, this->capacity,"nw");
		Rectangle northeast(x+w/2 , y , w / 2, h / 2);
		ne = new QuadTree(northeast, this->capacity,"ne");
		Rectangle southwest(x , y+h/2, w / 2, h / 2);
		sw = new QuadTree(southwest, this->capacity,"sw");
		Rectangle southeast(x+w/2,y+h/2, w / 2, h / 2);
		se = new QuadTree(southeast, this->capacity,"se");
		*this->divided = true;
	}
}

void QuadTree::Insert(Point p ) {
	if (!this->rec->contains(p)) {
		return;
	}
	if (*this->nbPoints < this->capacity) {
		this->points[*this->nbPoints] = p;
		*(this->nbPoints) = *(this->nbPoints) + 1;
		
	}
	else {
		if (!*this->divided)
		{
			this->SubDivide();
		}
		this->ne->Insert(p);
		this->nw->Insert(p);
		this->se->Insert(p);
		this->sw->Insert(p);
	}
}

void QuadTree::Insert(Point p,std::string __VERSION) {
	if (!this->rec->contains(p)) {
		return;
	}
	if (*this->nbPoints < this->capacity) {
		this->points[*this->nbPoints] = p;
		*(this->nbPoints) = *(this->nbPoints) + 1;
		std::cout << "inserted" << std::endl;
	}
	else {
		if (!*this->divided)
		{
			this->SubDivide();
		}
		this->ne->Insert(p);
		this->nw->Insert(p);
		this->se->Insert(p);
		this->sw->Insert(p);
	}
}

void QuadTree::search( Point search[10] , Point P) {
	if (!(*this->rec).contains(P)) {
		return; 
	}

	if (*this->divided) {
		ne->search(search, P);
		nw->search(search, P);
		se->search(search, P);
		sw->search(search, P);
	}
	else {
		for (int i = 0; i < 10; i++)
		{
			search[i] = this->points[i];
		}
	}
}


void QuadTree::draw(SDL_Window* win, SDL_Renderer* ren) {
	


	SDL_Rect rectangle = {  (int)this->rec->GetX(),
							(int)this->rec->GetY(),
							(int)this->rec->GetW(),
							(int)this->rec->GetH() };;
	
	
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderDrawRect(ren,&rectangle);

	for (int i = 0; i < 10; i++)
	{
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderDrawPoint(ren, this->points[i].GetX(), this->points[i].GetY());
	}

	if (*this->divided) {
		ne->draw(win, ren);
		nw->draw(win, ren);
		se->draw(win, ren);
		sw->draw(win, ren);
	}



}