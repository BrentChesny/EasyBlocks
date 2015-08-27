#include "blockrepr.h"
#include "paramrepr.h"
#include "spriterepr.h"
#include "project.h"
#include "blockreprholder.h"

#include <algorithm>
#include <QFontMetrics>
#include <QDebug>

using std::max;

QFont BlockRepr::FONT = QFont("Arial", 11, QFont::DemiBold);

const int BlockRepr::MARGIN = 3;

const int BlockRepr::MARGIN_HORIZONTAL = 5;

const int BlockRepr::LEFT_GUTTER = 10;

const int BlockRepr::FOOTER_HEIGHT = 10;

const int BlockRepr::FOOTER_WIDTH = 50;

const QSize BlockRepr::HOLDER_SIZE = QSize(48, 14);

BlockRepr::BlockRepr(Block *block, bool locked) : _parent(NULL), _holderParent(NULL), _nextBlock(NULL), _lastRemovedWasParam(false), _lastRemoved(NULL), _isLocked(locked)
{
    BlockRepr::FONT.setPixelSize(11);

    _id = block->getId();
    _returnType = block->getReturnType();
    _paramLabels = block->getParamDescription().split("%p");
    for (int i = 0; i < _paramLabels.size(); ++i) {
        _paramLabels.replace(i, _paramLabels.at(i).trimmed());
    }
    _bodyLabels = block->getBodiesDescription().split("%b", QString::SkipEmptyParts);
    for (int i = 0; i < _bodyLabels.size(); ++i) {
        _bodyLabels.replace(i, _bodyLabels.at(i).trimmed());
    }

    foreach (Block::ParamType type, block->getParamTypes()) {
        _params.append(new ParamRepr(type));
    }

    for (int i = 0; i < block->getNumBodies(); ++i) {
        _bodies.append(NULL);
    }

    calculateSizes(true, true, true);
    calculatePositions(true, true, true);
}

BlockRepr::BlockRepr(const BlockRepr& repr) : QObject(NULL), _parent(repr.getParent()), _holderParent(NULL), _nextBlock(NULL), _lastRemovedWasParam(false), _lastRemoved(NULL)
{
    BlockRepr::FONT.setPixelSize(11);

    _id = repr.getId();
    _returnType = repr.getReturnType();
    _paramLabels = repr.getParamDescriptions();
    _bodyLabels = repr.getBodyDescriptions();

    for (int i = 0; i < repr.getNumParams(); i++) {
        ParamRepr* p = new ParamRepr(repr.getParamType(i));
        if(repr.getParam(i) != NULL) {
            BlockRepr* newParam = repr.getParam(i)->copy();
            newParam->setParent(this);
            p->setBlock(newParam);
        }
        _params.append(p);
    }

    for (int i = 0; i < repr.getNumBodies(); ++i) {
        BlockRepr* body = repr.getBody(i);

        if (body == NULL)
            _bodies.append(NULL);
        else {
            BlockRepr* newBody = body->copy();
            newBody->setParent(this);
            _bodies.append(newBody);
        }
    }
    if (repr._nextBlock != NULL) {
        _nextBlock = repr._nextBlock->copy();
        _nextBlock->setParent(this);
    } else
        _nextBlock = NULL;
    _isLocked = repr._isLocked;
    _position = repr._position;
    calculateSizes(true, true, true);
    calculatePositions(true, true, true);
}

BlockRepr::BlockRepr(Block::ParamType type, QString name, bool locked, bool isVar) : _parent(NULL), _holderParent(NULL), _nextBlock(NULL), _lastRemovedWasParam(false), _lastRemoved(NULL), _isLocked(locked)
{
    BlockRepr::FONT.setPixelSize(11);

    if(isVar) {
        _id = QString("Var"); //used for creating variables
        _paramLabels.append(name);
    } else {
        QString cat;
        if (type == Block::NUMBER_EXPRESSION)
            cat = "Number";
        else if (type == Block::BOOLEAN_EXPRESSION)
            cat = "Boolean";
        else
            cat = "String";
        _id = cat + QString("_") + name; //used for creating true and false

        if (name == "true")
            _paramLabels.append(tr("true"));
        else
           _paramLabels.append(tr("false"));
    }
    _returnType = type;
    calculateSizes(true, true, true);
    calculatePositions(true, true, true);
}

BlockRepr::BlockRepr(Block::ParamType type, bool locked) : _parent(NULL), _holderParent(NULL), _nextBlock(NULL), _lastRemovedWasParam(false), _lastRemoved(NULL), _isLocked(locked)
{
    BlockRepr::FONT.setPixelSize(11);

    if(type == Block::STRING_EXPRESSION)
        _id = "String_String";
    else if (type == Block::NUMBER_EXPRESSION)
        _id = "Number_Number";
    else if (type == Block::SPRITE)
        _id = "Sprite_Sprite";
    else if (type == Block::FUNCTION_START)
        _id = "Function_Start";

    _returnType = type;

    calculateSizes(true, true, true);
    calculatePositions(true, true, true);
}

BlockRepr::~BlockRepr()
{
    if (_nextBlock != NULL)
        delete _nextBlock;

    foreach (BlockRepr* b, _bodies) {
        if (b != NULL)
            delete b;
    }

    foreach (ParamRepr* p, _params) {
        if (p != NULL)
            delete p;
    }
}

void BlockRepr::setHolderParent(BlockReprHolder *parent)
{
    _parent = NULL;
    _holderParent = parent;
}

QSize BlockRepr::getSize()
{
    return _size;
}

QSize BlockRepr::getTotalSize()
{
    return _totalSize;
}

QSize BlockRepr::getHeaderSize()
{
    return _headerSize;
}

QSize BlockRepr::getBodyDescriptionSize(int index)
{
    if (index < 0 || index >= _bodyLabels.size())
        return QSize();

    return getFontRect(_bodyLabels.at(index)).size() + QSize(MARGIN * 3, MARGIN * 2);
}

QSize BlockRepr::getBodySize(int index)
{
    if (_bodies.at(index) == NULL)
        return HOLDER_SIZE;

    return _bodies.at(index)->getTotalSize();
}

QSize BlockRepr::getParamDescriptionsize(int index)
{
    if (index < 0 || index >= _paramLabels.size())
        return QSize();

    return getFontRect(_paramLabels.at(index)).size();
}

QSize BlockRepr::getParamSize(int index)
{
    // voorlopig niet nodig
    return QSize();
}

QPoint BlockRepr::getParamPosition(int index)
{
    return _paramPositions.at(index);
}

QPoint BlockRepr::getParamDescriptionPosition(int index)
{
    return _paramLabelPositions.at(index);
}

QPoint BlockRepr::getBodyDescriptionPosition(int index)
{
    if (index < 0 || index >= _bodyLabels.size())
        return QPoint();

    QPoint pos(LEFT_GUTTER + MARGIN, getParamListSize().height() + MARGIN);

    for (int i = 0; i < _bodies.size(); ++i) {
        if (index == i)
            return pos + QPoint(0, getFontRect(_bodyLabels.at(index)).height()/2);

        pos += QPoint(0, getBodySize(i).height() + 19);
    }

    return QPoint();
}

QPoint BlockRepr::getBodyPosition(int index)
{
    QPoint pos(LEFT_GUTTER, getHeaderSize().height());

    for (int i = 0; i < index; ++i) {
            pos += QPoint(0, getBodySize(i).height());
            pos += QPoint(0, getBodyDescriptionSize(i+1).height());
    }

    return pos;
}

QPoint BlockRepr::getNextStatementPosition()
{
    return QPoint(0, getSize().height());
}

bool BlockRepr::doesBodyFit(BlockRepr* repr, int index)
{
    if(repr == NULL)
        return false;

    return (repr->getReturnType() == Block::VOID);
}

bool BlockRepr::placeBody(BlockRepr* repr, int index)
{
    if(repr == NULL)
        return false;

    if (!doesBodyFit(repr, index))
        return false;

    _bodies.replace(index, repr);
    repr->setParent(this);

    emitBlockUpdated(false, true, false);

    return true;
}

bool BlockRepr::doesParamFit(BlockRepr* repr, int index)
{
    if(repr == NULL)
        return false;

    Block::ParamType expected = _params.at(index)->getParamType();
    Block::ParamType type = repr->getReturnType();

    if (expected == type)
        return true;
    if (expected == Block::NUMBER_EXPRESSION && type == Block::NUMBER_VAR)
        return true;
    if (expected == Block::BOOLEAN_EXPRESSION && type == Block::BOOLEAN_VAR)
        return true;
    if (expected == Block::STRING_EXPRESSION && type == Block::STRING_VAR)
        return true;

    return false;
}

bool BlockRepr::placeParam(BlockRepr* repr, int index)
{
    if(repr == NULL)
        return false;

    if (!doesParamFit(repr, index))
        return false;

    _params.at(index)->setBlock(repr);
    repr->setParent(this);

    emitBlockUpdated(true, false, false);

    return true;
}

bool BlockRepr::placeNextStatement(BlockRepr* repr)
{
    if(repr == NULL)
        return false;

    if (!doesBodyFit(repr, -1))
        return false;

    _nextBlock = repr;
    repr->setParent(this);

    emitBlockUpdated(false, false, true);

    return true;
}

bool BlockRepr::removeBody(int index)
{
    _lastRemovedWasParam = false;
    _lastRemovedIndex = index;
    _lastRemoved = _bodies.at(index);

    _bodies.replace(index, NULL);

    emitBlockUpdated(false, true, false);

    return true;
}

bool BlockRepr::removeParam(int index)
{
    _lastRemovedWasParam = true;
    _lastRemovedIndex = index;
    _lastRemoved = _params.at(index)->getBlock();

    _params.at(index)->setBlock(NULL);

    emitBlockUpdated(true, false, false);

    return true;
}

bool BlockRepr::removeNextStatement()
{
    _lastRemovedWasParam = false;
    _lastRemovedIndex = -1;
    _lastRemoved = _nextBlock;

    _nextBlock = NULL;

    emitBlockUpdated(false, false, true);

    return true;
}

bool BlockRepr::removeFromParent()
{
    if (_parent == NULL && _holderParent == NULL)
        return true;

    if (_parent == NULL)
        return _holderParent->removeBlock(this);

    return _parent->remove(this);
}

bool BlockRepr::remove(BlockRepr* repr)
{
    int index = 0;
    bool found = false;
    foreach (BlockRepr* b, _bodies) {
        if (b == repr) {
            found = true;
            break;
        }
        index++;
    }

    if (found)
        return removeBody(index);

    index = 0;
    found = false;
    foreach (ParamRepr* p, _params) {
        if (p->getBlock() == repr) {
            found = true;
            break;
        }
        index++;
    }

    if (found)
        return removeParam(index);

    if (repr == _nextBlock)
        return removeNextStatement();

    return false;
}

int BlockRepr::getNumBodies() const
{

    return _bodies.size();
}

int BlockRepr::getNumParams() const
{
    return _params.size();
}

BlockRepr* BlockRepr::getBody(int index) const
{
    if (index < 0 || index >= _bodies.size())
        return NULL;

    return _bodies.at(index);
}

BlockRepr* BlockRepr::getParam(int index) const
{
    if (index < 0 || index >= _params.size())
        return NULL;

    return _params.at(index)->getBlock();
}

Block::ParamType BlockRepr::getParamType(int index) const
{
    return _params.at(index)->getParamType();
}

QRect BlockRepr::getFontRect(QString string)
{
    QFontMetrics metrics(FONT);
    return metrics.boundingRect(string);
}

QSize BlockRepr::getParamListSize()
{
    return _paramListSize;
}

void BlockRepr::revert()
{
    if (_parent == NULL && _holderParent == NULL)
        return;

    if (_parent == NULL) {
        _holderParent->addBlock(this);
        return;
    }

    _parent->revertToParent();
}

void BlockRepr::revertToParent()
{
    if (_lastRemoved == NULL)
        return;

    if (_lastRemovedWasParam)
        placeParam(_lastRemoved, _lastRemovedIndex);
    else if (_lastRemovedIndex >= 0)
        placeBody(_lastRemoved, _lastRemovedIndex);
    else
        placeNextStatement(_lastRemoved);
}

void BlockRepr::emitBlockUpdated(bool param, bool body, bool next) {
    calculateSizes(param, body, next);
    calculatePositions(param, body, next);

    emit blockUpdated();

    if(_parent != NULL)
        _parent->emitBlockUpdated(true, true, true);
}

void BlockRepr::calculateSizes(bool param, bool body, bool next)
{
    if (param) {
        calculateParamListSize();
        calculateHeaderSize();
    }
    if (param || body) {
        calculateSize();
    }
    if (param || body || next) {
        calculateTotalSize();
    }
}

void BlockRepr::calculatePositions(bool param, bool body, bool next)
{
    calculateParamPositions();
    calculateParamLabelPositions();
}

void BlockRepr::calculateTotalSize()
{
    QSize total = getSize();

    // next block
    if (_nextBlock != NULL) {
        QSize s = _nextBlock->getTotalSize();
        total += QSize(0, s.height());
        total.setWidth(max(total.width(), s.width()));
    } else if (_returnType == Block::VOID || _returnType == Block::EVENT) {
        QSize s = HOLDER_SIZE;
        total += QSize(0, s.height());
        total.setWidth(max(total.width(), s.width()));
    }

    _totalSize = total;
}

void BlockRepr::calculateSize()
{
    QSize total(0, 0);

    // header size
    QSize header = getHeaderSize();
    total += header;

    // size of body descriptions (starts at 1 because description 0 is in header)
    for (int i = 1; i < _bodyLabels.size(); ++i) {
        QSize s = getBodyDescriptionSize(i);
        total += QSize(0, s.height());
        total.setWidth(max(total.width(), s.width()));
    }

    // bodies
    foreach(BlockRepr* body, _bodies) {
        QSize s;
        if (body == NULL)
            s = HOLDER_SIZE;
        else
            s = body->getTotalSize();
        total += QSize(0, s.height());
        total.setWidth(max(total.width(), s.width()));
    }

    // fixed footer
    if (_bodyLabels.size() > 0) {
        total += QSize(0, FOOTER_HEIGHT);
    }

    if (_returnType == Block::VOID || _returnType == Block::EVENT)
        total += QSize(LEFT_GUTTER, 0);
    else
        total += QSize(2, 0);

    _size = total;
}

void BlockRepr::calculateParamListSize()
{
    QSize params(MARGIN, 2 * MARGIN);
    for (int i = 0; i < max(_params.size(), _paramLabels.size()); ++i) {
        if (i < _paramLabels.size()) {
            params += QSize(getFontRect(_paramLabels.at(i)).size().width() + MARGIN_HORIZONTAL, 0);
            params.setHeight(max(params.height(), 2 * MARGIN + getFontRect(_paramLabels.at(i)).size().height()));
        }

        if (i < _params.size()) {
            BlockRepr* block = _params.at(i)->getBlock();
            if (block != NULL) {
                params += QSize(block->getTotalSize().width() + MARGIN_HORIZONTAL, 0);
                params.setHeight(max(params.height(), 2 * MARGIN + block->getTotalSize().height()));
            } else {
                params += QSize(HOLDER_SIZE.width() + MARGIN_HORIZONTAL, 0);
                params.setHeight(max(params.height(), 2 * MARGIN + HOLDER_SIZE.height()));
            }
        }
    }

    _paramListSize = params;
}

void BlockRepr::calculateHeaderSize()
{
    QSize firstBodyDesc = getBodyDescriptionSize(0);
    firstBodyDesc -= QSize(0, MARGIN);

    // calculate params and text
    QSize params = getParamListSize();

    if (_bodyLabels.size() == 0)
        _headerSize = params;
    else
        _headerSize = QSize(max(params.width(), firstBodyDesc.width()), params.height() + firstBodyDesc.height());
}

void BlockRepr::calculateParamPositions()
{
    _paramPositions.clear();
    int margin = (getReturnType() == Block::VOID || getReturnType() == Block::EVENT) ? LEFT_GUTTER : 0;
    QSize params(margin + MARGIN, 2 * MARGIN);
    for (int i = 0; i < max(_params.size(), _paramLabels.size()); ++i) {
        if (i < _paramLabels.size()) {
            params += QSize(getFontRect(_paramLabels.at(i)).size().width() + MARGIN_HORIZONTAL, 0);
            params.setHeight(max(params.height(), 2 * MARGIN + getFontRect(_paramLabels.at(i)).size().height()));
        }

        if (i < _params.size()) {
            BlockRepr* block = _params.at(i)->getBlock();

            QPoint result;
            result.setX(params.width());
            if (block != NULL)
                result.setY(getParamListSize().height()/2 - block->getTotalSize().height()/2);
            else
                result.setY(getParamListSize().height()/2 - HOLDER_SIZE.height()/2);
            _paramPositions.append(result);

            if (block != NULL) {
                params += QSize(block->getTotalSize().width() + MARGIN_HORIZONTAL, 0);
                params.setHeight(max(params.height(), 2 * MARGIN + block->getTotalSize().height()));
            } else {
                params += QSize(HOLDER_SIZE.width() + MARGIN_HORIZONTAL, 0);
                params.setHeight(max(params.height(), 2 * MARGIN + HOLDER_SIZE.height()));
            }
        }
    }
}

void BlockRepr::calculateParamLabelPositions()
{
    _paramLabelPositions.clear();
    int margin = (getReturnType() == Block::VOID || getReturnType() == Block::EVENT) ? LEFT_GUTTER : 0;
    QSize params(margin + MARGIN, 2 * MARGIN);
    for (int i = 0; i < max(_params.size(), _paramLabels.size()); ++i) {
        if (i < _paramLabels.size()) {
            _paramLabelPositions.append(QPoint(params.width(), getParamListSize().height()/2 + getFontRect(_paramLabels.at(i)).height()/2 - MARGIN + 1));

            params += QSize(getFontRect(_paramLabels.at(i)).size().width() + MARGIN_HORIZONTAL, 0);
            params.setHeight(max(params.height(), 2 * MARGIN + getFontRect(_paramLabels.at(i)).size().height()));
        }

        if (i < _params.size()) {
            BlockRepr* block = _params.at(i)->getBlock();

            if (block != NULL) {
                params += QSize(block->getTotalSize().width() + MARGIN_HORIZONTAL, 0);
                params.setHeight(max(params.height(), 2 * MARGIN + block->getTotalSize().height()));
            } else {
                params += QSize(HOLDER_SIZE.width() + MARGIN_HORIZONTAL, 0);
                params.setHeight(max(params.height(), 2 * MARGIN + HOLDER_SIZE.height()));
            }
        }
    }
}

void BlockRepr::duplicateBlock()
{
    BlockRepr* block = this->copy();

    BlockRepr* b = this;
    BlockReprHolder* holder;
    while (b->getHolderParent() == NULL) {
        b = b->getParent();
    }
    holder = b->getHolderParent();
    block->setPosition(b->getPosition() + QPoint(40, 40));
    holder->addBlock(block);
}

void BlockRepr::deleteBlock()
{
    this->removeFromParent();
    delete this;
}

BlockRepr* BlockRepr::copy()
{
    return new BlockRepr(*this);
}

void BlockRepr::setParamLabels(QStringList paramLabels)
{
    _paramLabels = paramLabels;
    emitBlockUpdated(true, true, true);
}

void BlockRepr::setParamLabels(QString paramLabels)
{
    _paramLabels = paramLabels.split("%p");;
    emitBlockUpdated(true, true, true);
}

void BlockRepr::setParamTypes(QList<Block::ParamType> paramTypes)
{
    //delete params
    foreach (ParamRepr* p, _params) {
        if (p != NULL)
            delete p;
    }
    _params.clear();

    //create new params
    foreach (Block::ParamType type, paramTypes) {
        _params.append(new ParamRepr(type));
    }
    emitBlockUpdated(true, true, true);
}

void BlockRepr::checkExistance(Project* project)
{
    for (int i = 0; i < getNumParams(); i++) {
        if(getParam(i) != NULL)
            getParam(i)->checkExistance(project);
    }

    for (int i = 0; i < getNumBodies(); ++i) {
        BlockRepr* body = getBody(i);
        if (body != NULL)
            body->checkExistance(project);
    }

    if (_nextBlock != NULL)
        _nextBlock->checkExistance(project);
}
