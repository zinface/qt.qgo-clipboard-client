# install
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    message("Linux version " ${CMAKE_HOST_SYSTEM_VERSION})
    # prefix /usr
    set(CMAKE_INSTALL_PREFIX "/usr")
    # icon 可伸缩图标
    # install(FILES cmake/linux-install/${PROJECT_NAME}.svg 
        # DESTINATION "share/icons/hicolor/scalable/apps")
    # icon 图标集
    install(FILES cmake/linux-install/${PROJECT_NAME}.png 
        DESTINATION "share/icons/hicolor/350x350/apps")
    # destkop 文件
    install(FILES cmake/linux-install/${PROJECT_NAME}.desktop 
        DESTINATION "share/applications")
    # program 程序本身
    install(TARGETS ${PROJECT_NAME} 
        DESTINATION "bin/")

    # import DebPackage
    find_package(DebPackage PATHS ${CMAKE_SOURCE_DIR})
    add_package_descript(cmake/package-deb.descript)
endif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")


# NOTE:
# 此文件部分可作为使用 install 指令的参考
# 也可直接参与打包构建(依赖 cmake-package-deb 模板)

# USE:
# 如果需要使用此文件，请准备好与'项目名称'相同的: 
    # desktop/svg 后缀文件
    # 并修改 desktop 的文件模板内容以适用于你的部署
# 请复制以下内容粘贴到顶级构建脚本

# include(cmake/linux-install/linux-install.cmake)