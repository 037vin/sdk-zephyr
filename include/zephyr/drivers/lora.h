/*
 * Copyright (c) 2019 Manivannan Sadhasivam
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_LORA_H_
#define ZEPHYR_INCLUDE_DRIVERS_LORA_H_

/**
 * @file
 * @brief Public LoRa APIs
 * @defgroup lora_api LoRa APIs
 * @ingroup io_interfaces
 * @{
 */

#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

enum lora_signal_bandwidth {
	BW_125_KHZ = 0,
	BW_250_KHZ,
	BW_500_KHZ,
};

enum lora_datarate {
	SF_6 = 6,
	SF_7,
	SF_8,
	SF_9,
	SF_10,
	SF_11,
	SF_12,
};

enum lora_coding_rate {
	CR_4_5 = 1,
	CR_4_6 = 2,
	CR_4_7 = 3,
	CR_4_8 = 4,
};

struct lora_modem_config {
	/* Frequency in Hz to use for transceiving */
	uint32_t frequency;

	/* The bandwidth to use for transceiving */
	enum lora_signal_bandwidth bandwidth;

	/* The data-rate to use for transceiving */
	enum lora_datarate datarate;

	/* The coding rate to use for transceiving */
	enum lora_coding_rate coding_rate;

	/* Length of the preamble */
	uint16_t preamble_len;

	/* TX-power in dBm to use for transmission */
	int8_t tx_power;

	/* Set to true for transmission, false for receiving */
	bool tx;

	/**
	 * Invert the In-Phase and Quadrature (IQ) signals. Normally this
	 * should be set to false. In advanced use-cases where a
	 * differentation is needed between "uplink" and "downlink" traffic,
	 * the IQ can be inverted to create two different channels on the
	 * same frequency
	 */
	bool iq_inverted;

	/**
	 * Sets the sync-byte to use:
	 *  - false: for using the private network sync-byte
	 *  - true:  for using the public network sync-byte
	 * The public network sync-byte is only intended for advanced usage.
	 * Normally the private network sync-byte should be used for peer
	 * to peer communications and the LoRaWAN APIs should be used for
	 * interacting with a public network.
	 */
	bool public_network;
};

/**
 * @cond INTERNAL_HIDDEN
 *
 * For internal driver use only, skip these in public documentation.
 */

/**
 * @typedef lora_recv_cb()
 * @brief Callback API for receiving data asynchronously
 *
 * @see lora_recv() for argument descriptions.
 */
typedef void (*lora_recv_cb)(const struct device *dev, uint8_t *data, uint16_t size,
			     int16_t rssi, int8_t snr);

/**
 * @typedef lora_api_config()
 * @brief Callback API for configuring the LoRa module
 *
 * @see lora_config() for argument descriptions.
 */
typedef int (*lora_api_config)(const struct device *dev,
			       struct lora_modem_config *config);

/**
 * @typedef lora_api_send()
 * @brief Callback API for sending data over LoRa
 *
 * @see lora_send() for argument descriptions.
 */
typedef int (*lora_api_send)(const struct device *dev,
			     uint8_t *data, uint32_t data_len);

/**
 * @typedef lora_api_send_async()
 * @brief Callback API for sending data asynchronously over LoRa
 *
 * @see lora_send_async() for argument descriptions.
 */
typedef int (*lora_api_send_async)(const struct device *dev,
				   uint8_t *data, uint32_t data_len,
				   struct k_poll_signal *async);

/**
 * @typedef lora_api_recv()
 * @brief Callback API for receiving data over LoRa
 *
 * @see lora_recv() for argument descriptions.
 */
typedef int (*lora_api_recv)(const struct device *dev, uint8_t *data,
			     uint8_t size,
			     k_timeout_t timeout, int16_t *rssi, int8_t *snr);

/**
 * @typedef lora_api_recv_async()
 * @brief Callback API for receiving data asynchronously over LoRa
 *
 * @param dev Modem to receive data on.
 * @param cb Callback to run on receiving data.
 */
typedef int (*lora_api_recv_async)(const struct device *dev, lora_recv_cb cb);

/**
 * @typedef lora_api_test_cw()
 * @brief Callback API for transmitting a continuous wave
 *
 * @see lora_test_cw() for argument descriptions.
 */
typedef int (*lora_api_test_cw)(const struct device *dev, uint32_t frequency,
				int8_t tx_power, uint16_t duration);

/**
 * @typedef lora_api_soft_reset()
 * @brief Callback API for calling SX126xSetFs() and SX126xSetRxBoosted(0)
 *
 * @see custom driver changes
 */
typedef int (*lora_api_soft_reset)(const struct device *dev);

/**
 * @typedef lora_api_write_register()
 * @brief Callback API for calling SX126xWriteRegister()
 *
 * @see custom driver changes
 */
typedef int (*lora_api_write_register)(const struct device *dev, uint16_t address, uint8_t value);

/**
 * @typedef lora_api_read_register()
 * @brief Callback API for calling SX126xReadRegister()
 *
 * @see custom driver changes
 */
typedef int (*lora_api_read_register)(const struct device *dev, uint16_t address);

/**
 * @typedef lora_api_hard_reset()
 * @brief Callback API for calling hard_reset()
 *
 * @see custom driver changes
 */
typedef int (*lora_api_hard_reset)(const struct device *dev);

/**
 * @typedef lora_api_set_channel()
 * @brief Callback API for setting the radio channel
 *
 * @see custom driver changes
 */
typedef int (*lora_api_set_channel)(const struct device *dev, uint32_t channel);

/**
 * @typedef lora_api_set_standby()
 * @brief Callback API for setting the radio into standby RC
 *
 * @see custom driver changes
 */
typedef int (*lora_api_set_standby)(const struct device *dev);

/**
 * @typedef lora_api_set_sleep()
 * @brief Callback API for setting the radio into sleep
 *
 * @see custom driver changes
 */
typedef int (*lora_api_set_sleep)(const struct device *dev);

/**
 * @typedef lora_api_wait_on_busy()
 * @brief Callback API for looping while the radio is busy
 *
 * @see custom driver changes
 */
typedef int (*lora_api_wait_on_busy)(const struct device *dev);

/**
 * @typedef lora_api_wake_up()
 * @brief Callback API for waking up the lora radio
 *
 * @see custom driver changes
 */
typedef int (*lora_api_wake_up)(const struct device *dev);

/**
 * @typedef lora_api_set_RX_continuous()
 * @brief Callback API for setting the radio into continuous RX mode
 *
 * @see custom driver changes
 */
typedef int (*lora_api_set_RX_continuous)(const struct device *dev);

struct lora_driver_api {
	lora_api_config config;
	lora_api_send send;
	lora_api_send_async send_async;
	lora_api_recv recv;
	lora_api_recv_async recv_async;
	lora_api_test_cw test_cw;
	lora_api_soft_reset soft_reset;
	lora_api_write_register write_register;
	lora_api_read_register read_register;
	lora_api_hard_reset hard_reset;
	lora_api_set_channel set_channel;
	lora_api_set_standby set_standby;
	lora_api_set_sleep set_sleep;
	lora_api_wait_on_busy wait_on_busy;
	lora_api_wake_up wake_up;
	lora_api_set_RX_continuous set_RX_continuous;
};
/** @endcond */

/**
 * @brief Wake up the LoRa modem
 *
 * @param dev     LoRa device
 * @return 0 no indicator
 */
static inline int lora_wake_up(const struct device *dev)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->wake_up(dev);
}

/**
 * @brief Set the LoRa modem wait on busy
 *
 * @param dev     LoRa device
 * @return 0 no indicator
 */
static inline int lora_wait_on_busy(const struct device *dev)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->wait_on_busy(dev);
}

/**
 * @brief Set the LoRa modem standby
 *
 * @param dev     LoRa device
 * @return 0 on success, negative on error
 */
static inline int lora_set_standby(const struct device *dev)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->set_standby(dev);
}

/**
 * @brief Set the LoRa modem sleep
 *
 * @param dev     LoRa device
 * @return 0 on success, negative on error
 */
static inline int lora_set_sleep(const struct device *dev)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->set_sleep(dev);
}

/**
 * @brief Set the LoRa modem channel
 *
 * @param dev     LoRa device
 * @return 0 on success, negative on error
 */
static inline int lora_set_channel(const struct device *dev, uint32_t freq)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->set_channel(dev, freq);
}

/**
 * @brief Read to the LoRa modem register
 *
 * @param dev     LoRa device
 * @return 0 on success, negative on error
 */
static inline int lora_hard_reset(const struct device *dev)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->hard_reset(dev);
}

/**
 * @brief Read to the LoRa modem register
 *
 * @param dev     LoRa device
 * @return 0 on success, negative on error
 */
static inline int lora_read_register(const struct device *dev, uint16_t address)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->read_register(dev, address);
}

/**
 * @brief Write to the LoRa modem register
 *
 * @param dev     LoRa device
 * @return 0 on success, negative on error
 */
static inline int lora_write_register(const struct device *dev, uint16_t address, uint8_t value)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->write_register(dev, address, value);
}

/**
 * @brief Soft reset the LoRa modem
 *
 * @param dev     LoRa device
 * @return 0 on success, negative on error
 */
static inline int lora_soft_reset(const struct device *dev)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->soft_reset(dev);
}

/**
 * @brief Configure the LoRa modem
 *
 * @param dev     LoRa device
 * @param config  Data structure containing the intended configuration for the
		  modem
 * @return 0 on success, negative on error
 */
static inline int lora_config(const struct device *dev,
			      struct lora_modem_config *config)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->config(dev, config);
}

/**
 * @brief Send data over LoRa
 *
 * @note This blocks until transmission is complete.
 *
 * @param dev       LoRa device
 * @param data      Data to be sent
 * @param data_len  Length of the data to be sent
 * @return 0 on success, negative on error
 */
static inline int lora_send(const struct device *dev,
			    uint8_t *data, uint32_t data_len)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->send(dev, data, data_len);
}

/**
 * @brief Asynchronously send data over LoRa
 *
 * @note This returns immediately after starting transmission, and locks
 *       the LoRa modem until the transmission completes.
 *
 * @param dev       LoRa device
 * @param data      Data to be sent
 * @param data_len  Length of the data to be sent
 * @param async A pointer to a valid and ready to be signaled
 *        struct k_poll_signal. (Note: if NULL this function will not
 *        notify the end of the transmission).
 * @return 0 on success, negative on error
 */
static inline int lora_send_async(const struct device *dev,
				  uint8_t *data, uint32_t data_len,
				  struct k_poll_signal *async)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->send_async(dev, data, data_len, async);
}

/**
 * @brief Receive data over LoRa
 *
 * @note This is a blocking call.
 *
 * @param dev       LoRa device
 * @param data      Buffer to hold received data
 * @param size      Size of the buffer to hold the received data. Max size
		    allowed is 255.
 * @param timeout   Duration to wait for a packet.
 * @param rssi      RSSI of received data
 * @param snr       SNR of received data
 * @return Length of the data received on success, negative on error
 */
static inline int lora_recv(const struct device *dev, uint8_t *data,
			    uint8_t size,
			    k_timeout_t timeout, int16_t *rssi, int8_t *snr)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->recv(dev, data, size, timeout, rssi, snr);
}

/**
 * @brief Receive data asynchronously over LoRa
 *
 * Receive packets continuously under the configuration previously setup
 * by @ref lora_config.
 *
 * Reception is cancelled by calling this function again with @p cb = NULL.
 * This can be done within the callback handler.
 *
 * @param dev Modem to receive data on.
 * @param cb Callback to run on receiving data. If NULL, any pending
 *	     asynchronous receptions will be cancelled.
 * @return 0 when reception successfully setup, negative on error
 */
static inline int lora_recv_async(const struct device *dev, lora_recv_cb cb)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->recv_async(dev, cb);
}

/**
 * @brief Transmit an unmodulated continuous wave at a given frequency
 *
 * @note Only use this functionality in a test setup where the
 * transmission does not interfere with other devices.
 *
 * @param dev       LoRa device
 * @param frequency Output frequency (Hertz)
 * @param tx_power  TX power (dBm)
 * @param duration  Transmission duration in seconds.
 * @return 0 on success, negative on error
 */
static inline int lora_test_cw(const struct device *dev, uint32_t frequency,
			       int8_t tx_power, uint16_t duration)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	if (api->test_cw == NULL) {
		return -ENOSYS;
	}

	return api->test_cw(dev, frequency, tx_power, duration);
}

/** @endcond */

/**
 * @brief Wake up the LoRa modem
 *
 * @param dev     LoRa device
 * @return 0 no indicator
 */
static inline int lora_set_RX_continuous(const struct device *dev)
{
	const struct lora_driver_api *api =
		(const struct lora_driver_api *)dev->api;

	return api->set_RX_continuous(dev);
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif	/* ZEPHYR_INCLUDE_DRIVERS_LORA_H_ */
