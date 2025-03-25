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

void UIController::invoiceBtnClick()
{
    emit goInvoicePage();
}
