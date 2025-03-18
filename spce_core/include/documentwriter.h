#ifndef DOCUMENTWRITER_H
#define DOCUMENTWRITER_H

#include "spce_core_global.h"
#include "json.hpp"
#include "inja.hpp"

#include <QObject>

namespace spce_core {
enum DocumentType{
    BSD,
    Certificate,
    Invoice
};

class SPCE_CORE_EXPORT DocumentWriter : public QObject
{
public:
    DocumentWriter(QObject *parent = nullptr);

    inja::Environment env;

    static QString templatePath();

    /**
     * @brief Verify if the template file already exist in the template folder or not
     * @param filename The template file name
     * @return true if exists, false otherwise
     */
    bool templateExists(const QString &filename);

    /**
     * @brief This function will verify if the template files already exists, and create them if not
     */
    void initTemplates();

private:
    const QString BSD_TEMP = "bsd.html";
    const QString CERTIFICATE_TEMP = "certificate.html";
    const QString INVOICE_TEMP = "invoice.html";

private:
    void writeBSD(const nlohmann::json &data);
     /**
     * @brief Writes a certificate based on the provided JSON data.
     *
     * This method generates and writes a certificate file using the information provided
     * in the JSON object. The JSON parameter must contain the following key-value pairs:
     *
     * - `"ship_name"` (string, required): The full name of the ship.
     * - `"imo_number"` (string, required): The unique IMO number of the ship.
     * - `"flag_state"` (string, required): The registered flag state of the ship
     * - `"gross_tonnage"` (int, required): The ship gross tonnage
     * - `"callsign"`  (string, required): Distinctive number or letters of the ship
     * - `"ship_type"` (string, required: The type of the ship
     * Example JSON:
     * @code
     * {
     *     "ship_name": "F LINE",
     *     "imo_number": "9320324",
     *     "flag_state": "Barbados",
     *     "gross_tonnage": 23432,
     *     "callsign": "PO5D4R",
     *     "ship_type": "bulk carrier"
     * }
     * @endcode
     *
     * @param data The JSON object containing certificate details.
     */
    void writeCertificate(const nlohmann::json &data);
    void writeInvoice(const nlohmann::json &data);

    void createTemplateDir();

    QString fullPathOf(const QString &temp);

    QString outPath(const QString &fileName);
public slots:
    void write(const nlohmann::json &data);

};
} // namespace spce_core


#endif // DOCUMENTWRITER_H
