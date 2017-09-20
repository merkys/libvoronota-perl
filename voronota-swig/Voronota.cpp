//
//  Voronota.cpp
//
#include <vector>
#include <string>
#include <iostream>

#include "apollota/constrained_contacts_construction.h"
#include "apollota/constrained_contacts_utilities.h"
#include "apollota/spheres_boundary_construction.h"
#include "apollota/spherical_contacts_construction.h"

std::vector<apollota::SimpleSphere> make_spheres( const std::vector<double> &s ) {

    const double probe = 1.4;
    const bool exclude_hidden_balls = false;
    const std::string volumes_output = "";
    const double step = 0.2;
    const int projections = 5;
	const int sih_depth = 3;
    const bool add_mirrored = false;

    std::vector<apollota::SimpleSphere> spheres;
    std::set<std::size_t> mock_solvent_ids;
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

	{
		const std::map<apollota::Pair, double> constrained_contacts=apollota::ConstrainedContactsConstruction::construct_contacts(spheres, vertices_vector, probe, step, projections, mock_solvent_ids, volumes_map_bundle);
		for(std::map<apollota::Pair, double>::const_iterator it=constrained_contacts.begin();it!=constrained_contacts.end();++it)
		{
			if(it->first.get(0)<input_spheres_count && it->first.get(1)<input_spheres_count)
			{
				interactions_map[it->first]=it->second;
			}
		}
	}

	if(mock_solvent_ids.empty())
	{
		const std::map<std::size_t, double> constrained_contact_remainders=apollota::ConstrainedContactsConstruction::construct_contact_remainders(spheres, vertices_vector, probe, sih_depth, volumes_map_bundle);
		for(std::map<std::size_t, double>::const_iterator it=constrained_contact_remainders.begin();it!=constrained_contact_remainders.end();++it)
		{
			if(it->first<input_spheres_count)
			{
				interactions_map[apollota::Pair(it->first, it->first)]=it->second;
			}
		}
	}

    if(add_mirrored)
    {
        std::map< std::pair<std::size_t, std::size_t>, double > mirrored_interactions_map;
        for(std::map<apollota::Pair, double>::const_iterator it=interactions_map.begin();it!=interactions_map.end();++it)
        {
            mirrored_interactions_map[std::make_pair(it->first.get(0), it->first.get(1))]=it->second;
            if(it->first.get(0)!=it->first.get(1))
            {
                mirrored_interactions_map[std::make_pair(it->first.get(1), it->first.get(0))]=it->second;
            }
        }
        for(std::map< std::pair<std::size_t, std::size_t>, double >::const_iterator it=mirrored_interactions_map.begin();it!=mirrored_interactions_map.end();++it)
        {
            std::cout << it->first.first << " " << it->first.second << " " << it->second << "\n";
        }
    }
    else
    {
        for(std::map<apollota::Pair, double>::const_iterator it=interactions_map.begin();it!=interactions_map.end();++it)
        {
            std::cout << it->first.get(0) << " " << it->first.get(1) << " " << it->second << "\n";
        }
    }

    return spheres;
}
