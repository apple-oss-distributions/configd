/*
 * Copyright (c) 2022 Apple Inc. All rights reserved.
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

#ifndef _CATEGORY_MANAGER_COMMON_H
#define _CATEGORY_MANAGER_COMMON_H

/*
 * CategoryManagerCommon.h
 */

/*
 * Modification History
 *
 * December 22, 2022	Dieter Siegmund (dieter@apple.com)
 * - initial revision
 */

#include <CoreFoundation/CoreFoundation.h>
#include "SCNetworkCategoryManager.h"

typedef CFDictionaryRef CategoryInformationRef;

CFStringRef
CategoryInformationGetCategory(CategoryInformationRef info);

CFStringRef
CategoryInformationGetValue(CategoryInformationRef info);

CFStringRef
CategoryInformationGetInterfaceName(CategoryInformationRef info);

SCNetworkCategoryManagerFlags
CategoryInformationGetFlags(CategoryInformationRef info);

#endif /* _CATEGORY_MANAGER_SERVER_H */
