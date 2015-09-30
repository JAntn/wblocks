#include <QApplication>
#include "FW/tools.h"
#include "FW/controller.h"
#include "FW/UI/ui_main_window.h"
#include "FW/config.h"
#include "FW/document.h"
#include "FW/RC/root_struct.h"
#include "FW/RC/struct_record.h"
#include "FW/SC/scene.h"
#include "FW/BK/html_builder.h"

int main( int argc, char* argv[] )
{
    qDebug() << "Starting Aplication..";

    QApplication a( argc, argv );

    // Controller is an interface between user interface
    // and model data framework

    TypeController controller;

    // Config loads and saves scurrent app configuration

    TypeConfig config( QDir().canonicalPath(), &controller );
    controller.SetConfig( config );
    controller.Config().Load();

    // Document is the frame for all work related to model
    // data

    TypeDocument document( controller, "", "", &controller );
    controller.SetDocument( document );

    // We check config is ok

    bool config_ok = QFileInfo( controller.Config().ProjectFileName() ).exists();

    if( !config_ok )
    {
        // Create an empty document

        qDebug() << "Document file not found. Setting an empty document..";

        controller.Config().SetProjectPath( "" );
        controller.Config().SetProjectFileName( "" );
    }
    else
    {
        // Load document and change path

        qDebug() << "Config file ok";
        qDebug() << "Starting to setup document.. " << controller.Config().ProjectFileName();

        QDir().setCurrent( controller.Config().ProjectPath() );

        if( controller.Config().ProjectFileName().split( "." ).back() == "prj" )
            controller.Document().LoadFile( controller.Config().ProjectFileName() );

        else if( controller.Config().ProjectFileName().split( "." ).back() == "sql" )
            controller.Document().LoadSQL( controller.Config().ProjectFileName() );
    }

    // Build html content

    controller.Document().HtmlBuilder().Build( controller.Document().Root() );

    qDebug() << "Document state builded";

    // Main window

    TypeUiMainWindow window( controller );
    window.show();
    return a.exec();
}
