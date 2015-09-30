#ifndef STRUCTRECORD_H
#define STRUCTRECORD_H

#include "FW/RC/record.h"
#include "FW/BK/html_block_stream.h"

class TypeStruct;
class TypeStateWriter;
class TypeStateReader;
class TypeController;

class TypeStructRecord : public TypeRecord
{
public:

    explicit TypeStructRecord( TypeStateWriter& state, TypeVariant* Parent = 0 );
    TypeStructRecord( QString id, QString name, QString value, TypeVariant* Parent = 0 );
    ~TypeStructRecord() override;

    TypeStruct*                             Struct() const override;
    void                                    Html( TypeHtmlBlockStream& block_stream, long role, TypeStruct& root) override;

    bool                                    GetState( TypeStateReader& state ) override;
    bool                                    SetState( TypeStateWriter& state ) override;
    QWidget*                                PropertyWidget( TypeController& controller ) override;

    void                                    SetValue( const QString& value ) override;
    const QString&                          Value() const override;
    QString&                                Value() override;

private:

    TypeStruct*                             m_Struct;

    friend class                            TypeUiStructEditor;
    friend class                            TypeStructRecordFactory;
};

class TypeStructRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS                         ( TypeStructRecordFactory )

    TypeStructRecordFactory();

    TypeRecord*                             NewInstance( QString name, QString value, TypeVariant* parent = 0 ) override;
    TypeRecord*                             NewInstance( TypeStateWriter& table, TypeVariant* parent = 0 ) override;

};

#endif // STRUCTRECORD_H
