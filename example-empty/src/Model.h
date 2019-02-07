//
//  Model.hpp
//  example-empty
//
//  Created by Jerome Martinez on 2/6/19.
//

#ifndef Model_h
#define Model_h

#include <vector>

#include "Model.h"
#include "Facet.h"

class Model {
public:
    void setup();
    void update();
    void draw();
    
    void addFacet(const Facet&);
    std::vector<Facet> getFacets() const;
    
private:
    std::vector<Facet> facets;
};

#endif /* Model_h */
