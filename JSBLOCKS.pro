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

HEADERS += main.h \
    FW/BK/block.h \
    FW/BK/block_stream.h \
    FW/RC/HTML/html_record.h \
    FW/RC/JS/js_bool_record.h \
    FW/RC/JS/js_integer_record.h \
    FW/RC/JS/js_real_record.h \
    FW/RC/JS/js_reference_record.h \
    FW/RC/JS/js_script_file_record.h \
    FW/RC/JS/js_script_record.h \
    FW/RC/JS/js_string_record.h \
    FW/RC/PHP/php_file_record.h \
    FW/RC/bool_record.h \
    FW/RC/file_record.h \
    FW/RC/integer_record.h \
    FW/RC/real_record.h \
    FW/RC/record.h \
    FW/RC/record_struct.h \
    FW/RC/reference_record.h \
    FW/RC/string_record.h \
    FW/RC/struct_record.h \
    FW/SC/scene.h \
    FW/SC/scene_item.h \
    FW/SC/scene_line.h \
    FW/ST/state_reader.h \
    FW/ST/state_reader_database.h \
    FW/ST/state_reader_stream.h \
    FW/ST/state_reader_table.h \
    FW/ST/state_writer.h \
    FW/ST/state_writer_database.h \
    FW/ST/state_writer_stream.h \
    FW/ST/state_writer_table.h \
    FW/UI/ED/ui_editor.h \
    FW/UI/ED/ui_html_blocks_editor.h \
    FW/UI/ED/ui_text_editor.h \
    FW/UI/PR/ui_bool_property.h \
    FW/UI/PR/ui_file_property.h \
    FW/UI/PR/ui_integer_property.h \
    FW/UI/PR/ui_linetext_property.h \
    FW/UI/PR/ui_property.h \
    FW/UI/PR/ui_real_property.h \
    FW/UI/PR/ui_recordname_property.h \
    FW/UI/PR/ui_string_property.h \
    FW/UI/SH/ui_syntax_highlighter.h \
    FW/UI/SH/ui_syntax_highlighter_factory.h \
    FW/UI/ui_add_record.h \
    FW/UI/ui_editor_container.h \
    FW/UI/ui_file_explorer.h \
    FW/UI/ui_main_window.h \
    FW/UI/ui_record_contextmenu.h \
    FW/UI/ui_record_explorer.h \
    FW/UI/ui_record_tablemodel.h \
    FW/UI/ui_sceneitem_contextmenu.h \
    FW/clipboard.h \
    FW/config.h \
    FW/context.h \
    FW/controller.h \
    FW/database.h \
    FW/document.h \
    FW/htmlbuilder.h \
    FW/macro.h \
    FW/tools.h \
    FW/variant.h \
    FW/variant_struct.h



SOURCES += main.cpp \
    FW/BK/block.cpp \
    FW/BK/block_stream.cpp \
    FW/RC/HTML/html_record.cpp \
    FW/RC/JS/js_bool_record.cpp \
    FW/RC/JS/js_integer_record.cpp \
    FW/RC/JS/js_real_record.cpp \
    FW/RC/JS/js_reference_record.cpp \
    FW/RC/JS/js_script_file_record.cpp \
    FW/RC/JS/js_script_record.cpp \
    FW/RC/JS/js_string_record.cpp \
    FW/RC/PHP/php_file_record.cpp \
    FW/RC/bool_record.cpp \
    FW/RC/file_record.cpp \
    FW/RC/integer_record.cpp \
    FW/RC/real_record.cpp \
    FW/RC/record.cpp \
    FW/RC/record_struct.cpp \
    FW/RC/reference_record.cpp \
    FW/RC/string_record.cpp \
    FW/RC/struct_record.cpp \
    FW/SC/scene.cpp \
    FW/SC/scene_item.cpp \
    FW/SC/scene_line.cpp \
    FW/ST/state_reader.cpp \
    FW/ST/state_reader_database.cpp \
    FW/ST/state_reader_stream.cpp \
    FW/ST/state_reader_table.cpp \
    FW/ST/state_writer.cpp \
    FW/ST/state_writer_database.cpp \
    FW/ST/state_writer_stream.cpp \
    FW/ST/state_writer_table.cpp \
    FW/UI/ED/ui_editor.cpp \
    FW/UI/ED/ui_html_blocks_editor.cpp \
    FW/UI/ED/ui_text_editor.cpp \
    FW/UI/PR/ui_bool_property.cpp \
    FW/UI/PR/ui_file_property.cpp \
    FW/UI/PR/ui_integer_property.cpp \
    FW/UI/PR/ui_linetext_property.cpp \
    FW/UI/PR/ui_property.cpp \
    FW/UI/PR/ui_real_property.cpp \
    FW/UI/PR/ui_recordname_property.cpp \
    FW/UI/PR/ui_string_property.cpp \
    FW/UI/SH/ui_syntax_highlighter.cpp \
    FW/UI/SH/ui_syntax_highlighter_factory.cpp \
    FW/UI/ui_add_record.cpp \
    FW/UI/ui_editor_container.cpp \
    FW/UI/ui_file_explorer.cpp \
    FW/UI/ui_main_window.cpp \
    FW/UI/ui_record_contextmenu.cpp \
    FW/UI/ui_record_explorer.cpp \
    FW/UI/ui_record_tablemodel.cpp \
    FW/UI/ui_sceneitem_contextmenu.cpp \
    FW/clipboard.cpp \
    FW/config.cpp \
    FW/context.cpp \
    FW/controller.cpp \
    FW/database.cpp \
    FW/document.cpp \
    FW/htmlbuilder.cpp \
    FW/tools.cpp \
    FW/variant.cpp \
    FW/variant_struct.cpp


FORMS += \
    FW/UI/addrecord.ui \
    FW/UI/mainwindow.ui \
    FW/UI/fileexplorer.ui \
    FW/UI/recordexplorer.ui \
    FW/UI/ED/texteditor.ui \
    FW/UI/PR/boolproperty.ui \
    FW/UI/PR/stringproperty.ui \
    FW/UI/PR/fileproperty.ui \
    FW/UI/PR/integerproperty.ui \
    FW/UI/PR/realproperty.ui \
    FW/UI/PR/recordnameproperty.ui \
    FW/UI/PR/linetextproperty.ui

DISTFILES += \
    format_code.astylerc \

RESOURCES += \
    resource.qrc







