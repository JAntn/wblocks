#include "FW/UI/PR/ui_property.h"

TypeUiProperty::TypeUiProperty( TypeUiProperty::TypeSaveCallback on_changed , QWidget* parent ):
    QWidget( parent ),
    TypeVariant( 0 ),
    m_SaveCallback( on_changed )
{
    // void
}

bool TypeUiProperty::empty_save_callback( TypeUiProperty& )
{
    return true;
}

void TypeUiProperty::OnActionSave(  )
{
    if( m_SaveCallback( *this ) )
        emit HasSaved();
}
