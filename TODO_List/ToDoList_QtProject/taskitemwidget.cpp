#include "taskitemwidget.h"
#include "stylesheets.h"
#include "tasklistwidget.h"

#include <QVBoxLayout>
#include <QGridLayout>


TaskItemWidget::TaskItemWidget(const QDate date, const QString name, const QString description)
{
    setupCheckBox();
    setupTaskName(name);
    setupTaskDate(date);
    setupTaskDescription(description);

    setupToolButton();
    setupActions();
    setupLayout();
    setupEditLayout();

    setLayout(stackedLayout);
    stackedLayout->setCurrentIndex(0);
}


TaskItemWidget::~TaskItemWidget()
{
    delete m_item;

    delete stackedLayout;
    delete layout;
    delete editLayout;

    delete m_name;
    delete m_description;
    delete m_date;
    delete m_checkBox;

    delete m_toolButton;
    delete m_editTaskAction;
    delete m_deleteTaskAction;

    delete m_nameEdit;
    delete m_dateEdit;
    delete m_descriprionEdit;

    delete saveButton;
    delete cancelButton;
}



void TaskItemWidget::setupCheckBox()
{
    m_checkBox->setCheckState(Qt::Unchecked);
    m_checkBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum));
    m_checkBox->setStyleSheet(Stylesheet::getStyleSheet(Element::checkBox));
}

void TaskItemWidget::setupTaskName(const QString &name)
{
    m_name->setText(name);
    m_name->setWordWrap(true);
    m_name->setStyleSheet(Stylesheet::getStyleSheet(Element::taskName));

    m_name->setMaximumWidth(250);
    m_name->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum));

    QFont nameFont;
    nameFont.setFamilies({QString::fromUtf8("Segoe UI Semibold")});
    nameFont.setPointSize(16);
    nameFont.setBold(true);
    m_name->setFont(nameFont);
}

void TaskItemWidget::setupTaskDate(const QDate &date)
{
    m_date->setText(date.toString("dd.MM.yyyy"));
    m_date->setStyleSheet(Stylesheet::getStyleSheet(Element::taskDate));
    m_date->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum));
    m_date->setFont(QFont({QString::fromUtf8("Segoe UI Symbol")}, 10));
}

void TaskItemWidget::setupTaskDescription(const QString &description)
{
    m_description->setMinimumSize(QSize(300, 39));
    m_description->setMaximumSize(QSize(1000, 39));
    m_description->setStyleSheet("color: darkgray;");

    QFont font3;
    font3.setPointSize(11);
    m_description->setFont(font3);

    m_description->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    m_description->setWordWrap(true);

    setDescription(description);
}

void TaskItemWidget::setupNameEdit()
{
    m_nameEdit->setStyleSheet(Stylesheet::getStyleSheet(Element::taskNameEditLine));
    m_nameEdit->hide();
}

void TaskItemWidget::setupDateEdit()
{
    m_dateEdit->setCalendarPopup(false);
    m_dateEdit->setDisplayFormat("dd.MM.yyyy");
    m_dateEdit->setMinimumDate(QDate::currentDate());
    m_dateEdit->setMaximumDate(QDate(2024, 12, 31));
    m_dateEdit->setStyleSheet(Stylesheet::getStyleSheet(Element::taskDateEdit));
    m_dateEdit->hide();

}

void TaskItemWidget::setupDescriptionEdit()
{
    m_descriprionEdit->setMinimumSize(300, 0);
    m_descriprionEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_descriprionEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_descriprionEdit->setStyleSheet(Stylesheet::getStyleSheet(Element::taskDescriptionEditBrowser));
    m_descriprionEdit->setCursor(QCursor(Qt::IBeamCursor));
    m_descriprionEdit->setReadOnly(false);
    m_descriprionEdit->hide();

}

void TaskItemWidget::setupEditButtons()
{
    saveButton->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed));
    cancelButton->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed));

    connect(saveButton, &QPushButton::clicked, this, &TaskItemWidget::saveButtonPressed);
    connect(cancelButton, &QPushButton::clicked, this, &TaskItemWidget::cancelButtonPressed);

    saveButton->setStyleSheet(Stylesheet::getStyleSheet(Element::taskSaveButton));
    cancelButton->setStyleSheet(Stylesheet::getStyleSheet(Element::taskCancelButton));

    saveButton->hide();
    cancelButton->hide();
}

void TaskItemWidget::setupToolButton()
{
    m_toolButton->setText("...");
    m_toolButton->setInputMethodHints(Qt::ImhNone);
    m_toolButton->setIconSize(QSize(35, 35));
    m_toolButton->setPopupMode(QToolButton::InstantPopup);
    m_toolButton->setToolButtonStyle(Qt::ToolButtonFollowStyle);
    m_toolButton->setArrowType(Qt::NoArrow);
    m_toolButton->setFocusPolicy(Qt::NoFocus);
    m_toolButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum));
    m_toolButton->setStyleSheet(Stylesheet::getStyleSheet(Element::taskToolButton));

    QFont font;
    font.setPointSize(18);
    font.setBold(true);
    m_toolButton->setFont(font);

    m_toolButton->addAction(m_editTaskAction);
    m_toolButton->addAction(m_deleteTaskAction);
}

void TaskItemWidget::setupActions()
{
    m_editTaskAction->setIcon(QIcon(":/Icons/Edit.ico"));
    m_deleteTaskAction->setIcon(QIcon(":/Icons/Trash.ico"));

    connect(m_editTaskAction, &QAction::triggered, this, &TaskItemWidget::toggleEditMode);
    connect(m_deleteTaskAction, &QAction::triggered, this, &TaskItemWidget::deleteTask);
}

void TaskItemWidget::setupLayout()
{
    QGridLayout* taskGridLayout = new QGridLayout;
    QVBoxLayout* taskNameAndDataLayout = new QVBoxLayout;

    taskNameAndDataLayout->addWidget(m_date);
    taskNameAndDataLayout->addWidget(m_name);

    taskGridLayout->addLayout(taskNameAndDataLayout, 0, 2, 1, 1);
    taskGridLayout->addWidget(m_checkBox, 0, 1, 1, 1);
    layout->addLayout(taskGridLayout);

    QSpacerItem* spacer_1 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);
    QSpacerItem* spacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    layout->addItem(spacer_1);
    layout->addWidget(m_description);
    layout->addSpacerItem(spacer_2);
    layout->addWidget(m_toolButton);

    QWidget* layoutWidget = new QWidget(this);
    layoutWidget->setLayout(layout);
    stackedLayout->addWidget(layoutWidget);
}

void TaskItemWidget::setupEditLayout()
{
    setupNameEdit();
    setupDateEdit();
    setupDescriptionEdit();
    setupEditButtons();

    QVBoxLayout* nameDateEditLay = new QVBoxLayout();
    nameDateEditLay->addWidget(m_dateEdit);
    nameDateEditLay->addWidget(m_nameEdit);

    QHBoxLayout* buttonsLay = new QHBoxLayout();
    buttonsLay->addWidget(saveButton);
    buttonsLay->addWidget(cancelButton);

    editLayout->addLayout(nameDateEditLay, 2, 1, 1, 1);
    editLayout->addWidget(m_descriprionEdit, 2, 2, 2, 1);
    editLayout->addLayout(buttonsLay, 3, 1, 1, 1);

    QWidget* layoutWidget = new QWidget(this);
    layoutWidget->setLayout(editLayout);
    stackedLayout->addWidget(layoutWidget);
}

void TaskItemWidget::toggleDescriptionExpansion(QListWidgetItem *item)
{
    if (inEditMode) return;
    const int descriptionHeight = m_description->height();

    if (item->sizeHint().height() == widgetDefaultHeight) {
        m_description->setMaximumHeight(1000);
        QSize size = m_item->sizeHint();
        QFontMetrics metrics(m_description->font());
        int requiredHeight = metrics.boundingRect(0, 0, m_description->width(), 0, Qt::TextWordWrap, m_description->text()).height();

        if(descriptionHeight < requiredHeight) {
            size.setHeight(requiredHeight + widgetDefaultHeight - descriptionHeight - 1);
            item->setSizeHint( size );
        }
    }
    else {
        m_description->setMaximumHeight(39);
        QSize size = m_item->sizeHint();
        size.setHeight(widgetDefaultHeight);
        item->setSizeHint( size );
    }
}

void TaskItemWidget::saveButtonPressed()
{
    toggleEditMode(false);
}

void TaskItemWidget::cancelButtonPressed()
{
    toggleEditMode(true);
}

void TaskItemWidget::toggleEditMode(const bool cancelPressed)
{
    inEditMode = !inEditMode;

    if (inEditMode) {
        changeToEditMode();
    } else {
        changeToDefaultMode(cancelPressed);
    }
}

void TaskItemWidget::changeToEditMode()
{
    m_name->hide();
    m_date->hide();
    m_description->hide();
    m_checkBox->hide();
    m_toolButton->hide();

    // Show editing controls and populate with current values
    m_nameEdit->show();
    m_dateEdit->show();
    m_descriprionEdit->show();
    saveButton->show();
    cancelButton->show();

    stackedLayout->setCurrentIndex(1);
    m_item->setSizeHint(QSize(0, 150));

    // Populate the editing controls with the current values
    m_nameEdit->setText(m_name->text());
    m_dateEdit->setDate(QDate::fromString(m_date->text(), "dd.MM.yyyy"));
    m_descriprionEdit->setPlainText(m_description->text());
}

void TaskItemWidget::changeToDefaultMode(const bool cancelPressed)
{
    m_name->show();
    m_date->show();
    m_description->show();
    m_checkBox->show();
    m_toolButton->show();

    // Hide editing controls
    m_nameEdit->hide();
    m_dateEdit->hide();
    m_descriprionEdit->hide();
    saveButton->hide();
    cancelButton->hide();

    //setLayout(layout);
    stackedLayout->setCurrentIndex(0);
    m_item->setSizeHint(QSize(0, widgetDefaultHeight));

    // Update the labels with edited values
    if(!cancelPressed) {
        setName(m_nameEdit->text());
        setDate(m_dateEdit->date());
        setDescription(m_descriprionEdit->toPlainText());
    }

    TaskListWidget* list = dynamic_cast<TaskListWidget*>(m_item->listWidget());
    list->handleNewTaskAdd();
}

void TaskItemWidget::deleteTask()
{
    TaskListWidget* list = dynamic_cast<TaskListWidget*>(m_item->listWidget());
    list->handleDeleteingTask(list->row(m_item));
    list->removeItemWidget(m_item);
}

