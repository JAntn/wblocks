#ifndef MACRO_H
#define MACRO_H


#define C_SINGLETON_CLASS(__CLASS_NAME)     __CLASS_NAME(__CLASS_NAME const&) = delete;\
                                            void operator=(__CLASS_NAME const&)  = delete;\
                                            __CLASS_NAME(){}\
                                            static __CLASS_NAME& Instance() { static __CLASS_NAME singleton; return singleton; }

#define C_POINTER(__VAR_NAME,__VAR_TYPE)\
                                           private:\
                                           __VAR_TYPE* m_##__VAR_NAME;\
                                           public:\
                                           __VAR_TYPE& __VAR_NAME() const {return *m_##__VAR_NAME;}\
                                           void Set##__VAR_NAME(__VAR_TYPE& __ARG) { m_##__VAR_NAME = &__ARG;}

#define C_CONST_POINTER(__VAR_NAME,__VAR_TYPE)\
                                           private:\
                                           __VAR_TYPE* m_##__VAR_NAME;\
                                           public:\
                                           const __VAR_TYPE& __VAR_NAME() const {return *m_##__VAR_NAME;}

#define C_VALUE(__VAR_NAME,__VAR_TYPE)\
                                           private:\
                                           __VAR_TYPE m_##__VAR_NAME;\
                                           public:\
                                           const __VAR_TYPE& __VAR_NAME() const {return m_##__VAR_NAME;}\
                                           __VAR_TYPE& __VAR_NAME() {return m_##__VAR_NAME;}\
                                           void Set##__VAR_NAME(const __VAR_TYPE& __ARG) { m_##__VAR_NAME = __ARG;}

#define C_CONST_VALUE(__VAR_NAME,__VAR_TYPE)\
                                           private:\
                                           __VAR_TYPE m_##__VAR_NAME;\
                                           public:\
                                           const __VAR_TYPE& __VAR_NAME() const {return m_##__VAR_NAME;}


#include <list>
using std::list;

#define FLAG_ALL          0xFF
#define FLAG_ADD          0x01
#define FLAG_REMOVE       0x02
#define FLAG_EDIT         0x04
#define FLAG_ADD_SCENE    0x08
#define FLAG_REMOVE_SCENE 0x10

#endif // MACRO

