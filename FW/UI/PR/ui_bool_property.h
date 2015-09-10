#ifndef UIBOOLPROPERTY_H
#define UIBOOLPROPERTY_H

#include "FW/tools.h"
#include "FW/UI/PR/ui_property.h"

namespace Ui
{
class TypeUiBoolProperty;
}

class TypeUiBoolProperty : public TypeUiProperty
{
    Q_OBJECT

public:

    TypeUiBoolProperty( QString tag_name, bool value, TypeSaveCallback save_callback, QWidget* parent  = 0 );
    ~TypeUiBoolProperty() override;

    bool        Value();
    void        SetValue( bool value );

public slots:

    void        OnCurrentIndexChanged( int );

private:

    Ui::TypeUiBoolProperty* ui;
};

#endif // UIBOOLPROPERTY_H
