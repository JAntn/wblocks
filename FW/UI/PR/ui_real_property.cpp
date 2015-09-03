#include "FW/UI/PR/ui_real_property.h"
#include "FW/controller.h"
#include "ui_realproperty.h"


TypeUiRealProperty::TypeUiRealProperty( QString tag_name, double value, TypeSaveCallback on_changed, QWidget* parent ):
    TypeUiProperty( on_changed, parent ),
    ui( new Ui::TypeUiRealProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );
    ui->LineEdit->setText( QString::number( value ) );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        TypeUiRealProperty::OnReturnPressed
    );

}

TypeUiRealProperty::~TypeUiRealProperty()
{
    delete ui;
}


void TypeUiRealProperty::SetValue( double value )
{
    ui->LineEdit->setText( QString::number( value ) );
}

double TypeUiRealProperty::Value()
{
    return ui->LineEdit->text().toDouble();
}

void TypeUiRealProperty::OnReturnPressed()
{
    if( !QRegExp( "\\s*[-+]?\\d+(.\\d+)?([Ee][+-]?\\d+(.\\d+)?)?\\s*" ).exactMatch( ui->LineEdit->text() ) )
    {
        TypeController::Message( tr( "Bad real number string" ) );
        return;
    }

    OnApplyChanges();
}

