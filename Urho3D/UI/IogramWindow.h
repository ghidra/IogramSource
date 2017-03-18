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

#pragma once

#include <Urho3D/UI/Window.h>

namespace Urho3D
{

/// %Window %UI element that can optionally by moved or resized.
class URHO3D_API IogramWindow : public Window
{
    URHO3D_OBJECT(IogramWindow, Window);

public:
    /// Construct.
    IogramWindow(Context* context);
    /// Destruct.
    virtual ~IogramWindow();
    /// Register object factory.
    static void RegisterObject(Context* context);

    /// Return UI rendering batches.
    //virtual void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor);
   // virtual bool LoadXML(const XMLElement& source, XMLFile* styleFile, bool setInstanceDefault = false);
    /// React to mouse hover.
    virtual void OnHover(const IntVector2& position, const IntVector2& screenPosition, int buttons, int qualifiers, Cursor* cursor);
    /// React to mouse drag begin.

private:
    Vector<String> node_list;//this will hold a list of loaded nodes
};



}
