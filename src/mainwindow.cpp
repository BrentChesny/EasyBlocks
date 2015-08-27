#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fileio/projectxmlwriter.h"
#include "fileio/projectxmlreader.h"
#include "fileio/levelxmlreader.h"
#include "compiler/projectcompiler.h"

#include <QDebug>
#include <QPushButton>
#include <QTableWidget>
#include <QDomDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <QTranslator>

MainWindow::MainWindow(QCoreApplication *app, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _application(app)
{
    _trDutch.load(":/translations/easyblocks_nl.qm");
    //_application->installTranslator(&_trDutch);

    ui->setupUi(this);

    _model = new EasyBlocksModel;
    connect(_model, SIGNAL(updated()), this, SLOT(update()));

    setupUi();
    createToolbar();
    createMenubar();
    setUnifiedTitleAndToolBarOnMac(true);

    _unsaved = false;
    setTitle();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _model;
}

void MainWindow::setupUi()
{
    _mainLayout = new QHBoxLayout(this);
    _mainLayout->setContentsMargins(0, 0, 0, 0);
    _mainLayout->setAlignment(Qt::AlignLeft);
    ui->centralWidget->setLayout(_mainLayout);

    _blockReprLibrary = new BlockReprLibraryWidget(_model);
    _mainLayout->addWidget(_blockReprLibrary);

    _workspace = new WorkspaceWidget(_model, this);
    _workspace->setBlockReprLibWidget(_blockReprLibrary);
    _mainLayout->addWidget(_workspace);
}

void MainWindow::createToolbar()
{
    ui->mainToolBar->setContextMenuPolicy(Qt::NoContextMenu);
    _newAction = ui->mainToolBar->addAction(QIcon(":/img/img/document-new.png"), tr("New"), this, SLOT(newAction()));
    _openAction = ui->mainToolBar->addAction(QIcon(":/img/img/document-open.png"), tr("Open"), this, SLOT(openAction()));
    _saveAction = ui->mainToolBar->addAction(QIcon(":/img/img/document-save.png"), tr("Save"), this, SLOT(saveAction()));
    ui->mainToolBar->addSeparator();
    _runAction = ui->mainToolBar->addAction(QIcon(":/img/img/run.png"), tr("Run"), this, SLOT(runAction()));
    _stopAction = ui->mainToolBar->addAction(QIcon(":/img/img/stop.png"), tr("Stop"), this, SLOT(stopAction()));
    _pauseAction = ui->mainToolBar->addAction(QIcon(":/img/img/pause.png"), tr("Pause"), this, SLOT(pauseAction()));
    _pauseAction->setEnabled(false);
    _stopAction->setEnabled(false);
    ui->mainToolBar->addSeparator();
    _zoominAction = ui->mainToolBar->addAction(QIcon(":/img/img/zoomin.png"), tr("Zoom in"), _workspace, SLOT(incrementBlockViewScale()));
    _zoomoutAction = ui->mainToolBar->addAction(QIcon(":/img/img/zoomout.png"), tr("Zoom Out"), _workspace, SLOT(decrementBlockViewScale()));
}

void MainWindow::createMenubar()
{
    QMenu* fileMenu = ui->menuBar->addMenu(tr("File"));
    fileMenu->addAction(QIcon(":/img/img/document-new.png"), tr("New Project..."), this, SLOT(newAction()), QKeySequence::New);
    fileMenu->addAction(QIcon(":/img/img/document-open.png"), tr("Open Project..."), this, SLOT(openAction()), QKeySequence::Open);
    fileMenu->addSeparator();
    fileMenu->addAction(QIcon(":/img/img/document-save.png"), tr("Save"), this, SLOT(saveAction()), QKeySequence::Save);
    fileMenu->addAction(QIcon(":/img/img/document-saveas.png"), tr("Save As..."), this, SLOT(saveasAction()), QKeySequence::SaveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(QIcon(":/img/img/settings.png"), tr("Load configuration..."), this, SLOT(loadConfigAction()));
    fileMenu->addAction(tr("Reset configuration"), this, SLOT(resetConfigAction()));

    //QMenu* editMenu = ui->menuBar->addMenu(tr("Edit"));

    QMenu* projectMenu = ui->menuBar->addMenu(tr("Project"));
    projectMenu->addAction(QIcon(":/img/img/run.png"), tr("Run Project"), this, SLOT(runAction()), QKeySequence(Qt::CTRL + Qt::Key_R));

    QMenu* viewMenu = ui->menuBar->addMenu(tr("View"));
    ui->mainToolBar->toggleViewAction()->setText(tr("Show Toolbar"));
    viewMenu->addAction(ui->mainToolBar->toggleViewAction());

    QMenu* languageMenu = ui->menuBar->addMenu(tr("Language"));
    languageMenu->addAction(tr("English"), this, SLOT(translateEnglish()));
    languageMenu->addAction(tr("Nederlands"), this, SLOT(translateDutch()));
}

void MainWindow::disableToolsBasedOnTab(int index)
{
    if (index == 0) {
        _zoominAction->setEnabled(true);
        _zoomoutAction->setEnabled(true);
    }
    if (index == 1) {
        _zoominAction->setEnabled(false);
        _zoomoutAction->setEnabled(false);
    }
}

void MainWindow::renewBlockLibraryWidget()
{
    BlockReprLibraryWidget* newlib = new BlockReprLibraryWidget(_model);
    _mainLayout->removeWidget(_blockReprLibrary);
    _mainLayout->insertWidget(0, newlib);

    delete _blockReprLibrary;
    _blockReprLibrary = newlib;
    _workspace->setBlockReprLibWidget(_blockReprLibrary);
}

void MainWindow::setTitle()
{
    QString path = _model->getProject()->getPath();
    QString filename;

    if (path.isNull())
        filename = "untitled.ebp";
    else
        filename = QFileInfo(path).fileName();

    QString changes = _unsaved ? "*" : "";

    QString title = QString("EasyBlocks Visual Programming IDE - %1%2").arg(filename, changes);
    setWindowTitle(title);
}

void MainWindow::newAction()
{
    showSaveChangesDialog();

    _model->setProject(new Project);
    renewBlockLibraryWidget();
}

void MainWindow::openAction()
{
    showSaveChangesDialog();

    QString path = QFileDialog::getOpenFileName(this, tr("Opening file..."), QDir::homePath());//, tr("EasyBlocks Projects (*.epb)"));

    if (path.isNull())
        return;

    openProject(path);
}

void MainWindow::openProject(const QString &path)
{
    ProjectXMLReader reader;
    if (reader.readFromFile(path)) {
        _model->setProject(reader.getProject());
        renewBlockLibraryWidget();
    }
    else
        QMessageBox::critical(this, tr("Error: Could not open project"), reader.getLoadMessage());

    _unsaved = false;
    setTitle();
}

void MainWindow::saveAction()
{
    if (_model->getProject()->getPath().isNull())
        saveasAction();
    else {
        ProjectXMLWriter writer(_model->getProject());
        if (!writer.writeToFile(_model->getProject()->getPath()))
            QMessageBox::critical(this, tr("Error: Could not save project"), tr("An error occured while saving the project."));

        _unsaved = false;
        setTitle();
    }
}

void MainWindow::saveasAction()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Saving project..."), QDir::homePath(), tr("*.ebp"));

    if (path.isNull())
        return;

    ProjectXMLWriter writer(_model->getProject());
    if (!writer.writeToFile(path))
        QMessageBox::critical(this, tr("Error: Could not save project"), tr("An error occured while saving the project."));

    _unsaved = false;
    setTitle();
}

void MainWindow::loadConfigAction()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Choose configuration file..."), QDir::homePath());

    if (path.isNull())
        return;

    LevelXMLReader reader;
    if (reader.readFromFile(path)) {
        _model->getProject()->getBlockReprLibrary()->setLevelHandler(reader.getLevelHandler());
        renewBlockLibraryWidget();
    }
    else
        QMessageBox::critical(this, tr("Error: Could not open configuration file"), tr("An error occured while opening the configuration."));

}

void MainWindow::resetConfigAction()
{
    _model->getProject()->getBlockReprLibrary()->setLevelHandler(NULL);
    renewBlockLibraryWidget();
}

void MainWindow::runAction()
{
    //_program = _model->getProject()->createRunnableProgram();

    //compile
    ProjectCompiler compiler(_model->getProject());
    _program = compiler.compile();

    //if compilation failed: warn user
    if(compiler.compilationFailed()) {
        QMessageBox msgBox;
        msgBox.setText(compiler.getCompilationMessage());
        msgBox.setInformativeText(tr("Run anyway?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        if(ret != QMessageBox::Yes) { //don't run
            delete _program;
            _program = NULL;
            return;
        }
    }

    connect(_program, SIGNAL(stopped()), this, SLOT(programStopped()));
    _program->start();
    _stopAction->setEnabled(true);
    _pauseAction->setEnabled(true);
    _runAction->setEnabled(false);
}

void MainWindow::stopAction()
{
    if (_program != NULL)
    {
        _program->stop();
    }
}

void MainWindow::pauseAction()
{
    bool running = _program->pause();
    if (running)
        _pauseAction->setText(tr("Pause"));
    else
        _pauseAction->setText(tr("Resume"));
}

void MainWindow::programStopped()
{
    delete _program;
    _program = NULL;

    _stopAction->setEnabled(false);
    _pauseAction->setEnabled(false);
    _runAction->setEnabled(true);
}

void MainWindow::translateEnglish()
{
    _application->removeTranslator(&_trDutch);
    ui->retranslateUi(this);
    reload();
}

void MainWindow::translateDutch()
{
    _application->removeTranslator(&_trDutch);
    _application->installTranslator(&_trDutch);
    ui->retranslateUi(this);
    reload();
}

int MainWindow::showSaveChangesDialog()
{
    int ret = -1;
    if (_unsaved) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(tr("The project has been modified."));
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        ret = msgBox.exec();

        if (ret == QMessageBox::Cancel)
            return ret;
        else if (ret == QMessageBox::Save)
            saveAction();
    }

    return ret;
}

void MainWindow::reload()
{
    //renew blockReprLibrary to allow translation changes
    _model->getProject()->reloadBlockReprLibrary();
    renewBlockLibraryWidget();

    //workspace
    _mainLayout->removeWidget(_workspace);
    delete _workspace;
    _workspace = new WorkspaceWidget(_model, this);
    _workspace->setBlockReprLibWidget(_blockReprLibrary);
    _mainLayout->addWidget(_workspace);

    //toolbar
    removeToolBar(ui->mainToolBar);
    delete ui->mainToolBar;
    ui->mainToolBar = new QToolBar(this);
    ui->mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
    ui->mainToolBar->setMovable(false);
    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->mainToolBar->setFloatable(false);
    addToolBar(Qt::TopToolBarArea, ui->mainToolBar);
    createToolbar();

    //menubar
    ui->menuBar->clear();
    createMenubar();
}

void MainWindow::update()
{
    _unsaved = true;
    setTitle();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (_unsaved) {
        if (showSaveChangesDialog() == QMessageBox::Cancel)
        {
            event->ignore();
            return;
        }
    }
    event->accept();
}
