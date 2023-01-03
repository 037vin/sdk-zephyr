/*
 * Generated using zcbor version 0.6.0
 * https://github.com/NordicSemiconductor/zcbor
 * Generated with a --default-max-qty of 99
 */

#ifndef LWM2M_SENML_CBOR_TYPES_H__
#define LWM2M_SENML_CBOR_TYPES_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "zcbor_encode.h"

/** Which value for --default-max-qty this file was created with.
 *
 *  The define is used in the other generated file to do a build-time
 *  compatibility check.
 *
 *  See `zcbor --help` for more information about --default-max-qty
 */
#define DEFAULT_MAX_QTY 99

struct record_bn {
	struct zcbor_string _record_bn;
};

struct record_bt {
	int64_t _record_bt;
};

struct record_n {
	struct zcbor_string _record_n;
};

struct record_t {
	int64_t _record_t;
};

struct record_union_ {
	union {
		struct {
			int64_t _union_vi;
		};
		struct {
			double _union_vf;
		};
		struct {
			struct zcbor_string _union_vs;
		};
		struct {
			bool _union_vb;
		};
		struct {
			struct zcbor_string _union_vd;
		};
		struct {
			struct zcbor_string _union_vlo;
		};
	};
	enum {
		_union_vi,
		_union_vf,
		_union_vs,
		_union_vb,
		_union_vd,
		_union_vlo,
	} _record_union_choice;
};

struct value_ {
	union {
		struct zcbor_string _value_tstr;
		struct zcbor_string _value_bstr;
		int64_t _value_int;
		double _value_float;
		bool _value_bool;
	};
	enum {
		_value_tstr,
		_value_bstr,
		_value_int,
		_value_float,
		_value_bool,
	} _value_choice;
};

struct key_value_pair {
	int32_t _key_value_pair_key;
	struct value_ _key_value_pair;
};

struct record__key_value_pair {
	struct key_value_pair _record__key_value_pair;
};

struct record {
	struct record_bn _record_bn;
	uint_fast32_t _record_bn_present;
	struct record_bt _record_bt;
	uint_fast32_t _record_bt_present;
	struct record_n _record_n;
	uint_fast32_t _record_n_present;
	struct record_t _record_t;
	uint_fast32_t _record_t_present;
	struct record_union_ _record_union;
	uint_fast32_t _record_union_present;
	struct record__key_value_pair _record__key_value_pair[5];
	uint_fast32_t _record__key_value_pair_count;
};

struct lwm2m_senml {
	struct record _lwm2m_senml__record[99];
	uint_fast32_t _lwm2m_senml__record_count;
};

#endif /* LWM2M_SENML_CBOR_TYPES_H__ */
