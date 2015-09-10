#include "FW/tools.h"
#include "FW/UI/PR/ui_file_property.h"
#include "ui_fileproperty.h"


TypeUiFileProperty::TypeUiFileProperty( QString tag_name, QString value, TypeSaveCallback on_changed, QWidget* parent ):
    TypeUiProperty( on_changed, parent ),
    ui( new Ui::TypeUiFileProperty )
{
    ui->setupUi( this );

    ui->Label->setText( tag_name );
    ui->LineEdit->setText( value );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        TypeUiFileProperty::OnReturnPressed
    );

    connect(
        ui->SelectButton,
        QPushButton::clicked,
        this,
        TypeUiFileProperty::OnSelectButtonClicked
    );
}

TypeUiFileProperty::~TypeUiFileProperty()
{
    delete ui;
}

QString TypeUiFileProperty::Value()
{
    return ui->LineEdit->text();
}

void TypeUiFileProperty::SetValue(QString value)
{
    ui->LineEdit->setText(value);
}

void TypeUiFileProperty::OnReturnPressed()
{
    OnActionSave();
}

void TypeUiFileProperty::OnSelectButtonClicked()
{
    QString file_name =
        QFileDialog::getOpenFileName(
            this,
            tr( "Select a File" ),
            ui->LineEdit->text()
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File not selected" ;
        return;
    }

    ui->LineEdit->setText( file_name );
    OnActionSave();
}


