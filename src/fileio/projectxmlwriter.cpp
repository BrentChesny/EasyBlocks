#include "projectxmlwriter.h"
#include "../blockrepr/constantblockrepr.h"
#include "../blockrepr/spriteblockrepr.h"

#include <QBuffer>

ProjectXMLWriter::ProjectXMLWriter(Project* project) : _project(project)
{
}

bool ProjectXMLWriter::writeToFile(QString path)
{
    QDomDocument document("EasyBlocksProject");
    document.appendChild(projectToXML(_project));

    if (!path.isNull())
    {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return false;
        }
        else
        {
            QTextStream stream(&file);
            stream << document.toString();
            file.close();
            _project->setPath(path);
            return true;
        }
    }

    return false;
}

QDomElement ProjectXMLWriter::projectToXML(Project *project)
{
    QDomDocument doc;
    QDomElement projectElement = doc.createElement("Project");

    // screen
    projectElement.appendChild(screenToXML(project->getScreen()));

    // vars
    QDomElement vars = doc.createElement("Variables");
    foreach (VarBlockRepr* var, project->getVars()) {
        vars.appendChild(varToXML(var));
    }
    projectElement.appendChild(vars);

    // sprites
    foreach (SpriteRepr* sprite, project->getSprites()) {
        projectElement.appendChild(spriteToXML(sprite));
    }

    // userstatements
    foreach (UserStatementRepr* us, project->getUserStatements()) {
        projectElement.appendChild(userstatementToXML(us));
    }

    return projectElement;
}

QDomElement ProjectXMLWriter::screenToXML(ScreenRepr *screen)
{
    QDomDocument doc;

    QDomElement screenElement = doc.createElement("Screen");
    screenElement.setAttribute("width", QString::number(screen->getSize().width()));
    screenElement.setAttribute("height", QString::number(screen->getSize().height()));

    QDomElement color = doc.createElement("Color");
    color.setAttribute("red", QString::number(screen->getBackgroundColor().red()));
    color.setAttribute("green", QString::number(screen->getBackgroundColor().green()));
    color.setAttribute("blue", QString::number(screen->getBackgroundColor().blue()));
    screenElement.appendChild(color);

    QDomElement background = doc.createElement("Background");
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    screen->getBackgroundImage().save(&buffer, "PNG");
    QDomText imagedata = doc.createTextNode(QString(bytes.toBase64()));
    background.appendChild(imagedata);
    background.setAttribute("use", screen->useImage() ? "true" : "false");
    screenElement.appendChild(background);

    return screenElement;
}

QDomElement ProjectXMLWriter::spriteToXML(SpriteRepr *sprite)
{
    QDomDocument doc;

    QDomElement spriteElement = doc.createElement("Sprite");
    spriteElement.setAttribute("name", sprite->getName());
    spriteElement.setAttribute("width", QString::number(sprite->getSize().width()));
    spriteElement.setAttribute("height", QString::number(sprite->getSize().height()));
    spriteElement.setAttribute("x", QString::number(sprite->getPosition().x()));
    spriteElement.setAttribute("y", QString::number(sprite->getPosition().y()));
    spriteElement.setAttribute("rotation", QString::number(sprite->getRotation()));
    spriteElement.setAttribute("image", QString::number(sprite->getSelectedImageIndex()));

    // sprite images
    QDomElement images = doc.createElement("Images");
    foreach (QPixmap* pixmap, sprite->getImages()) {
        QDomElement data = doc.createElement("Data");
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        pixmap->save(&buffer, "PNG");
        QDomText imagedata = doc.createTextNode(QString(bytes.toBase64()));
        data.appendChild(imagedata);
        images.appendChild(data);
    }
    spriteElement.appendChild(images);

    // sprite blocks
    QDomElement blocks = doc.createElement("Blocks");
    foreach (BlockRepr* block, sprite->getBlocks()) {
        blocks.appendChild(blockToXML(block));
    }
    spriteElement.appendChild(blocks);

    // sprite vars
    QDomElement vars = doc.createElement("Variables");
    foreach (VarBlockRepr* var, sprite->getVars()) {
        vars.appendChild(varToXML(var));
    }
    spriteElement.appendChild(vars);

    return spriteElement;
}

QDomElement ProjectXMLWriter::blockToXML(BlockRepr *block)
{
    QDomDocument doc;
    QDomElement blockElement = doc.createElement("Block");
    blockElement.setAttribute("id", block->getId());
    blockElement.setAttribute("x", QString::number(block->getPosition().x()));
    blockElement.setAttribute("y", QString::number(block->getPosition().y()));
    blockElement.setAttribute("locked", block->isLocked() ? "true" : "false");
    blockElement.setAttribute("return", QString::number(block->getReturnType()));

    if (block->isVarBlockRepr()) {
        VarBlockRepr* v = (VarBlockRepr*) block;
        blockElement.setAttribute("name", v->getVarName());
        blockElement.setAttribute("var", "true");
    } else if (block->isConstantBlockRepr()) {
        ConstantBlockRepr* c = (ConstantBlockRepr*) block;
        blockElement.setAttribute("value", c->getValue().toString());
        blockElement.setAttribute("constant", "true");
    } else if (block->isSpriteBlockRepr()) {
        SpriteBlockRepr* s = (SpriteBlockRepr*) block;
        blockElement.setAttribute("spriteindex", _project->getIndexOfSprite(s->getSpriteRepr()));
        blockElement.setAttribute("sprite", "true");
    } else if (block->isUserStatementRepr()) {
        UserStatementBlockRepr* usbr = (UserStatementBlockRepr*) block;
        blockElement.setAttribute("userstatementindex", _project->getIndexOfUserStatement(usbr->getUserStatementRepr()));
        blockElement.setAttribute("userstatement", "true");
    }

    // params
    QDomElement params = doc.createElement("Params");
    for (int i = 0; i < block->getNumParams(); ++i) {
        QDomElement param = doc.createElement("Param");
        if(block->getParam(i) != NULL) {
            param.appendChild(blockToXML(block->getParam(i)));
        params.appendChild(param);
        }
    }
    blockElement.appendChild(params);

    // bodies
    QDomElement bodies = doc.createElement("Bodies");
    for (int i = 0; i < block->getNumBodies(); ++i) {
        QDomElement body = doc.createElement("Body");
        if(block->getBody(i) != NULL)
            body.appendChild(blockToXML(block->getBody(i)));
        bodies.appendChild(body);
    }
    blockElement.appendChild(bodies);

    // next block
    QDomElement next = doc.createElement("Next");
        if(block->getNextStatement() != NULL)
            next.appendChild(blockToXML(block->getNextStatement()));
    blockElement.appendChild(next);

    return blockElement;
}

QDomElement ProjectXMLWriter::varToXML(VarBlockRepr *var)
{
    QDomDocument doc;
    QDomElement varElement = doc.createElement("Var");
    varElement.setAttribute("name", var->getVarName());
    varElement.setAttribute("return", var->getReturnType());
    varElement.setAttribute("locked", var->isLocked() ? "true" : "false");

    return varElement;
}

QDomElement ProjectXMLWriter::userstatementToXML(UserStatementRepr *us)
{
    QDomDocument doc;
    QDomElement usElement = doc.createElement("UserStatement");
    usElement.setAttribute("description", us->getParamDescription());
    usElement.setAttribute("paramnames", us->getParamNames().join(","));
    QStringList types;
    foreach (Block::ParamType type, us->getParamTypes())
        types.append(QString::number(type));
    usElement.setAttribute("paramtypes", types.join(","));

    // blocks in the userstatement
    QDomElement blocks = doc.createElement("Blocks");
    foreach (BlockRepr* block, us->getBlocks()) {
        blocks.appendChild(blockToXML(block));
    }
    usElement.appendChild(blocks);

    // vars
    QDomElement vars = doc.createElement("Variables");
    foreach (VarBlockRepr* var, us->getVars()) {
        //if (!us->isParamVar(var->getVarName()))
            vars.appendChild(varToXML(var));
    }
    usElement.appendChild(vars);

    return usElement;
}
