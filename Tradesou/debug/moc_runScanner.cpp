/****************************************************************************
** Meta object code from reading C++ file 'runScanner.h'
**
** Created: Tue Oct 30 17:37:11 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../runScanner.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'runScanner.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_runScanner[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      37,   32,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_runScanner[] = {
    "runScanner\0\0on_bt_url_clicked()\0item\0"
    "urlItemClicked(QTreeWidgetItem*)\0"
};

void runScanner::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        runScanner *_t = static_cast<runScanner *>(_o);
        switch (_id) {
        case 0: _t->on_bt_url_clicked(); break;
        case 1: _t->urlItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData runScanner::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject runScanner::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_runScanner,
      qt_meta_data_runScanner, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &runScanner::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *runScanner::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *runScanner::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_runScanner))
        return static_cast<void*>(const_cast< runScanner*>(this));
    return QWidget::qt_metacast(_clname);
}

int runScanner::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
