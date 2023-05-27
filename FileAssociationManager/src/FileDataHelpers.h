#pragma once

#include "record.h"
#include <Shlwapi.h>

QByteArray readDataFromFile(const QString filePath, bool &error);

bool writeDataToFile(const QByteArray bytes, const QString filePath);

std::string getFileTypeProgram(const char *ext, int info);

std::vector<Record> parseFromJsonData(const QByteArray data, bool &error);

QByteArray parseToJsonData(const std::vector<Record> data);

std::vector<Record> parseFromCSVData(QList<QStringList> csvData, bool &error);

QByteArray parseToCSVData(std::vector<Record> data);
