#include "FW/UI/PR/ui_property.h"

TypeUiProperty::TypeUiProperty( TypeUiProperty::on_changed_t on_changed , QWidget* parent ):
    QWidget( parent ),
    m_ApplyChangesCallBack( on_changed )
{
    // void
}

void TypeUiProperty::OnApplyChanges(  )
{
    m_ApplyChangesCallBack( *this );
}
