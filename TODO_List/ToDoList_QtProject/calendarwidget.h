#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QObject>
#include <QCalendarWidget>

class CalendarWidget : public QCalendarWidget
{
public:
    CalendarWidget(QWidget* parent = nullptr);
};

#endif // CALENDARWIDGET_H
