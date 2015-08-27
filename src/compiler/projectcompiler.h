#ifndef PROJECTCOMPILER_H
#define PROJECTCOMPILER_H

#include "../project.h"
#include "../program.h"
#include "../programmodel.h"
#include "../screen.h"

#include "../expressionblock.h"
#include "../statementblock.h"
#include "../statementsblock.h"
#include "../constantblock.h"
#include "../value.h"
#include "../booleanvalue.h"
#include "../numbervalue.h"
#include "../stringvalue.h"
#include "../blockrepr/constantblockrepr.h"
#include "../blockrepr/spriteblockrepr.h"
#include "../blockrepr/userstatementblockrepr.h"
#include "../varblock.h"
#include "../listblock.h"
#include "../spriteblock.h"
#include "../userstatementblock.h"

/**
 * @brief The ProjectCompiler class
 *
 * @author Brecht Vandevoort
 */
class ProjectCompiler
{
public:
    /**
     * @brief Constructor
     * @param project The project to compile
     */
    ProjectCompiler(Project* project);

    /**
     * @brief Compiles the Project into a program
     * @return Pointer to the compiled program
     */
    Program* compile();

    /**
     * @brief Returns whether or not the compilation failed
     * @return True if the compilation failed, false if not
     */
    bool compilationFailed() const {return _compilationFailed;}

    /**
     * @brief Returns the compilation message. If compilation succeeded, this message is empty
     * @return The compilation message
     */
    QString getCompilationMessage() const {return _compilationMessage;}

private:
    Project* _project;
    bool _compilationFailed;
    QString _compilationMessage;

    /**
     * @brief Compiles and returns the model of the project
     * @return The ProgramModel compiled from the project
     */
    ProgramModel* compileModel();

    /**
     * @brief Compiles the screen
     * @param screen The screen to put the information in.
     */
    void compileScreen(Screen* screen);

    /**
     * @brief Creates a new Sprite
     * @param spriteRepr The SpriteRepr to convert
     * @param model Pointer to the ProgramModel
     * @return The newly created Sprite
     */
    Sprite* createSprite(SpriteRepr* spriteRepr, ProgramModel* model);

    /**
     * @brief Creates a UserStatement
     * @param userStatementRepr The UserStatementRepr to convert
     * @param model Pointer to the ProgramModel
     * @return The newly created UserStatement
     */
    UserStatement* createUserStatement(UserStatementRepr* userStatementRepr, ProgramModel* model);

    /**
     * @brief Compiles a given Sprite
     * @param spriteRepr The spriteRepr to convert
     * @param sprite The created Sprite to compile
     * @param sprites A QMap to connect SpriteReprs and Sprites
     * @param userStatements A QMap to connect UserStatementReprs and UserStatements
     * @param model Pointer to the model
     */
    void compileSprite(SpriteRepr* spriteRepr, Sprite* sprite, QMap<SpriteRepr*, Sprite*> sprites, QMap<UserStatementRepr*, UserStatement*> userStatements, ProgramModel* model);

    /**
     * @brief Compiles a given UserStatement
     * @param userStatementRepr The UserStatementRepr to convert
     * @param userStatement The created UserStatement to compile
     * @param userStatements A QMap to connect UserStatementReprs and UserStatements
     * @param model Pointer to the model
     */
    void compileUserStatement(UserStatementRepr* userStatementRepr, UserStatement* userStatement, QMap<UserStatementRepr*, UserStatement*> userStatements, ProgramModel* model);

    /**
     * @brief Compiles an EvenBlock
     * @param blockRepr The BlockRepr representing an eventBlock to compile
     * @param sprites A QMap to connect SpriteReprs and Sprites
     * @param userStatements A QMap to connect UserStatementReprs and UserStatements
     * @return The compiled EventBlock
     */
    EventBlock* compileEventBlock(BlockRepr* blockRepr, QMap<SpriteRepr*, Sprite*> sprites, QMap<UserStatementRepr*, UserStatement*> userStatements);

    /**
     * @brief Compiles a body by placing all blocks in a StatementsBlock
     * @param blockRepr The BlockRepr representing the first block of the body
     * @param sprites A QMap to connect SpriteReprs and Sprites
     * @param userStatements A QMap to connect UserStatementReprs and UserStatements
     * @return The compiled body
     */
    StatementBlock* compileBody(BlockRepr* blockRepr, QMap<SpriteRepr*, Sprite*> sprites, QMap<UserStatementRepr*, UserStatement*> userStatements);

    /**
     * @brief Compiles a StatementBlock
     * @param blockRepr The statement to compile
     * @param sprites A QMap to connect SpriteReprs and Sprites
     * @param userStatements A QMap to connect UserStatementReprs and UserStatements
     * @return The compiled StatementBlock
     */
    StatementBlock* compileStatement(BlockRepr* blockRepr, QMap<SpriteRepr*, Sprite*> sprites, QMap<UserStatementRepr*, UserStatement*> userStatements);

    /**
     * @brief Compiles a parameter
     * @param blockRepr The parameter to compile
     * @param sprites A QMap to connect SpriteReprs and Sprites
     * @param userStatements A QMap to connect UserStatementReprs and UserStatements
     * @return the compiled parameter as a Block
     */
    Block* compileParam(BlockRepr* blockRepr, QMap<SpriteRepr*, Sprite*> sprites, QMap<UserStatementRepr*, UserStatement*> userStatements);

    /**
     * @brief Compiles an ExpressionBlock
     * @param blockRepr The expression to compile
     * @param sprites A QMap to connect SpriteReprs and Sprites
     * @param userStatements A QMap to connect UserStatementReprs and UserStatements
     * @return The compiled ExpressionBlock
     */
    ExpressionBlock* compileExpression(BlockRepr* blockRepr, QMap<SpriteRepr *, Sprite *> sprites, QMap<UserStatementRepr*, UserStatement*> userStatements);

    /**
     * @brief Compiles a special ExpressionBlock (constant or variable)
     * @param blockRepr The expression to compile
     * @return The compiled ExpressionBlock
     */
    ExpressionBlock* compileSpecialCaseExpression(BlockRepr* blockRepr);

    /**
     * @brief Compiles a variable into a VarBlock
     * @param blockRepr The variable as a BlockRepr
     * @return The compiled VarBlock
     */
    VarBlock* compileVarBlock(BlockRepr* blockRepr);

    /**
     * @brief Compiles a list into a ListBlock
     * @param blockRepr the list as a BlockRepr
     * @return The compiled ListBlock
     */
    ListBlock* compileListBlock(BlockRepr* blockRepr);

    /**
     * @brief Compiles a spriteBlockRepr into a SpriteBlock
     * @param blockRepr The SpriteBlockRepr as a BlockRepr
     * @param sprites A QMap to connect SpriteReprs and Sprites
     * @return The compiled SpriteBlock
     */
    SpriteBlock* compileSpriteBlock(BlockRepr* blockRepr, QMap<SpriteRepr*, Sprite*> sprites);

    /**
     * @brief Compiles a UserStatementBlockRepr into a UserStatementBlock
     * @param blockRepr The UserStatementBlockRepr as a BlockRepr
     * @param userStatements A QMap to connect UserStatementReprs and UserStatements
     * @return The compiled UserStatementBlock
     */
    UserStatementBlock* compileUserStatementBlock(BlockRepr* blockRepr, QMap<UserStatementRepr*, UserStatement*> userStatements);

    /**
     * @brief Checks if a given VarBlockRepr is a list
     * @param varBlockRepr The VarBlockRepr to check
     * @return True if VarBlockRepr is list, false if not
     */
    bool isListVar(VarBlockRepr* varBlockRepr);

    /**
     * @brief Returns the datatype of a given BlockRepr
     * @param blockRepr The BlockRepr to get the dataType from
     * @return The DataType of the BlockRepr
     */
    Value::DataType getDataType(BlockRepr* blockRepr);

    /**
     * @brief Sets the compilation to have failed. If failed already, this function does nothing
     * @param message Reason for the failure
     */
    void setFailed(QString message);
};

#endif // PROJECTCOMPILER_H
