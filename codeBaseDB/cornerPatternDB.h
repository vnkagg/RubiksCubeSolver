//
// Created by Vinayak Aggarwal on 12/07/23.
//

#ifndef RUBIKSCUBESOLVER_CORNERPATTERNDB_H
#define RUBIKSCUBESOLVER_CORNERPATTERNDB_H

#include "PatternDatabase.h"
#include "permutationIndexer_BlackBox.h"
#include "array"

class cornerPatternDB : public PatternDatabase {

    typedef RubiksCube::FACE F;
    PermutationIndexer<8> permIndexer;

public:
    cornerPatternDB();
    cornerPatternDB(uint8_t init_val);
    uint32_t getDatabaseIndex(const RubiksCube& cube) const;

};

#endif //RUBIKSCUBESOLVER_CORNERPATTERNDB_H
