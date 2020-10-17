#pragma once
#include <Reach/Tools/Logging/Logger.h>
#include <Reach/ECS/Components.h>
#include <Reach/Tools/Files/FileLoaderFactory.h>
#include <unordered_map>
#include <vector>
#include <stdint.h>
#include <filesystem>

namespace reach{

    //static 
    class TextureManager{

        private:
            static std::unordered_map<uint64_t, int32_t> _hashToGLID;
            static std::unordered_map<uint64_t, int32_t> _hashToSlot;
            static uint64_t* _textureSlots;
            static int32_t _availableSlots;
            static uint16_t _currentIndex;
            static constexpr uint64_t _DEF_EMPTY_VALUE_ = 0;

             static void _populateFilePaths() {
                 REACH_WARN(std::filesystem::current_path());
                 for (const auto& entry : std::filesystem::directory_iterator("src/Resources/Textures/")) {
                     std::string fullPath = entry.path().string();
                     REACH_LOG(fullPath);
                 }

		     }
        public:

            static void __init(){
                _populateFilePaths();
                _currentIndex = 0;
                glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_availableSlots);
                _textureSlots = new uint64_t[_availableSlots];
                for(int i = 0; i < _availableSlots; i++) _textureSlots[i] = _DEF_EMPTY_VALUE_;

            }
            //Assumes texture component has a filepath 
            static void registerTexture(TextureComponent& texture){
                if(texture.keyFileName == -1){
                    FileLoaderFactory::loadOpenGLTexture(&texture);
                    //REACH_LOG("Was forced to load texture for user");
                }
                if(_hashToGLID.find(texture.keyFileName) == _hashToGLID.end()){
                    _hashToGLID[texture.keyFileName] = texture.id;
                    _textureSlots[_currentIndex] = texture.id;
                    _hashToSlot[texture.keyFileName] = _currentIndex;
                    _currentIndex++;
                }

            }

            static uint32_t getSlot(uint64_t hashedName){
                if(_hashToSlot.find(hashedName) == _hashToSlot.end()) REACH_WARN("Couldn't find texture id");
                return _hashToSlot[hashedName];
            }

            static void _dbg_printTextureSlots(){
                REACH_WARN("Start '_dbg_printTextureSlots'");
                for(int i = 0; i < _availableSlots; i++){
                    REACH_DEBUG(i << " -> " << _textureSlots[i]);

                }
                REACH_WARN("End '_dbg_printTextureSlots'");

            }


    };

}