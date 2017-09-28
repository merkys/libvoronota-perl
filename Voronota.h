/* Voronota.h */

#include <vector>

class Contact {
public:
    std::size_t first;
    std::size_t second;
    double area;
};

class Vertice {
public:
    std::size_t first;
    std::size_t second;
    std::size_t third;
    std::size_t fourth;
    double x;
    double y;
    double z;
    double r;
};

std::vector<Contact> calculate_contacts( const std::vector<double> &s );
std::vector<Vertice> calculate_vertices( const std::vector<double> &s );
