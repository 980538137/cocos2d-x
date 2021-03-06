#include "UIListViewTest.h"

USING_NS_CC;
using namespace cocos2d::ui;

const char* font_UIListViewTest = "fonts/Marker Felt.ttf";

UIListViewTests::UIListViewTests()
{
    ADD_TEST_CASE(UIListViewTest_Vertical);
    ADD_TEST_CASE(UIListViewTest_Horizontal);
    ADD_TEST_CASE(Issue12692);
    ADD_TEST_CASE(Issue8316);
}

// UIListViewTest_Vertical

UIListViewTest_Vertical::UIListViewTest_Vertical()
: _displayValueLabel(nullptr)
{
    
}

UIListViewTest_Vertical::~UIListViewTest_Vertical()
{
}

bool UIListViewTest_Vertical::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        _displayValueLabel = Text::create("Move by vertical direction", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                              widgetSize.height / 2.0f + _displayValueLabel->getContentSize().height * 1.5f));
        _uiLayer->addChild(_displayValueLabel);
        
        
        Text* alert = Text::create("ListView vertical", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                 widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        
        // create list view ex data
       
        for (int i = 0; i < 20; ++i)
        {
            std::string ccstr = StringUtils::format("listview_item_%d", i);
            _array.push_back(ccstr);
        }
        
        
        // Create the list view ex
        ListView* listView = ListView::create();
        // set list view ex direction
        listView->setDirection(ui::ScrollView::Direction::VERTICAL);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("cocosui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setContentSize(Size(240, 130));
        listView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                    (backgroundSize.width - listView->getContentSize().width) / 2.0f,
                                    (widgetSize.height - backgroundSize.height) / 2.0f +
                                    (backgroundSize.height - listView->getContentSize().height) / 2.0f));
        listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(UIListViewTest_Vertical::selectedItemEvent, this));
        listView->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(UIListViewTest_Vertical::selectedItemEventScrollView,this));
		listView->setScrollBarPositionFromCorner(Vec2(7, 7));
        _uiLayer->addChild(listView);
        
        
        // create model
        Button* default_button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
        default_button->setName("Title Button");
        
        Layout* default_item = Layout::create();
        default_item->setTouchEnabled(true);
        default_item->setContentSize(default_button->getContentSize());
        default_button->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
                                          default_item->getContentSize().height / 2.0f));
        default_item->addChild(default_button);
        
        // set model
        listView->setItemModel(default_item);
        
        // add default item
        ssize_t count = _array.size();
        for (int i = 0; i < count / 4; ++i)
        {
            listView->pushBackDefaultItem();
        }
        // insert default item
        for (int i = 0; i < count / 4; ++i)
        {
            listView->insertDefaultItem(0);
        }
        
        listView->removeAllChildren();
        
        Sprite* testSprite = Sprite::create("cocosui/backtotoppressed.png");
        testSprite->setPosition(Vec2(200,200));
        listView->addChild(testSprite);
        
        // add custom item
        for (int i = 0; i < count / 4; ++i)
        {
            Button* custom_button = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
            custom_button->setName("Title Button");
            custom_button->setScale9Enabled(true);
            custom_button->setContentSize(default_button->getContentSize());
            
            Layout *custom_item = Layout::create();
            custom_item->setContentSize(custom_button->getContentSize());
            custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
            custom_item->addChild(custom_button);
            
            listView->addChild(custom_item);
        }
        // insert custom item
        Vector<Widget*>& items = listView->getItems();
        ssize_t items_count = items.size();
        for (int i = 0; i < count / 4; ++i)
        {
            Button* custom_button = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
            custom_button->setName("Title Button");
            custom_button->setScale9Enabled(true);
            custom_button->setContentSize(default_button->getContentSize());
            
            Layout *custom_item = Layout::create();
            custom_item->setContentSize(custom_button->getContentSize());
            custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
            custom_item->addChild(custom_button);
            custom_item->setTag(1);
            
            listView->insertCustomItem(custom_item, items_count);
        }
        
        // set item data
        items_count = items.size();
        for (int i = 0; i < items_count; ++i)
        {
            Widget* item = listView->getItem(i);
            Button* button = static_cast<Button*>(item->getChildByName("Title Button"));
            ssize_t index = listView->getIndex(item);
            button->setTitleText(_array[index]);
        }
        
        // remove last item
        listView->removeChildByTag(1);
        
        // remove item by index
        items_count = items.size();
        listView->removeItem(items_count - 1);
        
        // set all items layout gravity
        listView->setGravity(ListView::Gravity::CENTER_VERTICAL);
        
        // set items margin
        listView->setItemsMargin(2.0f);
        
        return true;
    }
    
    return false;
}

void UIListViewTest_Vertical::selectedItemEvent(Ref *pSender, ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            break;
        }
        default:
            break;
    }
}

void UIListViewTest_Vertical::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
{
    switch (type) {
        case ui::ScrollView::EventType::SCROLL_TO_BOTTOM:
            CCLOG("SCROLL_TO_BOTTOM");
            break;
        case ui::ScrollView::EventType::SCROLL_TO_TOP:
            CCLOG("SCROLL_TO_TOP");
            break;
        default:
            break;
    }
}


// UIListViewTest_Horizontal

UIListViewTest_Horizontal::UIListViewTest_Horizontal()
: _displayValueLabel(nullptr)
{
}

UIListViewTest_Horizontal::~UIListViewTest_Horizontal()
{
}

bool UIListViewTest_Horizontal::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        _displayValueLabel = Text::create("Move by horizontal direction", "fonts/Marker Felt.ttf", 32);
        _displayValueLabel->setAnchorPoint(Vec2(0.5f, -1.0f));
        _displayValueLabel->setPosition(Vec2(widgetSize.width / 2.0f,
                                              widgetSize.height / 2.0f
                                              + _displayValueLabel->getContentSize().height * 1.5f));
        
        _uiLayer->addChild(_displayValueLabel);
        
        
        Text* alert = Text::create("ListView horizontal", "fonts/Marker Felt.ttf", 30);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = static_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        
        // create list view ex data
      
        for (int i = 0; i < 20; ++i)
        {
            std::string ccstr = StringUtils::format("listview_item_%d", i);
            _array.push_back(ccstr);
        }
        
        
        // Create the list view ex
        ListView* listView = ListView::create();
        // set list view ex direction
        listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
        listView->setTouchEnabled(true);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("cocosui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setContentSize(Size(240, 130));
        listView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                    (backgroundSize.width - listView->getContentSize().width) / 2.0f,
                                    (widgetSize.height - backgroundSize.height) / 2.0f +
                                    (backgroundSize.height - listView->getContentSize().height) / 2.0f));
        listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(UIListViewTest_Horizontal::selectedItemEvent, this));
		listView->setScrollBarPositionFromCorner(Vec2(7, 7));
        _uiLayer->addChild(listView);
        
        
        // create model
        Button* default_button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
        default_button->setName("Title Button");
        
        Layout *default_item = Layout::create();
        default_item->setTouchEnabled(true);
        default_item->setContentSize(default_button->getContentSize());
        default_button->setPosition(Vec2(default_item->getContentSize().width / 2.0f, default_item->getContentSize().height / 2.0f));
        default_item->addChild(default_button);
        
        // set model
        listView->setItemModel(default_item);
        
        // add default item
        ssize_t count = _array.size();
        for (int i = 0; i < count / 4; ++i)
        {
            listView->pushBackDefaultItem();
        }
        // insert default item
        for (int i = 0; i < count / 4; ++i)
        {
            listView->insertDefaultItem(0);
        }
        
        // add custom item
        for (int i = 0; i < count / 4; ++i)
        {
            Button* custom_button = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
            custom_button->setName("Title Button");
            custom_button->setScale9Enabled(true);
            custom_button->setContentSize(default_button->getContentSize());
            
            Layout* custom_item = Layout::create();
            custom_item->setContentSize(custom_button->getContentSize());
            custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
            custom_item->addChild(custom_button);
            
            listView->pushBackCustomItem(custom_item);
        }
        // insert custom item
        Vector<Widget*>& items = listView->getItems();
        ssize_t items_count = items.size();
        for (int i = 0; i < count / 4; ++i)
        {
            Button* custom_button = Button::create("cocosui/button.png", "cocosui/buttonHighlighted.png");
            custom_button->setName("Title Button");
            custom_button->setScale9Enabled(true);
            custom_button->setContentSize(default_button->getContentSize());
            
            Layout* custom_item = Layout::create();
            custom_item->setContentSize(custom_button->getContentSize());
            custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
            custom_item->addChild(custom_button);
            
            listView->insertCustomItem(custom_item, items_count);
        }
        
        // set item data
        items_count = items.size();
        for (int i = 0; i < items_count; ++i)
        {
            Widget *item = listView->getItem(i);
            Button *button = static_cast<Button*>(item->getChildByName("Title Button"));
            ssize_t index = listView->getIndex(item);
            button->setTitleText(_array[index]);
        }
        // remove last item
        listView->removeLastItem();
        
        // remove item by index
        items_count = items.size();
        listView->removeItem(items_count - 1);        
        
        // set all items layout gravity
        listView->setGravity(ListView::Gravity::CENTER_VERTICAL);
        
        // set items margin
        listView->setItemsMargin(2);
        
        return true;
    }
    
    return false;
}

void UIListViewTest_Horizontal::selectedItemEvent(Ref *pSender, ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            break;
        }
        default:
            break;
    }
}

bool Issue12692::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        auto label = Text::create("Issue 12692", "fonts/Marker Felt.ttf", 32);
        label->setAnchorPoint(Vec2(0.5f, -1.0f));
        label->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f + label->getContentSize().height * 1.5f));
        _uiLayer->addChild(label);
        
        
        Text* alert = Text::create("ListView in ListView enable Scissor Clipping", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        // Create the list view ex
        ListView* listView = ListView::create();
        // set list view ex direction
        listView->setDirection(ui::ScrollView::Direction::VERTICAL);
        listView->setBounceEnabled(true);
        listView->setBackGroundImage("cocosui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setContentSize(Size(240, 130));
        listView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                   (backgroundSize.width - listView->getContentSize().width) / 2.0f,
                                   (widgetSize.height - backgroundSize.height) / 2.0f +
                                   (backgroundSize.height - listView->getContentSize().height) / 2.0f));
        listView->setScrollBarPositionFromCorner(Vec2(7, 7));
        listView->setClippingEnabled(true);
        listView->setClippingType(ui::Layout::ClippingType::SCISSOR);
        listView->setName("listview1");
        _uiLayer->addChild(listView);
        
        auto list2 = ListView::create();
        list2->setDirection(ui::ScrollView::Direction::VERTICAL);
        list2->setBounceEnabled(true);
        list2->setBackGroundImage("cocosui/green_edit.png");
        list2->setBackGroundImageScale9Enabled(true);
        list2->setContentSize(Size(240, 65));
        list2->setClippingEnabled(true);
        list2->setClippingType(ui::Layout::ClippingType::SCISSOR);
        list2->setName("listview2");
        listView->insertCustomItem(list2, 0);
        
        {
            Button* default_button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
            default_button->setName("Title Button");
            
            Layout* default_item = Layout::create();
            default_item->setTouchEnabled(true);
            default_item->setContentSize(default_button->getContentSize());
            default_button->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
                                             default_item->getContentSize().height / 2.0f));
            default_item->addChild(default_button);
            
            // set model
            listView->setItemModel(default_item);
            listView->pushBackDefaultItem();
            listView->pushBackDefaultItem();
            listView->pushBackDefaultItem();
        }
        {
            Button* default_button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
            default_button->setName("Title Button");
            
            Layout* default_item = Layout::create();
            default_item->setTouchEnabled(true);
            default_item->setContentSize(default_button->getContentSize());
            default_button->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
                                             default_item->getContentSize().height / 2.0f));
            default_item->addChild(default_button);
            
            // set model
            list2->setItemModel(default_item);
            list2->pushBackDefaultItem();
            list2->pushBackDefaultItem();
            list2->pushBackDefaultItem();
        }
        return true;
    }
    
    return false;
}


bool Issue8316::init()
{
    if (UIScene::init())
    {
        Size widgetSize = _widget->getContentSize();
        
        auto label = Text::create("Issue 8316", "fonts/Marker Felt.ttf", 32);
        label->setAnchorPoint(Vec2(0.5f, -1.0f));
        label->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f + label->getContentSize().height * 1.5f));
        _uiLayer->addChild(label);
        
        
        Text* alert = Text::create("ListView Disable Touch", "fonts/Marker Felt.ttf", 20);
        alert->setColor(Color3B(159, 168, 176));
        alert->setPosition(Vec2(widgetSize.width / 2.0f,
                                widgetSize.height / 2.0f - alert->getContentSize().height * 3.075f));
        _uiLayer->addChild(alert);
        
        Layout* root = static_cast<Layout*>(_uiLayer->getChildByTag(81));
        
        Layout* background = dynamic_cast<Layout*>(root->getChildByName("background_Panel"));
        Size backgroundSize = background->getContentSize();
        
        // Create the list view ex
        ListView* listView = ListView::create();
        // set list view ex direction
        listView->setDirection(ui::ScrollView::Direction::VERTICAL);
        listView->setBounceEnabled(true);
        listView->setTouchEnabled(false);
        listView->setBackGroundImage("cocosui/green_edit.png");
        listView->setBackGroundImageScale9Enabled(true);
        listView->setContentSize(Size(240, 130));
        listView->setPosition(Vec2((widgetSize.width - backgroundSize.width) / 2.0f +
                                   (backgroundSize.width - listView->getContentSize().width) / 2.0f,
                                   (widgetSize.height - backgroundSize.height) / 2.0f +
                                   (backgroundSize.height - listView->getContentSize().height) / 2.0f));
        listView->setScrollBarPositionFromCorner(Vec2(7, 7));
        listView->setClippingEnabled(true);
        listView->setClippingType(ui::Layout::ClippingType::SCISSOR);
        listView->setName("listview1");
        
        {
            Button* default_button = Button::create("cocosui/backtotoppressed.png", "cocosui/backtotopnormal.png");
            default_button->setName("Title Button");
            
            Layout* default_item = Layout::create();
            default_item->setTouchEnabled(true);
            default_item->setContentSize(default_button->getContentSize());
            default_button->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
                                             default_item->getContentSize().height / 2.0f));
            default_item->addChild(default_button);
            
            // set model
            listView->setItemModel(default_item);
            listView->pushBackDefaultItem();
            listView->pushBackDefaultItem();
            listView->pushBackDefaultItem();
        }
        
        _uiLayer->addChild(listView);
        
      
        return true;
    }
    
    return false;
}
