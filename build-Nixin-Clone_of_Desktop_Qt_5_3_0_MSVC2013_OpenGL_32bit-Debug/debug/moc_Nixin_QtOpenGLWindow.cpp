/****************************************************************************
** Meta object code from reading C++ file 'Nixin_QtOpenGLWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Nixin/Nixin_QtOpenGLWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Nixin_QtOpenGLWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Nixin__QtOpenGLWindow_t {
    QByteArrayData data[1];
    char stringdata[22];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Nixin__QtOpenGLWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Nixin__QtOpenGLWindow_t qt_meta_stringdata_Nixin__QtOpenGLWindow = {
    {
QT_MOC_LITERAL(0, 0, 21)
    },
    "Nixin::QtOpenGLWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Nixin__QtOpenGLWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Nixin::QtOpenGLWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Nixin::QtOpenGLWindow::staticMetaObject = {
    { &QWindow::staticMetaObject, qt_meta_stringdata_Nixin__QtOpenGLWindow.data,
      qt_meta_data_Nixin__QtOpenGLWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *Nixin::QtOpenGLWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Nixin::QtOpenGLWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Nixin__QtOpenGLWindow.stringdata))
        return static_cast<void*>(const_cast< QtOpenGLWindow*>(this));
    if (!strcmp(_clname, "OpenGLFunctions"))
        return static_cast< OpenGLFunctions*>(const_cast< QtOpenGLWindow*>(this));
    return QWindow::qt_metacast(_clname);
}

int Nixin::QtOpenGLWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
