#include "ShaderProgram.h"


namespace reach{


    uint32_t ShaderProgram::_loadShader(const char* fileName, int type){
        uint32_t shaderID;
		std::string shaderSrc;
		reach::FileLoaderFactory::loadTextFromFile(fileName, shaderSrc);
		const char* shaderSrcChar = shaderSrc.c_str();
        shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &shaderSrcChar, NULL);
		glCompileShader(shaderID);
		{
			int  success;
			char infoLog[512];
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if(!success){
				glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
                std::string shaderType;
                if(type == GL_VERTEX_SHADER) shaderType = "VERTEX";
                else if(type == GL_FRAGMENT_SHADER) shaderType = "FRAGMENT";
                else if(type == GL_GEOMETRY_SHADER) shaderType = "GEOMETRY";
                else REACH_ERROR("SHADER::" << shaderType << "TYPE_UNKNOWN - TYPE = " << type);
				REACH_ERROR("SHADER::" << shaderType << "::COMPILATION_FAILED\t" <<  infoLog);
			}
		}

        return shaderID;

    }

    void ShaderProgram::loadShader(const char* vertexFile, const char* fragmentFile){
        uint32_t vid = _loadShader(vertexFile, SHADER_TYPE_VERTEX);
        uint32_t fid = _loadShader(fragmentFile, SHADER_TYPE_FRAGMENT);


        _shaderProgram = glCreateProgram();

		glAttachShader(_shaderProgram, vid);
		glAttachShader(_shaderProgram, fid);
		glLinkProgram(_shaderProgram);

		{
			int  success;
			char infoLog[512];
			glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
			if(!success) {
				glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
				REACH_ERROR("ERROR::SHADER::COMP::COMPILATION_FAILED\t "<< infoLog );
			}
		}

    }


}