#ifndef FOLDERCOMPRESSOR_H
#define FOLDERCOMPRESSOR_H

#include <QFile>
#include <QObject>
#include <QDataStream>
#include <QDir>

#include "gtutils_global.h"

class GTUTILSSHARED_EXPORT FolderCompressor : public QObject
{
    Q_OBJECT
public:
    explicit FolderCompressor(QObject *parent = 0);
    bool compressFolder(QString sourceFolder, QString destinationFile);
    bool decompressFolder(QString sourceFile, QString destinationFolder);

private:
    QFile m_file;
    QDataStream m_dataStream;

    bool compress(QString sourceFolder, QString prefex);
};

#endif // FOLDERCOMPRESSOR_H
