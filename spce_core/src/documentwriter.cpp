#include "documentwriter.h"
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QProcess>

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
    QString shipName = QString::fromStdString(data["ship_name"]);
    QString htmlFileName = QString("bsd_%1.html").arg(shipName);
    QString htmlPath = QDir::cleanPath(outPath(shipName) + QDir::separator() + htmlFileName);

    env.write(temp, data, htmlPath.toStdString());
    QString pdfName = QString("bsd_%1 %2.pdf").arg(shipName).arg(dateTimeNow());
    writePDF(htmlPath, QDir::cleanPath(outPath(shipName) + QDir::separator() + pdfName));
}

void DocumentWriter::writeCertificate(const nlohmann::json &data)
{
    qDebug() << "Parsing template...";
    inja::Template temp = env.parse_template(fullPathOf(CERTIFICATE_TEMP).toStdString());
    qDebug() << "CReating certificate file...";
    QString shipName = QString::fromStdString(data["ship_name"]);
    QString htmlFileName = QString("certificate_%1.html").arg(shipName);
    QString htmlPath = QDir::cleanPath(outPath(shipName) + QDir::separator() + htmlFileName);

    env.write(temp, data, htmlPath.toStdString());
    QString pdfName = QString("certificate_%1 %2.pdf").arg(shipName).arg(dateTimeNow());
    writePDF(htmlPath, QDir::cleanPath(outPath(shipName) + QDir::separator() + pdfName));
}

void DocumentWriter::writeInvoice(const nlohmann::json &data)
{
    inja::Template temp = env.parse_template(fullPathOf(INVOICE_TEMP).toStdString());
    QString shipName = QString::fromStdString(data["ship_name"]);
    QString htmlFileName = QString("invoice_%1.html").arg(shipName);
    QString htmlPath = QDir::cleanPath(outPath(shipName) + QDir::separator() + htmlFileName);

    env.write(temp, data, htmlPath.toStdString());
    QString pdfName = QString("invoice_%1 %2.pdf").arg(shipName).arg(dateTimeNow());
    writePDF(htmlPath, QDir::cleanPath(outPath(shipName) + QDir::separator() + pdfName));
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

QString DocumentWriter::outPath(const QString &shipName)
{
    QStringList docPaths = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString doc = docPaths.first();
    QString out = QDir::cleanPath(doc + QDir::separator() + "spce" + QDir::separator() + shipName);
    QDir dir(out);
    if (!dir.exists())
        dir.mkpath(out);
    return out;
}

QString DocumentWriter::dateTimeNow()
{
    return QDateTime::currentDateTime().toString("dd MMM yyyy hhmmss");
}

void DocumentWriter::write(const nlohmann::json &data)
{
    writeCertificate(data);
    writeInvoice(data);
    writeBSD(data);
    emit documentsCreated(outPath(QString::fromStdString(data["ship_name"])));
}

void DocumentWriter::writePDF(const QString &filePath, const QString &out)
{
    QString program("wkhtmltopdf.exe");
    QStringList args;
    args << "--no-pdf-compression" << "--dpi" << "300" << "--print-media-type";
    args << filePath << out;

    QProcess *process = new QProcess;
    process->start(program, args);
    QObject::connect(process, &QProcess::finished, this, [filePath](){
        QFile::remove(filePath);
    });

}
} // namespace spce_core

