#include "FW/tools.h"
#include "FW/UI/PR/ui_property.h"
#include "FW/UI/PR/ui_integer_property.h"
#include "FW/controller.h"
#include "ui_integerproperty.h"

TypeUiIntegerProperty::TypeUiIntegerProperty( QString tag_name, long value, TypeUiProperty::TypeSaveCallback on_changed, QWidget* parent ):
    TypeUiProperty( on_changed, parent ),
    ui( new Ui::TypeUiIntegerProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );
    ui->LineEdit->setText( QString::number(value) );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        TypeUiIntegerProperty::OnReturnPressed
    );

}

TypeUiIntegerProperty::~TypeUiIntegerProperty()
{
    delete ui;
}

void TypeUiIntegerProperty::SetValue(long value )
{
    ui->LineEdit->setText( QString::number(value) );
}

long TypeUiIntegerProperty::Value()
{
    return ui->LineEdit->text().toLong();
}

void TypeUiIntegerProperty::OnReturnPressed()
{
    if( !QRegExp( "\\s*[-+]?\\d+(E[+]?\\d+)?\\s*" ).exactMatch(ui->LineEdit->text()))
    {
        TypeController::Message( tr( "Bad integer number string" ) );
        return;
    }

    OnApplyChanges();
}




