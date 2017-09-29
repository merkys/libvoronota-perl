//
//  Voronota.cpp
//
#include "Voronota.h"
#include <string>
#include <iostream>

#include "apollota/constrained_contacts_construction.h"
#include "apollota/constrained_contacts_utilities.h"
#include "apollota/spheres_boundary_construction.h"
#include "apollota/spherical_contacts_construction.h"
#include "apollota/triangulation.h"

#include "auxiliaries/program_options_handler.h"

std::vector<Contact> calculate_contacts( const std::vector<double> &s ) {

    const double probe = 1.4;
    const bool exclude_hidden_balls = false;
    const std::string volumes_output = "";
    const double step = 0.2;
    const int projections = 5;
    const int sih_depth = 3;

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

    const std::map<apollota::Pair, double> constrained_contacts=apollota::ConstrainedContactsConstruction::construct_contacts(spheres, vertices_vector, probe, step, projections, std::set<std::size_t>(), volumes_map_bundle);
    for(std::map<apollota::Pair, double>::const_iterator it=constrained_contacts.begin();it!=constrained_contacts.end();++it)
    {
        if(it->first.get(0)<input_spheres_count && it->first.get(1)<input_spheres_count)
        {
            interactions_map[it->first]=it->second;
        }
    }

    const std::map<std::size_t, double> constrained_contact_remainders=apollota::ConstrainedContactsConstruction::construct_contact_remainders(spheres, vertices_vector, probe, sih_depth, volumes_map_bundle);
    for(std::map<std::size_t, double>::const_iterator it=constrained_contact_remainders.begin();it!=constrained_contact_remainders.end();++it)
    {
        if(it->first<input_spheres_count)
        {
            interactions_map[apollota::Pair(it->first, it->first)]=it->second;
        }
    }

    std::vector<Contact> contacts;
    for(std::map<apollota::Pair, double>::const_iterator it=interactions_map.begin();it!=interactions_map.end();++it)
    {
        Contact c = Contact();
        c.first  = it->first.get(0);
        c.second = it->first.get(1);
        c.area   = it->second;
        contacts.push_back( c );
    }
    return contacts;
}

std::vector<Vertice> calculate_vertices( const std::vector<double> &s ) {

    const bool exclude_hidden_balls = false;
    const bool include_surplus_quadruples = false;
    const double init_radius_for_BSH = 3.5;

    std::vector<apollota::SimpleSphere> spheres;
    for( unsigned long i = 0; i < s.size() / 4; i++ ) {
        spheres.push_back( apollota::SimpleSphere( s[i*4], s[i*4+1], s[i*4+2], s[i*4+3] ) );
    }

    if(spheres.size()<4)
    {
        throw std::runtime_error("Less than 4 balls provided to stdin.");
    }

    const apollota::Triangulation::Result triangulation_result=apollota::Triangulation::construct_result(spheres, init_radius_for_BSH, exclude_hidden_balls, include_surplus_quadruples);
    const apollota::Triangulation::VerticesVector& vertices_vector=apollota::Triangulation::collect_vertices_vector_from_quadruples_map(triangulation_result.quadruples_map);

    std::vector<Vertice> vertices;
    for(apollota::Triangulation::VerticesVector::const_iterator it=vertices_vector.begin();it!=vertices_vector.end();++it)
    {
        const apollota::Quadruple& quadruple = it->first;
        const apollota::SimpleSphere& tangent_sphere = it->second;
        Vertice v = Vertice();
        v.first  = quadruple.get(0);
        v.second = quadruple.get(1);
        v.third  = quadruple.get(2);
        v.fourth = quadruple.get(3);
        v.x = tangent_sphere.x;
        v.y = tangent_sphere.y;
        v.z = tangent_sphere.z;
        v.r = tangent_sphere.r;
        vertices.push_back( v );
    }
    return vertices;
}
