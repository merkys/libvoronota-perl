/* Voronota.h */

#include <vector>

class Contact {
public:
    std::size_t first;
    std::size_t second;
    double area;
};

std::vector<Contact> calculate_contacts( const std::vector<double> &s );
