/****************************************************************************
** Meta object code from reading C++ file 'originalsignalslot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../OriginalSignalSlot/originalsignalslot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'originalsignalslot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OriginalSignalSlot_t {
    QByteArrayData data[7];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OriginalSignalSlot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OriginalSignalSlot_t qt_meta_stringdata_OriginalSignalSlot = {
    {
QT_MOC_LITERAL(0, 0, 18), // "OriginalSignalSlot"
QT_MOC_LITERAL(1, 19, 17), // "textLengthChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 10), // "textLength"
QT_MOC_LITERAL(4, 49, 7), // "setText"
QT_MOC_LITERAL(5, 57, 4), // "text"
QT_MOC_LITERAL(6, 62, 21) // "on_pushButton_clicked"

    },
    "OriginalSignalSlot\0textLengthChanged\0"
    "\0textLength\0setText\0text\0on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OriginalSignalSlot[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   32,    2, 0x0a /* Public */,
       6,    0,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

       0        // eod
};

void OriginalSignalSlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OriginalSignalSlot *_t = static_cast<OriginalSignalSlot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->textLengthChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OriginalSignalSlot::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OriginalSignalSlot::textLengthChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject OriginalSignalSlot::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_OriginalSignalSlot.data,
      qt_meta_data_OriginalSignalSlot,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OriginalSignalSlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OriginalSignalSlot::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OriginalSignalSlot.stringdata0))
        return static_cast<void*>(const_cast< OriginalSignalSlot*>(this));
    return QWidget::qt_metacast(_clname);
}

int OriginalSignalSlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void OriginalSignalSlot::textLengthChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
