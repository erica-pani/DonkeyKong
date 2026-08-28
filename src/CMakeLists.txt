# Model
set(ModelSources
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Girder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Barrel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Ladder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Enemy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Ghost.cpp
    )

# Controller
set(ControlSources
    ${CMAKE_CURRENT_SOURCE_DIR}/control/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/BarrelControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/EnemyControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/LadderControl.cpp
    )

# View
set(ViewSources
    ${CMAKE_CURRENT_SOURCE_DIR}/view/Layer.cpp
    )

# add src code to target
add_executable(DonkeyKong
        ${ModelSources}
        ${ControlSources}
        ${ViewSources}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )