//
//  Model.cpp
//  example-empty
//
//  Created by Jerome Martinez on 2/6/19.
//

#include "Model.h"
#include "Facet.h"

void Model::setup() {
    
}

void Model::update() {
    
}

void Model::draw() {
//    for (int i = 0; i < facets.length(); i++) {
//        facets[i].draw();
//    }
    for (Facet& f : facets) {
        f.draw();
    }
}

void Model::addFacet(const Facet& f) {
    facets.push_back(f);
}

std::vector<Facet> Model::getFacets() const {
    return facets;
}
