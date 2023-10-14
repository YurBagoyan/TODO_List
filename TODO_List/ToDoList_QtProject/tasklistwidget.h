#ifndef TASKLISTWIDGET_H
#define TASKLISTWIDGET_H

#include "taskItemWidget.h"
#include "calendarwidget.h"

#include <QObject>
#include <QListWidget>
#include <QWheelEvent>
#include <QScrollBar>

class TaskListWidget : public QListWidget
{
    Q_OBJECT
public:
    TaskListWidget(QWidget* parent = nullptr);

    void setupNoTaskLabel();
    void setAllShowed(const bool allshowed) { isAllShowed = allshowed; } ;
    void setCalendar(CalendarWidget* calendarWidget) { m_calendarWidget = calendarWidget;};
    void addNewTask(TaskItemWidget* newTask);
    void toggleNoTask(bool noTasksForDate);

    void handleListWidgetItemDoubleClicked(QListWidgetItem* item);
    void handleDeleteingTask(const int row);
    void handleNewTaskAdd();

private:
    void wheelEvent(QWheelEvent *event) override;

private:
    CalendarWidget* m_calendarWidget;
    QLabel* noTasksLabel;

    bool isAllShowed = true;
    const int widgetDefaultHeight = 70;
};

#endif // TASKLISTWIDGET_H
