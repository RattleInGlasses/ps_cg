#include "statsdocument.h"
#include "statskeyvaluemodel.h"
#include "istatsmodelprovider.h"
#include "statsserializer.h"
#include <QWidget>
#include <QFileDialog>
#include <QStandardPaths>

namespace
{
const QLatin1String FILE_FORMAT_FILTER("*.json");
}

StatsDocument::StatsDocument(QWidget *parent, IStatsModelProvider &provider)
    : QObject(parent)
    , m_provider(provider)
{

}

void StatsDocument::createNew()
{
    StatsKeyValueModel model;
    m_provider.setStatsModel(model);
    m_loadedDocumentPath = "";
}

bool StatsDocument::open()
{
    QString openPath = selectOpenPath();
    if (openPath.isEmpty())
    {
        return false;
    }
    m_loadedDocumentPath = openPath;

    StatsKeyValueModel model;
    StatsSerializer serializer(openPath);
    if (!serializer.load(model))
    {
        return false;
    }

    m_provider.setStatsModel(model);
    return true;
}

bool StatsDocument::save()
{
    if (m_loadedDocumentPath.isEmpty())
    {
        return saveAs();
    }
    if (saveData(m_loadedDocumentPath))
    {
        return true;
    }
    return saveAs();
}

bool StatsDocument::saveAs()
{
    QString savePath = selectSavePath();
    if (savePath.isEmpty())
    {
        return false;
    }
    m_loadedDocumentPath = savePath;
    return saveData(savePath);
}

QString StatsDocument::selectSavePath() const
{
    QString fromDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    auto parentWindow = qobject_cast<QWidget *>(parent());
    return QFileDialog::getSaveFileName(parentWindow, QString(), fromDir, FILE_FORMAT_FILTER);
}

QString StatsDocument::selectOpenPath() const
{
    QString fromDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    auto parentWindow = qobject_cast<QWidget *>(parent());
    return QFileDialog::getOpenFileName(parentWindow, QString(), fromDir, FILE_FORMAT_FILTER);
}

bool StatsDocument::saveData(const QString &savePath) const
{
    StatsSerializer serializer(savePath);
    return serializer.save(m_provider.statsModel());
}
