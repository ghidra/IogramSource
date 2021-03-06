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


#include "Mesh_ClosestPoint.h"

#include <assert.h>

#include <Urho3D/Core/Variant.h>
#include <Urho3D/Math/Vector3.h>

#include "ConversionUtilities.h"
#include "Geomlib_TriMeshClosestPoint.h"
#include "TriMesh.h"

using namespace Urho3D;

String Mesh_ClosestPoint::iconTexture = "Textures/Icons/Mesh_ClosestPoint.png";

Mesh_ClosestPoint::Mesh_ClosestPoint(Context* context) :
	IoComponentBase(context, 2, 3)
{
	SetName("MeshClosestPoint");
	SetFullName("Closest Point to Mesh");
	SetDescription("Find point on Mesh closest to query point");
	SetGroup(IoComponentGroup::MESH);
	SetSubgroup("Analysis");

	inputSlots_[0]->SetName("Mesh");
	inputSlots_[0]->SetVariableName("M");
	inputSlots_[0]->SetDescription("Mesh to search");
	inputSlots_[0]->SetVariantType(VariantType::VAR_VARIANTMAP);
	inputSlots_[0]->SetDataAccess(DataAccess::ITEM);

	inputSlots_[1]->SetName("Query Point");
	inputSlots_[1]->SetVariableName("Q");
	inputSlots_[1]->SetDescription("Point to search from");
	inputSlots_[1]->SetVariantType(VariantType::VAR_VECTOR3);
	inputSlots_[1]->SetDataAccess(DataAccess::ITEM);

	outputSlots_[0]->SetName("Point");
	outputSlots_[0]->SetVariableName("P");
	outputSlots_[0]->SetDescription("Point on mesh closest to query point");
	outputSlots_[0]->SetVariantType(VariantType::VAR_VECTOR3);
	outputSlots_[0]->SetDataAccess(DataAccess::ITEM);

	outputSlots_[1]->SetName("Index");
	outputSlots_[1]->SetVariableName("I");
	outputSlots_[1]->SetDescription("Index of closest face");
	outputSlots_[1]->SetVariantType(VariantType::VAR_INT);
	outputSlots_[1]->SetDataAccess(DataAccess::ITEM);

	outputSlots_[2]->SetName("Distance");
	outputSlots_[2]->SetVariableName("D");
	outputSlots_[2]->SetDescription("Distance from query point to mesh");
	outputSlots_[2]->SetVariantType(VariantType::VAR_FLOAT);
	outputSlots_[2]->SetDataAccess(DataAccess::ITEM);
}

void Mesh_ClosestPoint::SolveInstance(
	const Vector<Variant>& inSolveInstance,
	Vector<Variant>& outSolveInstance
)
{
	assert(inSolveInstance.Size() == inputSlots_.Size());

	Variant inMesh = inSolveInstance[0];
	VariantMap meshMap = inMesh.GetVariantMap();
	Vector3 q = inSolveInstance[1].GetVector3();

	int index = -1;
	Vector3 p;

	///////////////////////////////////////////////////////////////////////////////////////////////
	bool success = false;

	if (TriMesh_Verify(inMesh)) {
		success = Geomlib::TriMeshClosestPoint(inMesh, q, index, p);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////

	if (success) {
		float dist = sqrt((q - p).LengthSquared());

		outSolveInstance[0] = Variant(p);
		outSolveInstance[1] = Variant(index);
		outSolveInstance[2] = Variant(dist);
	}
	else {
		outSolveInstance[0] = Variant();
		outSolveInstance[1] = Variant();
		outSolveInstance[2] = Variant();
	}
}