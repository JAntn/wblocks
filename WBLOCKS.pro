#-------------------------------------------------
#
# Project created by QtCreator 2015-07-14T23:12:47
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += webkitwidgets

CONFIG   += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WBLOCKS
TEMPLATE = app

HEADERS += main.h \
    FW/RC/record.h \
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
    FW/UI/ui_record_explorer.h \
    FW/UI/ui_record_tablemodel.h \
    FW/UI/ui_sceneitem_contextmenu.h \
    FW/clipboard.h \
    FW/config.h \
    FW/context.h \
    FW/controller.h \
    FW/database.h \
    FW/document.h \
    FW/BK/html_builder.h \
    FW/tools/macro.h \
    FW/tools.h \
    FW/variant.h \
    FW/variant_struct.h \
    FW/RC/struct.h \
    FW/RC/root_struct.h \
    FW/tools/variant_ptr.h \
    FW/tools/unique_ptr.h \
    FW/ST/state_flags.h \
    FW/tools/property_macro.h \
    FW/UI/ED/ui_html_text_view.h \
    FW/BK/html_block.h \
    FW/BK/html_block_stream.h \
    FW/UI/PR/ui_label_property.h \
    FW/UI/ui_record_contextmenu.h \
    FW/UI/PR/ui_combo_property.h \
    FW/UI/ui_file_contextmenu.h \
    FW/RC/record_flags.h \
    FW/UI/PR/ui_valueopen_property.h



SOURCES += main.cpp \
    FW/RC/record.cpp \
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
    FW/UI/ui_record_explorer.cpp \
    FW/UI/ui_record_tablemodel.cpp \
    FW/UI/ui_sceneitem_contextmenu.cpp \
    FW/clipboard.cpp \
    FW/config.cpp \
    FW/context.cpp \
    FW/controller.cpp \
    FW/database.cpp \
    FW/document.cpp \
    FW/tools.cpp \
    FW/variant.cpp \
    FW/variant_struct.cpp \
    FW/RC/struct.cpp \
    FW/RC/root_struct.cpp \
    FW/UI/ED/ui_html_text_view.cpp \
    FW/BK/html_block.cpp \
    FW/BK/html_block_stream.cpp \
    FW/UI/PR/ui_label_property.cpp \
    FW/UI/ui_record_contextmenu.cpp \
    FW/UI/PR/ui_combo_property.cpp \
    FW/UI/ui_file_contextmenu.cpp \
    FW/BK/html_builder.cpp \
    FW/UI/PR/ui_valueopen_property.cpp


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
    FW/UI/PR/linetextproperty.ui \
    FW/UI/PR/labelproperty.ui \
    FW/UI/PR/comboproperty.ui \
    FW/UI/PR/valueopenproperty.ui

DISTFILES += \
    format_code.astylerc \

RESOURCES += \
    resource.qrc







