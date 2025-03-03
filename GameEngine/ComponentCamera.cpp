#include "ComponentCamera.h"
#include "GameObject.h"
#include "Transform.h"
#include "imgui.h"
#include "Application.h"
#include "ModuleMesh.h"

CameraComponent::CameraComponent(ComponentType Ctype)
{
	//Component
	if (Ctype == ComponentType::CAMERA) {
		type = ComponentType::CAMERA;
		frustum.type = PerspectiveFrustum;
	}
	else if(Ctype == ComponentType::UICAMERA)
	{

		type = ComponentType::UICAMERA;
		frustum.type = OrthographicFrustum;
	}
	containerParent = nullptr;

	//Frustum
	frustum.nearPlaneDistance = nearDistance;
	frustum.farPlaneDistance = farDistance; //inspector
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;
	frustum.verticalFov = cameraFOV * DEGTORAD;
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * 1.7f); // 16:9 ~= 1,77777...
	frustum.pos = float3(0, 0, 0);

	CreateFrameBuffer();
}

CameraComponent::~CameraComponent()
{
	if (isMainCamera) Application::GetInstance()->renderer3D->SetMainCamera(nullptr);

	glDeleteFramebuffers(1, &cameraBuffer);
	glDeleteFramebuffers(1, &frameBuffer);
	glDeleteFramebuffers(1, &renderObjBuffer);

}

void CameraComponent::PrintInspector()
{
	//Roger tu turno
	const char* listType[]{ "Perspective", "Orthographic" };

	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth))
	{
		//is main camera??
		if (isMainCamera)
		{
			ImGui::SameLine();
			ImGui::Text(" ( Main Camera )");
		}

		ImGui::LabelText("##Game mesh", "Rendering Meshes:");
		ImGui::SameLine();
		ImGui::Text("%d", Application::GetInstance()->meshRenderer->renderedGameMeshes);

		ImGui::Text("");

		//Chose type of camera
		ImGui::Text("Camera type:\t ");
		ImGui::SameLine();
		if (ImGui::Combo("##CameraType", &typeCameraSelected, listType, IM_ARRAYSIZE(listType)))
		{
			if(typeCameraSelected == 0)
				frustum.type = PerspectiveFrustum;

			if(typeCameraSelected == 1)
				frustum.type = OrthographicFrustum;
		}

		ImGui::Text("");

		//Fov camera
		ImGui::Text("FOV\t\t\t  ");
		ImGui::SameLine();
		if (ImGui::SliderInt("##FOVert", &cameraFOV, 10, 170))
		{
			frustum.verticalFov = cameraFOV * DEGTORAD;
			frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * 1.7f);
		}

		ImGui::Text("");

		//Slider Set Near Distane
		ImGui::Text("Near Distance\t");
		ImGui::SameLine();
		if (ImGui::SliderFloat("##nearDistance", &nearDistance, 0.1f, farDistance))
		{
			frustum.nearPlaneDistance = nearDistance;
		}

		ImGui::Text("");

		//Input float Set Far Distane
		ImGui::Text("Far Distance\t ");
		ImGui::SameLine();
		if (ImGui::InputFloat("##farDistance", &farDistance))
		{
			if (farDistance <= nearDistance)
			{
				nearDistance = farDistance;
			}

			frustum.farPlaneDistance = farDistance;
		}
		
		ImGui::Text("");

		//Button Set main camera
		ImGui::Text("");
		ImGui::SameLine((ImGui::GetWindowWidth() / 2) - 75);
		if (ImGui::Button("Set as main camera", ImVec2(150,25)))
		{
			Application::GetInstance()->renderer3D->SetMainCamera(this);
		}
	}
}

void CameraComponent::Update()
{
	if (containerParent == nullptr) return;

	frustum.pos = containerParent->transform->getPosition();
	float4x4 m = containerParent->transform->getGlobalMatrix();
	frustum.up = m.RotatePart().Col(1).Normalized();
	frustum.front = m.RotatePart().Col(2).Normalized();
}

void CameraComponent::CreateFrameBuffer()
{
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	// generate texture
	glGenTextures(1, &cameraBuffer);
	glBindTexture(GL_TEXTURE_2D, cameraBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	float color[4] = { 0.1,0.1,0.1,0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cameraBuffer, 0);

	glGenRenderbuffers(1, &renderObjBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderObjBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderObjBuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		LOGT(LogsType::WARNINGLOG, "ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//bind ingame buffer
	Application::GetInstance()->renderer3D->SetMainCamera(this);
}

void CameraComponent::Look(const float3& Position, const float3& Reference)
{
	frustum.pos = Position;
	reference = Reference;

	LookAt(reference);
}

void CameraComponent::LookAt(const float3& Spot)
{
	reference = Spot;
	frustum.front = (Spot - frustum.pos).Normalized();
	float3 X = float3(0, 1, 0).Cross(frustum.front).Normalized();
	frustum.up = frustum.front.Cross(X);
}

void CameraComponent::Move(const float3& Movement)
{
	frustum.pos += Movement;
}

float* CameraComponent::GetViewMatrix()
{
	viewMatrix = frustum.ViewMatrix();
	viewMatrix.Transpose();
	return viewMatrix.ptr();
}

float* CameraComponent::GetProjetionMatrix()
{
	projectionMatrix = frustum.ProjectionMatrix();
	projectionMatrix.Transpose();
	return projectionMatrix.ptr();
}

bool CameraComponent::IsInsideFrustum(Mesh* mesh)
{
	float3 boxPoints[8];
	Plane frustumPlanes[6];

	mesh->Global_AABB_box.GetCornerPoints(boxPoints);
	frustum.GetPlanes(frustumPlanes);

	//Check all frustum planes
	for (size_t i = 0; i < 6; i++)
	{
		int p = 0;

		//Check all box points to each frustum plane
		for (size_t j = 0; j < 8; j++)
		{
			if (frustumPlanes[i].IsOnPositiveSide(boxPoints[j])) 
				p++;
		}

		//Check if all points are outside
		if (p == 8) {
			//All points outside one of the planes -> outside frustum
			return false;
		}
	}

	//AABB box is at least partially inside frustum
	return true;
}

void CameraComponent::SetAspectRatio(float aspectRatio)
{
	frustum.verticalFov = cameraFOV * DEGTORAD;
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * aspectRatio);
}