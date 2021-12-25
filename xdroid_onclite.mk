#
# Copyright (C) 2019-2020 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_p.mk)

# Inherit from device side
$(call inherit-product, device/xiaomi/onclite/device.mk)

# Inherit some common ConquerOS stuff.
$(call inherit-product, vendor/xdroid/config/common.mk)

# Device identifier. This must come after all inclusions.
PRODUCT_NAME := xdroid_onclite
PRODUCT_DEVICE := onclite
PRODUCT_BRAND := Xiaomi
PRODUCT_MODEL := Redmi 7
PRODUCT_MANUFACTURER := Xiaomi
XDROID_BOOT_76 := true

# Face Unlock
TARGET_FACE_UNLOCK_SUPPORTED := true

# GApps
TARGET_USE_GAPPS := false
#ifeq ($(TARGET_USE_GAPPS),true)
#PRODUCT_PACKAGES += \
#    GAppsExclude
#endif

