//
// Created by Vinayak Aggarwal on 12/07/23.
//

#ifndef RUBIKSCUBESOLVER_BUILDCORNERDB_H
#define RUBIKSCUBESOLVER_BUILDCORNERDB_H

#include "./cornerPatternDB.h"
#include "string"

using namespace std;

class buildCornerDB {
private:
    string fileName;
    cornerPatternDB cornerDB;
public:
    buildCornerDB(string _fileName);
    buildCornerDB(string _fileName, uint8_t init_val);

    bool bfsAndStore();
};


#endif //RUBIKSCUBESOLVER_BUILDCORNERDB_H
