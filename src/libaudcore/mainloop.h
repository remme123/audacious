/*
 * mainloop.h
 * Copyright 2014 John Lindgren
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions, and the following disclaimer in the documentation
 *    provided with the distribution.
 *
 * This software is provided "as is" and without any warranty, express or
 * implied. In no event shall the authors be liable for any damages arising from
 * the use of this software.
 */

/* Main loop abstraction layer which can use either GLib or Qt as a backend.
 * The API is completely thread-safe and can thus be used as a means to call
 * back into the main thread from a worker thread. */

#ifndef LIBAUDCORE_MAINLOOP_H
#define LIBAUDCORE_MAINLOOP_H

#include "tinylock.h"

// all instances must be declared static
class QueuedFunc
{
public:
    typedef void (* Func) (void * data);

    void queue (Func func, void * data);
    void cancel ();

    // implementation detail, do not call
    void run ();

private:
    TinyLock lock;
    Func stored_func;
    void * stored_data;
};

// all instances must be declared static
class TimedFunc
{
public:
    typedef void (* Func) (void * data);

    void start (int interval_ms, Func func, void * data);
    void stop ();

    // implementation detail, do not call
    void run ();

private:
    TinyLock lock;
    Func stored_func;
    void * stored_data;
    void * impl;
};

void mainloop_run ();
void mainloop_quit ();

#endif // LIBAUDCORE_MAINLOOP_H
