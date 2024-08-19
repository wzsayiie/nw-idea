plugins {
    alias(libs.plugins.android.application)
}

android {
    namespace = "com.corp.app"
    compileSdk = 34

    defaultConfig {
        applicationId = "com.corp.app"
        versionName = "1.0"
        versionCode = 1

        minSdk = 26
        targetSdk = 34

        ndk {
            abiFilters += listOf("x86_64", "arm64-v8a")
        }
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }

    sourceSets {
        getByName("main") {
            manifest.srcFile("../../../host/android/AndroidManifest.xml")
            java    .srcDir ("../../../host/android/java")
            res     .srcDir ("../../../host/android/res")
        }
    }

    externalNativeBuild {
        cmake {
            path = file("make/CMakeLists.txt")
        }
    }
}

dependencies {
    implementation(libs.appcompat)
    implementation(libs.material)
}
