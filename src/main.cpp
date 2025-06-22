#include <Geode/Geode.hpp> #include <Geode/modify/PlayLayer.hpp> #include <Geode/modify/EditorUI.hpp> #include <Geode/ui/EditorButton.hpp> #include <Geode/utils/cocos.hpp> #include <fstream> #include <filesystem>

using namespace geode::prelude;

class $modify(LmaoBotPlayLayer, PlayLayer) { CCPoint lmaoTriggerPos; bool foundLmao = false; bool macroGenerated = false;

std::vector<std::pair<float, bool>> inputTimeline;
float currentTime = 0;

bool init(GJGameLevel* level, bool useReplay, bool fromMyLevels) {
    if (!PlayLayer::init(level, useReplay, fromMyLevels)) return false;

        for (auto obj : level->m_objects) {
                if (obj->m_objectID == 69420) {
                            lmaoTriggerPos = obj->getPosition();
                                        foundLmao = true;
                                                    log::info("✅ LMAO Trigger found at: {}, {}", lmaoTriggerPos.x, lmaoTriggerPos.y);
                                                                break;
                                                                        }
                                                                            }

                                                                                return true;
                                                                                }

                                                                                void update(float dt) {
                                                                                    PlayLayer::update(dt);
                                                                                        currentTime += dt;

                                                                                            if (foundLmao && !macroGenerated) {
                                                                                                    generateMacro();
                                                                                                            macroGenerated = true;
                                                                                                                }
                                                                                                                }

                                                                                                                void generateMacro() {
                                                                                                                    float x = m_player1->getPositionX();
                                                                                                                        float step = 1.f;
                                                                                                                            float t = 0.f;
                                                                                                                                float gravity = -1000.f;
                                                                                                                                    float jumpVelocity = 450.f;
                                                                                                                                        float y = m_player1->getPositionY();

                                                                                                                                            bool clicked = false;

                                                                                                                                                while (x < lmaoTriggerPos.x) {
                                                                                                                                                        if (!clicked && static_cast<int>(x * 10) % 150 == 0) {
                                                                                                                                                                    inputTimeline.emplace_back(t, true);
                                                                                                                                                                                inputTimeline.emplace_back(t + 0.1f, false);
                                                                                                                                                                                            clicked = true;
                                                                                                                                                                                                    }

                                                                                                                                                                                                            if (static_cast<int>(x * 10) % 240 == 0) clicked = false;

                                                                                                                                                                                                                    x += step * 60.f * (1.f / 60.f);
                                                                                                                                                                                                                            y += jumpVelocity * (1.f / 60.f) + 0.5f * gravity * (1.f / 60.f) * (1.f / 60.f);
                                                                                                                                                                                                                                    jumpVelocity += gravity * (1.f / 60.f);
                                                                                                                                                                                                                                            t += 1.f / 60.f;
                                                                                                                                                                                                                                                }

                                                                                                                                                                                                                                                    std::string levelName = m_level->m_levelName;
                                                                                                                                                                                                                                                        std::replace(levelName.begin(), levelName.end(), ' ', '_');
                                                                                                                                                                                                                                                            std::replace_if(levelName.begin(), levelName.end(), [](char c) {
                                                                                                                                                                                                                                                                    return !(isalnum(c) || c == '_' || c == '-');
                                                                                                                                                                                                                                                                        }, '_');

                                                                                                                                                                                                                                                                            auto path = Mod::get()->getConfigDir() / "lmao_macros" / (levelName + ".gdr");
                                                                                                                                                                                                                                                                                std::filesystem::create_directories(path.parent_path());

                                                                                                                                                                                                                                                                                    std::ofstream macroFile(path, std::ios::binary);
                                                                                                                                                                                                                                                                                        for (auto& [time, action] : inputTimeline) {
                                                                                                                                                                                                                                                                                                macroFile.write(reinterpret_cast<const char*>(&time), sizeof(float));
                                                                                                                                                                                                                                                                                                        char state = action ? 1 : 0;
                                                                                                                                                                                                                                                                                                                macroFile.write(&state, sizeof(char));
                                                                                                                                                                                                                                                                                                                    }

                                                                                                                                                                                                                                                                                                                        log::info("✅ Macro saved to {} with {} inputs.", path.string(), inputTimeline.size());
                                                                                                                                                                                                                                                                                                                        }

                                                                                                                                                                                                                                                                                                                        };

                                                                                                                                                                                                                                                                                                                        class $modify(LmaoEditorUI, EditorUI) { void setupCreateMenu() { EditorUI::setupCreateMenu();

                                                                                                                                                                                                                                                                                                                        auto spr = CCSprite::createWithSpriteFrameName("particle_00.png");
                                                                                                                                                                                                                                                                                                                            auto btn = EditorButton::create("LMAO Trigger", spr, 0.7f);
                                                                                                                                                                                                                                                                                                                                btn->setTag(69420);
                                                                                                                                                                                                                                                                                                                                    m_createButtonBar->m_buttonArray->addObject(btn);

                                                                                                                                                                                                                                                                                                                                        log::info("✅ LMAO Trigger registered in editor.");
                                                                                                                                                                                                                                                                                                                                        }

                                                                                                                                                                                                                                                                                                                                        };

                                                                                                                                                                                                                                                                                                                                        