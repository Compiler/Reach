#pragma once
#include <Reach/Tools/Logging/Logger.h>
#include <Reach/ECS/Components.h>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <unordered_map>
#include <vector>
#include <stdint.h>

namespace reach{

    //static 
    class TextureManager{

        private:
            static std::unordered_map<uint64_t, int32_t> _hashToGLID;
            static std::vector<uint32_t> _textureSlots;

        public:

            //Assumes texture component has a filepath 
            static void registerTexture(TextureComponent& texture){
                if(texture.keyFileName == -1){
                    FileLoaderFactory::loadOpenGLTexture(&texture);
                }
                if(_hashToGLID.find(texture.keyFileName) == _hashToGLID.end()){
                    _hashToGLID[texture.keyFileName] = texture.id;
                    _textureSlots.push_back(texture.id);
                }

            }

            static uint32_t getOpenGLTextureID(uint64_t hashedName){
                if(_hashToGLID.find(hashedName) == _hashToGLID.end()) REACH_WARN("Couldn't find texture id");
                return _hashToGLID[hashedName];
            }

            static void _dbg_printTextureSlots(){
                REACH_WARN("Start '_dbg_printTextureSlots'");
                for(int i = 0; i < _textureSlots.size(); i++){
                    REACH_DEBUG(i << " -> " << _textureSlots[i]);

                }
                REACH_WARN("End '_dbg_printTextureSlots'");

            }


    };

}