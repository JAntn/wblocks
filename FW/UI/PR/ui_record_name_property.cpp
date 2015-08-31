#include "FW/UI/PR/ui_record_name_property.h"
#include "ui_recordnameproperty.h"
#include "FW/controller.h"

C_UiRecordNameProperty::C_UiRecordNameProperty( QString tag_name, QString value, on_changed_t on_changed, QWidget* parent ):
    C_UiProperty( on_changed, parent ),
    ui( new Ui::C_UiRecordNameProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );
    ui->LineEdit->setText( value );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        C_UiRecordNameProperty::OnReturnPressed
    );

}

C_UiRecordNameProperty::~C_UiRecordNameProperty()
{
    delete ui;
}

void C_UiRecordNameProperty::SetValue( QString value )
{
    ui->LineEdit->setText( value );
}

QString C_UiRecordNameProperty::Value()
{
    return ui->LineEdit->text();
}


void C_UiRecordNameProperty::OnReturnPressed()
{
    if( !QRegExp( "[A-Za-z][\\w.]+" ).exactMatch( ui->LineEdit->text() ) )
    {
        C_Controller::Message( tr( "Bad record name" ) );
        return;
    }

    OnApplyChanges();
}

