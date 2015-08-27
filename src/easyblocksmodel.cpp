#include "easyblocksmodel.h"

#include <QDebug>

EasyBlocksModel::EasyBlocksModel() : QObject(), _project(NULL)
{
    _project = new Project;
    connect(_project, SIGNAL(updated()), this, SLOT(projectUpdated()));
}

EasyBlocksModel::~EasyBlocksModel()
{
    delete _project;
}

void EasyBlocksModel::setProject(Project* project)
{
    if (_project != NULL)
        delete _project;

    _project = project;
    connect(_project, SIGNAL(updated()), this, SLOT(projectUpdated()));
    projectUpdated();
    emit projectLoaded();
}

void EasyBlocksModel::projectUpdated()
{
    emit updated();
}
