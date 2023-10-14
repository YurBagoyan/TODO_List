#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tasklistwidget.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void plusButtonPressed();
    void handleDateSelection();
    void applyFilter();

    void showAll_apply();
    void showAllForSelectedDate_apply();
    void showUncompleteds_apply();
    void showCompleteds_apply();

private:
    void setupUi();
    void setupLeftWidget();
    void setupRightWidget();
    void setupAddButton();
    void setupProgramNameLabel(QLabel* progName_TODO,  QLabel* progName_list);
    void setupNameAndAddButton(QVBoxLayout* leftWidgetLayout);

    void setupFilterWidget();
    void setupFilterLabel(QLabel* label);
    void setupFilterButtons();
    void setupFilterButton(QPushButton* button);

    void loadFromFile();
    void saveToFile();

    void closeEvent(QCloseEvent* event) override;

private:
    QWidget* centralwidget;
    QPushButton* addButton;

    QWidget* right_widget;
    TaskListWidget* taskListWidget;

    QWidget* left_widget;
    CalendarWidget* calendarWidget;
    QWidget* filterWidget;

    QPushButton* showAll;
    QPushButton* showAllForSelectedDate;
    QPushButton* showUncompleteds;
    QPushButton* showCompleteds;
};
#endif // MAINWINDOW_H
