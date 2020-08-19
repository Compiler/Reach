#include "TextureManager.h"

namespace reach{

    std::unordered_map<uint64_t, int32_t> TextureManager::_hashToGLID;
    std::vector<uint32_t> TextureManager::_textureSlots;

}