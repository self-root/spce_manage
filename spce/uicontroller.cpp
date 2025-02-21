#include "uicontroller.h"
#include <QDebug>

UIController::UIController(QObject *parent)
    : QObject{parent}
{
}

void UIController::scheduleMenuBtnClic()
{
    qDebug() << "Schedule menu btn clicked";
    emit goSchedulePage();
}

void UIController::operationMenuBtnClic()
{
    qDebug() << "Operation menu clic";
    emit goOperationPage();
}

void UIController::shipDocBtnClic()
{
    emit goOperationPage();
}
