#pragma once
#include "../common.hpp"

#define VOID void // suck it
namespace R {
	BOOL bMenuOpen = TRUE;
	class UnityRending {
	public:
		uintptr_t Label = NULL, Skin = NULL, Camera = NULL, customShader = NULL;
		int TabIndex = 1;
		int ScreenSizeX, ScreenSizeY;
		Matrix4x4 viewMatrix;
	public:
		UnityRending() { }
		inline VOID Init() {
			if (!this->Label || !this->Skin)
			{
				this->Skin = Unity::getSkin();
				this->Label = M::read<uintptr_t>(this->Skin + 0x38);

				Unity::setAlignment(this->Label, 0);
				Unity::setFontSize(this->Label, 12);
				Unity::setColor(Unity::Color(1, 1, 1, 1));
				if (DEBUG)
				{
					printf("[address] Gui::label          -> %p\n", this->Label);
					printf("[address] Gui::skin           -> %p\n", this->Skin);
					printf("[address] Unity::setColor     -> %p\n", Unity::setColor);
					printf("[address] Unity::setFontSize  -> %p\n", Unity::setFontSize);
					printf("[address] Unity::setAlignment -> %p\n", Unity::setAlignment);
				}
			}
		}

		inline VOID Text(Vector4 position, Unity::string* Text, Unity::Color clr, float size = 12.f) {
			Init();
			Unity::setColor(clr);

			uintptr_t content = (uintptr_t)Unity::guiContentTemp(Text);
			Unity::setFontSize(this->Label, size);
			Unity::setAlignment(this->Label, 0x0);

			Unity::label(position, content, this->Label);
		}

		inline VOID Text(Vector4 position, wchar_t* Text, Unity::Color clr, float size = 12.f) {
			Init();
			Unity::setColor(clr);
			std::wstring ws(Text);
			std::string test( ws.begin(), ws.end());
			uintptr_t content = (uintptr_t)Unity::guiContentTemp(Unity::string::newString(test.c_str()));
			Unity::setFontSize(this->Label, size);
			Unity::setAlignment(this->Label, 0x0);

			Unity::label(position, content, this->Label);
		}

		inline VOID FilledRectangle(Vector4 position, Unity::Color color) {

			Unity::setColor(color);
			Unity::drawTexture(position, Unity::getTextureWhite());
		}
		
		inline VOID Line(Vector4 position, Unity::Color color, float size = 1.0f) {

			Unity::setColor(color);
			Unity::drawTexture(Vector4{ position.x, position.y, position.h, size }, Unity::getTextureWhite());
		}

		inline VOID Rectangle(Vector2 pos, Vector2 size, Unity::Color color, float borderSize = 2.0f, bool filled = false)
		{
			Unity::setColor(color);
			Unity::drawTexture(Vector4{ pos.x, pos.y, borderSize, size.y }, Unity::getTextureWhite());
			Unity::drawTexture(Vector4{ pos.x + size.x, pos.y, borderSize, size.y }, Unity::getTextureWhite());
			Unity::drawTexture(Vector4{ pos.x, pos.y, size.x, borderSize }, Unity::getTextureWhite());
			Unity::drawTexture(Vector4{ pos.x, pos.y + size.y, size.x, borderSize }, Unity::getTextureWhite());
		}

		inline Matrix4x4 getViewMatrix() {
			auto getCamera = [&]() {
				Camera = Unity::getMainCamera();
			};

			if (!Camera)
				getCamera();

			auto camera_ = M::read<uintptr_t>(Camera + 0x10);
			if (!camera_) {
				getCamera();
				return {};
			}

			auto matrix = M::read<Matrix4x4>(camera_ + 0x2E4);
			if (!matrix.m) {
				getCamera();
				return {};
			}
			return matrix;
		}

		inline Vector3 getCameraPosition() {
			if (!Camera) {
				Camera = Unity::getMainCamera();
			}

			auto camera_ = M::read<uintptr_t>(Camera + 0x10);
			if (!camera_) {
				Camera = Unity::getMainCamera();
				return {};
			}

			auto matrix = M::read<Vector3>(camera_ + 0x42C);
			if (!matrix.x || !matrix.y) {
				Camera = Unity::getMainCamera();
				return {};
			}
			return matrix;
		}
		inline bool WorldToScreen(const Vector3& position, Vector2& screenPos)
		{
			viewMatrix = getViewMatrix();

			if (!viewMatrix.m)
				return false;

			Vector3 trans_vec{ viewMatrix._14, viewMatrix._24, viewMatrix._34 };
			Vector3 right_vec{ viewMatrix._11, viewMatrix._21, viewMatrix._31 };
			Vector3 up_vec{ viewMatrix._12, viewMatrix._22, viewMatrix._32 };

			float w = trans_vec.Dot(position) + viewMatrix._44;
			if (w < 0.098f)
				return false;
			float y = up_vec.Dot(position) + viewMatrix._42;
			float x = right_vec.Dot(position) + viewMatrix._41;
			screenPos = Vector2((ScreenSizeX / 2) * (1.f + x / w), (ScreenSizeY / 2) * (1.f - y / w));
			return true;
		}

		inline VOID RunESP() {
			static uintptr_t clientEntities = NULL;

			auto getClientEntities = [&]() {
				clientEntities = il2cpp::value(_("BaseNetworkable"), _("clientEntities"), false);
			};
			if(!clientEntities)
				getClientEntities();
			
			if (uintptr_t entityRealm = M::read<uintptr_t>(clientEntities + 0x10))
			{
				if (!entityRealm)
					getClientEntities();
				if (uintptr_t bufferList = M::read<uintptr_t>(entityRealm + 0x28))
				{
					if (!bufferList)
						getClientEntities();
					if (uintptr_t objectList = M::read<uintptr_t>(bufferList + 0x18))
					{
						if (!objectList)
							getClientEntities();
						if (uint32_t objectListSize = M::read<uint32_t>(bufferList + 0x10))
						{
							if (!objectListSize)
								getClientEntities();

							for (auto i = 0; i < objectListSize; i++) {
								auto curObject = M::read<uintptr_t>(objectList + (0x20 + (i * 0x8)));
								auto baseObject = *reinterpret_cast<uintptr_t*>(curObject + 0x10);
								auto entity = *reinterpret_cast<uintptr_t*>(baseObject + 0x28);
								auto entClassAddress = *reinterpret_cast<uintptr_t*>(entity);
								auto entClassName = (char*)*reinterpret_cast<uintptr_t*>(entClassAddress + 0x10);

								if (M::MFunc::m_strstr(entClassName, _("BasePlayer")))//rip performance
								{
									BasePlayer* player = (BasePlayer*)curObject;
									if (!player->GetHealth() >= 0.1)
										continue;

									if (player->GetPlayerModel()->IsLocalPlayer())
									{
										localPlayer = player;
										if(!Config::bUseLocal)
											continue;
									}

									if(player->GetModelState()->HasFlag(Unity::ModelStateFLAG::Sleeping) && !Config::bSleeperESP)
										continue;

									int Distance = player->GetTransform()->GetPosition().Distance(localPlayer->GetTransform()->GetPosition());
									if (Distance > 150)
										continue;
									Aimbot::DoAimbot(player);

									if (Config::bBoxESP || Config::bHealthESP || Config::bNameESP || Config::bWeaponESP) {
										Vector2 tempFeetL, tempFeetR, tempHead;
										if (WorldToScreen(player->GetBonePositionID(Unity::BoneList::head)->GetPosition() + Vector3(0, 0.2, 0), tempHead))
										{
											if (this->WorldToScreen(player->GetBonePositionID(Unity::BoneList::l_foot)->GetPosition(), tempFeetL) && this->WorldToScreen(player->GetBonePositionID(Unity::BoneList::r_foot)->GetPosition(), tempFeetR))
											{
												int Distance = (int)localPlayer->GetTransform()->GetPosition().Distance(player->GetTransform()->GetPosition());
												Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
												float Entity_h = tempHead.y - tempFeet.y;
												float w = Entity_h / 4;
												float Entity_x = tempFeet.x - w;
												float Entity_y = tempFeet.y;
												float Entity_w = Entity_h / 2;

												if (Config::bBoxESP)
												{
													if (player->IsTeamate(localPlayer))
														this->Rectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, Unity::Color(255, 255, 255, 255));
													else
													{
														if (localPlayer->IsVisible(getCameraPosition(), player->GetBonePositionID(Unity::BoneList::head)->GetPosition()))
															this->Rectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, Unity::Color(255, 0, 0, 255));
														else
															this->Rectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, Unity::Color(0, 0, 255, 255));
													}
												}

												if (Config::bWeaponESP) {
													if (!player->GetModelState()->HasFlag(Unity::ModelStateFLAG::Sleeping))
													{
														const auto currentItem = player->GetActiveItem()->GetItemName();
														if (currentItem)
															this->Text(Vector4{ tempFeet.x - 20, tempFeet.y + 10.0f, 150, 20 }, currentItem, Unity::Color(255, 255, 255, 255), false);
													}
												}


												if (Config::bHealthESP)
													this->Rectangle(Vector2{ Entity_x + 4, Entity_y }, Vector2{ 1.2, ((tempHead.y - tempFeet.y) / 10) * (player->GetHealth() / 10.f) }, Unity::Color(0, 255, 0, 255));

												if (Config::bNameESP) {
													char buffer[50];
													sprintf_s(buffer, _(" - %dm"), Distance);
													char buffer2[128];
													sprintf_s(buffer2, _("%ls"), player->GetName());
													std::string NameStr = buffer2;
													NameStr += buffer;
													this->Text(Vector4{ tempFeet.x - 25, tempHead.y - 20.0f, 150, 20 }, Unity::string::newString(NameStr.c_str()), player->IsTeamate(localPlayer) ? Unity::Color(0, 255, 0, 255) : Unity::Color(255, 0, 0, 255), 14.0f);
												}
											}
										}
									}

									if (Config::bChamsESP)
									{
										auto MultiMesh = player->GetPlayerModel()->MultiMesh();
										if (MultiMesh)
										{
											auto renders = Unity::getRenderers(MultiMesh);
											for (int i = 0; i < renders->getSize(); i++) {
												auto render = renders->getValue(i);
												if (render)
												{
													auto material = Unity::getMaterial(render);
													if (material) {
														static uintptr_t shader;
														if(!this->customShader)
															this->customShader = Unity::loadAssetFromFileInternal(Unity::string::newString(_("C:\\Shader.assets")), 0, 0);

														if (shader != Unity::getShader(material)) {
															if (!shader)
																shader = Unity::loadAssetInternal(this->customShader, Unity::string::newString(_("chams.shader")), il2cpp::typeObject(_("UnityEngine"), _("Shader")));
															/*shader = Unity::shaderFind(_(L"Hidden/Internal-Colored"));// shitty Chams
															Unity::setShader(material, shader);
															Unity::materialSetInt(material, _(L"_ZWrite"), 0);
															Unity::materialSetInt(material, _(L"_ZTest"), 8);
															Unity::materialSetFloat(material, _(L"_ZBias"), 0);
															Unity::materialSetInt(material, _(L"_Cull"), 0);
															Unity::materialSetColor(material, _(L"_Color"), Unity::Color(0, 1, 0.8f, 1));*/

															Unity::setShader(material, shader);
															Unity::materialSetColor(material, Unity::string::newString(_("_ColorBehind")), Unity::Color(0, 1, 0.8f, 1));
															Unity::materialSetColor(material, Unity::string::newString(_("_ColorVisible")), Unity::Color(1, 0, 0.4f, 1));
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	};
}