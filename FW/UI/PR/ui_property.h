#ifndef C_UIPROPERTY_H
#define C_UIPROPERTY_H

#include "FW/macro.h"
#include <QWidget>
#include <functional>

class C_UiProperty : public QWidget
{
    Q_OBJECT

public:

    typedef std::function<void( C_UiProperty& )> on_changed_t;

    C_UiProperty( on_changed_t on_changed, QWidget* parent );

    M_VALUE             ( ApplyChangesCallBack, on_changed_t )

public slots:

    void                OnApplyChanges();

};

#endif // C_UIPROPERTY_H
