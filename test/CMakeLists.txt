enable_testing()

set(ControlSources
    ${CMAKE_SOURCE_DIR}/src/control/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/control/BarrelControl.cpp
    ${CMAKE_SOURCE_DIR}/src/control/EnemyControl.cpp
    ${CMAKE_SOURCE_DIR}/src/control/LadderControl.cpp
    )

set(ModelSources
    ${CMAKE_SOURCE_DIR}/src/model/Girder.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Barrel.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Ladder.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Enemy.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Ghost.cpp
    )

set(ViewSources
    ${CMAKE_SOURCE_DIR}/src/view/Layer.cpp
    )

set(TestSources
    ${CMAKE_CURRENT_SOURCE_DIR}/GameTest.cpp
    )

add_executable(Test
    ${ModelSources}
    ${ControlSources}
    ${ViewSources}
    ${TestSources}
    )
