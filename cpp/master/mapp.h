#pragma once

#include "rfunction.h"

//lifecycle of an application:
//
//  launch ->
//  resume -> update... -> pause ->
//  resume -> update... -> pause ->
//  ...
//

//these functions should be invoked by host:
void _MAppLaunch();
void _MAppResume();
void _MAppUpdate();
void _MAppPause ();

double _MAppUpdateInterval();

void MAppAddResumeListener(const reflect::function<void ()>::ptr &listener);
void MAppAddUpdateListener(const reflect::function<void ()>::ptr &listener);
void MAppAddPauseListener (const reflect::function<void ()>::ptr &listener);
