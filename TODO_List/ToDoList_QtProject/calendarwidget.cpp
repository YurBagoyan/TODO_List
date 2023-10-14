#include "calendarwidget.h"
#include "stylesheets.h"

#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QHeaderView>

#include <QTextCharFormat>
#include <QToolButton>


CalendarWidget::CalendarWidget(QWidget* parent)
    : QCalendarWidget(parent)
{
    setGridVisible(false);
    setSelectionMode(QCalendarWidget::SingleSelection);
    setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
    setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    setNavigationBarVisible(true);
    setDateEditEnabled(true);
    setFocusPolicy(Qt::NoFocus);

    setMinimumDate(QDate(2023, 01, 1));
    setMaximumDate(QDate(2024, 12, 31));

    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    setMinimumSize(QSize(35, 250));

    setStyleSheet(Stylesheet::getStyleSheet(Element::calendar));
    setLocale(QLocale(QLocale::English, QLocale::Armenia));
    setFirstDayOfWeek(Qt::Monday);

    // Create a QTextCharFormat to set the desired background and text color
    QTextCharFormat headerFormat;
    headerFormat.setBackground(QColor("#262526"));  // Set the background color
    headerFormat.setForeground(Qt::white);          // Set the text color
    setHeaderTextFormat(headerFormat);

    // Icons for arrows
    QToolButton *prevMonth = findChild<QToolButton*>("qt_calendar_prevmonth");
    QToolButton *nextMonth = findChild<QToolButton*>("qt_calendar_nextmonth");
    prevMonth->setIcon(QIcon(":Calendar/Icons/leftArrow.png"));
    nextMonth->setIcon(QIcon(":Calendar/Icons/rightArrow.png"));
}

