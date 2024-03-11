#pragma once

#include "../FrogGameEngine/GameObject.h"
#include "imgui.h"
#include "../FrogGameEngine/EmmiterModule.h"
#include "../FrogGameEngine/SpawnModules.h"
#include "../FrogGameEngine/InitializeModules.h"
// #include "../FrogGameEngine/UpdateModules.h"
#include "../FrogGameEngine/BillboardingEM.h"

// spawn modules
void UIInspectorEmmiterSpawnModule(ConstantSpawnRate* spawnModule) {
	ImGui::SeparatorText("Constant Spawn Rate");
	ImGui::InputFloat("Spawn Rate", &spawnModule->spawnRate);
	ImGui::InputFloat("Particle Duration", &spawnModule->duration);
}

void UIInspectorEmmiterSpawnModule(SingleBurstSpawn* spawnModule) {
	ImGui::SeparatorText("Single Burst");
	ImGui::InputFloat("Amount", &spawnModule->amount);
	ImGui::InputFloat("Particle Duration", &spawnModule->duration);
}

void UIInspectorEmmiterSpawnModule(ConstantBurstSpawn* spawnModule) {
	ImGui::SeparatorText("Constant Burst");
	ImGui::InputFloat("Amount", &spawnModule->amount);
	ImGui::InputFloat("Spawn Rate", &spawnModule->spawnRate);
	ImGui::InputFloat("Particle Duration", &spawnModule->duration);
}

// initialize modules

void UIEmmiterWriteNode(Emmiter* emmiter) {
	ImGui::InputInt("maxParticles", &emmiter->maxParticles);
	if (ImGui::Button("Reset Pool")) {
		emmiter->RestartParticlePool();
	}
	ImGui::InputFloat("Duration", &emmiter->duration);
	ImGui::InputFloat("Delay", &emmiter->delay);
	ImGui::Checkbox("Loop", &emmiter->isLooping);

	ImGui::SeparatorText("Spawn Module");

	if (emmiter->spawnModule) {
		switch (emmiter->spawnModule->type)	{
		case EmmiterSpawnModule::CONSTANT:
			UIInspectorEmmiterSpawnModule((ConstantSpawnRate*)emmiter->spawnModule.get());
			
			break;
		case EmmiterSpawnModule::SINGLE_BURST:
			UIInspectorEmmiterSpawnModule((SingleBurstSpawn*)emmiter->spawnModule.get());

			break;
		case EmmiterSpawnModule::CONSTANT_BURST:
			UIInspectorEmmiterSpawnModule((ConstantBurstSpawn*)emmiter->spawnModule.get());

			break;
		default:
			break;
		}
		ImGui::Separator();
	}

	ImGui::SeparatorText("Initialize Modules");

	for (auto m = emmiter->initializeModules.begin(); m != emmiter->initializeModules.end(); ++m) {
		switch ((*m)->type) {
		case EmmiterInitializeModule::SET_SPEED:
			ImGui::PushItemWidth(60);

			ImGui::SeparatorText("Set Initial Speed: ");

			ImGui::Checkbox("Single Value", &((SetSpeed*)(*m).get())->speed.usingSingleValue);

			ImGui::PushItemWidth(60);

			if (((SetSpeed*)(*m).get())->speed.usingSingleValue) {
				ImGui::PushID("set_speed_single_PS");
				ImGui::InputDouble("X", &((SetSpeed*)(*m).get())->speed.singleValue.x, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::InputDouble("Y", &((SetSpeed*)(*m).get())->speed.singleValue.y, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::InputDouble("Z", &((SetSpeed*)(*m).get())->speed.singleValue.z, 0, 0, "%.2f");
				ImGui::PopID();
			}
			else {
				ImGui::PushID("set_speed_min_PS");
				ImGui::InputDouble("X", &((SetSpeed*)(*m).get())->speed.rangeValue.lowerLimit.x, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::InputDouble("Y", &((SetSpeed*)(*m).get())->speed.rangeValue.lowerLimit.y, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::InputDouble("Z", &((SetSpeed*)(*m).get())->speed.rangeValue.lowerLimit.z, 0, 0, "%.2f");
				ImGui::PopID();

				ImGui::PushID("set_speed_max_PS");
				ImGui::InputDouble("X", &((SetSpeed*)(*m).get())->speed.rangeValue.upperLimit.x, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::InputDouble("Y", &((SetSpeed*)(*m).get())->speed.rangeValue.upperLimit.y, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::InputDouble("Z", &((SetSpeed*)(*m).get())->speed.rangeValue.upperLimit.z, 0, 0, "%.2f");
				ImGui::PopID();
			}

			ImGui::PopItemWidth();

			break;
		case EmmiterInitializeModule::SET_COLOR:

			ImGui::PushItemWidth(60);

			ImGui::SeparatorText("Set Initial Color: ");

			ImGui::Checkbox("Single Value", &((SetColor*)(*m).get())->color.usingSingleValue);

			ImGui::PushItemWidth(60);

			if (((SetColor*)(*m).get())->color.usingSingleValue) {
				ImGui::InputDouble("R", &((SetColor*)(*m).get())->color.singleValue.r, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("G", &((SetColor*)(*m).get())->color.singleValue.g, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("B", &((SetColor*)(*m).get())->color.singleValue.b, 0, 0, "%.2f");
			}
			else {
				ImGui::InputDouble("R", &((SetColor*)(*m).get())->color.rangeValue.lowerLimit.r, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("G", &((SetColor*)(*m).get())->color.rangeValue.lowerLimit.g, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("B", &((SetColor*)(*m).get())->color.rangeValue.lowerLimit.b, 0, 0, "%.2f");

				ImGui::InputDouble("R", &((SetColor*)(*m).get())->color.rangeValue.upperLimit.r, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("G", &((SetColor*)(*m).get())->color.rangeValue.upperLimit.g, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("B", &((SetColor*)(*m).get())->color.rangeValue.upperLimit.b, 0, 0, "%.2f");
			}

			ImGui::PopItemWidth();

			break;
		default:
			break;
		}
	}

	ImGui::Separator();


	ImGui::SeparatorText("Update Modules");

	for (auto m = emmiter->updateModules.begin(); m != emmiter->updateModules.end(); ++m) {
		switch ((*m)->type) {
		case EmmiterUpdateModule::CHANGE_COLOR:
			break;
		default:
			break;
		}
	}

	ImGui::Separator();


	ImGui::SeparatorText("Render Modules");

	if (emmiter->renderModule) {
		switch (emmiter->spawnModule->type) {
		case EmmiterRenderModule::BILLBOARD:
			break;
		default:
			break;
		}
	}

	ImGui::Separator();

}