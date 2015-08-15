#-------------------------------------------------
#
# Project created by QtCreator 2015-07-14T23:12:47
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += webkitwidgets network widgets

CONFIG   += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JSBLOCKS
TEMPLATE = app


HEADERS += \
    FW/macro.h \
    FW/RC/record.h \
    FW/SC/scene.h \
    FW/document.h \
    FW/RC/integer_record.h \
    FW/RC/struct_record.h \
    FW/SC/scene_item.h \
    FW/UI/ui_add_record.h \
    FW/UI/ui_find_record.h \
    FW/UI/ui_integer_editor.h \
    FW/UI/ui_main_window.h \
    FW/UI/ui_record_table_model.h \
    FW/database.h \
    FW/UI/ui_scene_item_context_menu.h \
    FW/UI/ui_record_context_menu.h \
    FW/context.h \
    FW/script.h \
    FW/UI/ui_string_editor.h \
    FW/RC/string_record.h \
    FW/UI/ui_struct_editor.h \
    FW/RC/real_record.h \
    FW/UI/ui_real_editor.h \
    FW/variant.h \
    FW/variant_struct.h \
    FW/UI/ui_script_editor.h \
    FW/RC/record_struct.h \
    FW/RC/script_record.h \
    FW/RC/bool_record.h \
    FW/UI/ui_bool_editor.h \
    FW/UI/ui_record_struct_view.h \
    FW/clipboard.h \
    FW/ST/state_reader_table.h \
    FW/ST/state_reader.h \
    FW/ST/state_writer.h \
    FW/ST/state_writer_table.h \
    FW/ST/state_reader_stream.h \
    FW/ST/state_writer_stream.h \
    FW/ST/state_reader_database.h \
    FW/ST/state_writer_database.h \
    FW/RC/reference_record.h \
    FW/UI/ui_reference_editor.h \
    FW/events.h



SOURCES += \
    main.cpp \
    FW/RC/record.cpp \
    FW/document.cpp \
    FW/SC/scene.cpp \
    FW/RC/integer_record.cpp \
    FW/RC/struct_record.cpp \
    FW/SC/scene_item.cpp \
    FW/UI/ui_add_record.cpp \
    FW/UI/ui_find_record.cpp \
    FW/UI/ui_integer_editor.cpp \
    FW/UI/ui_main_window.cpp \
    FW/UI/ui_record_table_model.cpp \
    FW/database.cpp \
    FW/UI/ui_scene_item_context_menu.cpp \
    FW/UI/ui_record_context_menu.cpp \
    FW/context.cpp \
    FW/script.cpp \
    FW/UI/ui_string_editor.cpp \
    FW/RC/string_record.cpp \
    FW/UI/ui_struct_editor.cpp \
    FW/RC/real_record.cpp \
    FW/UI/ui_real_editor.cpp \
    FW/variant.cpp \
    FW/variant_struct.cpp \
    FW/UI/ui_script_editor.cpp \
    FW/RC/record_struct.cpp \
    FW/RC/script_record.cpp \
    FW/RC/bool_record.cpp \
    FW/UI/ui_bool_editor.cpp \
    FW/UI/ui_record_struct_view.cpp \
    FW/clipboard.cpp \
    FW/ST/state_reader_table.cpp \
    FW/ST/state_reader.cpp \
    FW/ST/state_writer.cpp \
    FW/ST/state_writer_table.cpp \
    FW/ST/state_reader_stream.cpp \
    FW/ST/state_writer_stream.cpp \
    FW/ST/state_reader_database.cpp \
    FW/ST/state_writer_database.cpp \
    FW/RC/reference_record.cpp \
    FW/UI/ui_reference_editor.cpp \
    FW/events.cpp

FORMS += \
    FW/UI/addrecord.ui \
    FW/UI/findrecord.ui \
    FW/UI/integereditor.ui \
    FW/UI/stringeditor.ui \
    FW/UI/mainwindow.ui \
    FW/UI/structeditor.ui \
    FW/UI/realeditor.ui \
    FW/UI/booleditor.ui \
    FW/UI/scripteditor.ui \
    FW/UI/recordstructview.ui \
    FW/UI/referenceeditor.ui

DISTFILES += \
    format_code.astylerc





