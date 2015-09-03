#include "FW/UI/PR/ui_linetext_property.h"
#include "ui_linetextproperty.h"

TypeUiLineTextProperty::TypeUiLineTextProperty( QString tag_name, QString value, TypeSaveCallback on_changed, QWidget* parent ):
    TypeUiProperty( on_changed, parent ),
    ui( new Ui::TypeUiLineTextProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );
    ui->LineEdit->setText( value );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        TypeUiLineTextProperty::OnReturnPressed
    );
}

TypeUiLineTextProperty::~TypeUiLineTextProperty()
{
    delete ui;
}

void TypeUiLineTextProperty::SetValue( QString value )
{
    ui->LineEdit->setText( value );
}

QString TypeUiLineTextProperty::Value()
{
    return ui->LineEdit->text();
}


void TypeUiLineTextProperty::OnReturnPressed()
{
    OnApplyChanges();
}



