#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/SC/scene.h"
#include "FW/UI/ui_add_record.h"
#include "FW/RC/reference_record.h"
#include "ui_addrecord.h"
#include <QMessageBox>
#include <QStringListModel>

C_UiAddRecord::C_UiAddRecord( C_Document& document, int index, QWidget* parent ) :
    QDialog( parent ),
    m_Document( &document ),
    ui( new Ui::C_UiAddRecord )
{
    ui->setupUi( this );

    QStringListModel* model = new QStringListModel( this );
    QStringList string_list;

    for( C_RecordFactory* record_factory : C_RecordStruct::FactoryList() )
        string_list << record_factory->RecordClass();

    model->setStringList( string_list );
    ui->ListView->setModel( model );
    ui->ListView->setCurrentIndex( model->index( 0 ) );

    int index_max =
        Document()
        .Context()
        .Records()
        .Size();

    if( index < 0 )
        index = index_max;

    ui->SpinBox->setMaximum( index_max );
    ui->SpinBox->setMinimum( 0 );
    ui->SpinBox->setValue( index  );
    ui->LineEdit->setText( "" );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiAddRecord::OnButtonBoxAccepted );

    connect(
        ui->EditButton,
        QPushButton::clicked,
        this,
        C_UiAddRecord::OnEditButtonClicked );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::rejected,
        this,
        C_UiAddRecord::OnButtonBoxRejected );
}

C_UiAddRecord::~C_UiAddRecord()
{
    delete ui;
}

bool C_UiAddRecord::CheckFormData() const
{
    int index = ui->SpinBox->value();

    int index_max =
        Document()
        .Context()
        .Records()
        .Size();

    if ( ( index > index_max ) || ( index < 0 ) )
    {
        C_Document::Message( tr( "Position out of bounds" ) );
        return false;
    }

    QString name = ui->LineEdit->text();

    if( name.isEmpty() )
    {
        C_Document::Message( tr( "Name is empty" ) );
        return false;
    }

    if( !name.contains( QRegExp( "^\\S+$" ) ) )
    {
        C_Document::Message( tr( "Name must not contain white spaces" ) );
        return false;
    }

    return true;
}

void C_UiAddRecord::OnButtonBoxAccepted()
{
    if( CheckFormData() )
    {
        auto iter = C_RecordStruct::FactoryList().begin();
        int count = 0;

        while( count < ui->ListView->currentIndex().row() )
        {
            ++iter;
            ++count;
        }

        QString class_name = ( *iter )->RecordClass();
        QString name = ui->LineEdit->text();
        int index = ui->SpinBox->value();

        C_Record* record =
            Document()
            .Context()
            .Records()
            .CreateRecord( name, "", class_name, index, &Document().Root() );

        if( ui->CheckBox->isChecked() )
        {
            Document()
            .Context()
            .Scene()
            .CreateItem( *record );
        }

        emit Document().Events().RecordsChanged();
        close();
    }
}

void C_UiAddRecord::OnEditButtonClicked()
{

    if( CheckFormData() )
    {
        auto iter = C_RecordStruct::FactoryList().begin();
        int count = 0;

        while( count < ui->ListView->currentIndex().row() )
        {
            ++iter;
            ++count;
        }

        QString class_name = ( *iter )->RecordClass();
        QString name = ui->LineEdit->text();
        int index = ui->SpinBox->value();

        C_Record* record =
            Document()
            .Context()
            .Records()
            .CreateRecord( name, "", class_name, index );

        if( ui->CheckBox->isChecked() )
        {
            Document()
            .Context()
            .Scene()
            .CreateItem( *record );
        }

        emit Document().Events().RecordsChanged();
        record->EditProperties( Document() );
        close();
    }
}

void C_UiAddRecord::OnButtonBoxRejected()
{
    close();
}
