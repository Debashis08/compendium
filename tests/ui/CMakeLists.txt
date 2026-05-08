find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickTest)

# ── Single executable ────────────────────────────────────────────────────────
# Qt Creator discovers tst_*.qml files and associates them with this one
# executable via QUICK_TEST_SOURCE_DIR. DO NOT use qt_add_quick_test here
# because that macro generates its own main(), which conflicts with the
# QUICK_TEST_MAIN_WITH_SETUP macro already defined in TestSetup.cpp.
qt_add_executable(unit_tests_ui
    TestSetup.cpp
)

target_link_libraries(unit_tests_ui PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickTest
    CoreLib
    BackendLib
    BackendLibplugin
    UiLibplugin
)

target_compile_definitions(unit_tests_ui PRIVATE
    "QUICK_TEST_SOURCE_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\""
    "APP_BUILD_DIR=\"${CMAKE_BINARY_DIR}\""
)

# ── Per-file CTest entries ────────────────────────────────────────────────────
# Each tst_*.qml becomes its own named CTest entry by passing -input.
# This is what gives you named rows in CI output and JUnit XML.
# Qt Creator is unaffected — it still uses the single executable above.
file(GLOB QML_TEST_FILES CONFIGURE_DEPENDS "tst_*.qml")

if(NOT QML_TEST_FILES)
    message(WARNING "ui tests: no tst_*.qml files found in ${CMAKE_CURRENT_SOURCE_DIR}")
endif()

foreach(_qml_file IN LISTS QML_TEST_FILES)
    get_filename_component(_name "${_qml_file}" NAME_WE)

    add_test(
        NAME    "UI::${_name}"
        COMMAND unit_tests_ui -input "${_qml_file}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    set_tests_properties("UI::${_name}" PROPERTIES
        ENVIRONMENT "QT_QPA_PLATFORM=minimal"
        TIMEOUT     60
    )
endforeach()

# ── No bare add_test(unit_tests_ui) ──────────────────────────────────────────
# The old single add_test() that registered the whole binary is intentionally
# gone. The per-file loop above replaces it entirely.