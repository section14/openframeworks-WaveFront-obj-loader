#include "waveFrontLoader.h"

waveFrontLoader::waveFrontLoader()
{
    indexCount = 0;
}

void waveFrontLoader::loadFile(const char *fileName)
{
    ifstream file;
    char line[255];

    //open file in openframeworks data folder
    file.open(ofToDataPath(fileName).c_str());

    if (file.is_open())
    {
        while (file.getline(line,255))
        {
            parseLine(line);
        }
    }
}

void waveFrontLoader::parseLine(char *line)
{
    //If empty, don't do anything with it
    if(!strlen(line))
    {
        return;
    }

    //get line type identifier from char string
    char *lineType = strtok(strdup(line), " ");

    //parse line depending on type
    if (!strcmp(lineType, "v")) // Vertices
    {
        parseVertex(line);
    }
    else if (!strcmp(lineType, "vn")) // Normals
    {
        parseNormal(line);
    }
    else if (!strcmp(lineType, "f")) // Indices (Faces)
    {
        parseFace(line);
    }
}

void waveFrontLoader::parseVertex(char *line)
{
    float x;
    float y;
    float z;

    vertices.push_back(ofVec3f(x,y,z));

    //get coordinates from vertex line and assign
    sscanf(line, "v %f %f %f", &vertices.back().x, &vertices.back().y, &vertices.back().z);
}

void waveFrontLoader::parseNormal(char *line)
{
    float x;
    float y;
    float z;

    normals.push_back(ofVec3f(x,y,z));

    //get coordinates from normal line and assign
    sscanf(line, "vn %f %f %f", &normals.back().x, &normals.back().y, &normals.back().z);
}

void waveFrontLoader::parseFace(char *line)
{
    //var to hold and discard un-needed texture data
    int discard;
    
    indices.push_back(Index());

    //get vertex and normal indices, discard texture data for now
    if(sscanf(line, "f %d//%d %d//%d %d//%d",
           &indices.back().v1,
           &indices.back().vn1,
           &indices.back().v2,
           &indices.back().vn2,
           &indices.back().v3,
           &indices.back().vn3) <= 1)
    {
        sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
               &indices.back().v1,
               &discard,
               &indices.back().vn1,
               &indices.back().v2,
               &discard,
               &indices.back().vn2,
               &indices.back().v3,
               &discard,
               &indices.back().vn3);
    }
}

ofMesh waveFrontLoader::generateMesh()
{
    for (std::vector<Index>::iterator i = indices.begin(); i != indices.end(); ++i)
    {
        //check if the vertex and normal location exists already
        addFace(&vertices[(i->v1) - 1], &normals[(i->vn1) - 1]);
        addFace(&vertices[(i->v2) - 1], &normals[(i->vn2) - 1]);
        addFace(&vertices[(i->v3) - 1], &normals[(i->vn3) - 1]);
    }

    return mesh;
}

void waveFrontLoader::addFace(ofVec3f *vertex, ofVec3f *normal)
{
    //temp vars
    int vertIndex;
    int normIndex;

    //check if this vertex exists already
    std::map<int,ofVec3f>::iterator faceIt;

    for (faceIt = faceVertices.begin(); faceIt != faceVertices.end(); ++faceIt)
    {
        if (faceIt->second == *vertex)
        {
            vertIndex = faceIt->first;
        }
    }

    //check if this normal exists already
    std::map<int,ofVec3f>::iterator normIt;

    for (normIt = faceNormals.begin(); normIt != faceNormals.end(); ++normIt)
    {
        if (normIt->second == *normal)
        {
            normIndex = normIt->first;
        }
    }

    //if a vertex and normal exist at this position, use those aready created
    //otherwise, add new
    if (vertIndex == normIndex)
    {
        mesh.addIndex(vertIndex);
    }
    else
    {
        int currentIndex = indexCount++;

        //add vertex
        mesh.addVertex(*vertex);
        faceVertices[currentIndex] = *vertex;

        //add normal
        mesh.addNormal(*normal);
        faceNormals[currentIndex] = *normal;

        //add index
        mesh.addIndex(currentIndex);
    }
}

waveFrontLoader::~waveFrontLoader()
{
    //
}
