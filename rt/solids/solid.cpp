#include <rt/solids/solid.h>

namespace rt {

Solid::Solid(CoordMapper* texMapper, Material* material) : texMapper(texMapper), material(material)
{
	if (texMapper == nullptr) {
		this->texMapper = new WorldMapper();
	}
}

}
