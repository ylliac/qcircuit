/* 
 * File:   FBPEditorNetwork.h
 * Author: acailly
 *
 * Created on 25 février 2014, 14:03
 */

#ifndef FBPEDITORNETWORK_H
#define	FBPEDITORNETWORK_H

#include "core/FBPNetwork.h"

class FBPEditor;

class FBPEditorNetwork : public FBPNetwork {
public:
    FBPEditorNetwork(FBPEditor* editor);
    virtual ~FBPEditorNetwork();
    
protected:
    virtual void define();

private:
    FBPEditor* m_Editor;    
};

#endif	/* FBPEDITORNETWORK_H */

