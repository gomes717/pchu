/****************************************************************************
 * pchu_app/ina219/ina219_main.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "../inc/manager_main.h"
#include "../inc/control_main.h"
#include "../inc/odometry_main.h"
#include "../inc/power_main.h"
#include "../inc/comm_main.h"

#define MANAGER_SLEEP 200 // ms

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * controller_main
 ****************************************************************************/

int main(int argc, FAR char *argv[])
{

  task_create("Communication App", 100, 2048, comm_main, NULL);
  task_create("Control App", 100, 2048, control_main, NULL);
  task_create("Odometry App", 100, 2048, odometry_main, NULL);
  task_create("Power App", 100, 2048, power_main, NULL);
  while(1)
  {
    printf("Manager App OK\t%ld\n", g_system_ticks);
    usleep(MANAGER_SLEEP*1000);
  }
  return 0;
}
