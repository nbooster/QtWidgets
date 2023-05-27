#include "filedatahelpers.h"

#include <array>
#include <sstream>
#include <stdexcept>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

static void errorFallback(const char *errorMessage, bool &error)
{
    error = true;
    qWarning(errorMessage);
}

/*! Reads byte data from a file. */
QByteArray readDataFromFile(const QString filePath, bool &error)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        error = true;
        return QByteArray();
    }

    QByteArray data = file.readAll();
    file.close();
    error = false;
    return data;
}

/*! Writes bytes data to a file. */
bool writeDataToFile(const QByteArray bytes, const QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    file.write(bytes);
    file.close();
    return true;
}

/*! Returns info about a particular file extension in a Windows OS. */
std::string getFileTypeProgram(const char *ext, int info)
{
    TCHAR szBuf[1000];
    DWORD cbBufSize = sizeof(szBuf);
    HRESULT hr = AssocQueryString(0, static_cast<ASSOCSTR>(info), ext, NULL, szBuf, &cbBufSize);
    if (FAILED(hr))
    {
        qDebug("Error");
        return std::string();
    }
    std::string strFriendlyProgramName = "";
    for (int i = 0; i < cbBufSize; ++i)
        strFriendlyProgramName += szBuf[i];
    return strFriendlyProgramName;
}

/*! Creates the model data from a byte sequence that encodes JSON file data. */
std::vector<Record> parseFromJsonData(const QByteArray data, bool &error)
{
    static const char *jsonErrorMessage = "Error while parsing JSON file...";
    QJsonParseError *tempError = nullptr;
    QJsonDocument document = QJsonDocument::fromJson(data, tempError);
    if (tempError)
    {
        errorFallback(jsonErrorMessage, error);
        return std::vector<Record>();
    }
    QJsonObject object = document.object();
    QJsonValue value = object.value("rows");
    if (!value.isArray())
    {
        errorFallback(jsonErrorMessage, error);
        return std::vector<Record>();
    }
    QJsonArray array = value.toArray();
    std::vector<Record> records;
    for (const QJsonValue &v : array)
    {
        QJsonObject tempJsonObject = v.toObject();
        QJsonValue valueStatus = tempJsonObject.value("status");
        QJsonValue valueIconFileName = tempJsonObject.value("icon");
        QJsonValue valueExtension = tempJsonObject.value("extension");
        QJsonValue valueAppName = tempJsonObject.value("appName");
        QJsonValue valueExePath = tempJsonObject.value("fullExePath");

        if (!valueStatus.isBool() || !valueIconFileName.isString() || !valueExtension.isString()
            || !valueAppName.isString() || !valueExePath.isString())
        {
            errorFallback(jsonErrorMessage, error);
            return std::vector<Record>();
        }

        records.emplace_back(valueStatus.toBool(), valueExtension.toString(),
                             valueIconFileName.toString(), valueAppName.toString(),
                             valueExePath.toString());
    }
    error = false;
    return records;
}

/*! Encodes the model data to a byte sequence that encodes a valid JSON format. */
QByteArray parseToJsonData(const std::vector<Record> data)
{
    QJsonArray array;
    for (const Record &r : data)
        array.append(QJsonValue({ { "status", r.checked },
                                  { "icon", r.iconFileName },
                                  { "extension", r.extension },
                                  { "appName", r.appName },
                                  { "fullExePath", r.fullExePath } }));
    return QJsonDocument(QJsonObject{ { "rows", array } }).toJson(QJsonDocument::Indented);
}

/*! Creates the model data from a byte sequence that encodes CSV file data. */
std::vector<Record> parseFromCSVData(QList<QStringList> csvData, bool &error)
{
    static const char *csvErrorMessage = "Error while parsing CSV file...";
    if (csvData.empty() || csvData[0].size() != numberOfColumns)
    {
        errorFallback(csvErrorMessage, error);
        return std::vector<Record>();
    }
    csvData.removeFirst();
    std::vector<Record> records;
    for (const QStringList row : csvData)
    {
        if (row.size() != numberOfColumns)
        {
            errorFallback(csvErrorMessage, error);
            return std::vector<Record>();
        }
        const QString status = row.at(0);
        bool checked;
        if (!status.compare("TRUE", Qt::CaseInsensitive))
        {
            checked = true;
        }
        else if (!status.compare("FALSE", Qt::CaseInsensitive))
        {
            checked = false;
        }
        else
        {
            errorFallback(csvErrorMessage, error);
            return std::vector<Record>();
        }
        records.emplace_back(checked, row.at(2), row.at(1), row.at(3), row.at(4));
    }
    error = false;
    return records;
}

/*! Escapes double quotes inside the string and encloses it in double quotes. */
static QString toCSVString(QString string)
{
    QString local = string;
    local.replace('"', R"(\")");
    return QString('"' + local + '"');
}

/*! Encodes the model data to a byte sequence that encodes a valid CSV format. */
QByteArray parseToCSVData(std::vector<Record> data)
{
    QByteArray output = QString("Status,Icon,Extension,DefaultApplication,FullPath\n").toUtf8();
    for (const Record &rec : data)
        output += QString(toCSVString(QVariant(rec.checked).toString()) + ','
                          + toCSVString(rec.iconFileName) + ',' + toCSVString(rec.extension)
                          + toCSVString(rec.appName) + toCSVString(rec.fullExePath) + '\n')
                      .toUtf8();
    return output;
}
