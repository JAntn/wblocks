#include "FW/UI/PR/ui_string_property.h"
#include "ui_stringproperty.h"

TypeUiStringProperty::TypeUiStringProperty( QString tag_name, QString value, TypeSaveCallback on_changed, QWidget* parent ):
    TypeUiProperty( on_changed, parent ),
    ui( new Ui::TypeUiStringProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );
    ui->PlainTextEdit->setPlainText( value );

    connect(
        ui->ApplyButton,
        QPushButton::clicked,
        this,
        TypeUiStringProperty::OnApplyButtonClicked
    );

}

TypeUiStringProperty::~TypeUiStringProperty()
{
    delete ui;
}

void TypeUiStringProperty::SetValue( QString value )
{
    ui->PlainTextEdit->setPlainText( value );
}

QString TypeUiStringProperty::Value()
{
    return ui->PlainTextEdit->toPlainText();
}


void TypeUiStringProperty::OnApplyButtonClicked()
{
    OnApplyChanges();
}



