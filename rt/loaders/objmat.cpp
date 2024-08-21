#include <rt/loaders/obj.h>
#include <fstream>
#include <rt/materials/phong.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/combine.h>
#include <iostream>
#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <core/color.h>
#include <cstring>
#include <core/assert.h>
#include <rt/materials/glass.h>
#include <rt/materials/mirror.h>
#include <rt/materials/fuzzymirror.h>

namespace rt {

namespace {

    class MaterialInfo {
    public:
        std::string name;
        float specularExp;
        MaterialInfo() : diffuse_(nullptr), ambient_(nullptr), specular_(nullptr), specularExp(1.0f) {}
        Texture* diffuse() { return diffuse_; }
        Texture* ambient() { return ambient_; }
        Texture* specular() { return specular_; }
        void diffuse(Texture* newtex) { delete diffuse_; diffuse_ = newtex; }
        void ambient(Texture* newtex) { delete ambient_; ambient_ = newtex; }
        void specular(Texture* newtex) { delete specular_; specular_ = newtex; }
        void drop() { name=""; specularExp=1.0f; diffuse_ = nullptr; ambient_ = nullptr; specular_ = nullptr; }

        // Glass:
        void glass(bool flag) { glass_ = flag; }
        bool glass() { return glass_; }
        void mirror(bool flag) { glass_ = flag; }
        bool mirror() { return mirror_; }
        void water(bool flag) { water_ = flag; }
        bool water() { return water_; }
        void fuzzy(bool flag) { fuzzy_ = flag; }
        bool fuzzy() { return fuzzy_; }
        void metal(bool flag) { metal_ = flag; }
        bool metal() { return metal_; }
    private:
        Texture* diffuse_;
        Texture* ambient_;
        Texture* specular_;
        
        // Glass:
        bool glass_ = false;
        bool water_ = false;
        bool mirror_ = false;
        bool fuzzy_ = false;
        bool metal_ = false;
    };

    void skipWS(const char * &aStr)
    {
        while(isspace(*aStr))
            aStr++;
    }

    std::string endSpaceTrimmed(const char* _str)
    {
        size_t len = std::strlen(_str);
        const char *firstChar = _str;
        const char *lastChar = firstChar + len - 1;
        while(lastChar >= firstChar && isspace(*lastChar))
            lastChar--;

        return std::string(firstChar, lastChar + 1);
    }

    void matCreate(MatLib* dest, MaterialInfo& matinfo) {
        if (matinfo.name != "") {
            std::cerr << "creating material " << matinfo.name << "\n";
            PhongMaterial* phong = nullptr;
            LambertianMaterial* lambertian = nullptr;
            Material* finalmat;
            if (matinfo.glass()) {
                finalmat = new GlassMaterial(2.0f);
                dest->insert(make_pair(matinfo.name, finalmat));
            }
            else if (matinfo.mirror()) {
                finalmat = new MirrorMaterial(0.177f, 3.638f);
                dest->insert(make_pair(matinfo.name, finalmat));
            }
            else if (matinfo.water()) {
                finalmat = new GlassMaterial(2.0f);
                finalmat->donot = true;
                dest->insert(make_pair(matinfo.name, finalmat));
            }
            else if (matinfo.fuzzy()) {
                finalmat = new FuzzyMirrorMaterial(2.485f, 3.433f, 0.05f);
                dest->insert(make_pair(matinfo.name, finalmat));
            }
            else if (matinfo.metal()) {
                finalmat = new MirrorMaterial(2.485, 3.433);
                dest->insert(make_pair(matinfo.name, finalmat));
            }
            else {
                if (matinfo.specular())
                    finalmat = phong = new PhongMaterial(matinfo.specular(), matinfo.specularExp);
                if (matinfo.diffuse())
                    finalmat = lambertian = new LambertianMaterial(matinfo.ambient(), matinfo.diffuse());
                if (phong && lambertian) {
                    CombineMaterial* combine = new CombineMaterial();
                    combine->add(phong, 1.0f);
                    combine->add(lambertian, 1.0f);
                    finalmat = combine;
                }
                dest->insert(make_pair(matinfo.name, finalmat));
            }
        }
        matinfo.water(false);
        matinfo.glass(false);
        matinfo.mirror(false);
        matinfo.fuzzy(false);
        matinfo.metal(false);
        matinfo.drop();
    }
}


void loadOBJMat(MatLib* dest, const std::string& path, const std::string& filename, BumpLib* blib) {
    std::string fullname = path + filename;
    std::ifstream matInput(fullname.c_str(), std::ios_base::in);
    std::string buf;
    MaterialInfo material;


    if(matInput.fail()) {
        std::cerr << "Failed to open file " << fullname << "\n";
        return;
    }

    size_t curLine = 0;

    while(!matInput.eof())
    {
        std::getline(matInput, buf);
        curLine++;
        const char* cmd = buf.c_str();
        skipWS(cmd);

        if(std::strncmp(cmd, "newmtl", 6) == 0)
        {
            matCreate(dest, material); //create the previous material (if it exists) and clear the material info
            cmd += 6;

            skipWS(cmd);
            material.name = endSpaceTrimmed(cmd);
        }
        else if(
            std::strncmp(cmd, "Kd", 2) == 0 || std::strncmp(cmd, "Ks", 2) == 0 
            || std::strncmp(cmd, "Ka", 2) == 0)
        {
            char coeffType = *(cmd + 1);

            RGBColor color;
            cmd += 2;

            char *newCmdString;
            for(int i = 0; i < 3; i++)
            {
                skipWS(cmd);
                ((float*)&color)[i] = (float)strtod(cmd, &newCmdString);
                if(newCmdString == cmd) goto parse_err_found;
                cmd = newCmdString; 
            }


            switch (coeffType)
            {
            case 'd': 
                material.diffuse(new ConstantTexture(color)); break;
            case 'a': 
                material.ambient(new ConstantTexture(color)); break;
            case 's': 
                material.specular(new ConstantTexture(color)); break;
            }
        }
        else if(std::strncmp(cmd,  "Ns", 2) == 0) 
        {
            cmd += 2;

            char *newCmdString;
            skipWS(cmd);
            float coeff = (float)strtod(cmd, &newCmdString);
            if(newCmdString == cmd) goto parse_err_found;
            cmd = newCmdString; 
            material.specularExp = coeff;
        }
        else if(
            std::strncmp(cmd, "map_Kd", 6) == 0 || std::strncmp(cmd, "map_Ks", 6) == 0 
            || std::strncmp(cmd, "map_Ka", 6) == 0) {
                char coeffType = *(cmd + 5);
                cmd += 6;
                skipWS(cmd);
                std::string texname = endSpaceTrimmed(cmd);
                ImageTexture* tex = new ImageTexture(path + texname);
                switch (coeffType)
                {
                case 'd': 
                    material.diffuse(tex); break;
                case 'a': 
                    material.ambient(tex); break;
                case 's': 
                    material.specular(tex); break;
                }
        }
        else if (std::strncmp(cmd, "bump", 4) == 0) {
            cmd += 4;
            skipWS(cmd);
            std::string texname = endSpaceTrimmed(cmd);
            ImageTexture* tex = new ImageTexture(path + texname);
            blib->insert(make_pair(material.name, tex));
        }
        else if (std::strncmp(cmd, "glass", 5) == 0) {
            material.glass(true);
        }
        else if (std::strncmp(cmd, "mirror", 6) == 0) {
            material.mirror(true);
        }
        else if (std::strncmp(cmd, "water", 5) == 0) {
            material.water(true);
        }
        else if (std::strncmp(cmd, "fuzzy", 5) == 0) {
            material.fuzzy(true);
        }
        else if (std::strncmp(cmd, "metal", 5) == 0) {
            material.metal(true);
        }

        continue;
parse_err_found:
        std::cerr << "Error at line " << curLine << "in " << fullname <<std::endl;
    }
    matCreate(dest, material);
}

}
