#!/usr/bin/perl

use strict;
use warnings;
use Voronota;
use Data::Dumper;

print Dumper Voronota::make_spheres( [ 1, 2, 3, 4 ] );
print "it works!\n";
