#ifndef PROPERTY_H
#define PROPERTY_H


// TypePropertyBase
// -----------------------------------------------------------------------------------
// Interface to work with properties macro

class TypePropertyBase
{
protected:

    QString m_Name;
    QString m_Type;

public:

    bool    Empty()
    {
        return true;
    }

    QString Name()
    {
        return m_Name;
    }

    QString Type()
    {
        return m_Type;
    }

};

// TypePropertyReturn
// -----------------------------------------------------------------------------------
// Object returned by Property method

class TypePropertyReturn
{
    TypePropertyBase* m_Ptr;

public:

    TypePropertyReturn( TypePropertyBase* ptr )
    {
        m_Ptr = ptr;
    }

    bool Empty()
    {
        return m_Ptr->Empty();
    }

    QString Name()
    {
        return m_Ptr->Name();
    }

    QString Type()
    {
        return m_Ptr->Type();
    }

    const TypePropertyBase* PropertyBase() const
    {
        return m_Ptr;
    }
};


// TypeProperty
// -----------------------------------------------------------------------------------
// Holds information of a class memeber
// It is generated using M_PROPERTY macros

template<typename T>
class TypeProperty : public TypePropertyBase
{

    T* m_Ptr;

public:

    virtual ~TypeProperty() {}


    TypeProperty( T* ptr, QString name, QString type )
    {
        m_Name = name;
        m_Type = type;
        m_Ptr = ptr;
    }

    TypeProperty()
    {
        m_Ptr = 0;
    }

    TypeProperty( const TypeProperty<T>& other )
    {
        m_Name = other.m_Name;
        m_Type = other.m_Type;
        m_Ptr = other.m_Ptr;
    }

    TypeProperty& operator = ( const TypeProperty<T>& other )
    {
        m_Name = other.m_Name;
        m_Type = other.m_Type;
        m_Ptr = other.m_Ptr;

        return *this;
    }


    TypeProperty( const TypePropertyReturn& val )
    {
        const TypeProperty<T>* other =
            static_cast<const TypeProperty<T>*>( val.PropertyBase() );

        m_Name = other->m_Name;
        m_Type = other->m_Type;
        m_Ptr = other->m_Ptr;
    }

    TypeProperty& operator = ( const TypePropertyReturn& val )
    {
        const TypeProperty<T>* other =
            static_cast<const TypeProperty<T>*>( val.PropertyBase() );

        m_Name = other->m_Name;
        m_Type = other->m_Type;
        m_Ptr = other->m_Ptr;

        return *this;
    }

    T* operator->()
    {

#ifdef M_NULLPTR_ACCESS_CHECK

        if( Empty() ) qDebug() << "M_NULLPTR_ACCESS_CHECK:" << "  Null pointer access";

#endif

        return static_cast<T*>( m_Ptr );
    }

    const T* operator->() const
    {

#ifdef M_NULLPTR_ACCESS_CHECK

        if( Empty() ) qDebug() << "M_NULLPTR_ACCESS_CHECK:" << "  Null pointer access";


#endif
        return static_cast<T*>( m_Ptr );
    }

    T& operator*()
    {

#ifdef M_NULLPTR_ACCESS_CHECK

        if( Empty() ) qDebug() << "M_NULLPTR_ACCESS_CHECK:" << "  Null pointer access";

#endif
        return *static_cast<T*>( m_Ptr );
    }

    const T& operator*() const
    {

#ifdef M_NULLPTR_ACCESS_CHECK

        if( Empty() ) qDebug() << "M_NULLPTR_ACCESS_CHECK:" << "  Null pointer access";

#endif
        return *static_cast<T*>( m_Ptr );
    }

    operator T* ()
    {
        return static_cast<T*>( m_Ptr );
    }

    operator const T* () const
    {
        return static_cast<T*>( m_Ptr );
    }

    bool Empty()
    {
        return m_Ptr == 0;
    }
};


//
// M_PROPERTY_TABLE
// --------------------------------------------------------------------------------------------
// Class member property generator
// Properties can be selected through Property(`property_name`) class method
//
// Example:
//
//    class Example
//    {
//        M_PROPERTY_TABLE(
//            M_PROPERTY( value1, int, M_atribute({ return m_value1; }) )
//            M_PROPERTY( value2, double )
//            M_END )
//    public:
//        Example()
//        {
//            TypeProperty<int> a = Property( "value1" );
//            *a = 5;
//
//            TypeProperty<double> b = Property( "value2" );
//            *b = 192375.5;
//
//            cout << *a << *b;
//        }
//    };

#define M_END END_KEY

#define M_PROPERTY_TABLE __hidden_PROPERTY_TABLE
#define M_PROPERTY( name, type) CONTINUE_KEY, name, type

#define __hidden_PROPERTY_TABLE(...)\
    __hidden_declare_M_PROPERTY_TABLE(__VA_ARGS__)\
    __hidden_map_M_PROPERTY_TABLE(__VA_ARGS__)

#define __hidden_declare_M_PROPERTY_TABLE(  ignore, name, type, sep_key0, ...)\
    private: type m_##name;\
    __hidden_declare_##sep_key0##_M_PROPERTY_TABLE(__VA_ARGS__)\

#define __hidden_declare_CONTINUE_KEY_M_PROPERTY_TABLE( ignore, name, type, sep_key0, ...)\
    private: type m_##name;\
    __hidden_declare_##sep_key0##_M_PROPERTY_TABLE(__VA_ARGS__)\

#define __hidden_declare_END_KEY_M_PROPERTY_TABLE(...)\
    /* __hidden_declare_AND_M_PROPERTY_TABLE ends */

#define __hidden_map_M_PROPERTY_TABLE( ignore, name, type, sep_key0, ...)\
    public: TypePropertyReturn Property(QString str) { \
        if(#name == str) {return (TypePropertyBase*)new TypeProperty<type>(&m_##name,#name,#type);}\
        __hidden_map_##sep_key0##_M_PROPERTY_TABLE(__VA_ARGS__)\
        return new TypePropertyBase();\
    }

#define __hidden_map_CONTINUE_KEY_M_PROPERTY_TABLE( ignore, name, type, sep_key0, ...)\
        if(#name == str) {return (TypePropertyBase*)new TypeProperty<type>(&m_##name,#name,#type);}\
        __hidden_map_##sep_key0##_M_PROPERTY_TABLE(__VA_ARGS__)\

#define __hidden_map_END_KEY_M_PROPERTY_TABLE(...)\
    /* __hidden_map_M_PROPERTY_TABLE ends */

#endif // PROPERTY_H

