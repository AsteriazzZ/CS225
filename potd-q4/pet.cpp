#include "pet.h"

// Put your constructor code here!

void Pet::pet(){
	name = "Rover";
	birth_year = 2016;
	type = "dog";
	owner_name = "Cinda";
}

void Pet::setPet(std::string Name, int BY, std::string Type, std::string OName){
	name = Name;
	birth_year = BY;
	type = Type;
	owner_name = OName;
}

void Pet::setName(std::string newName) {
  name = newName;
}

void Pet::setBY(int newBY) {
  birth_year = newBY;
}

void Pet::setType(std::string newType) {
  type = newType;
}

void Pet::setOwnerName(std::string newName) {
  owner_name = newName;
}

std::string Pet::getName() {
  return name;
}

int Pet::getBY() {
  return birth_year;
}

std::string Pet::getType() {
  return type;
}

std::string Pet::getOwnerName() {
  return owner_name;
}
