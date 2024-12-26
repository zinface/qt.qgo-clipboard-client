spark_add_executable_paths(test
    toutf8
)

spark_framework_include_with_git(test-toutf8
    https://gitee.com/spark-framework-libs/spark-framework-features
    FEATURES version screenutil qd
)