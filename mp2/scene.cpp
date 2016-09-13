#include <iostream>
#include <string>
#include "scene.h"
using namespace std;

Scene::Scene(int max){
	
	//dynamically allocating an array of Image pointers of size "max"
	sceneImage = new Image*[max];
	
	//initializing all of them to NULL
	for(int i = 0; i < max; i++)
		sceneImage[i] = NULL;
	
	//storing "max" as a member variable
	maxIndex = max;
	
	//creating storage for the coordinates
	x = new int[max];
	y = new int[max];
	for(int i = 0; i < max; i++){
		x[i] = 0;
		y[i] = 0;
	}
	
}

Scene::~Scene(){
	
	//Frees all space that was dynamically allocated by this Scene.
	for(int i = 0; i < maxIndex; i++){
		if(sceneImage[i] != NULL){
			delete sceneImage[i];
			sceneImage[i] = NULL;
		}
	}
	if(x != NULL) delete[] x;
	if(y != NULL) delete[] y;
	delete[] sceneImage;
	
}

Scene::Scene(const Scene& source){
	
	//The copy constructor makes this Scene an independent copy of the source.
	maxIndex = source.maxIndex;
	sceneImage = new Image* [maxIndex];
	
	for(int i = 0; i < maxIndex; i++)
		sceneImage[i] = NULL;
	
	x = new int[maxIndex];
	y = new int[maxIndex];
	
	for(int i = 0; i < maxIndex; i++){
		x[i] = 0;
		y[i] = 0;
	}
	
	for(int i = 0; i < maxIndex; i++){
		if(source.sceneImage[i] != NULL){
			sceneImage[i] = new Image(*(source.sceneImage[i]));
			x[i] = source.x[i];
			y[i] = source.y[i];
		}else{
			sceneImage[i] = NULL;
		}
	}
}

const Scene& Scene::operator = (const Scene& source){

	//checks for self assignment
	if((sceneImage == source.sceneImage) && (x == source.x) && (y == source.y))
		return (*this);
	
	else{
	
		//deletes everything this Scene has allocated
		for(int i=0; i<maxIndex; i++){
			if(sceneImage[i] != NULL){
				delete sceneImage[i];
				sceneImage[i] = NULL;
			}
		}
		delete[] sceneImage;
		delete[] x;
		delete[] y;
		
		//makes this Scene an independent copy of the source
		maxIndex = source.maxIndex;
		sceneImage = new Image*[maxIndex];
		x = new int[maxIndex];
		y = new int[maxIndex];
		
		for(int i = 0; i < maxIndex; i++){
			x[i] = 0;
			y[i] = 0;
		}
		for(int i = 0; i < maxIndex; i++){
            if(source.sceneImage[i] != NULL){
                sceneImage[i] = new Image(*(source.sceneImage[i]));
				x[i] = source.x[i];
				y[i] = source.y[i];
            }else{
                sceneImage[i] = NULL;
            }
		}
		//returns a reference to the current instance
		return (*this);
	}
}

void Scene::changemaxlayers(int newmax){
	
	//Modifies the size of the array of Image pointers without changing their indices.
	if(newmax < maxIndex){
	//cannot be done because there are non-null pointers outside the range
		for(int i = newmax; i < maxIndex; i++){
			if(sceneImage[i] != NULL){
				cout << "invalid newmax" << endl;
				return;
			}
		}
	}
	
	Image** tempMaxArray = new Image*[newmax];
	int* xi = new int[newmax];
	int* yi = new int[newmax];
	
	//the pointers within the original range
	for(int i=0; i < maxIndex; i++){
		tempMaxArray[i] = sceneImage[i];
		xi[i] = x[i];
		yi[i] = y[i];
	}
	
	//the new range of pointers will be 0
	for(int i = maxIndex; i < newmax; i++){
		tempMaxArray[i] = NULL;
		xi[i] = 0;
		yi[i] = 0;
	}
	delete[] sceneImage;
	delete[] x;
	delete[] y;
	
	sceneImage = tempMaxArray;
	x = xi;
	y = yi;
	maxIndex = newmax;
	
}

void Scene::addpicture(const char* FileName, int index, int x, int y){
	//add a picture to the scene
	
	//If the index is not within the range
	if((index < 0) || (index >= maxIndex)){
		cout << "index out of bounds" << endl;
		return;
	}
	
	//If there is already an Image in cell location index it should be replaced by the new Image.
	if(sceneImage[index] != NULL){
		delete sceneImage[index];
	}
	
	//Place it in the array cell corresponding to the given index, and store its x coordinate and y coordinate.
	sceneImage[index] = new Image;
	(*sceneImage[index]).readFromFile(FileName);
	(*this).x[index] = x;
	(*this).y[index] = y;
	return;
	
}

void Scene::changelayer(int index, int newindex){
	//Moves an Image from one layer to another.
	
	//If either index is invalid
	if((index < 0) || (index > maxIndex - 1) || (newindex < 0) || (newindex > maxIndex - 1)){
		cout << "invalid index" << endl;
		return;
	}
	
	//If the new index is the same as the old index, do nothing and return.
	if(index == newindex){
		return;
	}
	
	//If the destination is already occupied, delete the image there.
	if(sceneImage[newindex] != NULL)
		delete sceneImage[newindex];
	
	//Move!
	sceneImage[newindex] = sceneImage[index];
	sceneImage[index] = NULL;
	x[newindex] = x[index];
	x[index] = 0;
	y[newindex] = y[index];
	y[index] = 0;
	return;
}


void Scene::translate(int index, int xcoord, int ycoord){
	//Changes the x and y coordinates of the Image in the specified layer.

	//If the index is invalid or if it contains a NULL pointer
	if((index < 0) || (index > maxIndex - 1) || (sceneImage[index] == NULL)){
		cout << "invalid index" << endl;
		return;
	}
	
	(*this).x[index] = xcoord;
	(*this).y[index] = ycoord;
	return;
}


void Scene::deletepicture(int index){
	//Deletes the Image at the given index.
	
	//If the index is invalid or if it contains a NULL pointer
	if((index < 0) || (index > maxIndex - 1) || (sceneImage[index] == NULL)){
		cout << "invalid index" << endl;
		return;
	}
	delete sceneImage[index];
	sceneImage[index] = NULL;

}

Image* Scene::getpicture(int index) const{
	//return a pointer to the Image at the specified index, not a copy of it.

	//If the index is invalid
	if((index < 0) || (index > maxIndex - 1)){
		cout << "invalid index" << endl;
		return NULL;
	}
	return sceneImage[index];
	
}


Image Scene::drawscene() const{
	//Draws the whole scene on one Image and returns that Image by value.
	
	int width = 0;
	int height = 0;
	
	//First determine the minimum width and height necessary to ensure that 
	//none of the images go off of the bottom or the right edge of the returned image
	for(int i = 0; i < maxIndex; i++){
		if(sceneImage[i] != NULL){
			int width1 = (*sceneImage[i]).width() + x[i];
			if(width1 > width) width = width1;
			int height1 = (*sceneImage[i]).height() + y[i];
			if(height1 > height) height = height1;
		}
	}

	Image result;
	result.resize(width, height);
	for(int a = 0; a < maxIndex; a++){
		if(sceneImage[a] != NULL){
			for(int i = 0; i < int((*sceneImage[a]).width()); i++){
				for(int j = 0; j < int((*sceneImage[a]).height()); j++){
					result(i + x[a], j+y[a])->red = (*sceneImage[a])(i, j)->red;
					result(i + x[a], j+y[a])->green = (*sceneImage[a])(i, j)->green;
					result(i + x[a], j+y[a])->blue = (*sceneImage[a])(i, j)->blue;
				}
			}
		}
	}
	return result;
}































