/*
 * Copyright (c) 2000, 2001, 2003, 2010, 2011, 2013, 2016, 2018, 2020-2022 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*
 * Modification History
 *
 * May 19, 2001		Allan Nathanson <ajn@apple.com>
 * - initial revision
 */

#include "SCDynamicStoreInternal.h"
#include "config.h"		/* MiG generated file */

Boolean
SCDynamicStoreNotifyValue(SCDynamicStoreRef	store,
			  CFStringRef		key)
{
	SCDynamicStorePrivateRef	storePrivate;
	kern_return_t			status;
	CFDataRef			utfKey;		/* serialized key */
	xmlData_t			myKeyRef;
	CFIndex				myKeyLen;
	int				sc_status;

	if (!__SCDynamicStoreNormalize(&store, TRUE)) {
		return FALSE;
	}

	storePrivate = (SCDynamicStorePrivateRef)store;

	if (storePrivate->cache_active) {
		if (storePrivate->cached_notifys == NULL)  {
			storePrivate->cached_notifys = CFArrayCreateMutable(NULL,
									    0,
									    &kCFTypeArrayCallBacks);
		}

		if (!CFArrayContainsValue(storePrivate->cached_notifys,
					  CFRangeMake(0, CFArrayGetCount(storePrivate->cached_notifys)),
					  key)) {
			CFArrayAppendValue(storePrivate->cached_notifys, key);
		}

		return TRUE;
	}

	/* serialize the key */
	if (!_SCSerializeString(key, &utfKey, &myKeyRef, &myKeyLen)) {
		_SCErrorSet(kSCStatusFailed);
		return FALSE;
	}

    retry :

	/* send the key to the server */
	status = confignotify(storePrivate->server,
			      myKeyRef,
			      (mach_msg_type_number_t)myKeyLen,
			      (int *)&sc_status);

	if (__SCDynamicStoreCheckRetryAndHandleError(store,
						     status,
						     &sc_status,
						     "SCDynamicStoreNotifyValue confignotify()")) {
		goto retry;
	}

	/* clean up */
	CFRelease(utfKey);

	sc_status = __SCDynamicStoreMapInternalStatus(sc_status, TRUE);

	if (sc_status != kSCStatusOK) {
		_SCErrorSet(sc_status);
		return FALSE;
	}

	return TRUE;
}
