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
    void invoiceBtnClick();

signals:
    void goSchedulePage();
    void goInvoicePage();
};

#endif // UICONTROLLER_H
