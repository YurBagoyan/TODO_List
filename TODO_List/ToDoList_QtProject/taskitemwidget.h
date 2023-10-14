#ifndef TASKITEMWIDGET_H
#define TASKITEMWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QStackedLayout>

#include <QLabel>
#include <QDate>
#include <QCheckBox>

#include <QLineEdit>
#include <QTextBrowser>
#include <QDateEdit>

#include <QListWidget>
#include <QToolButton>


class TaskItemWidget : public QWidget
{
    Q_OBJECT
public:
    TaskItemWidget(const QDate date = QDate::currentDate(), const QString name = "New Task Name", const QString description = "Description");
    ~TaskItemWidget();

public:
    // geters and setters
    void setName(const QString& name) { m_name->setText(name); };
    void setDescription(const QString& description) { m_description->setText(description); };
    void setDate(const QDate& date) { m_date->setText(date.toString("dd.MM.yyyy"));};
    void setCompleted(const bool checked) { m_checkBox->setChecked(checked);};
    void setListWidgetItem(QListWidgetItem* item) { m_item = item; };

    QString name() const { return m_name->text(); };
    QString description() const { return m_description->text(); };
    QDate date() const { return QDate::fromString(m_date->text(), "dd.MM.yyyy"); };
    bool isCompleted() const { return m_checkBox->isChecked(); };
    QListWidgetItem* listWidgetItem() { return m_item; };

    void toggleDescriptionExpansion(QListWidgetItem *item);
    void toggleEditMode(const bool cancelPressed = false);

private:
    void setupCheckBox();
    void setupTaskName(const QString& name);
    void setupTaskDate(const QDate& date);
    void setupTaskDescription(const QString& description);
    void setupNameEdit();
    void setupDateEdit();
    void setupDescriptionEdit();
    void setupEditButtons();
    void setupToolButton();
    void setupActions();
    void setupLayout();
    void setupEditLayout();

    void changeToEditMode();
    void changeToDefaultMode(const bool cancelPressed);

    void saveButtonPressed();
    void cancelButtonPressed();

    void togleNoTask();
    void deleteTask();

private:
    QListWidgetItem* m_item = new QListWidgetItem;

    QStackedLayout* stackedLayout = new QStackedLayout(this);
    QHBoxLayout* layout = new QHBoxLayout();
    QGridLayout* editLayout = new QGridLayout();

    QLabel* m_name = new QLabel(this);
    QLabel* m_date = new QLabel(this);
    QLabel* m_description = new QLabel(this);
    QCheckBox* m_checkBox = new QCheckBox(this);

    QToolButton* m_toolButton = new QToolButton(this);
    QAction* m_editTaskAction = new QAction("Edit task", this);
    QAction* m_deleteTaskAction = new QAction("Delete task", this);

    // Edit
    QLineEdit* m_nameEdit = new QLineEdit(this);
    QDateEdit* m_dateEdit = new QDateEdit(this);
    QTextBrowser* m_descriprionEdit = new QTextBrowser(this);

    QPushButton* saveButton = new QPushButton("Save", this);
    QPushButton* cancelButton = new QPushButton("Cancel", this);

    bool inEditMode = false;
    const int widgetDefaultHeight = 70;

};

#endif // TASKITEMWIDGET_H
