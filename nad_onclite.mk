#
# Copyright (C) 2019-2020 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_p.mk)

# Inherit from onclite device
$(call inherit-product, device/xiaomi/onclite/device.mk)

# Inherit some common Nusantara stuff.
$(call inherit-product, vendor/nusantata/config/common_full_phone.mk)

# Device identifier. This must come after all inclusions.
PRODUCT_NAME := nusantara_onclite
PRODUCT_DEVICE := onclite
PRODUCT_BRAND := Xiaomi
PRODUCT_MODEL := Redmi 7
PRODUCT_MANUFACTURER := Xiaomi

BUILD_FINGERPRINT := "xiaomi/onc/onc:9/PKQ1.181021.001/V11.0.3.0.PFLMIXM:user/release-keys"

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="onc-user 9 PKQ1.181021.001 V11.0.3.0.PFLMIXM release-keys"

PRODUCT_GMS_CLIENTID_BASE := android-xiaomi

# Nusantara
NAD_BUILD_TYPE := OFFICIAL

# Face Unlock
TARGET_FACE_UNLOCK_SUPPORTED := true

# Pixel Charging
USE_PIXEL_CHARGING := true

# GApps
ifeq ($(USE_GAPPS),true)
USE_AOSP_CLOCK := true
PRODUCT_PACKAGES += \
    GAppsExclude
endif

# Blur
TARGET_USES_BLUR := true
