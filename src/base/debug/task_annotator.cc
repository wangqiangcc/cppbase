// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/debug/task_annotator.h"

#include "base/debug/alias.h"
#include "base/pending_task.h"

namespace base {
namespace debug {

TaskAnnotator::TaskAnnotator() {
}

TaskAnnotator::~TaskAnnotator() {
}

void TaskAnnotator::DidQueueTask(const char* queue_function,
                                 const PendingTask& pending_task) {

}

void TaskAnnotator::RunTask(const char* queue_function,
                            const PendingTask& pending_task) {

  // Before running the task, store the program counter where it was posted
  // and deliberately alias it to ensure it is on the stack if the task
  // crashes. Be careful not to assume that the variable itself will have the
  // expected value when displayed by the optimizer in an optimized build.
  // Look at a memory dump of the stack.
  const void* program_counter = pending_task.posted_from.program_counter();
  debug::Alias(&program_counter);

  pending_task.task.Run();
}

uint64_t TaskAnnotator::GetTaskTraceID(const PendingTask& task) const {
  return (static_cast<uint64_t>(task.sequence_num) << 32) |
         ((static_cast<uint64_t>(reinterpret_cast<intptr_t>(this)) << 32) >>
          32);
}

}  // namespace debug
}  // namespace base
