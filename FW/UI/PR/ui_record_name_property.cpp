#include "FW/UI/PR/ui_record_name_property.h"
#include "ui_recordnameproperty.h"
#include "FW/controller.h"

TypeUiRecordNameProperty::TypeUiRecordNameProperty( QString tag_name, QString value, on_changed_t on_changed, QWidget* parent ):
    TypeUiProperty( on_changed, parent ),
    ui( new Ui::TypeUiRecordNameProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );
    ui->LineEdit->setText( value );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        TypeUiRecordNameProperty::OnReturnPressed
    );

}

TypeUiRecordNameProperty::~TypeUiRecordNameProperty()
{
    delete ui;
}

void TypeUiRecordNameProperty::SetValue( QString value )
{
    ui->LineEdit->setText( value );
}

QString TypeUiRecordNameProperty::Value()
{
    return ui->LineEdit->text();
}


void TypeUiRecordNameProperty::OnReturnPressed()
{
    if( !QRegExp( "[A-Za-z][\\w.]+" ).exactMatch( ui->LineEdit->text() ) )
    {
        TypeController::Message( tr( "Bad record name" ) );
        return;
    }

    OnApplyChanges();
}

