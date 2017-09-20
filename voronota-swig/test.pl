#!/usr/bin/perl

use strict;
use warnings;
use Voronota;
use Data::Dumper;

my $coords = [];
while( <> ) {
    my @line = split /\s+/, $_;
    push @$coords, ( $line[0] + 0.0, $line[1] + 0.0, $line[2] + 0.0, 0 );
}

my $contacts = Voronota::make_spheres( $coords );
local $, = ' ';
local $\ = "\n";
foreach (@$contacts) {
    print $_->{first}, $_->{second}, $_->{area};
}
