#include "image.h"

void Image::flipleft(){
	
	RGBAPixel *temp = new RGBAPixel;
	
	for(size_t i = 0; i < (this -> width()/2); i++){
		for (size_t j = 0; j < (this -> height()); j++){
		
			RGBAPixel *left = (*this)(i , j);
			RGBAPixel *right = (*this)(width() - i - 1, j);
			*temp = *left;
			*left = *right;
			*right = *temp;
			
		}
	}
	delete temp;
}


void Image::adjustbrightness(int r, int g, int b){

	for(size_t i = 0; i < (this -> width()); i++){
		for (size_t j = 0; j < (this -> height()); j++){
			RGBAPixel *temp = (*this)(i, j);
			
			if(temp -> red+r < 0)
				temp -> red = 0;
			else if(temp -> red+r > 255)
				temp -> red = 255;
			else temp -> red += r;
			
			if(temp -> green+g < 0)
				temp -> green = 0;
			else if(temp -> green+g > 255)
				temp -> green = 255;
			else temp -> green += g;
			
			if(temp -> blue+b < 0)
				temp -> blue = 0;
			else if(temp -> blue+b > 255)
				temp -> blue = 255;
			else temp -> blue += b;
			
		}
	}
}

void Image::invertcolors(){
	
	for(size_t i = 0; i < (this -> width()); i++){
		for (size_t j = 0; j < (this -> height()); j++){
			RGBAPixel *pixel = (*this)(i, j);
			
			pixel -> red = 255 - pixel -> red;
            pixel -> green = 255 - pixel -> green;
            pixel -> blue = 255 - pixel -> blue;
        }
    }
    
}
	
