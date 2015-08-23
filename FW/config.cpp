#include "FW/config.h"
#include <QFile>
#include <QDir>

C_Config::C_Config( QString config_path, C_Variant* parent ):
    C_Variant( parent )
{
    m_ConfigPath = config_path;
    m_ConfigFileName = "config.cfg";
}

void C_Config::Load()
{
    QStringList cfg;
    QString config_file = ConfigPath() + "/" + ConfigFileName();

    if( !QFileInfo( config_file ).exists() )
    {
        cfg << "project_file=\n"
            << "project_path=\n";

        C_Document::SaveTextFile( config_file , cfg.join( "" ) );
        cfg.clear();
    }

    cfg = C_Document::LoadTextFile( config_file ).split( "\n" );

    for( QString row : cfg )
    {
        QStringList token = row.split( "=" );

        if( token[0] == "project_path" )
            m_ProjectPath = token[1];

        else if( token[0] == "project_file" )
            m_ProjectFileName = token[1];
    }
}

void C_Config::Save()
{
    QStringList cfg;
    QString config_file = ConfigPath() + "/" + ConfigFileName();

    cfg << "project_file=" << m_ProjectFileName << "\n";
    cfg << "project_path=" << m_ProjectPath << "\n";

    C_Document::SaveTextFile(
        config_file,
        cfg.join( "" )
    );
}

QString C_Config::ConfigFileFullName()
{
    return ConfigPath() + "/" + ConfigFileName();
}

QString C_Config::ProjectFileFullName()
{
    return ProjectPath() + "/" + ProjectFileName();
}

