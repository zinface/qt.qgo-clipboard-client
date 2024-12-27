
cmake_minimum_required(VERSION 3.5.1)

project(qgo-clipboard-client LANGUAGES CXX VERSION 0.0.1)

include(cmake/SparkWithGit.cmake)
spark_initialize_modules()

if(NOT DEFINED REMOTE_HOST)
    set(REMOTE_HOST "http://127.0.0.1:9090")
endif(NOT DEFINED REMOTE_HOST)

configure_file(src/global/config.h.in config.h @ONLY)

# 资源文件路径
set(QRC_SOURCES "assets/sources.qrc")

spark_aux_source_directories(sources
    src/backend
    src/utils
    src/global
    src/view
)

spark_add_executable_path(${PROJECT_NAME} src
    ${QRC_SOURCES} ${sources}
)
target_link_qt5(${PROJECT_NAME})

spark_framework_include_with_git(${PROJECT_NAME}
    https://gitee.com/spark-framework-libs/spark-framework-features
    FEATURES version screenutil qd)

spark_framework_include_with_git(${PROJECT_NAME}
    https://gitee.com/spark-framework-libs/network-access-libs
    FEATURES httpmanager)

spark_framework_include_with_git(${PROJECT_NAME}
    https://gitee.com/zinface/qt.clipboard-history-analyzer
    FEATURES historyitem)

add_subdirectory(tests)

spark_include(cmake/SparkBuildGraphviz.cmake)


spark_include(cmake/SparkDesktopMacros.cmake)
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
install(FILES ${SPARK_DESKTOP_FILE}
    DESTINATION "/usr/share/applications")
install(FILES assets/icon.png 
        DESTINATION "/usr/share/${PROJECT_NAME}")
install(TARGETS ${PROJECT_NAME} 
        DESTINATION "/usr/bin/")

# 注释行(使用方式)
spark_include(cmake/SparkDebPackageConfig.cmake)
add_package_descript(cmake/spark-deb-package.descript)


# 1. 在顶层构建中导入 Appimage 的构建
spark_include(cmake/SparkAppimageConfig.cmake)  # 导入来自 Spark 构建的 Appimage 构建
add_appimage_icon(assets/icon.png)       # 添加到 Appimage 中的默认的图标
add_appimage_desktop()                    # 添加到 Appimage 中的默认desktop(使用来自 Spark 构建的 Desktop 构建中配置的信息(必须要求 spark-desktop))
add_appimage_target(${PROJECT_NAME})      # 添加到 Appimage 中的默认目标，应用对 Appimage 的构建

# 在 Windows 中开启 UNICODE 以支持 TCHAR 功能
if(WIN32)
    # Windows 下为目标追加图标资源与目标属性
    add_compile_definitions(_UNICODE= UNICODE=)
    target_sources(${PROJECT_NAME} PRIVATE icon.rc)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
    return()
    
    include(cmake/windows-deployqt.cmake)
endif(WIN32)

