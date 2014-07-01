QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES      += GLEW_MX NOMINMAX
DEFINES -= UNICODE

QMAKE_INCDIR += $$_PRO_FILE_PWD_/Includes/Include
QMAKE_LIBDIR += $$_PRO_FILE_PWD_/Includes/Lib
LIBS         += -lFreeImage
LIBS         += -lfreetype252MT
LIBS         += -lglew32mx
#LIBS         += -lglew32
#LIBS         += -lglew32s
#LIBS         += -lglew32mx
LIBS         += -llibOpenAL32
LIBS         += -lOpengl32


TARGET = Nixin
TEMPLATE = app
CONFIG   += c++11

SOURCES += main.cpp\
    Nixin_Camera.cpp \
    Nixin_Canvas.cpp \
    Nixin_Colour.cpp \
    Nixin_Font.cpp \
    Nixin_GameTime.cpp \
    Nixin_Image.cpp \
    Nixin_Keyboard.cpp \
    Nixin_Material.cpp \
    Nixin_Math.cpp \
    Nixin_Matrix.cpp \
    Nixin_Mouse.cpp \
    Nixin_Point.cpp \
    Nixin_Quaternion.cpp \
    Nixin_Rectangle.cpp \
    Nixin_ShaderProgram.cpp \
    Nixin_SoundEffect.cpp \
    Nixin_SoundEngine.cpp \
    Nixin_SoundFile.cpp \
    Nixin_SpriteBuffer.cpp \
    Nixin_Texture.cpp \
    Nixin_Timer.cpp \
    Nixin_Utility.cpp \
    Nixin_WorldObject.cpp \   
    Nixin_QtOpenGLWindow.cpp \
    Nixin_QtOpenGLWidget.cpp \
    Nixin_GameWindow.cpp \
    Nixin_Application.cpp \
    Nixin_GLBuffer.cpp \
    Nixin_Renderbuffer.cpp \
    Nixin_FramebufferAttachment.cpp \
    mainwindowtest.cpp \
    Nixin_Debug.cpp \
    Nixin_Framebuffer.cpp \
    Nixin_TransformFeedbackBinding.cpp \
    Nixin_TransformFeedback.cpp \
    Nixin_TextureBase.cpp \
    Nixin_Texture1DImmutable.cpp \
    Nixin_Texture1DArrayImmutable.cpp \
    Nixin_ShaderFile.cpp \
    Nixin_UniformBase.cpp \
    Nixin_UniformValues.cpp \
    Nixin_Uniform.cpp \
    Nixin_VertexAttribute.cpp

HEADERS += \
    Nixin_Camera.h \
    Nixin_Canvas.h \
    Nixin_Colour.h \
    Nixin_Font.h \
    Nixin_GameTime.h \
    Nixin_Image.h \
    Nixin_Keyboard.h \
    Nixin_Material.h \
    Nixin_Math.h \
    Nixin_Matrix.h \
    Nixin_Memory_Utility.h \
    Nixin_Mouse.h \
    Nixin_Point.h \
    Nixin_Quaternion.h \
    Nixin_Rectangle.h \
    Nixin_ShaderProgram.h \
    Nixin_SoundEffect.h \
    Nixin_SoundEngine.h \
    Nixin_SoundFile.h \
    Nixin_SpriteBuffer.h \
    Nixin_Texture.h \
    Nixin_Timer.h \
    Nixin_Utility.h \
    Nixin_Vertex.h \
    Nixin_WorldObject.h \
    Nixin_QtOpenGLWindow.h \
    Nixin_QtOpenGLWidget.h \
    Nixin_GameWindow.h \
    Nixin_Application.h \
    Nixin_GLBuffer.h \
    Nixin_Renderbuffer.h \
    Nixin_FramebufferAttachment.h \
    Nixin_Types.h \
    mainwindowtest.h \
    Nixin_Debug.h \
    Nixin_Framebuffer.h \
    Nixin_TransformFeedbackBinding.h \
    Nixin_TransformFeedback.h \
    Nixin_TextureBase.h \
    Nixin_Texture1DImmutable.h \
    Nixin_Texture1DArrayImmutable.h \
    Nixin_ShaderFile.h \
    Nixin_Uniform.h \
    Nixin_UniformBase.h \
    Nixin_UniformValues.h \
    Nixin_VertexAttribute.h

FORMS += \
    mainwindowtest.ui


