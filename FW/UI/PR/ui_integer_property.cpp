#include "FW/UI/PR/ui_property.h"
#include "FW/UI/PR/ui_integer_property.h"
#include "ui_integerproperty.h"
#include <QRegExp>
#include "FW/controller.h"

C_UiIntegerProperty::C_UiIntegerProperty( QString tag_name, long value, C_UiProperty::on_changed_t on_changed, QWidget* parent ):
    C_UiProperty( on_changed, parent ),
    ui( new Ui::C_UiIntegerProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );
    ui->LineEdit->setText( QString::number(value) );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        C_UiIntegerProperty::OnReturnPressed
    );

}

C_UiIntegerProperty::~C_UiIntegerProperty()
{
    delete ui;
}

void C_UiIntegerProperty::SetValue(long value )
{
    ui->LineEdit->setText( QString::number(value) );
}

long C_UiIntegerProperty::Value()
{
    return ui->LineEdit->text().toLong();
}

void C_UiIntegerProperty::OnReturnPressed()
{
    if( !QRegExp( "\\s*[-+]?\\d+(E[+]?\\d+)?\\s*" ).exactMatch(ui->LineEdit->text()))
    {
        C_Controller::Message( tr( "Bad integer number string" ) );
        return;
    }

    OnApplyChanges();
}




