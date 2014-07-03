#ifndef NIXIN_TYPES_H
#define NIXIN_TYPES_H

#include <memory>

class QOpenGLFunctions_4_3_Core;

typedef unsigned int GLuint;

namespace Nixin
{
    typedef         QOpenGLFunctions_4_3_Core        OpenGLFunctions;
    typedef         std::shared_ptr<GLuint>          OpenGLHandle;
}


#endif // NIXIN_TYPES_H
