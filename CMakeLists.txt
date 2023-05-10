
cmake_minimum_required(VERSION 3.5.1)

project(qgo-clipboard-client LANGUAGES CXX VERSION 0.0.1)

include(cmake/SparkEnvConfig.cmake)
include(cmake/SparkMacrosConfig.cmake)
include(cmake/SparkFindLibraries.cmake)
include(cmake/SparkFindQt5Config.cmake)
include(cmake/SparkFindQt6Config.cmake)

# 资源文件路径
set(QRC_SOURCES "assets/sources.qrc")

spark_add_library_path(BackendApi backend)
target_link_qt5(BackendApi)

spark_add_executable_path(${PROJECT_NAME} src
    ${QRC_SOURCES}
)
target_link_BackendApi(${PROJECT_NAME})

include(cmake/SparkBuildGraphviz.cmake)


include(cmake/SparkDesktopMacros.cmake)
# 内容默认应用名称: Name= 应与项目名称相同
spark_desktop_macros(
    # 应用名称: Name=
    "${PROJECT_NAME}" 
    # 应用名称: Name[zh_CN]=
    "云剪贴板(基于Qt的客户端)" 
    # 应用说明: Comment=
    "用于简单的使用共享剪贴板"
    # 应用类型: Type=
    "Application"
    # 执行程序: Exec=
    "qgo-clipboard-client"
    # 图标路径: Icon=
    "/usr/share/${PROJECT_NAME}/icon.png"
    # 应用分类: Category=
    "Development"

)
install(FILES ${SPARK_DESKTOP}
    DESTINATION "/usr/share/applications")
install(FILES assets/icon.png 
        DESTINATION "/usr/share/${PROJECT_NAME}")
install(TARGETS ${PROJECT_NAME} 
        DESTINATION "/usr/bin/")

# 注释行(使用方式)
find_package(DebPackage PATHS ${CMAKE_SOURCE_DIR})
add_package_descript(cmake/package-deb.descript)


# 1. 在顶层构建中导入 Appimage 的构建
include(cmake/SparkAppimageConfig.cmake)  # 导入来自 Spark 构建的 Appimage 构建
add_appimage_icon(assets/icon.png)       # 添加到 Appimage 中的默认的图标
add_appimage_desktop()                    # 添加到 Appimage 中的默认desktop(使用来自 Spark 构建的 Desktop 构建中配置的信息(必须要求 spark-desktop))
add_appimage_target(${PROJECT_NAME})      # 添加到 Appimage 中的默认目标，应用对 Appimage 的构建
