#ifndef TypeUIEDITOR_H
#define TypeUIEDITOR_H

#include <QWidget>
#include "FW/macro.h"
#include <functional>

class TypeUiEditor : public QWidget
{
    Q_OBJECT

public:

    typedef std::function<void( TypeUiEditor& )> save_callback_t;

    explicit TypeUiEditor( QString id, QString name, QString tab_name, save_callback_t save_callback, QWidget* parent = 0 );
    ~TypeUiEditor();

    M_CONST_VALUE                ( Id,                QString )
    M_VALUE                      ( Name,              QString )
    M_VALUE                      ( TabName,           QString )
    M_VALUE                      ( HasChanged,        bool )
    M_VALUE                      ( SaveCallBack,      save_callback_t )

public slots:

    void                         OnActionSave();

};

#endif // TypeUIEDITOR_H
