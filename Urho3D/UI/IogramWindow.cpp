//
// Copyright (c) 2008-2017 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <Urho3D/Precompiled.h>

#include <Urho3D/Core/Context.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/UI/Cursor.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>

#include <Urho3D/Resource/ResourceCache.h>

#include "IogramWindow.h"
#include "../../Core/IoComponentBase.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

namespace Urho3D
{

static const int DEFAULT_RESIZE_BORDER = 4;

//extern const char* UI_CATEGORY;
const char* UI_CATEGORY = "UI";

IogramWindow::IogramWindow(Context* context) :
    Window(context)
{
    bringToFront_ = true;
    clipChildren_ = true;
    SetEnabled(true);

    //URHO3D_LOGWARNING("THIS IS A IOGRAM WINDOW");
    //NOTES
    //Should i get this everytime i make a window?
    //one argument, it would let me get only the relevant nodes to whatever specific context this graph is
    const HashMap<StringHash, SharedPtr<ObjectFactory> >& factories = context_->GetObjectFactories();
    HashMap<StringHash, SharedPtr<ObjectFactory> >::ConstIterator j = factories.Begin();
    while (j != factories.End()) {
      const TypeInfo* typeInfo = j->second_->GetTypeInfo();
      if (typeInfo->IsTypeOf<IoComponentBase>()) {
        node_list.Push( String(typeInfo->GetTypeName()) );
        //URHO3D_LOGRAW(typeInfo->GetTypeName() + " is a IoComponentBase\n");
      }
      j++;
    }

    ///now just to test... lets loop the new string podvector
    /*for(unsigned i=0; i<node_list.Size(); ++i)
    {
        URHO3D_LOGRAW(node_list[i] + " is a IoComponentBase\n");
    }
    */
    //ResourceCache* cache = GetSubsystem<ResourceCache>();
    //XMLFile* style = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");

    //SetDefaultStyle(style);

    /*UIElement* MainContainer = new UIElement(context_);
    MainContainer->SetMinSize(800, 400);
    MainContainer->SetMaxSize(2147483647, 2147483647);
    MainContainer->SetLayoutMode(LM_HORIZONTAL);
    //MainContainer->SetDefaultStyle(style);
    
    AddChild(MainContainer);

    Window* nodelist = new Window(context_);
    nodelist->SetName("NodeList");
    nodelist->SetMinSize(200, 400);
    nodelist->SetMaxSize(200, 2147483647);
    //nodelist->SetDefaultStyle(style);

    MainContainer->AddChild(nodelist);

    ApplyAttributes();
    UpdateLayout();*/
    UIElement* nodelist = GetChild("NodeList",true);
    if(nodelist != NULL)
    {
        URHO3D_LOGRAW("FOUND THE CHILD NODE");
    }
    else
    {
        URHO3D_LOGRAW("DID NOT FIND THE CHILD NODE");
    }
}

IogramWindow::~IogramWindow()
{
}

void IogramWindow::RegisterObject(Context* context)
{
    context->RegisterFactory<IogramWindow>(UI_CATEGORY);

    URHO3D_COPY_BASE_ATTRIBUTES(BorderImage);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Bring To Front", true);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Clip Children", true);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Is Enabled", true);
    URHO3D_ACCESSOR_ATTRIBUTE("Resize Border", GetResizeBorder, SetResizeBorder, IntRect, IntRect(DEFAULT_RESIZE_BORDER, \
        DEFAULT_RESIZE_BORDER, DEFAULT_RESIZE_BORDER, DEFAULT_RESIZE_BORDER), AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Is Movable", IsMovable, SetMovable, bool, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Is Resizable", IsResizable, SetResizable, bool, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Fixed Width Resizing", GetFixedWidthResizing, SetFixedWidthResizing, bool, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Fixed Height Resizing", GetFixedHeightResizing, SetFixedHeightResizing, bool, false, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Is Modal", IsModal, SetModal, bool, false, AM_FILE | AM_NOEDIT);
    URHO3D_ACCESSOR_ATTRIBUTE("Modal Shade Color", GetModalShadeColor, SetModalShadeColor, Color, Color::TRANSPARENT, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Modal Frame Color", GetModalFrameColor, SetModalFrameColor, Color, Color::TRANSPARENT, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Modal Frame Size", GetModalFrameSize, SetModalFrameSize, IntVector2, IntVector2::ZERO, AM_FILE);
    // Modal auto dismiss is purposefully not an attribute, as using it can make the editor lock up.
    // Instead it should be set false in code when needed
}


void IogramWindow::OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor)
{
    //NOTES
    //so maybe in here, I can make my node menu item, when in the window and tab is pressed

    UIElement::OnHover(position, screenPosition, buttons, qualifiers, cursor);

    if (dragMode_ == DRAG_NONE)
    {
        WindowDragMode mode = GetDragMode(position);
        SetCursorShape(mode, cursor);
    }
    else
        SetCursorShape(dragMode_, cursor);

    //it dpes find the child node
    UIElement* nodelist = GetChild("NodeList",true);
    if(nodelist != NULL)
    {
        URHO3D_LOGRAW("FOUND THE CHILD NODE");
    }
    else
    {
        URHO3D_LOGRAW("DID NOT FIND THE CHILD NODE");
    }

}



}
