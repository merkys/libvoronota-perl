%include "Voronota.i"
%module Voronota
%{
/* Put headers and other declarations here */
#include "Voronota.h"
%}

%include "std_vector.i"

%template(DoubleVector) std::vector<double>;

/*
%include "std_vector.i"
%include "std_string.i"

%template(IntVector) std::vector<int>;
%template(DoubleVector) std::vector<double>;
*/
    
%include "Voronota.h"
