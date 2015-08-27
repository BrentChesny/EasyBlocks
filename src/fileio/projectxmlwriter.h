#ifndef PROJECTXMLWRITER_H
#define PROJECTXMLWRITER_H

#include <QDomDocument>
#include <QDomElement>

#include "../project.h"

/**
 * @brief The ProjectXMLWriter class
 *
 * @author Brent Chesny
 */
class ProjectXMLWriter
{
public:
    /**
     * @brief Constructor method
     * @param project The project to write to a file.
     */
    ProjectXMLWriter(Project* project);

    /**
     * @brief Writes the project to the file located by the given path
     * @param path The path of the file to write to
     * @return True if the file as successfully written, false otherwize
     */
    bool writeToFile(QString path);

private:
    Project* _project;

    QDomElement projectToXML(Project* project);
    QDomElement screenToXML(ScreenRepr* screen);
    QDomElement spriteToXML(SpriteRepr* sprite);
    QDomElement blockToXML(BlockRepr* block);
    QDomElement varToXML(VarBlockRepr* var);
    QDomElement userstatementToXML(UserStatementRepr* us);
};

#endif // PROJECTXMLWRITER_H
