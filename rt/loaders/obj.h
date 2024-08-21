#ifndef CG1RAYTRACER_LOADERS_OBJ_HEADER
#define CG1RAYTRACER_LOADERS_OBJ_HEADER

#include <string>
#include <map>
#include <vector>
#include <rt/textures/imagetex.h>

namespace rt {

class Group;
class Material;

typedef std::map<std::string, Material*> MatLib;
typedef std::map<std::string, ImageTexture*> BumpLib;

void loadOBJ(Group* dest, const std::string& path, const std::string& filename, MatLib* inmats=nullptr);
void loadOBJMat(MatLib* dest, const std::string& path, const std::string& filename, BumpLib* blib);

}

#endif