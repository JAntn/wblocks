#ifndef C_UIBOOLPROPERTY_H
#define C_UIBOOLPROPERTY_H

#include "FW/macro.h"
#include "FW/UI/PR/ui_property.h"
#include <QWidget>

namespace Ui
{
class C_UiBoolProperty;
}

class C_UiBoolProperty : public C_UiProperty
{
    Q_OBJECT

public:

    C_UiBoolProperty( QString tag_name, bool value, on_changed_t on_changed, QWidget* parent  = 0 );
    ~C_UiBoolProperty() override;

    bool        Value();
    void        SetValue( bool value );

public slots:

    void        OnCurrentIndexChanged( int );

private:

    Ui::C_UiBoolProperty* ui;
};

#endif // C_UIBOOLPROPERTY_H
