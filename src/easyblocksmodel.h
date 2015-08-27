#ifndef EASYBLOCKSMODEL_H
#define EASYBLOCKSMODEL_H

#include <QObject>

#include "project.h"

/**
 * @brief The EasyBlocksModel class
 *
 * @author Brent Chesny
 */
class EasyBlocksModel : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor method
     */
    EasyBlocksModel();

    /**
     * @brief Destructor method
     */
    ~EasyBlocksModel();

    /**
     * @brief Returns a pointer to the current project
     * @return A pointer to the current project
     */
    Project* getProject() const { return _project; }

    void setProject(Project* project);

signals:
    void updated();
    void projectLoaded();

public slots:
    void projectUpdated();

private:
    Project* _project;

};

#endif // EASYBLOCKSMODEL_H
