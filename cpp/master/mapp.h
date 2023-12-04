#pragma once

#include "dexport.h"
#include "rfunction.h"

//lifecycle of an application:
//
//  launch ->
//  resume -> update... -> pause ->
//  resume -> update... -> pause ->
//  ...
//

//these functions should be invoked by host.
d_exportable void _MAppResume();
d_exportable void _MAppUpdate();
d_exportable void _MAppPause ();

d_exportable void MAppAddResumeListener(const reflect::function<void ()>::ptr &listener);
d_exportable void MAppAddUpdateListener(const reflect::function<void ()>::ptr &listener);
d_exportable void MAppAddPauseListener (const reflect::function<void ()>::ptr &listener);
