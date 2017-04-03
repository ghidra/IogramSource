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

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Scene/SceneEvents.h>

#include <Urho3D/UI/Cursor.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/UIEvents.h>

#include <Urho3D/Resource/ResourceCache.h>

#include "IogramNodeAddButton.h"
#include "../../Core/IoComponentBase.h"

#include <Urho3D/DebugNew.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Engine/DebugHud.h>

namespace Urho3D
{

static const int DEFAULT_RESIZE_BORDER = 4;

IogramNodeAddButton::IogramNodeAddButton(Context* context) :
    Button(context)
{

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    XMLFile* style = cache->GetResource<XMLFile>("UI/IogramDefaultStyle.xml");
    SetStyleAuto(style);

    SetName("Add Node");
    SetMinHeight(24);
    
    
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

    //SubscribeToEvent(GetNode(), E_ELEMENTADDED, URHO3D_HANDLER(IogramWindow, HandleElementAdded));
    //SubscribeToEvent(E_LAYOUTUPDATED, URHO3D_HANDLER(IogramWindow, HandleSomething));

}

IogramNodeAddButton::~IogramNodeAddButton()
{
}

void IogramNodeAddButton::RegisterObject(Context* context)
{
    context->RegisterFactory<IogramNodeAddButton>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(BorderImage);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Is Enabled", true);
    URHO3D_UPDATE_ATTRIBUTE_DEFAULT_VALUE("Focus Mode", FM_FOCUSABLE);
    URHO3D_ACCESSOR_ATTRIBUTE("Pressed Image Offset", GetPressedOffset, SetPressedOffset, IntVector2, IntVector2::ZERO, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Pressed Child Offset", GetPressedChildOffset, SetPressedChildOffset, IntVector2, IntVector2::ZERO, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Repeat Delay", GetRepeatDelay, SetRepeatDelay, float, 1.0f, AM_FILE);
    URHO3D_ACCESSOR_ATTRIBUTE("Repeat Rate", GetRepeatRate, SetRepeatRate, float, 0.0f, AM_FILE);
}



}
