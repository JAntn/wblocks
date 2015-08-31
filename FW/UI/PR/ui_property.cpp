#include "FW/UI/PR/ui_property.h"

C_UiProperty::C_UiProperty( C_UiProperty::on_changed_t on_changed , QWidget* parent ):
    QWidget( parent ),
    m_ApplyChangesCallBack( on_changed )
{
    // void
}

void C_UiProperty::OnApplyChanges(  )
{
    m_ApplyChangesCallBack( *this );
}
