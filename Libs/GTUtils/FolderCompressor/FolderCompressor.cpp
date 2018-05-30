#include "FolderCompressor.h"

FolderCompressor::FolderCompressor(QObject *parent) :
    QObject(parent)
{
}

bool FolderCompressor::compressFolder(QString sourceFolder, QString destinationFile)
{
    QDir src(sourceFolder);
    if (!src.exists())
    {
        return false;
    }

    m_file.setFileName(destinationFile);
    if (!m_file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    m_dataStream.setDevice(&m_file);

    bool success = compress(sourceFolder, "");
    m_file.close();

    return success;
}

bool FolderCompressor::compress(QString sourceFolder, QString prefex)
{
    QDir dir(sourceFolder);
    if (!dir.exists())
        return false;

    dir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    QFileInfoList foldersList = dir.entryInfoList();

    for(int i = 0; i < foldersList.length(); i++)
    {
        QString folderName = foldersList.at(i).fileName();
        QString folderPath = dir.absolutePath() + "/"+folderName;
        QString newPrefex = prefex + "/" + folderName;

        compress(folderPath, newPrefex);
    }

    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    QFileInfoList filesList = dir.entryInfoList();

    for(int i = 0; i < filesList.length(); i++)
    {
        QFile file(dir.absolutePath() + "/" + filesList.at(i).fileName());
        if(!file.open(QIODevice::ReadOnly))
        {
            return false;
        }

        m_dataStream << QString(prefex + "/" + filesList.at(i).fileName());
        m_dataStream << qCompress(file.readAll());

        file.close();
    }

    return true;
}

bool FolderCompressor::decompressFolder(QString sourceFile, QString destinationFolder)
{
    QFile src(sourceFile);
    if (!src.exists())
    {
        return false;
    }
    QDir dir;
    if (!dir.mkpath(destinationFolder))
    {
        return false;
    }

    m_file.setFileName(sourceFile);
    if (!m_file.open(QIODevice::ReadOnly))
        return false;

    m_dataStream.setDevice(&m_file);

    while (!m_dataStream.atEnd())
    {
        QString fileName;
        QByteArray data;

        m_dataStream >> fileName >> data;

        QString subfolder;
        for(int i = fileName.length() - 1; i > 0; i--)
        {
            if ((QString(fileName.at(i)) == QString("\\")) || (QString(fileName.at(i)) == QString("/")))
            {
                subfolder = fileName.left(i);
                dir.mkpath(destinationFolder + "/" + subfolder);
                break;
            }
        }

        QFile outFile(destinationFolder + "/" + fileName);
        if (!outFile.open(QIODevice::WriteOnly))
        {
            m_file.close();
            return false;
        }
        outFile.write(qUncompress(data));
        outFile.close();
    }

    m_file.close();
    return true;
}
