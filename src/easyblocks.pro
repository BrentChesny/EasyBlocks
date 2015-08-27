#-------------------------------------------------
#
# Project created by QtCreator 2014-03-04T23:56:51
#
#-------------------------------------------------

QT       += core gui widgets xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyBlocks
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        signal.cpp \
    block.cpp \
    message.cpp \
    value.cpp \
    executionthread.cpp \
    vartable.cpp \
    sprite.cpp \
    executionstackelement.cpp \
    simplemessage.cpp \
    executionhandler.cpp \
    numbervalue.cpp \
    stringvalue.cpp \
    booleanvalue.cpp \
    variable.cpp \
    valuelist.cpp \
    simplevartable.cpp \
    spritevartable.cpp \
    screen.cpp \
    constantblock.cpp \
    eventblock.cpp \
    expressionblock.cpp \
    statementblock.cpp \
    varblock.cpp \
    statementsblock.cpp \
    intmessage.cpp \
    listblock.cpp \
    blocks/conditional/ifblock.cpp \
    blocks/loop/whileblock.cpp \
    programmodel.cpp \
    program.cpp \
    programwindow.cpp \
    screenview.cpp \
    blocks/sprite/rotatespriteblock.cpp \
    blocks/event/startblock.cpp \
    blocks/number/numberassignment.cpp \
    blocks/sprite/nextimageblock.cpp \
    blocks/number/plusblock.cpp \
    valuemessage.cpp \
    spriteview.cpp \
    blocks/event/mouseclickblock.cpp \
    blocklibrary.cpp \
    blockrepr.cpp \
    paramrepr.cpp \
    applicationgui/draginfo.cpp \
    applicationgui/blockreprview.cpp \
    applicationgui/blockmimedata.cpp \
    applicationgui/blockreprviewholder.cpp \
    applicationgui/blockcolors.cpp \
    blocks/number/equalnumberblock.cpp \
    applicationgui/blockcanvas.cpp \
    spriterepr.cpp \
    blockreprlibrary.cpp \
    screenrepr.cpp \
    applicationgui/blockreprlibrarywidget.cpp \
    project.cpp \
    easyblocksmodel.cpp \
    applicationgui/categorybutton.cpp \
    applicationgui/screencanvas.cpp \
    applicationgui/spritegraphicsitem.cpp \
    applicationgui/workspacewidget.cpp \
    applicationgui/spriteswidget.cpp \
    applicationgui/propertybrowser/qtbuttonpropertybrowser.cpp \
    applicationgui/propertybrowser/qteditorfactory.cpp \
    applicationgui/propertybrowser/qtgroupboxpropertybrowser.cpp \
    applicationgui/propertybrowser/qtpropertybrowser.cpp \
    applicationgui/propertybrowser/qtpropertybrowserutils.cpp \
    applicationgui/propertybrowser/qtpropertymanager.cpp \
    applicationgui/propertybrowser/qttreepropertybrowser.cpp \
    applicationgui/propertybrowser/qtvariantproperty.cpp \
    applicationgui/spritepropertieswidget.cpp \
    blocks/conditional/ifelseblock.cpp \
    applicationgui/spriteresizegraphicsitem.cpp \
    applicationgui/sizedialog.cpp \
    applicationgui/xresizegraphicsitem.cpp \
    applicationgui/yresizegraphicsitem.cpp \
    applicationgui/xyresizegraphicsitem.cpp \
    applicationgui/rotategraphicsitem.cpp \
    blockrepr/varblockrepr.cpp \
    applicationgui/variablewidget.cpp \
    applicationgui/variabledialog.cpp \
    blockrepr/constantblockrepr.cpp \
    applicationgui/stringconstantblockreprview.cpp \
    applicationgui/numberconstantblockreprview.cpp \
    blockrepr/trueconstantblockrepr.cpp \
    blockrepr/falseconstantblockrepr.cpp \
    compiler/projectcompiler.cpp \
    blocks/number/lessthannumberblock.cpp \
    blocks/number/greaterthannumberblock.cpp \
    fileio/projectxmlwriter.cpp \
    fileio/projectxmlreader.cpp \
    spriteblock.cpp \
    blocks/event/arrowupblock.cpp \
    blocks/event/arrowdownblock.cpp \
    blocks/event/arrowleftblock.cpp \
    blocks/event/arrowrightblock.cpp \
    blocks/sprite/gotopositionblock.cpp \
    blockrepr/spriteblockrepr.cpp \
    applicationgui/spriteblockswidget.cpp \
    blocks/sprite/gotospriteblock.cpp \
    blocks/sprite/collidesspriteblock.cpp \
    blocks/sprite/movestepsblock.cpp \
    blocks/sprite/bounceedgeblock.cpp \
    blocks/bool/boolassignmentblock.cpp \
    blocks/bool/logicalandblock.cpp \
    blocks/bool/logicalorblock.cpp \
    blocks/bool/logicalnotblock.cpp \
    blocks/sprite/setvisibleblock.cpp \
    blocks/sprite/setinvisibleblock.cpp \
    blocks/sprite/resizeblock.cpp \
    blocks/sprite/resizetoblock.cpp \
    blocks/number/minusblock.cpp \
    blocks/number/multiplyblock.cpp \
    blocks/number/divideblock.cpp \
    blocks/sprite/spriteheightblock.cpp \
    blocks/sprite/spritewidthblock.cpp \
    blocks/sprite/spritexposblock.cpp \
    blocks/sprite/spriteyposblock.cpp \
    blocks/sprite/spriterotationblock.cpp \
    blocks/sprite/spritevisibleblock.cpp \
    blocks/number/randomblock.cpp \
    iohandler.cpp \
    blocks/string/concatenateblock.cpp \
    blocks/string/charatblock.cpp \
    blocks/string/lengthblock.cpp \
    blocks/bool/equalboolblock.cpp \
    blocks/string/equalstringblock.cpp \
    blocks/io/printblock.cpp \
    blocks/io/askblock.cpp \
    atomicpointermessage.cpp \
    blocks/list/numberfromlistblock.cpp \
    blocks/loop/repeatxblock.cpp \
    blocks/list/addnumbertolistblock.cpp \
    blocks/list/appendnumbertolist.cpp \
    blocks/string/convertnumbertostringblock.cpp \
    blocks/event/enterblock.cpp \
    blocks/event/spaceblock.cpp \
    levelhandler.cpp \
    fileio/levelxmlreader.cpp \
    userstatementblock.cpp \
    valuelistmessage.cpp \
    userstatement.cpp \
    applicationgui/spriteimagedialog.cpp \
    simplevariable.cpp \
    aliasvariable.cpp \
    simplevaluelist.cpp \
    aliasvaluelist.cpp \
    userstatementrepr.cpp \
    applicationgui/variablevaluewidget.cpp \
    blockreprholder.cpp \
    blockrepr/userstatementblockrepr.cpp \
    blockrepr/functionstartblockrepr.cpp \
    applicationgui/userstatementdialog.cpp \
    applicationgui/edituserstatementbutton.cpp \
    blocks/list/numberlistsize.cpp \
    blocks/conditional/waituntilblock.cpp \
    blocks/event/sendmessagesignaltospriteblock.cpp \
    blocks/event/messagesignalreceivedblock.cpp \
    blocks/string/stringassignmentblock.cpp \
    timemessage.cpp \
    blocks/conditional/waitsecondsblock.cpp

HEADERS  += mainwindow.h \
    signal.h \
    block.h \
    message.h \
    value.h \
    executionthread.h \
    vartable.h \
    sprite.h \
    executionstackelement.h \
    simplemessage.h \
    executionhandler.h \
    numbervalue.h \
    stringvalue.h \
    booleanvalue.h \
    variable.h \
    valuelist.h \
    simplevartable.h \
    spritevartable.h \
    screen.h \
    constantblock.h \
    eventblock.h \
    expressionblock.h \
    statementblock.h \
    varblock.h \
    statementsblock.h \
    intmessage.h \
    listblock.h \
    blocks/conditional/ifblock.h \
    blocks/loop/whileblock.h \
    programmodel.h \
    program.h \
    programwindow.h \
    screenview.h \
    blocks/sprite/rotatespriteblock.h \
    blocks/event/startblock.h \
    blocks/number/numberassignment.h \
    blocks/sprite/nextimageblock.h \
    blocks/number/plusblock.h \
    valuemessage.h \
    spriteview.h \
    blocks/event/mouseclickblock.h \
    blocklibrary.h \
    blocks/blocks.h \
    blockrepr.h \
    paramrepr.h \
    applicationgui/draginfo.h \
    applicationgui/blockreprview.h \
    applicationgui/blockmimedata.h \
    applicationgui/blockreprviewholder.h \
    applicationgui/blockcolors.h \
    blocks/number/equalnumberblock.h \
    applicationgui/blockcanvas.h \
    spriterepr.h \
    blockreprlibrary.h \
    screenrepr.h \
    applicationgui/blockreprlibrarywidget.h \
    project.h \
    easyblocksmodel.h \
    applicationgui/screencanvas.h \
    applicationgui/categorybutton.h \
    applicationgui/spritegraphicsitem.h \
    applicationgui/workspacewidget.h \
    applicationgui/spriteswidget.h \
    applicationgui/propertybrowser/qtbuttonpropertybrowser.h \
    applicationgui/propertybrowser/qteditorfactory.h \
    applicationgui/propertybrowser/qtgroupboxpropertybrowser.h \
    applicationgui/propertybrowser/qtpropertybrowser.h \
    applicationgui/propertybrowser/qtpropertybrowserutils_p.h \
    applicationgui/propertybrowser/qtpropertymanager.h \
    applicationgui/propertybrowser/qttreepropertybrowser.h \
    applicationgui/propertybrowser/qtvariantproperty.h \
    applicationgui/spritepropertieswidget.h \
    blocks/conditional/ifelseblock.h \
    applicationgui/spriteresizegraphicsitem.h \
    applicationgui/sizedialog.h \
    applicationgui/xresizegraphicsitem.h \
    applicationgui/yresizegraphicsitem.h \
    applicationgui/xyresizegraphicsitem.h \
    applicationgui/rotategraphicsitem.h \
    blockrepr/varblockrepr.h \
    applicationgui/variablewidget.h \
    applicationgui/variabledialog.h \
    blockrepr/constantblockrepr.h \
    applicationgui/stringconstantblockreprview.h \
    applicationgui/numberconstantblockreprview.h \
    blockrepr/trueconstantblockrepr.h \
    blockrepr/falseconstantblockrepr.h \
    compiler/projectcompiler.h \
    blocks/number/lessthannumberblock.h \
    blocks/number/greaterthannumberblock.h \
    fileio/projectxmlwriter.h \
    fileio/projectxmlreader.h \
    spriteblock.h \
    blocks/event/arrowupblock.h \
    blocks/event/arrowdownblock.h \
    blocks/event/arrowleftblock.h \
    blocks/event/arrowrightblock.h \
    blocks/sprite/gotopositionblock.h \
    blockrepr/spriteblockrepr.h \
    applicationgui/spriteblockswidget.h \
    blocks/sprite/gotospriteblock.h \
    blocks/sprite/collidesspriteblock.h \
    blocks/sprite/movestepsblock.h \
    blocks/sprite/bounceedgeblock.h \
    blocks/bool/boolassignmentblock.h \
    blocks/bool/logicalandblock.h \
    blocks/bool/logicalorblock.h \
    blocks/bool/logicalnotblock.h \
    blocks/sprite/setvisibleblock.h \
    blocks/sprite/setinvisibleblock.h \
    blocks/sprite/resizeblock.h \
    blocks/sprite/resizetoblock.h \
    blocks/number/minusblock.h \
    blocks/number/multiplyblock.h \
    blocks/number/divideblock.h \
    blocks/sprite/spriteheightblock.h \
    blocks/sprite/spritewidthblock.h \
    blocks/sprite/spritexposblock.h \
    blocks/sprite/spriteyposblock.h \
    blocks/sprite/spriterotationblock.h \
    blocks/sprite/spritevisibleblock.h \
    blocks/number/randomblock.h \
    iohandler.h \
    blocks/string/concatenateblock.h \
    blocks/string/charatblock.h \
    blocks/string/lengthblock.h \
    blocks/bool/equalboolblock.h \
    blocks/string/equalstringblock.h \
    blocks/io/printblock.h \
    blocks/io/askblock.h \
    atomicpointermessage.h \
    blocks/list/numberfromlistblock.h \
    blocks/loop/repeatxblock.h \
    blocks/list/addnumbertolistblock.h \
    blocks/list/appendnumbertolist.h \
    blocks/string/convertnumbertostringblock.h \
    blocks/event/enterblock.h \
    blocks/event/spaceblock.h \
    levelhandler.h \
    fileio/levelxmlreader.h \
    userstatementblock.h \
    valuelistmessage.h \
    userstatement.h \
    applicationgui/spriteimagedialog.h \
    simplevariable.h \
    aliasvariable.h \
    simplevaluelist.h \
    aliasvaluelist.h \
    userstatementrepr.h \
    applicationgui/variablevaluewidget.h \
    blockreprholder.h \
    blockrepr/userstatementblockrepr.h \
    blockrepr/functionstartblockrepr.h \
    applicationgui/userstatementdialog.h \
    applicationgui/edituserstatementbutton.h \
    blocks/list/numberlistsize.h \
    blocks/conditional/waituntilblock.h \
    blocks/event/sendmessagesignaltospriteblock.h \
    blocks/event/messagesignalreceivedblock.h \
    blocks/string/stringassignmentblock.h \
    timemessage.h \
    blocks/conditional/waitsecondsblock.h


FORMS    += mainwindow.ui \
    programwindow.ui \
    applicationgui/variabledialog.ui \
    applicationgui/spriteimagedialog.ui \
    applicationgui/userstatementdialog.ui

TRANSLATIONS = easyblocks_nl.ts

CODECFORTR      = ISO-8859-5

 unix {
QMAKE_CFLAGS_WARN_ON += -Wno-unused-parameter
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
 }

ICON = easyblocks.icns

RC_FILE = easyblocks.rc

RESOURCES += \
    resources.qrc \
    applicationgui/propertybrowser/qtpropertybrowser.qrc
