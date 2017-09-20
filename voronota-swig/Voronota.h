/* Voronota.h */

#include <vector>

class Contact {
public:
    std::size_t first;
    std::size_t second;
    double area;
};

std::vector<Contact> make_spheres( const std::vector<double> &s );
