#include "levelxmlreader.h"

#include <QFile>
#include <QDomDocument>

LevelXMLReader::LevelXMLReader() : _levelHandler(NULL)
{
}

bool LevelXMLReader::readFromFile(const QString &path)
{
    if(_levelHandler != NULL) {
        delete _levelHandler;
        _levelHandler = NULL;
    }

    if(!path.isNull()) {
        QFile file(path);
        //if failed to open
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

        //create DomDocument
        else {
            QDomDocument doc;
            doc.setContent(&file);
            _levelHandler = new LevelHandler;
            return createLevelHandler(doc.firstChildElement());
        }
    }

    return false;
}

bool LevelXMLReader::createLevelHandler(const QDomElement& element)
{
    if(element.isNull())
        return false;

    //set default
    if(element.attribute("default") == "invisible")
        _levelHandler->setDefault(false);

    //invisible blocks
    QDomNodeList invisible = element.firstChildElement("InvisibleBlocks").elementsByTagName("Block");
    for(int i = 0; i < invisible.length(); i++)
        _levelHandler->registerInvisible(invisible.at(i).toElement().attribute("id"));

    //visible blocks
    QDomNodeList visible = element.firstChildElement("VisibleBlocks").elementsByTagName("Block");
    for(int i = 0; i < visible.length(); i++)
        _levelHandler->registerVisible(visible.at(i).toElement().attribute("id"));

    return true;
}
