# DO NOT EDIT: generated by java_import_external()

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

java_import(
    name = "compile",
    jars = ["auto-value-1.4-rc2.jar"],
    neverlink = True,
    deps = ["@com_google_auto_common", "@com_google_code_findbugs_jsr305", "@com_google_guava"],
)

java_import(
    name = "processor",
    jars = ["auto-value-1.4-rc2.jar"],
    deps = ["@com_google_auto_common", "@com_google_code_findbugs_jsr305", "@com_google_guava"],
)

java_plugin(
    name = "AutoAnnotationProcessor",
    output_licenses = ["unencumbered"],
    processor_class = "com.google.auto.value.processor.AutoAnnotationProcessor",
    tags = ["annotation=com.google.auto.value.AutoAnnotation;genclass=${package}.AutoAnnotation_${outerclasses}${classname}_${methodname}"],
    deps = [":processor"],
)

java_plugin(
    name = "AutoValueProcessor",
    output_licenses = ["unencumbered"],
    processor_class = "com.google.auto.value.processor.AutoValueProcessor",
    tags = ["annotation=com.google.auto.value.AutoValue;genclass=${package}.AutoValue_${outerclasses}${classname}"],
    deps = [":processor"],
)

java_library(
    name = "com_google_auto_value",
    exported_plugins = [
        ":AutoAnnotationProcessor",
        ":AutoValueProcessor",
    ],
    exports = [
        ":compile",
        "@com_google_code_findbugs_jsr305",
    ],
)
