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

#include "../inc/control_main.h"
#include <nuttx/timers/pwm.h>

#define CONTROL_SLEEP 200 // ms

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * controller_main
 ****************************************************************************/

int control_main(int argc, FAR char *argv[])
{
  struct pwm_info_s info;
  int fd = open("/dev/pwm0", O_RDWR);
  info.frequency = 1000;
  info.channels[1].duty = 1;
  int ret = ioctl(fd, PWMIOC_SETCHARACTERISTICS,
              (unsigned long)((uintptr_t)&info));

  ret = ioctl(fd, PWMIOC_START, 0);
  while(1)
  {
    printf("Duty 1  %ld\n", info.channels[1].duty);
    ret = ioctl(fd, PWMIOC_GETCHARACTERISTICS,
              (unsigned long)((uintptr_t)&info));
    info.channels[1].duty += 100;
    ret = ioctl(fd, PWMIOC_SETCHARACTERISTICS,
            (unsigned long)((uintptr_t)&info));
    printf("Controller App OK\t%ld\n", g_system_ticks);
    usleep(CONTROL_SLEEP*1000);
  }
  return 0;
}
