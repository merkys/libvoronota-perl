%include "Voronota.i"
%module Voronota
%{
/* Put headers and other declarations here */
#include "Voronota.h"
%}

%include "std_vector.i"

%template(DoubleVector) std::vector<double>;
%template(ContactVector) std::vector<Contact>;
    
%include "Voronota.h"
