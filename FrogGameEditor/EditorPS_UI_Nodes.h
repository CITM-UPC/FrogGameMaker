#pragma once

#include "../FrogGameEngine/GameObject.h"
#include "imgui.h"
#include "../FrogGameEngine/EmmiterModule.h"
#include "../FrogGameEngine/SpawnModules.h"
#include "../FrogGameEngine/InitializeModules.h"
// #include "../FrogGameEngine/UpdateModules.h"
#include "../FrogGameEngine/BillboardingEM.h"



void UIEmmiterWriteNode(Emmiter* emmiter) {
	ImGui::InputInt("maxParticles", &emmiter->maxParticles);
	if (ImGui::Button("Reset Pool")) {
		emmiter->RestartParticlePool();
	}
	ImGui::InputFloat("Duration", &emmiter->duration);
	ImGui::InputFloat("Delay", &emmiter->delay);
	ImGui::Checkbox("Loop", &emmiter->isLooping);

	if (emmiter->spawnModule) {
		ImGui::SeparatorText("Spawn Module");

		switch (emmiter->spawnModule->type)	{
		case EmmiterSpawnModule::CONSTANT:
			ImGui::SeparatorText("Constant Spawn Rate");
			ImGui::InputFloat("Spawn Rate", &((ConstantSpawnRate*)emmiter->spawnModule.get())->spawnRate);

			break;
		case EmmiterSpawnModule::SINGLE_BURST:
			ImGui::SeparatorText("Single Burst");
			ImGui::InputFloat("Amount", &((SingleBurstSpawn*)emmiter->spawnModule.get())->amount);

			break;
		case EmmiterSpawnModule::CONSTANT_BURST:
			ImGui::SeparatorText("Single Burst");
			ImGui::InputFloat("Spawn Rate", &((ConstantBurstSpawn*)emmiter->spawnModule.get())->spawnRate);
			ImGui::InputFloat("Amount", &((ConstantBurstSpawn*)emmiter->spawnModule.get())->amount);

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
				ImGui::InputDouble("X", &((SetSpeed*)(*m).get())->speed.singleValue.x, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("Y", &((SetSpeed*)(*m).get())->speed.singleValue.y, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("Z", &((SetSpeed*)(*m).get())->speed.singleValue.z, 0, 0, "%.2f");
			}
			else {
				ImGui::InputDouble("X", &((SetSpeed*)(*m).get())->speed.rangeValue.lowerLimit.x, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("Y", &((SetSpeed*)(*m).get())->speed.rangeValue.lowerLimit.y, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("Z", &((SetSpeed*)(*m).get())->speed.rangeValue.lowerLimit.z, 0, 0, "%.2f");

				ImGui::InputDouble("X", &((SetSpeed*)(*m).get())->speed.rangeValue.upperLimit.x, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("Y", &((SetSpeed*)(*m).get())->speed.rangeValue.upperLimit.y, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("Z", &((SetSpeed*)(*m).get())->speed.rangeValue.upperLimit.z, 0, 0, "%.2f");
			}

			ImGui::PopItemWidth();

			break;
		case EmmiterInitializeModule::SET_COLOR:

			ImGui::PushItemWidth(60);

			ImGui::SeparatorText("Set Initial Speed: ");

			ImGui::Checkbox("Single Value", &((SetColor*)(*m).get())->color.usingSingleValue);

			ImGui::PushItemWidth(60);

			if (((SetColor*)(*m).get())->color.usingSingleValue) {
				ImGui::InputDouble("X", &((SetColor*)(*m).get())->color.singleValue.x, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("Y", &((SetColor*)(*m).get())->color.singleValue.y, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("Z", &((SetColor*)(*m).get())->color.singleValue.z, 0, 0, "%.2f");
			}
			else {
				ImGui::InputDouble("X", &((SetColor*)(*m).get())->color.rangeValue.lowerLimit.x, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("Y", &((SetColor*)(*m).get())->color.rangeValue.lowerLimit.y, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("Z", &((SetColor*)(*m).get())->color.rangeValue.lowerLimit.z, 0, 0, "%.2f");

				ImGui::InputDouble("X", &((SetColor*)(*m).get())->color.rangeValue.upperLimit.x, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("Y", &((SetColor*)(*m).get())->color.rangeValue.upperLimit.y, 0, 0, "%.2f");
				ImGui::SameLine();
				ImGui::PopID();
				ImGui::InputDouble("Z", &((SetColor*)(*m).get())->color.rangeValue.upperLimit.z, 0, 0, "%.2f");
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