#include "FW/UI/PR/ui_file_property.h"
#include "ui_fileproperty.h"
#include <QFileDialog>

C_UiFileProperty::C_UiFileProperty( QString tag_name, QString value, on_changed_t on_changed, QWidget* parent ):
    C_UiProperty( on_changed, parent ),
    ui( new Ui::C_UiFileProperty )
{
    ui->setupUi( this );

    ui->Label->setText( tag_name );
    ui->LineEdit->setText( value );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        C_UiFileProperty::OnReturnPressed
    );

    connect(
        ui->SelectButton,
        QPushButton::clicked,
        this,
        C_UiFileProperty::OnSelectButtonClicked
    );
}

C_UiFileProperty::~C_UiFileProperty()
{
    delete ui;
}

QString C_UiFileProperty::Value()
{
    return ui->LineEdit->text();
}

void C_UiFileProperty::SetValue(QString value)
{
    ui->LineEdit->setText(value);
}

void C_UiFileProperty::OnReturnPressed()
{
    OnApplyChanges();
}

void C_UiFileProperty::OnSelectButtonClicked()
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
    OnApplyChanges();
}


