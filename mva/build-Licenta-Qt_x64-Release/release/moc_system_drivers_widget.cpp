/****************************************************************************
** Meta object code from reading C++ file 'system_drivers_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Licenta/gui/headers/system_drivers_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'system_drivers_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CSystemDriversWidget_t {
    QByteArrayData data[7];
    char stringdata[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CSystemDriversWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CSystemDriversWidget_t qt_meta_stringdata_CSystemDriversWidget = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 12),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 8),
QT_MOC_LITERAL(4, 44, 15),
QT_MOC_LITERAL(5, 60, 19),
QT_MOC_LITERAL(6, 80, 6)
    },
    "CSystemDriversWidget\0OnShowWidget\0\0"
    "QWidget*\0OnSetTableModel\0QStandardItemModel*\0"
    "pModel\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CSystemDriversWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void CSystemDriversWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CSystemDriversWidget *_t = static_cast<CSystemDriversWidget *>(_o);
        switch (_id) {
        case 0: _t->OnShowWidget((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->OnSetTableModel((*reinterpret_cast< QStandardItemModel*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QStandardItemModel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CSystemDriversWidget::*_t)(QWidget * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CSystemDriversWidget::OnShowWidget)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject CSystemDriversWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CSystemDriversWidget.data,
      qt_meta_data_CSystemDriversWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *CSystemDriversWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CSystemDriversWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSystemDriversWidget.stringdata))
        return static_cast<void*>(const_cast< CSystemDriversWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CSystemDriversWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CSystemDriversWidget::OnShowWidget(QWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
