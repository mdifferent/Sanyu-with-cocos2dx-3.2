//
//  CharacterLayer.cpp
//  Sanyu
//
//  Created by wuhanming on 14-9-7.
//
//

#include "CharacterLayer.h"

bool CharacterLayer::init()
{
    return true;
}

void CharacterLayer::setCharacter(const string& name, const int position, Vector<string> *property, ActionInterval *action)
{
    
}

void CharacterLayer::setCharacter(const string& name, Vec2 posistion, Vector<string> *property, ActionInterval *action)
{
    
}

void CharacterLayer::setCharacter(const string& name, float xpos, Vector<string> *property, ActionInterval *action)
{
    
}

void CharacterLayer::removeCharacter(const string& name, ActionInterval *action)
{
    
}

int CharacterLayer::getCharacterCount()
{
    return _characters.size();
}
