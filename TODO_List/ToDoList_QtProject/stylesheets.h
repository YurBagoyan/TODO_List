#ifndef STYLESHEETS_H
#define STYLESHEETS_H

#include "colors.h"

#include <QString>

enum Element { mainWindow,
               programName_TODO,
               programName_list,
               addButton,
               leftWidget,
               listWidget,
               calendar,
               checkBox,
               taskName,
               taskDate,
               taskToolButton,
               taskNameEditLine,
               taskDateEdit,
               taskDescriptionEditBrowser,
               taskSaveButton,
               taskCancelButton,
               filterButtton
};

namespace Stylesheet {

static QString getStyleSheet(const Element element)
{

    switch (element) {


    case mainWindow:
        return ("QMainWindow { "
                "   background-color: " + getColor(Color::main_window_background) +
                "}");

    case programName_TODO:
        return ("color: " + getColor(Color::program_name_TODO));

    case programName_list:
        return ("color: " + getColor(Color::program_name_list));

    case addButton:
        return ("QPushButton{"
                "   background-color: " + getColor(Color::add_button) +
                "   border-radius: 10px;"
                "   color: white;"
                "   padding: 1px 3px;"
                "   font-size: 40px;"
                "}");

    case leftWidget:
        return ("QWidget {"
                "   background-color: " + getColor(Color::left_widget) +
                "   border-radius: 15px;"
                "}");

    case listWidget:
        return ("QListWidget {"
                "    background-color:" + getColor(Color::list_widget_background) +
                "    border: none; "
                "}"
                ""
                "QListWidget::item {"
                "   background-color: "  + getColor(Color::task_item_background) +
                "   border-radius: 10px;"
                "   border: 1px solid "  + getColor(Color::task_item_border) +
                "   color: white;"
                "}"
                ""
                "QListWidget::item:selected {"
                "   border: 2px solid " + getColor(Color::task_item_selected) +
                "}"
                ""
                "QListWidget::item:hover {"
                "   background-color: "  + getColor(Color::task_item_hover) +
                "}");

    case calendar:
        return ("QCalendarWidget {"
                "   background-color: " + getColor(Color::calendar_background) +
                "}"
                ""
                ""
                "QCalendarWidget QAbstractItemView::item:selected {"
                "   background-color: "  + getColor(Color::calendar_item) +
                "   border-radius: 15px;"
                "   color: black;"
                "}"
                ""
                "QCalendarWidget QAbstractItemView::item:hover {"
                "   border: 1px solid "  + getColor(Color::calendar_item) +
                "   border-radius: 15px;"
                "}"
                "QCalendarWidget QWidget { "
                "   alternate-background-color: #141214;"
                "}"
                "QCalendarWidget QAbstractItemView:enabled {"
                "   font-size: 15px;"
                "   color: white;  "
                "   background-color:" + getColor(Color::calendar_background) +
                "}"
                ""
                "QCalendarWidget QWidget#qt_calendar_navigationbar {"
                "   background-color: " + getColor(Color::calendar_background) +
                "}"
                ""
                "QCalendarWidget QMenu {"
                "    left: 20px;"
                "    color: white;"
                "    font-size: 14px;"
                "    background-color: " + getColor(Color::calendar_menu) +
                "}"
                ""
                "QCalendarWidget QMenu::item:selected {"
                "   background-color: gray; "
                "   color: " + getColor(Color::calendar_menu_selected) +
                "}"
                ""
                "QCalendarWidget QSpinBox { "
                "   font-size: 18px; "
                "   color: white; "
                "   background-color: " + getColor(Color::calendar_background) +
                "   selection-background-color: gray;"
                "}"
                ""
                "QCalendarWidget QSpinBox::up-button { subcontrol-origin: border;  subcontrol-position: top right;  }"
                "QCalendarWidget QSpinBox::down-button { subcontrol-origin: border; subcontrol-position: bottom right;  } "
                ""
                "QCalendarWidget QToolButton {"
                "   background-color: transparent; "
                "   margin: 2px;"
                "   font-size: 18px;  "
                "   color: white; "
                "}"
                "QCalendarWidget QToolButton::menu-indicator {"
                "    image: none;"
                "}"
                "QCalendarWidget QToolButton:hover {"
                "   background-color: #555555; "
                "}"
                ""
                "QCalendarWidget QToolButton::pressed {"
                "   background-color: " + getColor(Color::calendar_item) +
                "   color: black;"
                "}");

    case taskName:
        return ("color: " +  getColor(Color::task_name));

    case taskDate:
        return ("color: " + getColor(Color::task_date));

    case checkBox:
        return ("QCheckBox {"
                "    spacing: 10px;"
                "}"
                ""
                "QCheckBox::indicator {"
                "    width: 20px; "
                "    height: 20px; "
                "}"
                ""
                "QCheckBox::indicator:unchecked {"
                "    border: 2px solid "  + getColor(Color::check_box_border) +
                "    background-color: "  + getColor(Color::check_box_unchecked) +
                "    border-radius: 10px; "
                "}"
                ""
                "QCheckBox::indicator:checked {"
                "    border: 2px solid "  + getColor(Color::check_box_border) +
                "    background-color: "  + getColor(Color::check_box_checked) +
                "    border-radius: 10px; "
                "}");

    case taskToolButton:
        return ("QToolButton {\n"
                "    background-color: " + getColor(Color::tool_button_background) +
                "    color: " + getColor(Color::edit_widget_text_color) +
                "    border: none; "
                "}"
                ""
                "QToolButton::menu-indicator {"
                "    image: none;"
                "}"
                ""
                "QToolButton:hover {"
                "    background-color: " + getColor(Color::tool_button_hover) +
                "	 color: #f7c667;"
                "}"
                ""
                "QMenu {"
                "    background-color: " + getColor(Color::tool_button_menu_background) +
                "    color: white;"
                "}"
                ""
                "QMenu::item {"
                "   font-size: 16px;"
                "   padding: 5px 20px;"
                "}"
                ""
                "QMenu::item:selected {"
                "    color: " + getColor(Color::tool_button_menu_selected) +
                "}");


    case taskNameEditLine:
        return ("QLineEdit {"
                "   background-color: " + getColor(Color::edit_widget_items_background) +
                "   color: " + getColor(Color::edit_widget_text_color) +
                "   border-radius: 5px;"
                "   padding: 5px;"
                "   selection-background-color: darkgray;"
                "}"
                ""
                "QLineEdit:focus {"
                "   color: " + getColor(Color::edit_widget_text_color_focused) +
                "   border: 1px solid #f7c667;"
                "}"
                );

    case taskDateEdit:
        return ("QDateEdit {"
                "   background-color: "  + getColor(Color::edit_widget_items_background) +
                "   color: " + getColor(Color::edit_widget_text_color) +
                "   border-radius: 5px;"
                "   padding: 5px;"
                "   selection-background-color: darkgray;"
                "}"
                ""
                "QDateEdit:focus {"
                "   border: 1px solid #f7c667;"
                "   color: " + getColor(Color::edit_widget_text_color_focused) +
                "}");

    case taskDescriptionEditBrowser:
        return ("QTextBrowser {"
                "   background-color: "  + getColor(Color::edit_widget_items_background) +
                "   border-radius: 5px;"
                "   color: " + getColor(Color::edit_widget_text_color) +
                "   font-size: 13px;"
                "   selection-background-color: darkgray;"
                "}"
                ""
                "QTextBrowser:focus {"
                "   border: 1px solid #f7c667;"
                "   color: " + getColor(Color::edit_widget_text_color_focused) +
                "}");

    case taskSaveButton:
        return ("QPushButton{"
                "   background-color: "  + getColor(Color::edit_widget_items_background) +
                "   border-radius: 10px;"
                "   color: white;"
                "   padding: 5px 15px;"
                "   font-size: 16px;"
                "}"
                ""
                "QPushButton:hover {"
                "   border: 1px solid #f7c667;"
                "}"
                "");

    case taskCancelButton:
        return ("QPushButton{"
                "   background-color: "  + getColor(Color::edit_widget_items_background) +
                "   border-radius: 10px;"
                "   color: white;"
                "   padding: 5px 15px;"
                "   font-size: 16px;"
                "}"
                ""
                "QPushButton:hover {"
                "   border: 1px solid #f7c667;"
                "}"
                "");

    case filterButtton:
        return  ("QPushButton {"
                "   color: white;"
                "	border-radius: 5px; "
                "   border: none; "
                "   background: " + getColor(Color::filter_button_background) +
                "   padding: 8px 8px; "
                "   font-size: 18px;"
                "}"
                ""
                "QPushButton:checked {"
                "    border-bottom: 2px solid " + getColor(Color::filter_button_indicator) +
                "}");




    }


    return "";
}


}; //namespace stylesheet


#endif // STYLESHEETS_H
