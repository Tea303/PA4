#include "City.h"

City::City() : city(""), country(""), population(0), latitude(0.0) {}

City::City(std::string city, std::string country, long population, double latitude)
    : city(city), country(country), population(population), latitude(latitude) {}

// Accessors,..
std::string City::getCity() const { return city; }
std::string City::getCountry() const { return country; }
long City::getPopulation() const { return population; }
double City::getLatitude() const { return latitude; } 

std::ostream& operator<<(std::ostream& os, const City& c) {
    os << c.city << ", " << c.country << ", " << c.population << ", " << c.latitude;
    return os;
}