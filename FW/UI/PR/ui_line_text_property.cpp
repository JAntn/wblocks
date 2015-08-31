#include "FW/UI/PR/ui_line_text_property.h"
#include "ui_linetextproperty.h"

C_UiLineTextProperty::C_UiLineTextProperty( QString tag_name, QString value, on_changed_t on_changed, QWidget* parent ):
    C_UiProperty( on_changed, parent ),
    ui( new Ui::C_UiLineTextProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );
    ui->LineEdit->setText( value );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        C_UiLineTextProperty::OnReturnPressed
    );
}

C_UiLineTextProperty::~C_UiLineTextProperty()
{
    delete ui;
}

void C_UiLineTextProperty::SetValue( QString value )
{
    ui->LineEdit->setText( value );
}

QString C_UiLineTextProperty::Value()
{
    return ui->LineEdit->text();
}


void C_UiLineTextProperty::OnReturnPressed()
{
    OnApplyChanges();
}



