#include "FW/UI/ui_main_window.h"
#include <QApplication>
#include <QDir>
#include "FW/config.h"
#include "FW/document.h"
#include "FW/RC/record_struct.h"
#include "FW/SC/scene.h"

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );

    // Controller is an interface between user interface
    // and model data framework

    C_Controller controller;

    // Config loads and saves scurrent app configuration

    C_Config config( QDir().canonicalPath(), &controller );
    controller.SetConfig( config );
    controller.Config().Load();

    // Document is the frame for all work related to model
    // data

    C_Document document( controller, "", "", &controller );
    controller.SetDocument( document );

    // We check config is ok

    bool config_ok =
        QFileInfo( controller.Config().ProjectPath() ).exists() &&
        QFileInfo( controller.Config().ProjectFileFullName() ).exists();

    if( !config_ok )
    {
        // Create an empty document

        controller.Config().SetProjectPath( "");
        controller.Config().SetProjectFileName( "" );

        C_Record* string_record =
            controller.Document().Root().CreateRecord(
                "SampleString",
                "Welcome to JS Blocks.\nThis is a sample string",
                "String"
            );

        controller.Document().Scene().CreateItem( *string_record );
    }
    else
    {
        // Load document and change path

        QDir().setCurrent( controller.Config().ProjectPath() );

        if( controller.Config().ProjectFileName().split( "." ).back() == "prj" )
            controller.Document().LoadFile( controller.Config().ProjectFileFullName() );

        else if( controller.Config().ProjectFileName().split( "." ).back() == "sql" )
            controller.Document().LoadSQL( controller.Config().ProjectFileFullName() );
    }

    // Main window

    C_UiMainWindow window( controller );
    window.show();

    return a.exec();
}
