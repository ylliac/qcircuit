/* 
 * File:   ImportDiagram.cpp
 * Author: acailly
 * 
 * Created on 27 mai 2014, 10:30
 */

#include "ImportDiagram.h"

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <iostream>

#include "editor/FBPEditor.h"
#include "editor/scene/BlockItem.h"
#include "editor/scene/ArrowItem.h"

ImportDiagram::ImportDiagram(FBPEditor* editor) :
FBPEditorAction(editor)
{

}

ImportDiagram::~ImportDiagram()
{
}

void ImportDiagram::execute(QString inputFileName, QString, QString, QString, QString)
{
    //TODO ACY Vider le diagramme existant avant ?

    QString fileName = inputFileName;

    //If input file name is empty, ask the user a file name
    if (fileName.isEmpty())
    {
        fileName = QFileDialog::getOpenFileName(getEditor(), "Import diagram", "", "FBP diagram (*.fbp)");
        if (fileName.isEmpty())
        {
            return;
        }
    }

    QString content;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(getEditor(), tr("Unable to open file"),
                file.errorString());
        return;
    }
    else
    {
        QTextStream in(&file);
        content = in.readAll();
        file.close();
    }

    //Example : BlockName ( BlockClass )
    QRegExp blockDeclarationExp("^\\s*([^\\s]+)\\s*\\(\\s*([^\\s]+)\\s*\\)\\s*$");

    //Example : SourceBlockName SourceBlockOutput -> TargetBlockInput TargetBlockName
    QRegExp arrowDeclarationExp("^\\s*([^\\s]+)\\s+([^\\s]+)\\s*-+>\\s*([^\\s]+)\\s*([^\\s]+)\\s*$");

    QStringList instructions = content.split(",");

    foreach(QString instruction, instructions)
    {
        //Import block
        if (blockDeclarationExp.exactMatch(instruction))
        {
            QString blockName = blockDeclarationExp.cap(1);
            QString blockClass = blockDeclarationExp.cap(2);
            
            //TODO ACY Vérifier qu'un block du même nom n'est pas déjà pris 
            //Si c'est le cas, arrêter tout et renvoyer une erreur car la gestion des flêches par la suite va être tordue sinon
                        
            getEditor()->runScriptCommand(
                    QString("Create a new block with name %1 and class %2")
                    .arg(blockName)
                    .arg(blockClass)
                    );
        }
            //Import arrow
        else if (arrowDeclarationExp.exactMatch(instruction))
        {
            QString sourceBlockName = arrowDeclarationExp.cap(1);
            QString sourceBlockOutput = arrowDeclarationExp.cap(2);
            QString targetBlockInput = arrowDeclarationExp.cap(3);
            QString targetBlockName = arrowDeclarationExp.cap(4);
            
            getEditor()->runScriptCommand(
                    QString("Create a new arrow from block %1 port %2 to block %3 port %4")
                    .arg(sourceBlockName)
                    .arg(sourceBlockOutput)
                    .arg(targetBlockName)
                    .arg(targetBlockInput)
                    );
        }
    }

    QMessageBox::information(getEditor(), tr("Import successful"), "Diagram was successfully imported.");
}

