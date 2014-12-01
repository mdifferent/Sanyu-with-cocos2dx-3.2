#include "HelloWorldScene.h"
#include "Resources.h"
#include "Views\DigitSprite.h"
#include "Views\MonsterHeadSprite.h"
#include "Views\CharacterLayer.h"
#include "Views\ChoiceLayer.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::create();
	label->setDimensions(400, 100);
	label->setLineBreakWithoutSpace(true);
	label->setString("123456789012345678901234567890 123456789012345678901234567890 12345678901234567890");
	label->setSystemFontName("Arial");
	label->setSystemFontSize(24);
    
    // position the label on the center of the screen
    //label->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));
	label->setAnchorPoint(Vec2(0, 1));
	label->setPosition(Vec2(100,100));

    // add the label as a child to this layer
    //this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("images/bk.jpg");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);

	/*
	MonsterHeadSprite *monster = MonsterHeadSprite::create("ɭ������");
	monster->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(monster, 0);

	DigitSprite* digit = DigitSprite::create();
	digit->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(digit, 0);
	digit->showDigit(21);*/
	
	/*
	//dialogue layer test
	Node* stencil = Node::create();
	auto clip1 = LayerColor::create(Color4B::BLACK, 24, 24);
	clip1->setPosition(Vec2(100,76));
	stencil->addChild(clip1);

	ClippingNode* clippingNode = ClippingNode::create(stencil);
	clippingNode->addChild(sprite);
	addChild(clippingNode, 2);*/

	/*
	//CharacterLayer test
	CharacterLayer *clayer = CharacterLayer::create();
	addChild(clayer, 1, 1);*/


	auto layer = ChoiceLayer::create();
	layer->setAnchorPoint(Vec2(0.5, 0.5));
	layer->setPosition(Vec2(400, 300));
	addChild(layer, 2, 2);


    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	CCLOG("Exit");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif
	auto layer = static_cast<ChoiceLayer*>(this->getChildByTag(2));
	vector<string> choices;
	choices.push_back("������");
	choices.push_back("������");
	layer->setChoices(choices);

	/*
	DigitSprite *digit = (DigitSprite*)getChildByName("digit");
	digit->showDigit(73);*/
	/*
	static int counter = 0;

	CharacterLayer *clayer = dynamic_cast<CharacterLayer*>(getChildByTag(1));
	list<string> properlist1;
	CCLOG("%d", counter);
		switch (counter % 6)
		{
		case 0:
			properlist1.push_back("����");
			clayer->showCharacter("��˿��", properlist1);
			break;
		case 1:
			properlist1.push_back("����");
			clayer->showCharacter("��˿��", properlist1, "left", CHAR_TRANSITION::MOVE_BOTTOM_BOUND);
			break;
		case 2:
			properlist1.push_back("����");
			clayer->showCharacter("��˿��", properlist1, "right", CHAR_TRANSITION::MOVE_BETWEEN);
			break;
		case 3:
			properlist1.push_back("����");
			clayer->showCharacter("��˿��", properlist1);
			break;
		case 4:
			properlist1.push_back("����");
			clayer->showCharacter("��˿��", properlist1, "left", CHAR_TRANSITION::MOVE_LEFT_BOUND);
			break;
		default:
			clayer->removeCharacter("��˿��", CHAR_TRANSITION::MOVE_TOP_BOUND);
			break;
		}
		counter++;*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}