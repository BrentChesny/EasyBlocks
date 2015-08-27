#include "projectxmlreader.h"

#include <QDebug>

ProjectXMLReader::ProjectXMLReader() : _project(NULL), _loadingFailed(false)
{
}

bool ProjectXMLReader::readFromFile(QString path)
{
    if (_project != NULL) {
        delete _project;
        _project = NULL;
    }

    if (!path.isNull())
    {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            setLoadingFailed(QObject::tr("Could not open file"));
            return false;
        }
        else
        {
            QDomDocument document;
            document.setContent(&file);
            _project = new Project;
            _project->setPath(path);
            projectFromXML(document.firstChildElement());
            return !_loadingFailed;
        }
    }

    setLoadingFailed(QObject::tr("Could not open file"));
    return false;
}

void ProjectXMLReader::projectFromXML(QDomElement project)
{
    //check if containing the required elements
    if(project.isNull() || project.elementsByTagName("Screen").size() == 0) {
        setLoadingFailed(QObject::tr("File is corrupted"));
        return;
    }

    _project->setScreen(screenFromXML(project.elementsByTagName("Screen").at(0).toElement()));

    // remove old sprites
    for (int i = _project->getSprites().size() - 1; i >= 0; --i) {
        _project->removeSprite(i);
    }

    // userstatements
    QDomElement us = project.firstChildElement("UserStatement");
    while (!us.isNull()) {
        UserStatementRepr* usrepr = userstatementFromXML(us);
        _project->addUserStatement(usrepr);
        us = us.nextSiblingElement("UserStatement");
    }
    us = project.firstChildElement("UserStatement");
    QList<UserStatementRepr*> usreprs = _project->getUserStatements();
    int i = 0;
    while (!us.isNull()) {
        UserStatementRepr* usrepr = usreprs.at(i);
        addBlocksToUserStatement(usrepr, us);
        i++;
        us = us.nextSiblingElement("UserStatement");
    }

    // add loaded sprites
    QDomElement sprite = project.firstChildElement("Sprite");
    while (!sprite.isNull()) {
        SpriteRepr* s = spriteFromXML(sprite);
        _project->addSprite(s);
        sprite = sprite.nextSiblingElement("Sprite");
    }
    sprite = project.firstChildElement("Sprite");
    QList<SpriteRepr*> sprites = _project->getSprites();
    i = 0;
    while (!sprite.isNull()) {
        SpriteRepr* s = sprites.at(i);
        addBlocksToSprite(s, sprite);
        i++;
        sprite = sprite.nextSiblingElement("Sprite");
    }

    // add vars
    QDomElement var = project.firstChildElement("Variables").firstChildElement("Var");
    while (!var.isNull()) {
        _project->addVariable(varFromXML(var));
        var = var.nextSiblingElement("Var");
    }
}

ScreenRepr* ProjectXMLReader::screenFromXML(QDomElement screen)
{
    ScreenRepr* scr = new ScreenRepr;

    scr->setSize(QSize(screen.attribute("width").toInt(), screen.attribute("height").toInt()));

    QDomElement color = screen.elementsByTagName("Color").at(0).toElement();
    scr->setBackgroundColor(QColor(color.attribute("red").toInt(), color.attribute("green").toInt(), color.attribute("blue").toInt()));

    QDomElement bg = screen.elementsByTagName("Background").at(0).toElement();
    if (bg.attribute("use") == "true") {
        QPixmap image;
        image.loadFromData(QByteArray::fromBase64(bg.text().trimmed().toUtf8().constData()));
        scr->setBackgroundImage(image);
    }

    return scr;
}

SpriteRepr* ProjectXMLReader::spriteFromXML(QDomElement sprite)
{
    SpriteRepr* spr = new SpriteRepr;
    return spr;
}

void ProjectXMLReader::addBlocksToSprite(SpriteRepr *spr, QDomElement xml)
{
    QDomElement imagedata = xml.firstChildElement("Images").firstChildElement("Data");
    while (!imagedata.isNull()) {
        QPixmap* image = new QPixmap;
        image->loadFromData(QByteArray::fromBase64(imagedata.text().trimmed().toUtf8().constData()));
        spr->appendImage(image);
        imagedata = imagedata.nextSiblingElement("Data");
    }

    spr->setPosition(QPoint(xml.attribute("x").toInt(), xml.attribute("y").toInt()));
    spr->setSize(QSize(xml.attribute("width").toInt(), xml.attribute("height").toInt()));
    spr->setName(xml.attribute("name"));
    spr->setRotation(xml.attribute("rotation").toInt());
    spr->setSelectedImage(xml.attribute("image").toInt());

    // blocks
    QDomElement block = xml.firstChildElement("Blocks").firstChildElement("Block");
    while (!block.isNull()) {
        BlockRepr* bl = blockFromXML(block);
        if(bl != NULL) {
            bl->setHolderParent(spr);
            spr->addBlock(bl);
        }
        block = block.nextSiblingElement("Block");
    }

    // vars
    QDomElement var = xml.firstChildElement("Variables").firstChildElement("Var");
    while (!var.isNull()) {
        spr->addVariable(varFromXML(var));
        var = var.nextSiblingElement("Var");
    }

}

void ProjectXMLReader::addBlocksToUserStatement(UserStatementRepr *us, QDomElement xml)
{
    // blocks
    QDomElement block = xml.firstChildElement("Blocks").firstChildElement("Block");
    while (!block.isNull()) {
        BlockRepr* bl = blockFromXML(block);
        bl->setHolderParent(us);
        us->addBlock(bl);
        block = block.nextSiblingElement("Block");
    }

    // vars
    QDomElement var = xml.firstChildElement("Variables").firstChildElement("Var");
    while (!var.isNull()) {
        us->addVariable(varFromXML(var));
        var = var.nextSiblingElement("Var");
    }
}

BlockRepr* ProjectXMLReader::blockFromXML(QDomElement block)
{
    if(block.attribute("var") == "true")
        return varFromXML(block);
    else if(block.attribute("constant") == "true")
        return constantFromXML(block);
    else if(block.attribute("sprite") == "true")
        return spriteBlockFromXML(block);
    else if(block.attribute("userstatement") == "true")
        return userstatementBlockFromXML(block);
    else if (block.attribute("id") == "Function_Start")
        return functionStartBlockFromXML(block);
    else
        return regularBlockFromXML(block);
}

BlockRepr* ProjectXMLReader::regularBlockFromXML(QDomElement block)
{
    QString id = block.attribute("id");
    BlockRepr* bl = _project->getBlockReprLibrary()->getBlockReprInstance(id);

    if(bl == NULL) {
        setLoadingFailed(QObject::tr("The following block could not be found: ") + id);
        return bl;
    }

    bl->setPosition(QPoint(block.attribute("x").toInt(), block.attribute("y").toInt()));
    bl->setLock(block.attribute("locked") == "true");

    // parameters
    QDomElement param = block.firstChildElement("Params").firstChildElement("Param");
    int i = 0;
    while (!param.isNull()) {
        if (!param.firstChildElement("Block").isNull())
            bl->placeParam(blockFromXML(param.firstChildElement("Block")), i);
        i++;
        param = param.nextSiblingElement("Param");
    }

    // bodies
    QDomElement body = block.firstChildElement("Bodies").firstChildElement("Body");
    i = 0;
    while (!body.isNull()) {
        if (!body.firstChildElement("Block").isNull())
            bl->placeBody(blockFromXML(body.firstChildElement("Block")), i);
        i++;
        body = body.nextSiblingElement("Body");
    }

    // next block
    if (!block.firstChildElement("Next").firstChildElement("Block").isNull())
        bl->placeNextStatement(blockFromXML(block.firstChildElement("Next").firstChildElement("Block")));

    return bl;
}

SpriteBlockRepr* ProjectXMLReader::spriteBlockFromXML(QDomElement block)
{
    SpriteBlockRepr* s = new SpriteBlockRepr(_project->getSprites().at(block.attribute("spriteindex").toInt()));
    s->setPosition(QPoint(block.attribute("x").toInt(), block.attribute("y").toInt()));
    s->setLock(block.attribute("locked") == "true");

    return s;
}

VarBlockRepr* ProjectXMLReader::varFromXML(QDomElement var)
{
    VarBlockRepr* v = new VarBlockRepr((Block::ParamType) var.attribute("return").toInt(), var.attribute("name"), _project, false);
    v->setPosition(QPoint(var.attribute("x").toInt(), var.attribute("y").toInt()));
    v->setLock(var.attribute("locked") == "true");
    return v;
}

ConstantBlockRepr* ProjectXMLReader::constantFromXML(QDomElement constant)
{
    QString id = constant.attribute("id");
    ConstantBlockRepr* c = (ConstantBlockRepr*) _project->getBlockReprLibrary()->getBlockReprInstance(id);
    c->setPosition(QPoint(constant.attribute("x").toInt(), constant.attribute("y").toInt()));
    c->setLock(constant.attribute("locked") == "true");
    if (id == "Number_Number")
        c->setValue(QVariant(constant.attribute("value").toDouble()));
    else if (id == "String_String")
        c->setValue(QVariant(constant.attribute("value")));

    return c;
}

UserStatementRepr *ProjectXMLReader::userstatementFromXML(QDomElement us)
{
    QStringList strtypes = us.attribute("paramtypes").split(",");
    QList<Block::ParamType> types;
    foreach(QString type, strtypes)
        types.append((Block::ParamType) type.toInt());

    UserStatementRepr* usrepr = new UserStatementRepr(us.attribute("description"), types, us.attribute("paramnames").split(","));

    return usrepr;
}

UserStatementBlockRepr *ProjectXMLReader::userstatementBlockFromXML(QDomElement block)
{
    UserStatementBlockRepr* usbr = new UserStatementBlockRepr(_project->getUserStatements().at(block.attribute("userstatementindex").toInt()));

    // parameters
    QDomElement param = block.firstChildElement("Params").firstChildElement("Param");
    int i = 0;
    while (!param.isNull()) {
        if (!param.firstChildElement("Block").isNull())
            usbr->placeParam(blockFromXML(param.firstChildElement("Block")), i);
        i++;
        param = param.nextSiblingElement("Param");
    }

    // next block
    if (!block.firstChildElement("Next").firstChildElement("Block").isNull())
        usbr->placeNextStatement(blockFromXML(block.firstChildElement("Next").firstChildElement("Block")));


    return usbr;
}

FunctionStartBlockRepr *ProjectXMLReader::functionStartBlockFromXML(QDomElement block)
{
    FunctionStartBlockRepr* fs = new FunctionStartBlockRepr;
    fs->setPosition(QPoint(block.attribute("x").toInt(), block.attribute("y").toInt()));
    fs->setLock(block.attribute("locked") == "true");

    // next block
    if (!block.firstChildElement("Next").firstChildElement("Block").isNull())
        fs->placeNextStatement(blockFromXML(block.firstChildElement("Next").firstChildElement("Block")));

    return fs;
}

void ProjectXMLReader::setLoadingFailed(QString message)
{
    if(_loadingFailed)
        return;

    _loadingFailed = true;
    _loadMessage = message;
}
