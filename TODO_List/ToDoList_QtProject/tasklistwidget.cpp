#include "tasklistwidget.h"
#include "stylesheets.h"


TaskListWidget::TaskListWidget(QWidget *parent)
    : QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);
    setSpacing(15);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet(Stylesheet::getStyleSheet(Element::listWidget));

    noTasksLabel = new QLabel("You don't have tasks for this date", parent);
    setupNoTaskLabel();
    parent->layout()->addWidget(noTasksLabel);

    connect(this, &QListWidget::itemDoubleClicked, this, &TaskListWidget::handleListWidgetItemDoubleClicked);
}

void TaskListWidget::setupNoTaskLabel()
{
    noTasksLabel->setAlignment(Qt::AlignCenter);
    noTasksLabel->setStyleSheet("color: " + getColor(Color::no_task_label));
    noTasksLabel->setFont(QFont({QString::fromUtf8("Segoe UI Semibold")}, 24));
    noTasksLabel->hide();
}

void TaskListWidget::addNewTask(TaskItemWidget* newTask)
{
    QListWidgetItem* newItem = new QListWidgetItem();
    newTask->setListWidgetItem(newItem);
    newItem->setSizeHint( QSize(0, widgetDefaultHeight) );

    insertItem(0, newItem);
    setItemWidget(newItem, newTask);
}

void TaskListWidget::handleNewTaskAdd()
{
    // Set text format for calendar cell where is unchecked task
    QTextCharFormat taskDateFormat;
    taskDateFormat.setFontUnderline(true);
    taskDateFormat.setFontItalic(true);

    const TaskItemWidget* task = qobject_cast<TaskItemWidget*>(itemWidget(item(0)));
    if(!task->isCompleted()) {
        QDate date = task->date();
        m_calendarWidget->setDateTextFormat(date, taskDateFormat);
    }

    m_calendarWidget->update();
}

void TaskListWidget::handleDeleteingTask(const int row)
{
    if(isAllShowed) return;

    const TaskItemWidget* deleted_task = qobject_cast<TaskItemWidget*>(itemWidget(item(row)));
    QDate date = deleted_task->date();
    bool noTasksForDate = true;

    for(int i = 0; i < count(); ++i) {
        if(i == row) continue;

        const TaskItemWidget* task = qobject_cast<TaskItemWidget*>(itemWidget(item(i)));
        if(task->date() == date) {
            noTasksForDate = false;
            break;
        }
    }

    toggleNoTask(noTasksForDate);
}

void TaskListWidget::toggleNoTask(bool noTasksForDate)
{
    if (noTasksForDate) {
        hide();
        noTasksLabel->show();
    } else {
        show();
        noTasksLabel->hide();
    }
}

void TaskListWidget::handleListWidgetItemDoubleClicked(QListWidgetItem *item)
{
    QWidget *widget = itemWidget(item);

    TaskItemWidget* taskItemWidget = qobject_cast<TaskItemWidget*>(widget);
    if (taskItemWidget) {
        // Handle the double-click action for the TaskItemWidget
        taskItemWidget->toggleDescriptionExpansion(item);
    }
}

void TaskListWidget::wheelEvent(QWheelEvent *event) {
    int delta = event->angleDelta().y();
    float scrollAmount = 0.5; // Scroll speed

    // Decrease the scroll amount to make it softer
    int steps = -delta / 50 * scrollAmount;

    // Scroll by the specified number of steps
    verticalScrollBar()->setValue(verticalScrollBar()->value() + steps);
}
