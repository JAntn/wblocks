#ifndef UILABELPROPERTY_H
#define UILABELPROPERTY_H

#include "FW/tools.h"
#include "FW/UI/PR/ui_property.h"


namespace Ui
{
class TypeUiLabelProperty;
}

class TypeUiLabelProperty : public TypeUiProperty
{
    Q_OBJECT

public:

    TypeUiLabelProperty( QString tag_name, QString value, QWidget* parent  = 0 );
    ~TypeUiLabelProperty() override;

    QString                       Value();
    void                          SetValue( QString value );

private:

    Ui::TypeUiLabelProperty* ui;
};

#endif // UIREALPROPERTY_H
