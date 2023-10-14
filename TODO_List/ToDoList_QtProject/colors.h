#ifndef COLORS_H
#define COLORS_H

#include <QString>

enum Color { main_window_background,
             program_name_TODO,
             program_name_list,
             add_button,
             no_task_label,
             left_widget,
             list_widget_background,
             task_item_background,
             task_item_border,
             task_item_selected,
             task_item_hover,
             task_name,
             task_date,
             check_box_border,
             check_box_checked,
             check_box_unchecked,
             tool_button_background,
             tool_button_hover,
             tool_button_menu_background,
             tool_button_menu_selected,
             calendar_background,
             calendar_item,
             calendar_menu,
             calendar_menu_selected,
             edit_widget_items_background,
             edit_widget_text_color,
             edit_widget_text_color_focused,

             edit_name_line,
             edit_date,
             edit_description_browser,
             edit_save_button,
             edit_cancel_button,

             filter_label,
             filter_button_background,
             filter_button_indicator

};

static QString getColor(const Color color)
{
    switch (color) {
    case main_window_background: return "#141214;";
    case program_name_TODO: return "#f7c667;";
    case program_name_list: return "white;";
    case add_button: return "#262526;";
    case no_task_label: return "gray;";
    case left_widget: return "#262526;";
    case list_widget_background: return "#141214;";
    case task_item_background: return "#262526;";
    case task_item_border: return "transparent;";
    case task_item_selected: return "#f7c667;";
    case task_item_hover: return "";
    case task_name: return "white;";
    case task_date: return "gray;";
    case check_box_border: return "#f7c667;";
    case check_box_checked : return "#f7c667;";
    case check_box_unchecked: return "transparent;";
    case tool_button_background: return "#262526;" ;
    case tool_button_hover: return "#262526;" ;
    case tool_button_menu_background: return "#262526;" ;
    case tool_button_menu_selected: return "#f7c667;";
    case calendar_background: return "#262526;";
    case calendar_item: return "#f7c667;";
    case calendar_menu: return "#262526;";
    case calendar_menu_selected: return "#f7c667;";
    case edit_widget_items_background: return "#141214;";
    case edit_widget_text_color: return "gray;";
    case edit_widget_text_color_focused: return "white;";
    case edit_description_browser: return "#141214;";
    case edit_save_button: return "#141214;";
    case edit_cancel_button: return "#141214;";
    case filter_label: return "white;";
    case filter_button_background: return "#141214;";
    case filter_button_indicator: return "#f7c667;";

    default: return "";
    }
}




#endif // COLORS_H
