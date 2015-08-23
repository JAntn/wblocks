#ifndef C_DATABASE_H
#define C_DATABASE_H
#include "FW/variant.h"
#include "FW/macro.h"

#include <QString>
#include <QObject>

class C_Database : public C_Variant
{

public:

    C_Database( C_Variant* parent = 0 );
    ~C_Database() override;

    void                OpenDatabase( QString file_name );
    void                CloseDatabase();
    QString             GetDatabaseName();
    void                CreateTable( QString class_name, QStringList field_list );
    void                RemoveTable( QString class_name );
    void                AppendRecord( QString class_name, QStringList value_list );
    void                RemoveRecord( QString class_name, QString field, QString value );
    bool                TableExists( QString class_name );
    bool                RecordExists( QString class_name, QString field, QString value );
    QStringList         GetRecord( QString class_name, QString field, QString value );
    int                 RowCount( QString class_name );
};

#endif // C_DATABASE_H
