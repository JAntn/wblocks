#ifndef UICOMBOPROPERTY_H
#define UICOMBOPROPERTY_H

#include "FW/tools.h"
#include "FW/UI/PR/ui_property.h"

namespace Ui
{
class TypeUiComboProperty;
}

class TypeUiComboProperty : public TypeUiProperty
{
    Q_OBJECT

public:

    TypeUiComboProperty( QString tag_name, int value, QStringList value_list, TypeSaveCallback save_callback, QWidget* parent  = 0 );
    ~TypeUiComboProperty() override;

    int                                     Value();
    void                                    SetValue( int value );

public slots:

    void                                    OnCurrentIndexChanged( int );

private:
    Ui::TypeUiComboProperty*                ui;
};

#endif // UICOMBOPROPERTY_H
