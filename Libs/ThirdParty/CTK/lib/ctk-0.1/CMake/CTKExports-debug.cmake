#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "CTKCore" for configuration "Debug"
set_property(TARGET CTKCore APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(CTKCore PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKCore.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "Qt5::Core;dbghelp"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKCore.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS CTKCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_CTKCore "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKCore.lib" "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKCore.dll" )

# Import target "CTKDummyPlugin" for configuration "Debug"
set_property(TARGET CTKDummyPlugin APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(CTKDummyPlugin PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKDummyPlugin.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "Qt5::Core;CTKCore"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKDummyPlugin.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS CTKDummyPlugin )
list(APPEND _IMPORT_CHECK_FILES_FOR_CTKDummyPlugin "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKDummyPlugin.lib" "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKDummyPlugin.dll" )

# Import target "CTKPluginFramework" for configuration "Debug"
set_property(TARGET CTKPluginFramework APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(CTKPluginFramework PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKPluginFramework.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "CTKCore;Qt5::Sql;Qt5::Concurrent"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKPluginFramework.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS CTKPluginFramework )
list(APPEND _IMPORT_CHECK_FILES_FOR_CTKPluginFramework "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKPluginFramework.lib" "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKPluginFramework.dll" )

# Import target "CTKWidgets" for configuration "Debug"
set_property(TARGET CTKWidgets APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(CTKWidgets PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKWidgets.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "CTKCore;Qt5::Widgets;Qt5::Xml;Qt5::OpenGL"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKWidgets.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS CTKWidgets )
list(APPEND _IMPORT_CHECK_FILES_FOR_CTKWidgets "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKWidgets.lib" "${_IMPORT_PREFIX}/lib/ctk-0.1/CTKWidgets.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
