/* 
 * File:   FBPSubNetwork.cpp
 * Author: acailly
 * 
 * Created on 19 février 2014, 14:04
 */

#include "FBPSubNetwork.h"

FBPSubNetwork::FBPSubNetwork(QObject* parent)
: FBPNetwork(parent)
{
}

FBPSubNetwork::~FBPSubNetwork()
{
}

void FBPSubNetwork::execute()
{
    go();
}

