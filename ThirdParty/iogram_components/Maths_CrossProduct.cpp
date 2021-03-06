//
// Copyright (c) 2016 - 2017 Mesh Consultants Inc.
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


#include "Maths_CrossProduct.h"

#include <assert.h>

#include <Urho3D/Core/Variant.h>

using namespace Urho3D;

String Maths_CrossProduct::iconTexture = "Textures/Icons/Maths_CrossProduct.png";

Maths_CrossProduct::Maths_CrossProduct(Urho3D::Context* context) : IoComponentBase(context, 2, 1)
{
	SetName("CrossProduct");
	SetFullName("Cross Product");
	SetDescription("Computes the cross product of two vectors");
	SetGroup(IoComponentGroup::MATHS);
	SetSubgroup("Operators");

	Variant default_vec = Vector3(0.0f, 0.0f, 0.0f);

	inputSlots_[0]->SetName("firstVector");
	inputSlots_[0]->SetVariableName("X");
	inputSlots_[0]->SetDescription("First vector");
	inputSlots_[0]->SetVariantType(VariantType::VAR_VECTOR3);
	inputSlots_[0]->SetDefaultValue(default_vec);
	inputSlots_[0]->DefaultSet();

	inputSlots_[1]->SetName("secondVector");
	inputSlots_[1]->SetVariableName("Y");
	inputSlots_[1]->SetDescription("Second vector");
	inputSlots_[1]->SetVariantType(VariantType::VAR_VECTOR3);
	inputSlots_[1]->SetDefaultValue(default_vec);
	inputSlots_[1]->DefaultSet();

	outputSlots_[0]->SetName("Cross Product");
	outputSlots_[0]->SetVariableName("C");
	outputSlots_[0]->SetDescription("Float representing X cross Y");
	outputSlots_[0]->SetVariantType(VariantType::VAR_FLOAT);
	outputSlots_[0]->SetDataAccess(DataAccess::ITEM);

}

void Maths_CrossProduct::SolveInstance(
	const Vector<Variant>& inSolveInstance,
	Vector<Variant>& outSolveInstance
	)
{
	assert(inSolveInstance.Size() == inputSlots_.Size());

	///////////////////
	// EXTRACT & VERIFY

	if (!IsAllInputValid(inSolveInstance)) {
		SetAllOutputsNull(outSolveInstance);
		return;
	}

	Vector3 X = inSolveInstance[0].GetVector3();
	Vector3 Y = inSolveInstance[1].GetVector3();

	///////////////////
	// COMPONENT'S WORK

	Variant cross_prod;

	cross_prod = X.CrossProduct(Y);

	/////////////////
	// ASSIGN OUTPUTS

	outSolveInstance[0] = cross_prod;
}
