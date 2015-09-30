#include "FW/UI/PR/ui_valueopen_property.h"
#include "ui_valueopenproperty.h"

TypeUiValueOpenProperty::TypeUiValueOpenProperty( QString tag_name, QString value, TypeSaveCallback on_changed, TypeOpenCallback on_open, QWidget* parent ):
    TypeUiProperty( on_changed, parent ),
    m_OpenCallback( on_open ),
    ui( new Ui::TypeUiValueOpenProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );
    ui->LineEdit->setText( value );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        TypeUiValueOpenProperty::OnReturnPressed
    );

    connect(
        ui->OpenButton,
        QPushButton::clicked,
        this,
        TypeUiValueOpenProperty::OnOpenButtonClicked
    );
}

TypeUiValueOpenProperty::~TypeUiValueOpenProperty()
{
    delete ui;
}

void TypeUiValueOpenProperty::SetValue( QString value )
{
    ui->LineEdit->setText( value );
}

QString TypeUiValueOpenProperty::Value()
{
    return ui->LineEdit->text();
}


void TypeUiValueOpenProperty::OnReturnPressed()
{
    OnActionSave();
}

void TypeUiValueOpenProperty::OnOpenButtonClicked()
{
    m_OpenCallback( *this );
}



