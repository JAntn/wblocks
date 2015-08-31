#include "FW/UI/PR/ui_string_property.h"
#include "ui_stringproperty.h"

C_UiStringProperty::C_UiStringProperty( QString tag_name, QString value, on_changed_t on_changed, QWidget* parent ):
    C_UiProperty( on_changed, parent ),
    ui( new Ui::C_UiStringProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );
    ui->PlainTextEdit->setPlainText( value );

    connect(
        ui->ApplyButton,
        QPushButton::clicked,
        this,
        C_UiStringProperty::OnApplyButtonClicked
    );

}

C_UiStringProperty::~C_UiStringProperty()
{
    delete ui;
}

void C_UiStringProperty::SetValue( QString value )
{
    ui->PlainTextEdit->setPlainText( value );
}

QString C_UiStringProperty::Value()
{
    return ui->PlainTextEdit->toPlainText();
}


void C_UiStringProperty::OnApplyButtonClicked()
{
    OnApplyChanges();
}



