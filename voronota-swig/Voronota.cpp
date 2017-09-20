//
//  Voronota.cpp
//
#include <vector>
#include <string>

#include "apollota/constrained_contacts_construction.h"
#include "apollota/constrained_contacts_utilities.h"
#include "apollota/spheres_boundary_construction.h"
#include "apollota/spherical_contacts_construction.h"

std::vector<apollota::SimpleSphere> make_spheres( const std::vector<double> &s ) {

    const double probe = 1.4;
    const bool exclude_hidden_balls = true;
    const std::string volumes_output = "";

    std::vector<apollota::SimpleSphere> spheres;
    for( unsigned long i = 0; i < s.size() / 4; i++ ) {
        spheres.push_back( apollota::SimpleSphere( s[i*4], s[i*4+1], s[i*4+2], s[i*4+3] ) );
    }

	const std::size_t input_spheres_count=spheres.size();
	const std::vector<apollota::SimpleSphere> artificial_boundary=apollota::construct_artificial_boundary(spheres, probe*2.0);
	spheres.insert(spheres.end(), artificial_boundary.begin(), artificial_boundary.end());

	const apollota::Triangulation::Result triangulation_result=apollota::Triangulation::construct_result(spheres, 3.5, exclude_hidden_balls, false);
	const apollota::Triangulation::VerticesVector vertices_vector=apollota::Triangulation::collect_vertices_vector_from_quadruples_map(triangulation_result.quadruples_map);

	std::map<apollota::Pair, double> interactions_map;
	std::pair< bool, std::map<std::size_t, double> > volumes_map_bundle(!volumes_output.empty(), std::map<std::size_t, double>());

    return spheres;
}
