#include <QApplication>
#include "FW/tools.h"
#include "FW/controller.h"
#include "FW/UI/ui_main_window.h"
#include "FW/config.h"
#include "FW/document.h"
#include "FW/RC/record_struct.h"
#include "FW/SC/scene.h"
#include "FW/htmlbuilder.h"

int main( int argc, char* argv[] )
{
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

    bool config_ok =
        QFileInfo( controller.Config().ProjectPath() ).exists() &&
        QFileInfo( controller.Config().ProjectFileFullName() ).exists();

    if( !config_ok )
    {
        // Create an empty document

        controller.Config().SetProjectPath( "" );
        controller.Config().SetProjectFileName( "" );

        TypeRecord* string_record =
            controller.Document().Root().NewRecord(
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

    // Build html content
    controller.HtmlBuilder().Build( controller.Document().Root() );

    // Main window

    TypeUiMainWindow window( controller );
    window.show();

    return a.exec();
}
