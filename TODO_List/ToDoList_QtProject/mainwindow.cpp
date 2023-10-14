#include "mainwindow.h"
#include "stylesheets.h"
#include "calendarwidget.h"

#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    connect(addButton, &QPushButton::clicked, this, &MainWindow::plusButtonPressed);
    connect(calendarWidget, &CalendarWidget::selectionChanged, this, &MainWindow::handleDateSelection);

    // Connect the buttons' clicked signals to filter slots
    connect(showAll, &QPushButton::clicked, this, &MainWindow::showAll_apply);
    connect(showAllForSelectedDate, &QPushButton::clicked, this, &MainWindow::showAllForSelectedDate_apply);
    connect(showUncompleteds, &QPushButton::clicked, this, &MainWindow::showUncompleteds_apply);
    connect(showCompleteds, &QPushButton::clicked, this, &MainWindow::showCompleteds_apply);

    loadFromFile();
}

MainWindow::~MainWindow()
{

    delete addButton;
    delete showAll;
    delete showAllForSelectedDate;
    delete showUncompleteds;
    delete showCompleteds;

    delete calendarWidget;
    delete taskListWidget;

    delete filterWidget;

    delete left_widget;
    delete right_widget;
    delete centralwidget;
}

void MainWindow::plusButtonPressed()
{
    taskListWidget->toggleNoTask(false);
    QDate date = calendarWidget->selectedDate();
    TaskItemWidget* newTask = new TaskItemWidget(date);
    taskListWidget->addNewTask(newTask);
    newTask->toggleEditMode();
}

void MainWindow::handleDateSelection()
{
    // Set hidden what needs to be hidden
    QDate selectedDate = calendarWidget->selectedDate();
    bool hasTasksForDate = false;
    for (int i = 0; i < taskListWidget->count(); ++i) {
        const TaskItemWidget* task = qobject_cast<TaskItemWidget*>(taskListWidget->itemWidget(taskListWidget->item(i)));
        if(task->date() != selectedDate) {
            taskListWidget->setRowHidden(i, true);
        } else {
            taskListWidget->setRowHidden(i, false);
            hasTasksForDate = true;
        }
    }

    // Show "No task for this date" label if there is no tasks
    taskListWidget->toggleNoTask(!hasTasksForDate);

    applyFilter();
}

void MainWindow::applyFilter()
{
    if(showAll->isChecked()) {
        showAll_apply();
    } else if(showAllForSelectedDate->isChecked()) {
        showAllForSelectedDate_apply();
    }
}

void MainWindow::setupUi()
{
    setWindowTitle("To Do List");
    setWindowIcon(QIcon(":/Icons/TODO_List_Icon.ico"));
    setMinimumSize(1100, 700);
    resize(1150, 700);
    setFocusPolicy(Qt::NoFocus);
    setStyleSheet(Stylesheet::getStyleSheet(Element::mainWindow));

    centralwidget = new QWidget(this);

    setupLeftWidget();
    setupRightWidget();

    QHBoxLayout* centralWidgetLayout = new QHBoxLayout(centralwidget);
    centralWidgetLayout->addWidget(left_widget);
    centralWidgetLayout->addWidget(right_widget);
    setCentralWidget(centralwidget);
}

void MainWindow::setupLeftWidget()
{
    left_widget = new QWidget(centralwidget);
    left_widget->setMinimumSize(QSize(350, 0));
    left_widget->setMaximumSize(QSize(350, 1000));
    left_widget->setStyleSheet(Stylesheet::getStyleSheet(Element::leftWidget));

    QVBoxLayout* leftWidgetLayout = new QVBoxLayout(left_widget);

    // Setup Program Name and add button
    setupNameAndAddButton(leftWidgetLayout);

    // Setup calendar widget
    calendarWidget = new CalendarWidget(left_widget);
    leftWidgetLayout->addWidget(calendarWidget);

    // Setup widget where filter
    setupFilterWidget();
    leftWidgetLayout->addWidget(filterWidget);

}

void MainWindow::setupAddButton()
{
    addButton = new QPushButton("+");
    addButton->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    addButton->setStyleSheet(Stylesheet::getStyleSheet(Element::addButton));
}

void MainWindow::setupProgramNameLabel(QLabel* progName_TODO,  QLabel* progName_list)
{
    progName_TODO->setStyleSheet(Stylesheet::getStyleSheet(Element::programName_TODO));
    progName_list->setStyleSheet(Stylesheet::getStyleSheet(Element::programName_list));

    QFont font({QString::fromUtf8("Berlin Sans FB")}, 28);
    progName_TODO->setFont(font);
    progName_list->setFont(font);

    progName_TODO->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
}

void MainWindow::setupNameAndAddButton(QVBoxLayout* leftWidgetLayout)
{
    // Add Buton
    setupAddButton();

    // Program name
    QLabel* progName_TODO = new QLabel("TODO");
    QLabel* progName_list = new QLabel("List");

    setupProgramNameLabel(progName_TODO, progName_list);

    QLabel* icon = new QLabel();
    icon->setPixmap(QPixmap(":/Icons/TODO_List_Icon.ico"));
    icon->setMaximumWidth(30);

    QHBoxLayout* progNameLayout = new QHBoxLayout();
    progNameLayout->addWidget(icon);
    progNameLayout->addWidget(progName_TODO);
    progNameLayout->addWidget(progName_list);

    QHBoxLayout* nameAndAddButtonLayout = new QHBoxLayout();
    nameAndAddButtonLayout->addLayout(progNameLayout);
    nameAndAddButtonLayout->addWidget(addButton);

    leftWidgetLayout->addLayout(nameAndAddButtonLayout);
}

void MainWindow::setupRightWidget()
{
    right_widget = new QWidget(centralwidget);
    QVBoxLayout* rightWidgetLayout = new QVBoxLayout(right_widget);
    taskListWidget = new TaskListWidget(right_widget);
    taskListWidget->setCalendar(calendarWidget);

    rightWidgetLayout->addWidget(taskListWidget);
}

void MainWindow::setupFilterWidget()
{
    filterWidget = new QWidget(left_widget);
    filterWidget->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));

    QVBoxLayout* mainWidgetLayout = new QVBoxLayout(filterWidget);

    QVBoxLayout* layoutForFilter = new QVBoxLayout();
    QLabel* filterLabel = new QLabel("Filter", filterWidget);
    setupFilterLabel(filterLabel);

    layoutForFilter->addWidget(filterLabel);

    setupFilterButtons();

    QGridLayout* filterButtonsLayout = new QGridLayout();
    filterButtonsLayout->addWidget(showAll, 0, 1, 1, 1);
    filterButtonsLayout->addWidget(showAllForSelectedDate, 0, 2, 1, 1);
    filterButtonsLayout->addWidget(showUncompleteds, 1, 2, 1, 1);
    filterButtonsLayout->addWidget(showCompleteds, 1, 1, 1, 1);

    layoutForFilter->addLayout(filterButtonsLayout);

    QSpacerItem* verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);

    mainWidgetLayout->addLayout(layoutForFilter);
    mainWidgetLayout->addItem(verticalSpacer);
}

void MainWindow::setupFilterLabel(QLabel* label)
{
    label->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum));
    label->setFont(QFont({QString::fromUtf8("Segoe UI Semibold")}, 22));
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: " + getColor(Color::filter_label));
}

void MainWindow::setupFilterButtons()
{
    showAll = new QPushButton("All", filterWidget);
    showAllForSelectedDate = new QPushButton("All for selected date", filterWidget);
    showUncompleteds = new QPushButton("Uncompleted", filterWidget);
    showCompleteds = new QPushButton("Completed", filterWidget);

    setupFilterButton(showAll);
    setupFilterButton(showAllForSelectedDate);
    setupFilterButton(showUncompleteds);
    setupFilterButton(showCompleteds);

    showAll->setChecked(true);
}

void MainWindow::setupFilterButton(QPushButton *button)
{
    button->setCheckable(true);
    button->setMinimumSize(QSize(0, 50));
    button->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed));
    button->setStyleSheet(Stylesheet::getStyleSheet(Element::filterButtton));
}

void MainWindow::showAll_apply()
{
    if(!showAll->isChecked()) {
        showAll->setChecked(true);
    }

    showAllForSelectedDate->setChecked(false);
    bool showUncompleted = showUncompleteds->isChecked();
    bool showCompleted = showCompleteds->isChecked();
    bool hasTask = false;

    for (int i = 0; i < taskListWidget->count(); ++i) {
        const TaskItemWidget* task = qobject_cast<TaskItemWidget*>(taskListWidget->itemWidget(taskListWidget->item(i)));
        bool taskCompleted = task->isCompleted();
        if( (showUncompleted && taskCompleted) || (showCompleted && !taskCompleted) ) {
            taskListWidget->setRowHidden(i, true);
        } else {
            taskListWidget->setRowHidden(i, false);
            hasTask = true;
        }
    }

    taskListWidget->setAllShowed(true);
    taskListWidget->toggleNoTask(!hasTask);
}

void MainWindow::showAllForSelectedDate_apply()
{
    if(!showAllForSelectedDate->isChecked()) {
        showAllForSelectedDate->setChecked(true);
    }

    showAll->setChecked(false);

    bool showUncompleted = showUncompleteds->isChecked();
    bool showCompleted = showCompleteds->isChecked();
    bool hasTask = false;

    for (int i = 0; i < taskListWidget->count(); ++i) {
        const TaskItemWidget* task = qobject_cast<TaskItemWidget*>(taskListWidget->itemWidget(taskListWidget->item(i)));
        bool taskCompleted = task->isCompleted();

        if(task->date() == calendarWidget->selectedDate()) {
            if( (showUncompleted && taskCompleted) || (showCompleted && !taskCompleted) ) {
                taskListWidget->setRowHidden(i, true);
            } else {
                taskListWidget->setRowHidden(i, false);
                hasTask = true;
            }

        } else {
            taskListWidget->setRowHidden(i, true);
        }
    }

    taskListWidget->setAllShowed(false);
    taskListWidget->toggleNoTask(!hasTask);
}

void MainWindow::showUncompleteds_apply()
{
    if(showUncompleteds->isChecked()) {
        showCompleteds->setChecked(false);
    }

    applyFilter();
}

void MainWindow::showCompleteds_apply()
{
    if(showCompleteds->isChecked()) {
        showUncompleteds->setChecked(false);
    }

    applyFilter();
}

void MainWindow::loadFromFile()
{
    qDebug() << "Loading form file";
    bool hasTask = false;

    const QString fileName = "info.txt";
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        // Read task data from the file and create Task objects
        while (!in.atEnd()) {

            QString status = in.readLine().split(':').takeLast();
            bool completed = (status == " Completed");
            QString name = in.readLine();
            QDate date = QDate::fromString(in.readLine(), "dd.MM.yyyy");
            QString description = in.readLine();
            in.readLine();

            // Create a Task object and add it to your list of tasks
            TaskItemWidget* task = new TaskItemWidget(date, name, description);
            task->setCompleted(completed);
            taskListWidget->addNewTask(task);
            taskListWidget->handleNewTaskAdd();
            hasTask = true;
        }

        file.close();

        taskListWidget->toggleNoTask(!hasTask);
    } else {
        // Handle the case where the file cannot be opened for reading
        QMessageBox::critical(this, "File Load Error", "An error occurred while loading data from the file.");
    }
}

void MainWindow::saveToFile()
{
    qDebug() << "Saving...";
    const QString fileName = "info.txt";
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        // Iterate through your list of tasks and write each task to the file
        for (int i = taskListWidget->count() - 1; i >= 0; --i) {
            const TaskItemWidget* task = qobject_cast<TaskItemWidget*>(taskListWidget->itemWidget(taskListWidget->item(i)));

            out << i << ": ";
            bool state = task->isCompleted();
            out << (state ? "Completed" : "Not completed") << '\n';
            out << task->name() << '\n';
            out << task->date().toString("dd.MM.yyyy") << '\n';
            out << task->description() << "\n\n";
        }

        file.close();

    } else {
        // Handle the case where the file cannot be opened for writing
        QMessageBox::critical(this, "File Save Error", "An error occurred while saving the data to the file.");
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveToFile();
    QMainWindow::closeEvent(event);
}

