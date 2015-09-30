#include "FW/config.h"
#include "FW/tools.h"
#include "FW/controller.h"

TypeConfig::TypeConfig( QString config_path, TypeVariant* parent ):
    TypeVariant( parent )
{
    m_ConfigPath = config_path;

    if( !config_path.isEmpty() )
        m_ConfigFileName = config_path + "/config.cfg";
    else
        m_ConfigFileName = "config.cfg";
}

QString EMPTY_CONFIGURATION_TEXT()
{
    QStringList config_file_tokens;

    config_file_tokens << "project_file=\n"
                       << "project_path=\n";

    return config_file_tokens.join( "" );
}

void TypeConfig::Load()
{
    qDebug() << "Loading configuration..";

    if( !QFileInfo( ConfigFileName() ).exists() )
        TypeController::SaveTextFile( ConfigFileName() , EMPTY_CONFIGURATION_TEXT() );

    QStringList token_list =
        TypeController::LoadTextFile( ConfigFileName() ).split( "\n" );

    for( QString token_row : token_list )
    {
        QStringList token = token_row.split( "=" );

        if( token[0] == "project_path" )
            m_ProjectPath = token[1];

        else if( token[0] == "project_file" )
            m_ProjectFileName = token[1];
    }

    qDebug() << "Configuration loaded";
}

void TypeConfig::Save()
{
    QStringList tokens_list;

    tokens_list << "project_file=" << ProjectFileName() << "\n";
    tokens_list << "project_path=" << ProjectPath() << "\n";

    TypeController::SaveTextFile(
        ConfigFileName(),
        tokens_list.join( "" )
    );
}





