#ifndef C_RECORD_STRUCT_H
#define C_RECORD_STRUCT_H

#include "FW/variant.h"
#include "FW/macro.h"

class C_Record;
class C_RecordFactory;
class C_StateReader;
class C_StateWriter;

class C_RecordStruct : public C_VariantStruct
{
public:

    explicit C_RecordStruct( QString name, C_Variant* parent = 0 );
    ~C_RecordStruct() override;

    C_Record*                          CreateRecord( C_StateWriter& state, int position = -1 );
    C_Record*                          CreateRecord( QString name, QString value, QString class_name, int position = -1 );
    C_Record*                          CreateRecord(C_StateWriter& state, iterator position );
    C_Record*                          CreateRecord(QString name, QString value, QString class_name, iterator position );

    C_Record*                          FromIndex( int row ) const;
    C_Record*                          FromName( QString name , bool deep = false ) const;
    C_Record*                          FromId( QString record_id, bool deep = false ) const;
    int                                GetIndex( C_Record* record ) const;
    C_Record*                          FromFullName(QString name) const;

    static
    C_RecordFactory*                   FactoryFromName( QString class_name );

    static
    const QList<C_RecordFactory*>&     FactoryList() ;

    static
    void                               InitFactoryList();
    QString                            FullName();
    ATR_VALUE                          ( Name, QString )
    ATR_VALUE                          ( Flags, long )

private:

    static
    QList<C_RecordFactory*>             m_FactoryList;
};


#endif // C_RECORD_STRUCT_H
