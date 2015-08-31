#include "FW/config.h"
#include <QFile>
#include <QDir>

TypeConfig::TypeConfig( QString config_path, TypeVariant* parent ):
    TypeVariant( parent )
{
    m_ConfigPath = config_path;
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
    QString config_file_name = ConfigFileName();

    if( !ConfigPath().isEmpty() )
        config_file_name.prepend( ConfigPath() + "/" );

    if( !QFileInfo( config_file_name ).exists() )
        TypeController::SaveTextFile( config_file_name , EMPTY_CONFIGURATION_TEXT() );

    QStringList config_file_tokens;
    config_file_tokens = TypeController::LoadTextFile( config_file_name ).split( "\n" );

    for( QString token_row : config_file_tokens )
    {
        QStringList token = token_row.split( "=" );

        if( token[0] == "project_path" )
            m_ProjectPath = token[1];

        else if( token[0] == "project_file" )
            m_ProjectFileName = token[1];
    }
}

void TypeConfig::Save()
{
    QStringList config_file_tokens;
    QString config_file_name =  ConfigFileName();

    if( !ConfigPath().isEmpty() )
        config_file_name.prepend( ConfigPath() + "/" );

    config_file_tokens << "project_file=" << m_ProjectFileName << "\n";
    config_file_tokens << "project_path=" << m_ProjectPath << "\n";

    TypeController::SaveTextFile(
        config_file_name,
        config_file_tokens.join( "" )
    );
}

QString TypeConfig::ConfigFileFullName()
{
    QString config_file_name =  ConfigFileName();

    if( !ConfigPath().isEmpty() )
        config_file_name.prepend( ConfigPath() + "/" );

    return config_file_name;
}

QString TypeConfig::ProjectFileFullName()
{
    QString project_file_name =  ProjectFileName();

    if( !ProjectPath().isEmpty() )
        project_file_name.prepend( ProjectPath() + "/" );

    return project_file_name;
}

