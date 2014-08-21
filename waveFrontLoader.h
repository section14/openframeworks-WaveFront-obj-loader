#ifndef _WAVEFRONTLOADER
#define _WAVEFRONTLOADER

#include "ofMain.h"

class waveFrontLoader {

public:

    ofMesh mesh;

    waveFrontLoader();
    ~waveFrontLoader();

    void loadFile(const char *fileName);
    ofMesh generateMesh();

private:

    typedef struct
    {
        ofIndexType v1,v2,v3;
        ofIndexType vn1,vn2,vn3;
    }
    Index;

    std::vector<ofVec3f> vertices;
    std::vector<ofVec3f> normals;
    std::vector<Index> indices;

    std::map<int,ofVec3f>faceVertices;
    std::map<int,ofVec3f>faceNormals;
    std::vector<ofIndexType>faceIndices;

    int indexCount;

    void parseLine(char *line);
    void parseVertex(char *line);
    void parseNormal(char *line);
    void parseFace(char *line);

    void addFace(ofVec3f *vertex, ofVec3f *normal);
};

#endif
