#include "documentformmodel.h"
#include "databasemanager.h"
#include <QDir>

namespace spce_core {
DocumentFormModel::DocumentFormModel(APICaller *api, QObject *parent)
    :mApi(api), QObject{parent},
    commNameListModel(new BaseEntityListModel<Commissionnaire>),
    collNameListModel(new BaseEntityListModel<Collecteur>),
    driverNameListModel(new BaseEntityListModel<Driver>),
    vehicleListModel(new BaseEntityListModel<Vehicle>),
    eliminateurListModel(new BaseEntityListModel<Eliminateur>),
    terminalListModel(new TerminalListModel)
{
    setShipPropertyValues();
    commNameListModel->getDataFromDb();
    currentCommissionnaire = commNameListModel->firstEntity();
    setCommissionnairePropertyValues();

    collNameListModel->getDataFromDb();
    currentCollecteur = collNameListModel->firstEntity();
    setCollecteurPropertyValues();

    driverNameListModel->getDataFromDb();
    currentDriver = driverNameListModel->firstEntity();
    setDriverProperyValues();

    vehicleListModel->getDataFromDb();
    currentVehicle = vehicleListModel->firstEntity();
    setVehicleProperyValues();

    eliminateurListModel->getDataFromDb();
    currentEliminateur = eliminateurListModel->firstEntity();
    setEliminateurPropertyValues();
    QObject::connect(mApi, &APICaller::shipFetched, this, &DocumentFormModel::onShipDetailFetched);
}

void DocumentFormModel::getShip(const QString &imo)
{
    currentShip = DatabaseManager::instance()->mShipDao.getShip(imo);
    if (currentShip.id() < 0)
    {
        mApi->fetchShip(imo);
    }
    else
    {
        setShipPropertyValues();
    }

}

void DocumentFormModel::onShipDetailFetched(const Ship &ship)
{
    qDebug() << "Ship flag: " << ship.flagUrl();
    if (!FlagSVGDownloader::flagExists(ship.flagUrl()))
        flagDownloader.downloadFlag(ship.flagUrl());
    currentShip = ship;
    setShipPropertyValues();
    DatabaseManager::instance()->mShipDao.add(currentShip);
    qDebug() << "New ship added to the db, ship id: " << currentShip.id();
}

BaseEntityListModel<Commissionnaire> *DocumentFormModel::getCommListModel()
{
    return commNameListModel;
}

BaseEntityListModel<Collecteur> *DocumentFormModel::getCollListModel()
{
    return collNameListModel;
}

BaseEntityListModel<Driver> *DocumentFormModel::getDriverListModel()
{
    return driverNameListModel;
}

BaseEntityListModel<Vehicle> *DocumentFormModel::getVehiclListModel()
{
    return vehicleListModel;
}

BaseEntityListModel<Eliminateur> *DocumentFormModel::getEliminateurListModel()
{
    return eliminateurListModel;
}

TerminalListModel *DocumentFormModel::getTerminalListModel()
{
    return terminalListModel;
}

void DocumentFormModel::setShipPropertyValues()
{
    set_imo(currentShip.imo());
    set_shipName(currentShip.name());
    set_flagState(currentShip.flag());
    set_callSign(currentShip.callSign());
    set_shipType(currentShip.type());
    set_tonnage(currentShip.tonnage());
    set_flagUrl(QDir::cleanPath(FlagSVGDownloader::flagsFolder() + QDir::separator() + currentShip.flagUrl()));
}

void DocumentFormModel::setCommissionnairePropertyValues()
{
    set_commAddress(currentCommissionnaire.address());
    set_commTel(currentCommissionnaire.tel());
    set_commMail(currentCommissionnaire.email());
    set_commResponsable(currentCommissionnaire.responsabble());
}

void DocumentFormModel::setCollecteurPropertyValues()
{
    set_collAddress(currentCollecteur.address());
    set_collTel(currentCollecteur.tel());
    set_collMail(currentCollecteur.email());
    set_collResponsable(currentCollecteur.responsabble());
}

void DocumentFormModel::setDriverProperyValues()
{
    set_driverName(currentDriver.nom());
}

void DocumentFormModel::setVehicleProperyValues()
{
    set_vehicleType(currentVehicle.type());
}

void DocumentFormModel::setEliminateurPropertyValues()
{
    set_elimAddress(currentEliminateur.address());
    set_elimTel(currentEliminateur.tel());
    set_elimMail(currentEliminateur.email());
    set_elimResponsable(currentEliminateur.responsabble());
    set_elimReceptionSite(currentEliminateur.receptionSite());
}

QString DocumentFormModel::makeInvoiceNumber()
{
    QString lastInvoiceNumber = DatabaseManager::instance()->mInvoiceDao.lastInvoiceNumber();
    qDebug() << "Last invoice number: " << lastInvoiceNumber;
    QString invoiceNumberFormat = "F%1-%2/SPCE";
    QDate date = QDate::currentDate();
    QString year = date.toString("yy");
    if (lastInvoiceNumber.isEmpty())
    {
        return invoiceNumberFormat.arg("001").arg(year);
    }

    QStringList parts = lastInvoiceNumber.split("-");
    int lastNumber = parts.at(0).mid(1).toInt(nullptr, 10);
    int nextNumber = lastNumber + 1;
    int lastYear = parts.at(1).first(2).toInt();

    if (lastYear != year.toInt())
    {
        return invoiceNumberFormat.arg("001").arg(year);
    }

    QString number = QString::number(nextNumber);

    switch (number.length()) {
    case 1:
        return invoiceNumberFormat.arg(QString("00") + number).arg(year);
        break;
    case 2:
        return invoiceNumberFormat.arg(QString("0") + number).arg(year);
        break;
    default:
        return invoiceNumberFormat.arg(number).arg(year);
    }

}

void DocumentFormModel::commissionnaireAt(int index)
{
    currentCommissionnaire = commNameListModel->entityAt(index);
    setCommissionnairePropertyValues();
}

void DocumentFormModel::collecteurAt(int index)
{
    currentCollecteur = collNameListModel->entityAt(index);
    setCollecteurPropertyValues();
}

void DocumentFormModel::vehicleAt(int index)
{
    currentVehicle = vehicleListModel->entityAt(index);
    setVehicleProperyValues();
}

void DocumentFormModel::eliminateurAt(int index)
{
    currentEliminateur = eliminateurListModel->entityAt(index);
    setEliminateurPropertyValues();
}


void DocumentFormModel::createDocuments(const QVariantMap &form_data)
{
    nlohmann::json data;
    data["type"] = "certificate";
    data["ship_name"] = currentShip.name().toStdString();
    data["imo_number"] = currentShip.imo().toStdString();
    data["flag_state"] = currentShip.flag().toStdString();
    data["callsign"] = currentShip.callSign().toStdString();
    data["gross_tonnage"] = currentShip.tonnage();
    data["ship_type"] = currentShip.type().toStdString();
    data["terminal"] = form_data["terminal"].toString().toStdString();
    data["start_date"] = DocumentFormModel::formatDate(form_data["start_date"].toDate()).toStdString();
    data["end_date"] = DocumentFormModel::formatDate(form_data["end_date"].toDate()).toStdString();
    data["document_date"] = DocumentFormModel::formatDate(form_data["document_date"].toDate()).toStdString();
    data["bsd_date"] = form_data["document_date"].toDate().toString("dd/MM/yyyy").toStdString();
    data["commissionnaire"] = form_data["commissionnaire"].toString().toStdString();
    data["comm_address"] = m_commAddress.toStdString();
    data["comm_responsable"] = m_commResponsable.toStdString();
    data["comm_mail"] = m_commMail.toStdString();
    data["comm_tel"] = m_commTel.toStdString();
    data["driver"] = form_data["driver"].toString().toStdString();
    data["coll_vehicle_type"] = form_data["vehicle"].toString().toStdString();
    data["collecteur"] = form_data["collecteur"] .toString().toStdString();
    data["coll_address"] = m_collAddress.toStdString();
    data["coll_tel"] = m_collTel.toStdString();
    data["coll_mail"] = m_collMail.toStdString();
    data["coll_responsable"] = m_collResponsable.toStdString();
    data["coll_vehicle_type"] = m_vehicleType.toStdString();
    data["coll_vehicle"] = form_data["vehicle"].toString().toStdString();
    data["aliminateur"] = form_data["eliminateur"].toString().toStdString();
    data["elim_address"] = m_elimAddress.toStdString();
    data["elim_tel"] = m_elimTel.toStdString();
    data["elim_mail"] = m_elimMail.toStdString();
    data["elim_responsable"] = m_elimResponsable.toStdString();
    data["reception_site"] = m_elimReceptionSite.toStdString();
    data["quantity"] = form_data["invoice_quantity"].toString().toStdString();
    data["amount"] = form_data["invoice_amount"].toString().toStdString();
    data["unit_price"] = "";
    data["total"] = form_data["invoice_amount"].toString().toStdString();
    data["invoice_number"] = makeInvoiceNumber().toStdString();
    emit writeShipDocument(data);
    Commissionnaire comm(
        form_data["commissionnaire"].toString(),
        m_commAddress,
        m_commTel,
        m_commMail,
        m_commResponsable,
        currentCommissionnaire.id()
    );
    if (!comm.nom().isEmpty())
    {
        Commissionnaire commissionnaire = DatabaseManager::instance()->mCommissionnaireDao.get(comm.nom());
        if (commissionnaire.id() > 0)
        {
            if (!commissionnaire.equal(comm))
            {
                DatabaseManager::instance()->mCommissionnaireDao.update(comm);
                commNameListModel->getDataFromDb();
            }
        }

        else{
            DatabaseManager::instance()->mCommissionnaireDao.add(comm);
            commNameListModel->getDataFromDb();
        }
    }

    Collecteur coll(
        form_data["collecteur"] .toString(),
        m_collAddress,
        m_collTel,
        m_collMail,
        m_collResponsable,
        currentCollecteur.id()
    );
    if (!coll.nom().isEmpty())
    {
        Collecteur collecteur = DatabaseManager::instance()->mCollecteurDao.get(coll.nom());
        qDebug() << "CollF: " << coll.id() << coll.nom() << "addr: " << coll.address() << "tel: " << coll.tel() << " mail: " << coll.email() << "resp: " << coll.responsabble();
        qDebug() << "CollD: " << collecteur.id() << collecteur.nom() << "addr: " << collecteur.address() << "tel: " << collecteur.tel() << " mail: " << collecteur.email() << "resp: " << collecteur.responsabble();
        if (collecteur.id() > 0)
        {
            if (!coll.equal(collecteur))
            {
                DatabaseManager::instance()->mCollecteurDao.update(coll);
                collNameListModel->getDataFromDb();
            }

        }
        else
        {
            DatabaseManager::instance()->mCollecteurDao.add(coll);
            collNameListModel->getDataFromDb();
        }
    }

    Driver driver(form_data["driver"].toString(), currentDriver.id());
    if (!driver.nom().isEmpty())
    {
        Driver d = DatabaseManager::instance()->mDriverDao.get(driver.nom());
        if (d.id() < 0)
            DatabaseManager::instance()->mDriverDao.add(driver);
        driverNameListModel->getDataFromDb();
    }

    Vehicle vehicle(
        m_vehicleType,
        form_data["vehicle"].toString(),
        currentVehicle.id()
    );
    if (!vehicle.number().isEmpty())
        vehicleListModel->addOrUpdate(vehicle);

    Eliminateur eliminateur(
        form_data["eliminateur"].toString(),
        m_elimAddress,
        m_elimTel,
        m_elimMail,
        m_elimResponsable,
        m_elimReceptionSite,
        currentEliminateur.id()
    );
    if (!eliminateur.nom().isEmpty())
    {
        Eliminateur elim = DatabaseManager::instance()->mEliminateurDao.get(eliminateur.nom());
        if (elim.id() > 0)
        {
            if (!eliminateur.equal(elim))
            {
                DatabaseManager::instance()->mEliminateurDao.update(eliminateur);
                eliminateurListModel->getDataFromDb();
            }
        }
        else
        {
            DatabaseManager::instance()->mEliminateurDao.add(eliminateur);
            eliminateurListModel->getDataFromDb();
        }
    }
    terminalListModel->addIfNotExist(form_data["terminal"].toString());



    Invoice invoice(
        QString::fromStdString(data["invoice_number"]),
        form_data["invoice_quantity"].toString().toDouble(),
        0.0,
        form_data["invoice_amount"].toString().toDouble(),
        currentShip,
        "GARBAGE REMOVAL",
        form_data["document_date"].toDate()
    );

    DatabaseManager::instance()->mInvoiceDao.add(invoice);

    BSD bsd(
        comm,
        coll,
        eliminateur,
        driver,
        vehicle,
        currentShip,
        form_data["document_date"].toDate(),
        invoice.id()
        );
    DatabaseManager::instance()->getDao<BSD>().add(bsd);
}

QString DocumentFormModel::formatDate(const QDate &date)
{
    QLocale::setDefault(QLocale::English);
    QLocale local;
    QString month = local.monthName(date.month());
    int day = date.day();
    int year = date.year();

    const char suffixes [][3] = {"th", "st", "nd", "rd"};
    auto ord = day % 100;
    if (ord / 10 == 1) { ord = 0; }
    ord = ord % 10;
    if (ord > 3)
    {
        ord = 0;
    }
    QString suffix = suffixes[ord];

    return QString("%1 %2%3 %4").arg(month).arg(day).arg(suffix).arg(year);
}

} // namespace spce_core
