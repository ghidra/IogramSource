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


#include "Scene_LoadScene.h"
//#include "OrbitCamera.h"

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Viewport.h>

using namespace Urho3D;

String Scene_LoadScene::iconTexture = "Textures/Icons/Scene_LoadScene.png";

Scene_LoadScene::Scene_LoadScene(Urho3D::Context* context) :IoComponentBase(context, 0, 0)
{
	SetName("LoadScene");
	SetFullName("Load Scene");
	SetDescription("Loads a Scene resource file from XML or JSON");

	AddInputSlot(
		"ScenePath",
		"P",
		"Resource Path to scene file",
		VAR_STRING,
		DataAccess::ITEM
	);

	AddInputSlot(
		"Additive",
		"A",
		"If true, loads scene additively",
		VAR_BOOL,
		DataAccess::ITEM
	);

	AddOutputSlot(
		"SceneReference",
		"S",
		"Pointer to loaded scene",
		VAR_PTR,
		DataAccess::ITEM
	);
}

void Scene_LoadScene::SolveInstance(
	const Urho3D::Vector<Urho3D::Variant>& inSolveInstance,
	Urho3D::Vector<Urho3D::Variant>& outSolveInstance
)
{
	String path = inSolveInstance[0].GetString();

	if (path.Empty())
	{
		outSolveInstance[0] = Variant();
		return;
	}

	ResourceCache* c = GetSubsystem<ResourceCache>();

	//check that resource exists
	

	if (path.Contains(".json"))
	{

		JSONFile* sceneFile = c->GetResource<JSONFile>(path);
		if (!sceneFile)
		{
			outSolveInstance[0] = Variant();
			return;
		}

		Scene* scene = (Scene*)GetGlobalVar("Scene").GetPtr();
		if (scene)
		{
			scene->Remove();
			
			scene->LoadJSON(sceneFile->GetRoot());
			outSolveInstance[0] = scene;

			//add orbit camera back in
			/*OrbitCamera* orbitCamera = scene->GetComponent<OrbitCamera>(true);
			if (!orbitCamera)
			{
				Node* cameraNode_ = scene->CreateChild("OrbitCamera");
				orbitCamera = cameraNode_->CreateComponent<OrbitCamera>();
			}


			//make sure to hook up camera to viewport??
			Camera* cam = orbitCamera->GetNode()->GetComponent<Camera>(true);
			Viewport* vp = (Viewport*)GetGlobalVar("activeViewport").GetVoidPtr();
			if (vp && cam)
			{
				vp->SetCamera(cam);
			}*/


			return;

		}

	}
	else if (path.Contains(".xml"))
	{
		
		XMLFile* sceneFile = c->GetResource<XMLFile>(path);
		if (!sceneFile)
		{
			outSolveInstance[0] = Variant();
			return;
		}
		
		Scene* scene = (Scene*)GetGlobalVar("Scene").GetPtr();
		if (scene)
		{
			scene->Remove();
			
			scene->LoadXML(sceneFile->GetRoot());
			outSolveInstance[0] = scene;

			//add orbit camera back in
			// Create the camera
			/*OrbitCamera* orbitCamera = scene->GetComponent<OrbitCamera>(true);
			if (!orbitCamera)
			{
				Node* cameraNode_ = scene->CreateChild("OrbitCamera");
				orbitCamera = cameraNode_->CreateComponent<OrbitCamera>();
			}


			//make sure to hook up camera to viewport??
			Camera* cam = orbitCamera->GetNode()->GetComponent<Camera>(true);
			Viewport* vp = (Viewport*)GetGlobalVar("activeViewport").GetVoidPtr();
			if (vp && cam)
			{
				vp->SetCamera(cam);
			}
			*/


			return;

		}
	}
	else
	{
		outSolveInstance[0] = Variant();
		return;
	}
}

