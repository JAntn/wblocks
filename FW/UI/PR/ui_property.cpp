#include "FW/UI/PR/ui_property.h"

TypeUiProperty::TypeUiProperty( TypeUiProperty::TypeSaveCallback on_changed , QWidget* parent ):
    QWidget( parent ),
    TypeVariant( 0 ),
    m_SaveCallback( on_changed )
{
    // void
}

void TypeUiProperty::OnApplyChanges(  )
{
    m_SaveCallback( *this );
}
