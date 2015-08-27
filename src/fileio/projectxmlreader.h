#ifndef PROJECTXMLREADER_H
#define PROJECTXMLREADER_H

#include <QDomElement>
#include <QDomDocument>

#include "../project.h"
#include "../blockrepr/constantblockrepr.h"
#include "../blockrepr/spriteblockrepr.h"
#include "../blockrepr/functionstartblockrepr.h"

/**
 * @brief The ProjectXMLReader class
 *
 * @author Brent Chesny
 */
class ProjectXMLReader
{
public:
    /**
     * @brief Constructor method
     * @param path The path of the file to read
     */
    ProjectXMLReader();

    /**
     * @brief Reads the file at the given path and creates a project with it. The project can then be retrieved with the getProject method.
     * @param path The path at which the file is located
     * @return True if the file was successfully read, false otherwise
     */
    bool readFromFile(QString path);

    /**
     * @brief Returns the project created with the readFromFile method
     * @return The project created with the readFromFile method
     */
    Project* getProject() const { return _project; }

    /**
     * @brief Returns whether or not the loading of the file failed
     * @return True if failed to load the file, false if succeeded
     */
    bool loadingFailed() const {return _loadingFailed;}

    /**
     * @brief Returns the loadMessage. This message is empty if the loading did not fail
     * @return The loadMessage
     */
    QString getLoadMessage() const {return _loadMessage;}

private:
    Project* _project;
    bool _loadingFailed;
    QString _loadMessage;

    void projectFromXML(QDomElement project);
    ScreenRepr* screenFromXML(QDomElement screen);
    SpriteRepr* spriteFromXML(QDomElement sprite);
    BlockRepr* blockFromXML(QDomElement block);
    BlockRepr* regularBlockFromXML(QDomElement block);
    SpriteBlockRepr* spriteBlockFromXML(QDomElement block);
    VarBlockRepr* varFromXML(QDomElement var);
    ConstantBlockRepr* constantFromXML(QDomElement constant);
    UserStatementRepr* userstatementFromXML(QDomElement us);
    UserStatementBlockRepr* userstatementBlockFromXML(QDomElement us);
    FunctionStartBlockRepr* functionStartBlockFromXML(QDomElement block);
    void addBlocksToSprite(SpriteRepr* spr, QDomElement xml);
    void addBlocksToUserStatement(UserStatementRepr* us, QDomElement xml);

    void setLoadingFailed(QString message);
};

#endif // PROJECTXMLREADER_H
