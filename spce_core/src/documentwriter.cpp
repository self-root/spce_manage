#include "documentwriter.h"
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFile>

namespace spce_core {
DocumentWriter::DocumentWriter(QObject *parent): QObject(parent), env()
{
    env.set_comment("{&", "&}");
    createTemplateDir();
    initTemplates();
}

QString DocumentWriter::templatePath()
{
    QStringList locations = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    QString appLocation = locations.first();
    return QDir::cleanPath(appLocation + QDir::separator() + "templates");
}

bool DocumentWriter::templateExists(const QString &filename)
{
    QString filePath = QDir::cleanPath(templatePath() + QDir::separator() + filename);

    QFile file(filePath);
    return file.exists();
}

void DocumentWriter::initTemplates()
{
    for (auto temp : {CERTIFICATE_TEMP, BSD_TEMP, INVOICE_TEMP})
    {
        if (!templateExists(temp))
        {
            QFile file(QString(":/templates/templates/%1").arg(temp));
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                QFile certificate_temp(fullPathOf(temp));
                if (certificate_temp.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream out(&certificate_temp);
                    out << in.readAll();
                    certificate_temp.close();
                }
                file.close();
            }
        }
    }
}

void DocumentWriter::writeBSD(const nlohmann::json &data)
{
    inja::Template temp = env.parse_template(fullPathOf(BSD_TEMP).toStdString());
    QString path = QString("bsd_%1.html").arg(QString::fromStdString(data["ship_name"]));
    env.write(temp, data, outPath(path).toStdString());
}

void DocumentWriter::writeCertificate(const nlohmann::json &data)
{
    qDebug() << "Parsing template...";
    inja::Template temp = env.parse_template(fullPathOf(CERTIFICATE_TEMP).toStdString());
    qDebug() << "CReating certificate file...";
    QString path = QString("certificate_%1.html").arg(QString::fromStdString(data["ship_name"]));
    env.write(temp, data, outPath(path).toStdString());
}

void DocumentWriter::writeInvoice(const nlohmann::json &data)
{
    inja::Template temp = env.parse_template(fullPathOf(INVOICE_TEMP).toStdString());
    QString path = QString("invoice_%1.html").arg(QString::fromStdString(data["ship_name"]));
    env.write(temp, data, outPath(path).toStdString());
}

void DocumentWriter::createTemplateDir()
{
    QDir templateDir(templatePath());
    if (!templateDir.exists())
    {
        templateDir.mkpath(templatePath());
    }

}

QString DocumentWriter::fullPathOf(const QString &temp)
{
    return QDir::cleanPath(templatePath() + QDir::separator() + temp);
}

QString DocumentWriter::outPath(const QString &fileName)
{
    QStringList docPaths = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString doc = docPaths.first();
    return QDir::cleanPath(doc + QDir::separator() + fileName);
}

void DocumentWriter::write(const nlohmann::json &data)
{

    writeCertificate(data);
    writeInvoice(data);
    writeBSD(data);
}
} // namespace spce_core

