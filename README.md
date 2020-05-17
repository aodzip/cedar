# Allwinner CedarX Driver for Mainline Linux 5.4
### VideoEngine driver based on Allwinner H6 Homlet BSP
### Ion driver based on Google Android Ion

## Install

### Put all file in "drivers/staging/media/sunxi/cedar"

### Add source to "drivers/staging/media/sunxi/Kconfig"
```
source "drivers/staging/media/sunxi/cedar/Kconfig"
```
Demo
```
# SPDX-License-Identifier: GPL-2.0
config VIDEO_SUNXI
    bool "Allwinner sunXi family Video Devices"
    depends on ARCH_SUNXI || COMPILE_TEST
    help
      If you have an Allwinner SoC based on the sunXi family, say Y.

      Note that this option doesn't include new drivers in the
      kernel: saying N will just cause Kconfig to skip all the
      questions about Allwinner media devices.

if VIDEO_SUNXI

source "drivers/staging/media/sunxi/cedrus/Kconfig"
source "drivers/staging/media/sunxi/cedar/Kconfig"

endif
```

### Add obj to "drivers/staging/media/sunxi/Makefile"
```
obj-y += cedar/
```
Demo
```
# SPDX-License-Identifier: GPL-2.0
obj-$(CONFIG_VIDEO_SUNXI_CEDRUS)        += cedrus/
obj-y += cedar/
```

## DeviceTree
### Demo for Allwinner V3 / V3s / S3L / S3
```
syscon: syscon@1c00000 {
    compatible = "allwinner,sun8i-v3s-system-controller", "allwinner,sun8i-h3-system-control", "syscon";
    reg = <0x01c00000 0xd0>;
    #address-cells = <1>;
    #size-cells = <1>;
    ranges;

    sram_c: sram@1d00000 {
        compatible = "mmio-sram";
        reg = <0x01d00000 0x80000>;
        #address-cells = <1>;
        #size-cells = <1>;
        ranges = <0 0x01d00000 0x80000>;

        ve_sram: sram-section@0 {
            compatible = "allwinner,sun8i-v3s-sram-c", "allwinner,sun4i-a10-sram-c1";
            reg = <0x000000 0x80000>;
        };
    };
};

cedarx: video-codec@1c0e000 {
    compatible = "allwinner,sun8i-v3-cedar";
    reg = <0x01c0e000 0x1000>;
    clocks = <&ccu CLK_BUS_VE>, <&ccu CLK_VE>, <&ccu CLK_DRAM_VE>;
    clock-names = "ahb", "mod", "ram";
    resets = <&ccu RST_BUS_VE>;
    interrupts = <GIC_SPI 58 IRQ_TYPE_LEVEL_HIGH>;
    allwinner,sram = <&ve_sram 1>;
    status = "disabled";
};
        
ion: ion {
    compatible = "allwinner,sunxi-ion";
    status = "disabled";
    heap_cma@0{
        compatible = "allwinner,cma";
        heap-name  = "cma";
        heap-id    = <0x4>;
        heap-base  = <0x0>;
        heap-size  = <0x0>;
        heap-type  = "ion_cma";
    };
};
```
### Demo for Allwinner F1C100s / F1C200s (untested)
```
sram-controller@1c00000 {
    compatible = "allwinner,suniv-f1c100s-system-control",
             "allwinner,sun4i-a10-system-control";
    reg = <0x01c00000 0x30>;
    #address-cells = <1>;
    #size-cells = <1>;
    ranges;

    sram_c: sram@1d00000 {
        compatible = "mmio-sram";
        reg = <0x01d00000 0x80000>;
        #address-cells = <1>;
        #size-cells = <1>;
        ranges = <0 0x01d00000 0x80000>;

        ve_sram: sram-section@0 {
            compatible = "allwinner,suniv-f1c100s-sram-c", "allwinner,sun4i-a10-sram-c1";
            reg = <0x000000 0x80000>;
        };
    };
};

cedarx: video-codec@1c0e000 {
    compatible = "allwinner,suniv-f1c100s-cedar";
    reg = <0x01c0e000 0x1000>;
    clocks = <&ccu CLK_BUS_VE>, <&ccu CLK_VE>, <&ccu CLK_DRAM_VE>;
    clock-names = "ahb", "mod", "ram";
    resets = <&ccu RST_BUS_VE>;
    interrupts = <34>;
    allwinner,sram = <&ve_sram 1>;
    status = "disabled";
};

ion: ion {
    compatible = "allwinner,sunxi-ion";
    status = "disabled";
    heap_cma@0{
        compatible = "allwinner,cma";
        heap-name  = "cma";
        heap-id    = <0x4>;
        heap-base  = <0x0>;
        heap-size  = <0x0>;
        heap-type  = "ion_cma";
    };
};
```
## Compile
### Enable Driver in 
```
> Device Drivers > Staging drivers > Media staging drivers
[*]   Allwinner sunXi family Video Devices
<*>     Allwinner CedarX Video Engine Driver
<*>     Allwinner CedarX Ion Driver 
```
### Config "DMA Contiguous Memory Allocator"
```
> Library routines
-*- DMA Contiguous Memory Allocator
*** Default contiguous memory area size: ***
(32)  Size in Mega Bytes
Selected region size (Use mega bytes value only)  --->
```
... and here we go.

## Debug
### ION_IOC_ALLOC error / memory alloc fail
Increase
```
CMA_AREAS
CMA_SIZE_MBYTES
```
### Default
Report in issue.
