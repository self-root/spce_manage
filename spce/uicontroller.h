#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QObject>

class UIController : public QObject
{
    Q_OBJECT
public:
    explicit UIController(QObject *parent = nullptr);
public slots:
    void scheduleMenuBtnClic();
    void operationMenuBtnClic();
    void shipDocBtnClic();

signals:
    void goSchedulePage();
    void goOperationPage();
};

#endif // UICONTROLLER_H
