#ifndef __HIDUTILS_H
#define __HIDUTILS_H

#include "usbhid.h"

#define HID_KIND_INPUT          (1 << hid_input)
#define HID_KIND_OUTPUT         (1 << hid_output)
#define HID_KIND_FEATURE        (1 << hid_feature)
#define HID_KIND_COLLECTION     (1 << hid_collection)
#define HID_KIND_ENDCOLLECTION  (1 << hid_endcollection)
#define HID_KIND_ALL            (HID_KIND_INPUT         | \
                                 HID_KIND_OUTPUT        | \
                                 HID_KIND_FEATURE       | \
                                 HID_KIND_COLLECTION    | \
                                 HID_KIND_ENDCOLLECTION | \
                                 HID_KIND_OUTPUT)

/*
 * Fetch the report descriptor from the device given an fd for the
 * device's control endpoint. Descriptor length is written to the
 * rlen out paramter and a pointer to a malloc'ed buffer containing
 * the descriptor is returned. Returns NULL on failure.
 */
unsigned char* hidu_fetch_report_descriptor(int fd, int* rlen);

/*
 * Locate an item matching the given parameters. If found, the
 * item is copied to the supplied buffer. Returns true on success,
 * false on failure. Any of usage, app, phys, logical, and kind
 * may be set to -1 for "don't care".
 */
int hidu_locate_item(report_desc_t rdesc, int usage, int app, int phys,
                     int logical, int kind, hid_item_t* outitem);

/*
 * Fetch a report from a device given an fd for the device's control
 * endpoint, the populated item structure describing the report, and
 * a data buffer in which to store the result. Returns report length
 * (in bytes) on success and -1 on failure.
 */
int hidu_get_report(int fd, hid_item_t* item, unsigned char* data);

/*
 * Send a report to the device given an fd for the device's control
 * endpoint, the populated item structure, and the data to send. 
 * Returns true on success, false on failure.
 */
int hidu_set_report(int fd, hid_item_t* item, unsigned char* data);

/*
 * Fetch a string descriptor from the device given an fd for the
 * device's control endpoint and the string index. Returns a pointer
 * to a static buffer containing the NUL-terminated string or NULL
 * on failure.
 */
const char* hidu_get_string(int fd, int index);


#endif