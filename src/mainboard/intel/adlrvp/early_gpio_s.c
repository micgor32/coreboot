/* SPDX-License-Identifier: GPL-2.0-only */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <soc/gpio.h>

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
	PAD_CFG_GPO(GPP_H16, 1, DEEP), // CPU M.2 SSD Slot Power enable
	PAD_CFG_GPO(GPP_E5, 1, PLTRST),// CPU PCIE Graphics (PEG) Power Enable
	PAD_CFG_GPO(GPP_E1, 1, DEEP),  // PCH PCIE Slot 1 - X4 Connector Power enable
	PAD_CFG_GPO(GPP_H11, 1, DEEP), // PCH PCIE Slot 2 - X4 Connector Power enable
	PAD_CFG_GPO(GPP_B21, 1, DEEP), // PCH PCIE Slot 3 - X2 Connector Power enable
	PAD_CFG_GPO(GPP_K11, 1, DEEP), // PCH M.2 SSD Slot 1 Power enable
	PAD_CFG_GPO(GPP_B22, 1, DEEP), // PCH M.2 SSD Slot 2 Power enable,
	PAD_CFG_GPO(GPP_K2, 1, DEEP),  // PCH M.2 SSD Slot 3 Power enable
	PAD_CFG_GPO(GPP_E2, 1, DEEP),  // CPU PCIE (PEG) Slot 1 Reset
	PAD_CFG_GPO(GPP_F11, 1, DEEP), // PCH PCIE Slot 1 - X4 Connector Reset
	PAD_CFG_GPO(GPP_F12, 1, DEEP), // PCH PCIE Slot 2 - X4 Connector Reset
	PAD_CFG_GPO(GPP_F13, 1, DEEP), // PCH PCIE Slot 3 - X2 Connector Reset
	PAD_CFG_GPO(GPP_F18, 1, DEEP), // CPU M.2 SSD Reset
	PAD_CFG_GPO(GPP_C10, 1, DEEP), // PCH M.2 SSD Slot 1 Reset
	PAD_CFG_GPO(GPP_F16, 1, DEEP), // PCH M.2 SSD Slot 2 Reset
	PAD_CFG_GPO(GPP_B6, 1, DEEP),  // PCH M.2 SSD Slot 3 Reset

	PAD_CFG_NF(GPP_C0, NONE, DEEP, NF1), // SMBCLK ==> SMB CLK Resume (PCI Devices)
	PAD_CFG_NF(GPP_C1, NONE, DEEP, NF1), // SMBDATA ==> SMB DATA Resume (PCI Devices)
};

static const struct pad_config early_uart_gpio_table[] = {
	// UART2 is connected to USB2.0 Micro Debug Port
	// and therefore need's to be initialized early on
	PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1), // UART2_RXD
	PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1), // UART2_TXD
};

void variant_configure_early_gpio_pads(void)
{
	if (CONFIG(INTEL_LPSS_UART_FOR_CONSOLE))
		gpio_configure_pads(early_uart_gpio_table, ARRAY_SIZE(early_uart_gpio_table));

	gpio_configure_pads(early_gpio_table, ARRAY_SIZE(early_gpio_table));
}
