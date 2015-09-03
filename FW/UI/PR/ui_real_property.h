#ifndef UIREALPROPERTY_H
#define UIREALPROPERTY_H

#include "FW/macro.h"
#include <QWidget>
#include "FW/UI/PR/ui_property.h"


namespace Ui
{
class TypeUiRealProperty;
}

class TypeUiRealProperty : public TypeUiProperty
{
    Q_OBJECT

public:

    TypeUiRealProperty( QString tag_name, double value, TypeSaveCallback on_changed, QWidget* parent  = 0 );
    ~TypeUiRealProperty() override;

    double                        Value();
    void                          SetValue( double value );

public slots:

    void                          OnReturnPressed();

private:

    Ui::TypeUiRealProperty* ui;
};

#endif // UIREALPROPERTY_H
