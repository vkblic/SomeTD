/****************************************************************************
Copyright (c) 2013 kelyad
****************************************************************************/
#ifndef __CCMENU_H_
#define __CCMENU_H_

#include "CC.h"
#include "layers_scenes_transitions_nodes/CCLayer.h"

NS_CC_BEGIN

/**
 * @addtogroup GUI
 * @{
 * @addtogroup menu
 * @{
 */
typedef enum  
{
    kCCMenuStateWaiting,
    kCCMenuStateTrackingTouch
} tCCMenuState;

enum {
    //* priority used by the menu for the event handler
    kCCMenuHandlerPriority = -128,
};

/** @brief A CCMenu
* 
* Features and Limitation:
*  - You can add MenuItem objects in runtime using addChild:
*  - But the only accepted children are MenuItem objects
*/
class CC_DLL CCMenu : public CCLayer, public CCRGBAProtocol
{
    /** Color: conforms with CCRGBAProtocol protocol */
    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color);
    /** Opacity: conforms with CCRGBAProtocol protocol */
    CC_PROPERTY(GLubyte, m_cOpacity, Opacity);
    /** whether or not the menu will receive events */
    bool m_bEnabled;
    
public:
    CCMenu()
        : m_cOpacity(0)
        , m_pSelectedItem(NULL)
    {}
    virtual ~CCMenu(){}

    /** creates an empty CCMenu */
    static CCMenu* create();

    /** creates a CCMenu with CCMenuItem objects */
    static CCMenu* create(CCMenuItem* item, ...);

    /** creates a CCMenu with a CCArray of CCMenuItem objects */
    static CCMenu* createWithArray(CCArray* pArrayOfItems);

    /** creates a CCMenu with it's item, then use addChild() to add 
      * other items. It is used for script, it can't init with undetermined
      * number of variables.
    */
    static CCMenu* createWithItem(CCMenuItem* item);
    
    /** creates a CCMenu with CCMenuItem objects */
    static CCMenu* createWithItems(CCMenuItem *firstItem, va_list args);

    /** initializes an empty CCMenu */
    bool init();

    /** initializes a CCMenu with a NSArray of CCMenuItem objects */
    bool initWithArray(CCArray* pArrayOfItems);

    /** align items vertically */
    void alignItemsVertically();
    /** align items vertically with padding
    @since v0.7.2
    */
    void alignItemsVerticallyWithPadding(float padding);

    /** align items horizontally */
    void alignItemsHorizontally();
    /** align items horizontally with padding
    @since v0.7.2
    */
    void alignItemsHorizontallyWithPadding(float padding);

    /** align items in rows of columns */
    void alignItemsInColumns(unsigned int columns, ...);
    void alignItemsInColumns(unsigned int columns, va_list args);
    void alignItemsInColumnsWithArray(CCArray* rows);

    /** align items in columns of rows */
    void alignItemsInRows(unsigned int rows, ...);
    void alignItemsInRows(unsigned int rows, va_list args);
    void alignItemsInRowsWithArray(CCArray* columns);

    /** set event handler priority. By default it is: kCCMenuTouchPriority */
    void setHandlerPriority(int newPriority);

    //super methods
    virtual void addChild(CCNode * child);
    virtual void addChild(CCNode * child, int zOrder);
    virtual void addChild(CCNode * child, int zOrder, int tag);
    virtual void registerWithTouchDispatcher();
    virtual void removeChild(CCNode* child, bool cleanup);

    /**
    @brief For phone event handle functions
    */
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual void ccTouchCancelled(CCTouch *touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

    /**
    @since v0.99.5
    override onExit
    */
    virtual void onExit();

    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
    
    virtual bool isEnabled() { return m_bEnabled; }
    virtual void setEnabled(bool value) { m_bEnabled = value; };

protected:
    CCMenuItem* itemForTouch(CCTouch * touch);
    tCCMenuState m_eState;
    CCMenuItem *m_pSelectedItem;
};

// end of GUI group
/// @}
/// @}

NS_CC_END

#endif//__CCMENU_H_
