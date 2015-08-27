#include "programwindow.h"
#include "ui_programwindow.h"

#include <QDebug>

ProgramWindow::ProgramWindow(ProgramModel* model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgramWindow),
    _model(model),
    _askingInput(false),
    _varWidget(NULL)
{
    ui->setupUi(this);
    ui->screenView->setFixedSize(model->getScreen()->getSize());
    ui->screenView->setModel(model);

    ui->question->setText("");
    ui->answer->setEnabled(false);
    QFont font = QFont("Arial", 11);
    font.setPixelSize(11);
    ui->console->setFont(font);

    connect(_model, SIGNAL(update()), this, SLOT(update()));
    connect(_model->getIOHandler(), SIGNAL(inputRequestReceived()), this, SLOT(inputRequestReceived()));
    connect(_model->getIOHandler(), SIGNAL(outputReceived(QString)), this, SLOT(outputReceived(QString)));
    connect(ui->answer, SIGNAL(returnPressed()), this, SLOT(sendAnswer()));

    setFixedSize(model->getScreen()->getSize().width(), model->getScreen()->getSize().height() + 100);
    setWindowTitle("EasyBlocks Project");
}

ProgramWindow::~ProgramWindow()
{
    delete ui;

    if (_varWidget != NULL)
        delete _varWidget;
}

void ProgramWindow::update()
{
    ui->screenView->update();
}

void ProgramWindow::outputReceived(const QString &output)
{
    ui->console->setHtml(ui->console->toHtml().append(output));
    QTextCursor c =  ui->console->textCursor();
    c.movePosition(QTextCursor::End);
    ui->console->setTextCursor(c);
}

void ProgramWindow::inputRequestReceived()
{
    if (_askingInput)
        return;

    QString question = _model->getIOHandler()->getFirstInputQuestion();
    if (question.isNull())
        return;

    ui->question->setText(question);
    ui->answer->setEnabled(true);
    ui->answer->setFocus();

    _askingInput = true;
}

void ProgramWindow::sendAnswer()
{
    QString answer = ui->answer->text();
    _model->getIOHandler()->sendInput(answer);
    _askingInput = false;
    ui->question->setText("");
    ui->answer->setText("");
    ui->answer->setEnabled(false);
    ui->screenView->setFocus();
    inputRequestReceived();
}

void ProgramWindow::closeEvent(QCloseEvent *event)
{
    emit closed();
}

void ProgramWindow::on_actionShow_Variables_triggered()
{
    if (_varWidget != NULL)
        delete _varWidget;

    _varWidget = new VariableValueWidget(_model);
    _varWidget->setWindowTitle(tr("Variables"));
    _varWidget->show();
}
