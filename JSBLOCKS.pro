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
    FW/document.h \
    FW/config.h \
    FW/database.h \
    FW/context.h \
    FW/variant.h \
    FW/variant_struct.h \
    FW/clipboard.h \
    FW/events.h \
    FW/RC/record.h \
    FW/RC/script_file_record.h\
    FW/RC/file_record.h \
    FW/RC/integer_record.h \
    FW/RC/struct_record.h \
    FW/RC/string_record.h \
    FW/RC/real_record.h \
    FW/RC/record_struct.h \
    FW/RC/bool_record.h \
    FW/UI/ui_add_record.h \
    FW/UI/ui_find_record.h \
    FW/UI/ui_main_window.h \
    FW/UI/ui_record_table_model.h \
    FW/UI/ui_scene_item_context_menu.h \
    FW/UI/ui_record_context_menu.h \
    FW/ST/state_reader_table.h \
    FW/ST/state_reader.h \
    FW/ST/state_writer.h \
    FW/ST/state_writer_table.h \
    FW/ST/state_reader_stream.h \
    FW/ST/state_writer_stream.h \
    FW/ST/state_reader_database.h \
    FW/ST/state_writer_database.h \
    FW/RC/reference_record.h \
    FW/UI/ui_record_explorer.h \
    FW/UI/ui_file_explorer.h \
    FW/SC/scene.h \
    FW/SC/scene_line.h \
    FW/SC/scene_item.h \
    FW/UI/ui_text_editor_container.h \
    FW/UI/ui_text_editor.h \
    FW/UI/ui_file_text_editor.h \
    FW/RC/script_record.h \
    FW/UI/ui_record_value_editor.h \
    FW/UI/ui_record_properties.h \
    FW/htmlbuilder.h \
    FW/UI/PR/ui_bool_record_properties.h \
    FW/UI/PR/ui_file_record_properties.h \
    FW/UI/PR/ui_integer_record_properties.h \
    FW/UI/PR/ui_real_record_properties.h \
    FW/UI/PR/ui_record_properties.h \
    FW/UI/PR/ui_reference_record_properties.h \
    FW/UI/PR/ui_script_file_record_properties.h \
    FW/UI/PR/ui_script_record_properties.h \
    FW/UI/PR/ui_string_record_properties.h \
    FW/UI/PR/ui_struct_record_properties.h \
    FW/RC/JS/js_bool_record.h \
    FW/RC/JS/js_integer_record.h \
    FW/RC/JS/js_real_record.h \
    FW/RC/JS/js_reference_record.h \
    FW/RC/JS/js_string_record.h \
    FW/RC/HTML/html_record.h \
    FW/UI/PR/ui_html_record_properties.h


SOURCES += \
    main.cpp \
    FW/document.cpp \
    FW/database.cpp \
    FW/context.cpp \
    FW/variant.cpp \
    FW/config.cpp \
    FW/events.cpp \
    FW/variant_struct.cpp \
    FW/clipboard.cpp \
    FW/RC/string_record.cpp \
    FW/RC/record.cpp \
    FW/RC/integer_record.cpp \
    FW/RC/struct_record.cpp \
    FW/RC/real_record.cpp \
    FW/RC/record_struct.cpp \
    FW/RC/bool_record.cpp \
    FW/RC/reference_record.cpp \
    FW/RC/file_record.cpp \
    FW/RC/script_file_record.cpp \
    FW/SC/scene.cpp \
    FW/SC/scene_item.cpp \
    FW/SC/scene_line.cpp \
    FW/UI/ui_add_record.cpp \
    FW/UI/ui_find_record.cpp \
    FW/UI/ui_main_window.cpp \
    FW/UI/ui_record_table_model.cpp \
    FW/UI/ui_scene_item_context_menu.cpp \
    FW/UI/ui_record_context_menu.cpp \
    FW/UI/ui_file_explorer.cpp \
    FW/UI/ui_record_explorer.cpp \
    FW/ST/state_reader_table.cpp \
    FW/ST/state_reader.cpp \
    FW/ST/state_writer.cpp \
    FW/ST/state_writer_table.cpp \
    FW/ST/state_reader_stream.cpp \
    FW/ST/state_writer_stream.cpp \
    FW/ST/state_reader_database.cpp \
    FW/ST/state_writer_database.cpp \
    FW/UI/ui_text_editor_container.cpp \
    FW/UI/ui_text_editor.cpp \
    FW/UI/ui_file_text_editor.cpp \
    FW/RC/script_record.cpp \
    FW/UI/ui_record_value_editor.cpp \
    FW/htmlbuilder.cpp \
    FW/UI/PR/ui_bool_record_properties.cpp \
    FW/UI/PR/ui_file_record_properties.cpp \
    FW/UI/PR/ui_integer_record_properties.cpp \
    FW/UI/PR/ui_real_record_properties.cpp \
    FW/UI/PR/ui_record_properties.cpp \
    FW/UI/PR/ui_reference_record_properties.cpp \
    FW/UI/PR/ui_script_file_record_properties.cpp \
    FW/UI/PR/ui_script_record_properties.cpp \
    FW/UI/PR/ui_string_record_properties.cpp \
    FW/UI/PR/ui_struct_record_properties.cpp \
    FW/RC/JS/js_bool_record.cpp \
    FW/RC/JS/js_integer_record.cpp \
    FW/RC/JS/js_real_record.cpp \
    FW/RC/JS/js_reference_record.cpp \
    FW/RC/JS/js_string_record.cpp \
    FW/RC/HTML/html_record.cpp \
    FW/UI/PR/ui_html_record_properties.cpp

FORMS += \
    FW/UI/addrecord.ui \
    FW/UI/findrecord.ui \
    FW/UI/mainwindow.ui \
    FW/UI/fileexplorer.ui \
    FW/UI/recordexplorer.ui \
    FW/UI/texteditor.ui \
    FW/UI/PR/boolrecordproperties.ui \
    FW/UI/PR/filerecordproperties.ui \
    FW/UI/PR/integerrecordproperties.ui \
    FW/UI/PR/realrecordproperties.ui \
    FW/UI/PR/recordproperties.ui \
    FW/UI/PR/referencerecordproperties.ui \
    FW/UI/PR/scriptfilerecordproperties.ui \
    FW/UI/PR/scriptrecordproperties.ui \
    FW/UI/PR/stringrecordproperties.ui \
    FW/UI/PR/structrecordproperties.ui \
    FW/UI/PR/htmlrecordproperties.ui

DISTFILES += \
    format_code.astylerc





