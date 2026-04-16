#ifndef CITY_H
#define CITY_H

#include <string>
#include <iostream>

class City {
private:
    std::string city;
    std::string country;
    long population;
    double latitude;

public:
    //constructors...
    City();
    City(std::string city, std::string country, long population, double latitude);

    //getters...
    std::string getCity() const;
    std::string getCountry() const;
    long getPopulation() const;
    double getLatitude() const;

    //operator overload...
    friend std::ostream& operator<<(std::ostream& os, const City& c);
};

#endif