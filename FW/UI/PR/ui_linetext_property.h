#ifndef UILINETEXTPROPERTY_H
#define UILINETEXTPROPERTY_H

#include "FW/tools.h"
#include "FW/UI/PR/ui_property.h"

namespace Ui
{
class TypeUiLineTextProperty;
}

class TypeUiLineTextProperty : public TypeUiProperty
{
    Q_OBJECT

public:

    TypeUiLineTextProperty( QString tag_name, QString value, TypeSaveCallback on_changed, QWidget* parent  = 0 );
    ~TypeUiLineTextProperty() override;

    QString                       Value();
    void                          SetValue( QString value );

private slots:

    void                          OnReturnPressed();

private:

    Ui::TypeUiLineTextProperty*         ui;
};

#endif // UILINETEXTPROPERTY_H
