#ifndef C_UIEDITOR_H
#define C_UIEDITOR_H

#include <QWidget>
#include "FW/macro.h"
#include <functional>

class C_UiEditor : public QWidget
{
    Q_OBJECT

public:

    typedef std::function<void( C_UiEditor& )> save_callback_t;

    explicit C_UiEditor( QString id, QString name, QString tab_name, save_callback_t save_callback, QWidget* parent = 0 );
    ~C_UiEditor();

    M_CONST_VALUE                ( Id,                QString )
    M_VALUE                      ( Name,              QString )
    M_VALUE                      ( TabName,           QString )
    M_VALUE                      ( HasChanged,        bool )
    M_VALUE                      ( SaveCallBack,      save_callback_t )

public slots:

    void                         OnActionSave();

};

#endif // C_UIEDITOR_H
