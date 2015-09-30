#ifndef RECORD_H
#define RECORD_H

#include "FW/tools.h"
#include "FW/RC/record_flags.h"

class TypeUiEditor;
class TypeStruct;
class TypeStateReader;
class TypeStateWriter;
class TypeController;
class TypeHtmlBlockStream;

class TypeRecord : public TypeVariant
{
public:

    static QString                          ParseText( const QString& text, TypeRecord& record, TypeStruct& root );

    explicit TypeRecord( TypeStateWriter& state, TypeVariant* Parent = 0 );
    TypeRecord( QString id, QString name, QString value, TypeVariant* Parent = 0 );
    ~TypeRecord() override;

    virtual bool                            GetState( TypeStateReader& state );
    virtual bool                            SetState( TypeStateWriter& state );
    virtual QWidget*                        PropertyWidget( TypeController& controller );
    virtual TypeUiEditor*                   EditorWidget( QString id, TypeController& controller );

    virtual TypeStruct*                     Struct() const;
    virtual TypeStruct*                     ParentStruct() const;
    virtual TypeRecord*                     ParentRecord() const;

    virtual void                            Html( TypeHtmlBlockStream& block_stream, long role, TypeStruct& root );

    virtual void                            SetValue( const QString& value );
    virtual const QString&                  Value() const;
    virtual QString&                        Value();

    virtual QString                         Property( const QStringList& token_list );

    QString                                 FullName() ;

    M_VALUE_READONLY                        ( Id,    QString )
    M_VALUE                                 ( Name,  QString )
    M_VALUE_READONLY                        ( Class, QString )
    M_VALUE                                 ( Flags, long )

protected:

    QString                                 m_Value;
};

class TypeRecordFactory
{
public:

    SINGLETON_CLASS                         ( TypeRecordFactory )

    TypeRecordFactory();

    virtual TypeRecord*                     NewInstance( QString name, QString value, TypeVariant* parent = 0 );
    virtual TypeRecord*                     NewInstance( TypeStateWriter& state, TypeVariant* parent = 0 );

    static QString                          GenerateId();
    static QString                          IdCount();

    M_VALUE_READONLY                        ( RecordClass, QString )

private:

    static long                             m_IdCount;
    friend class                            TypeDocument;
};

#endif // RECORD_H

#include "FW/RC/root_struct.h"
#include "FW/controller.h"
