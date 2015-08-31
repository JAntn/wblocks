#ifndef TypeUIPROPERTY_H
#define TypeUIPROPERTY_H

#include "FW/macro.h"
#include <QWidget>
#include <functional>

class TypeUiProperty : public QWidget
{
    Q_OBJECT

public:

    typedef std::function<void( TypeUiProperty& )> on_changed_t;

    TypeUiProperty( on_changed_t on_changed, QWidget* parent );

    M_VALUE             ( ApplyChangesCallBack, on_changed_t )

public slots:

    void                OnApplyChanges();

};

#endif // TypeUIPROPERTY_H
