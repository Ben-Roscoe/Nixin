#ifndef NIXIN_SHADERFILE_H
#define NIXIN_SHADERFILE_H


#include "Nixin_Types.h"
#include "Nixin_VertexAttribute.h"

#include <string>
#include <map>
#include <vector>
#include <QOpenGLFunctions_4_3_Core>


namespace Nixin
{
    class ShaderProgram;


    struct Field
    {
        std::string         name;
        std::string         type;

        // How many files is this field present in?
        size_t              count   = 1;


        Field( const std::string& fieldName, const std::string& fieldType )
        {
            name = fieldName;
            type = fieldType;
        }
    };

    struct UniformType
    {
        std::string                             name;
        std::vector<Field>                      members;


        UniformType()
        {

        }

        UniformType( const std::string& typeName )
        {
            name = typeName;
        }
    };


    class ShaderFile
    {



    public:




        ShaderFile( GLenum shaderType );
        ShaderFile( const std::string& fileName, GLenum shaderType, bool compileShader = false );
        ShaderFile( const ShaderFile& other );
        ShaderFile( ShaderFile&& other );
        ShaderFile& operator=( ShaderFile other );
        ~ShaderFile();

        friend void                 swap( ShaderFile& a, ShaderFile& b );

        bool                        Compile();

        const std::vector<Field>&   GetAttributes() const;
        const std::vector<Field>&   GetUniforms() const;
        const std::map<std::string, UniformType>& GetUniformTypes() const;
        GLuint                      GetID() const;
        GLenum                      GetType() const;
        bool                        IsCompiled() const;
        const std::string&          GetSource() const;
        std::string&                GetSource();
        void                        SetSource( const std::string& fileSource );
        void                        LoadSourceFromFile( const std::string& fileName );



    private:



        OpenGLFunctions*            gl                  = QOpenGLContext::currentContext()->versionFunctions<OpenGLFunctions>();
        GLuint                      id                  = 0;
        GLenum                      type                = GL_VERTEX_SHADER;
        std::string                 source              = "";
        std::vector<Field>          uniformFields;
        std::vector<Field>          attributeFields;
        std::map<std::string, UniformType>              uniformTypes;


        bool                        compiled            = false;


        void                        GenFile();
        void                        GenerateMetaData();
    };
}

#endif // NIXIN_SHADERFILE_H
