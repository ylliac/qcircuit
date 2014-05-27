/* 
 * File:   ExportDiagram.cpp
 * Author: HOME
 * 
 * Created on 17 mai 2014, 12:02
 */

#include "ExportDiagram.h"

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <iostream>

#include "editor/FBPEditor.h"
#include "editor/scene/SceneDetective.h"
#include "editor/scene/EditorScene.h"
#include "editor/scene/BlockItem.h"
#include "editor/scene/ArrowItem.h"

ExportDiagram::ExportDiagram(FBPEditor* editor) :
FBPEditorAction(editor) {

}

ExportDiagram::~ExportDiagram() {
}

void ExportDiagram::execute(QString inputFileName, QString, QString, QString, QString) {

    QString fileName = inputFileName;

    //If input file name is empty, ask the user a file name
    if (fileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(getEditor(), "Export diagram", "", "FBP diagram (*.fbp)");
        if (fileName.isEmpty()) {
            return;
        }
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(getEditor(), tr("Unable to open file"),
                file.errorString());
        return;
    }

    {
        QTextStream out(&file);
        QGraphicsScene* scene = getEditor()->getScene();

        //Export block list
        QList<BlockItem*> blocks = SceneDetective::getBlocks(scene);
        foreach(BlockItem* block, blocks) {
            out << block->name() << " (null)," << endl;
        }

        //Export arrow list
        QList<ArrowItem*> arrows = SceneDetective::getArrows(scene);
        foreach(ArrowItem* arrow, arrows) {
            out << arrow->getStartBlock()->name() << " OUT -> IN " << arrow->getEndBlock()->name() << "," << endl;
        }
    }

    file.close();
    QMessageBox::information(getEditor(), tr("Export successful"), "Diagram was successfully exported.");
}

