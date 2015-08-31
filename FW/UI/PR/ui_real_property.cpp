#include "FW/UI/PR/ui_real_property.h"
#include "ui_realproperty.h"
#include "FW/controller.h"


C_UiRealProperty::C_UiRealProperty( QString tag_name, double value, on_changed_t on_changed, QWidget* parent ):
    C_UiProperty( on_changed, parent ),
    ui( new Ui::C_UiRealProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );
    ui->LineEdit->setText( QString::number( value ) );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        C_UiRealProperty::OnReturnPressed
    );

}

C_UiRealProperty::~C_UiRealProperty()
{
    delete ui;
}


void C_UiRealProperty::SetValue( double value )
{
    ui->LineEdit->setText( QString::number( value ) );
}

double C_UiRealProperty::Value()
{
    return ui->LineEdit->text().toDouble();
}

void C_UiRealProperty::OnReturnPressed()
{
    if( !QRegExp( "\\s*[-+]?\\d+(.\\d+)?([Ee][+-]?\\d+(.\\d+)?)?\\s*" ).exactMatch( ui->LineEdit->text() ) )
    {
        C_Controller::Message( tr( "Bad real number string" ) );
        return;
    }

    OnApplyChanges();
}

