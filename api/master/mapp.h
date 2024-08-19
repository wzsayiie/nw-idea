#pragma once

#include "rfunction.h"

//lifecycle of an application:
//
//  launch ->
//  resume -> update... -> pause ->
//  resume -> update... -> pause ->
//  ...
//

void MAppAddResumeListener(const reflect::function<void ()>::ptr &listener);
void MAppAddUpdateListener(const reflect::function<void ()>::ptr &listener);
void MAppAddPauseListener (const reflect::function<void ()>::ptr &listener);

void _MAppLaunch(); //low type: void ().
void _MAppResume(); //low type: void ().
void _MAppUpdate(); //low type: void ().
void _MAppPause (); //low type: void ().

void _MAppUpdateInterval(); //low type: double ().
