#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/SC/scene.h"
#include "FW/UI/ui_add_record.h"
#include "FW/RC/reference_record.h"
#include "ui_addrecord.h"
#include <QMessageBox>
#include <QStringListModel>

C_UiAddRecord::C_UiAddRecord( C_Controller& controller, C_Context& context, int index, QWidget* parent ) :
    QDialog( parent ),
    m_Context( &context ),
    m_Controller( &controller ),
    ui( new Ui::C_UiAddRecord )
{
    ui->setupUi( this );

    QStringListModel* model = new QStringListModel( this );
    QStringList class_list;

    for( C_RecordFactory* record_factory : C_RecordStruct::FactoryList() )
        class_list << record_factory->RecordClass();

    model->setStringList( class_list );
    ui->ListView->setModel( model );
    ui->ListView->setCurrentIndex( model->index( 0 ) );
    ui->SpinBox->setMaximum( ( index < 0 ) ? Context().Records().Size() : index );
    ui->SpinBox->setMinimum( 0 );
    ui->SpinBox->setValue( index  );
    ui->LineEdit->setText( "" );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiAddRecord::OnButtonBoxAccepted );

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

    if ( ( index > Context().Records().Size() ) || ( index < 0 ) )
    {
        C_Controller::Message( tr( "Position out of bounds" ) );
        return false;
    }

    if( !QRegExp( "[A-Za-z][\\w.]+" ).exactMatch( ui->LineEdit->text() ) )
    {
        C_Controller::Message( tr( "Bad record name" ) );
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

        C_Record* record = Context().Records().CreateRecord(
                               name, "", class_name, index, &Context().Root() );

        if( ui->CheckBox->isChecked() )
            Context().Scene().CreateItem( *record );

        Controller().SetPropertyWidgetRecord( *record );
        emit Controller().RecordsChanged();
        close();
    }
}


void C_UiAddRecord::OnButtonBoxRejected()
{
    close();
}
