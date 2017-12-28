#ifndef PROGRAMMODEEDITOR_H
#define PROGRAMMODEEDITOR_H

#include <SFML/Graphics/CircleShape.hpp>

#include "src/graphics/gui/gui_tools/DevelopmentOverlay.h"
#include "src/graphics/gui/SFMLWindowListener.h"
#include "src/graphics/gui/PMIDGEditorWindow.h"
#include "src/graphics/gui/brush/Brush.h"
#include "src/graphics/gui/brush/SelectMoveableBrushState.h"
#include "src/game/FPSRunner.h"
#include "src/game/GameState.h"
#include "src/game/mode/ProgramMode.h"
#include "src/game/control/GameLoader.h"
#include "src/utils/window/WindowUtils.h"
#include "src/utils/sfml/SFMLUtils.h"
#include "src/system/SystemController.h"
#include "src/game/PMIDGGameRunner.h"
#include "src/utils/lua/InstanceFileBuilder.h"
#include "src/controllers/ControllersSystem.h"
#include "src/utils/math/Geometry.h"
#include "src/ui/BaseUI.h"
#include "src/graphics/gui/gui_tools/UIVisualizer.h"

#define MAX_SCROLL_TICKS 50
#define EDITOR_MODE_FPS 30
#define GAME_RUNNER_FPS 30

class ProgramModeEditor : public ProgramMode, public SFMLWindowListener, public DevelopmentOverlayListener, 
  public FPSRunner, public FPSRunnable, public EventSubscriber, public PMIDGGameRunnerListener,
  public std::enable_shared_from_this<ProgramModeEditor>
{
  public:
    enum WindowTransformState
    {
        DORMANT,
        PANNING
    };

    enum EditMode
    {
        GAME_STATE_MODE,
        UI_MODE
    };

    ProgramModeEditor();

    void Init();

    void Load();

    void Update(std::chrono::time_point<std::chrono::high_resolution_clock> &current_time) override;

    void Tick(float seconds_elapsed);

    void Unload();

    void Exit() override;

    //######################### DEV TOOL CALLBACKS ########################

    void OnCreateBlankInstance(std::string &instance_name, int rows, int columns) override;

    void OnCreateBlankStage();

    void OnLaunchInstance() override;

    void OnLaunchStage() override;

    void OnStopGameRunner();

    void OnGameRunnerShutdown();

    void OnModeChangeGame();

    void OnModeChangeUI();

    void OnNewUI();

    void OnAttachUI(const std::string& file_name);

    //###################### ENGINE EVENTS ################################
    void OnEvent(Event &e);

    std::list<Subscription> GetSubscriptions();

    // ######################## LOADING / SAVING #################################
    void OnLoadStageFile(const std::string &file_name) override;

    void OnSaveStageFile(const std::string &file_name) override;

    void SaveInstanceTilemap(ptr<Instance> instance);

    void GenerateInstanceTemplate(ptr<Instance> instance);

    bool OnWindowEvent(sf::Event &e);

    //################ SCREEN CONTROLS #################

    void Render(float seconds_elapsed) override;

    void PanView();

    bool ClickOnActiveTileMap(int x, int y);

    ptr<Entity> ClickOnEntity(int x, int y);

    bool CanEdit();

  private:
    FPSRunner _game_runner;
    FPSRunner _editor_runner;
    ptr<PMIDGGameRunner> _external_game_runner = nullptr;
    ControllersSystem _controllers_system;
    MouseHistory _mouse_history;
    DevelopmentOverlay _dev_tools;
    int _abs_scroll_ticks = 50;
    Brush _brush;
    ptr<GameState> _game_state;
    WindowTransformState _window_transform_state = DORMANT;
    PMIDGEditorWindow _window;
    std::string file_path;
    std::string tile_maps_path;
    std::string instances_path;
    std::list<ptr<Container>> _root_containers;
    EditMode _edit_mode = GAME_STATE_MODE;
    ptr<UI> ui = nullptr;

    ptr<UIElement> ClickOnUIElement(int x, int y);
};

#endif