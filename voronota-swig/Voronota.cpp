//
//  Voronota.cpp
//
#include <vector>
#include <apollota/basic_operations_on_spheres.h>

std::vector<apollota::SimpleSphere> make_spheres( const std::vector<double> &s ) {
    std::vector<apollota::SimpleSphere> spheres;
    for( unsigned long i = 0; i < s.size() / 4; i++ ) {
        spheres.push_back( apollota::SimpleSphere( s[i*4], s[i*4+1], s[i*4+2], s[i*4+3] ) );
    }
    return spheres;
}
