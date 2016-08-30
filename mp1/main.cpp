#include <algorithm>
#include <iostream>

#include "rgbapixel.h"
#include "png.h"

using namespace std;
int main(){
	PNG image("in.png");
	PNG image2("in.png");
	for (size_t yi = 0; yi < image.height(); yi++){
		for (size_t xi = 0; xi < image.width(); xi++){
			image(image.width()-1-xi, image.height()-1-yi) -> green=image2(xi, yi) -> green;
                        image(image.width()-1-xi, image.height()-1-yi) -> red = image2(xi, yi) -> green;
                        image(image.width()-1-xi, image.height()-1-yi) -> blue = image2(xi, yi) -> blue;
		}
	}
image.writeToFile("out.png");
}
