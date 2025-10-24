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

#include "../inc/power_main.h"
#include <nuttx/sensors/ina219.h>

#define POWER_SLEEP 200 // ms

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * power_main
 ****************************************************************************/

int power_main(int argc, FAR char *argv[])
{
  struct ina219_s sample;
  int fd;
  int ret;
  uint8_t i = 0;
  
  printf("Power App OK\n");

  fd = open("/dev/voltamp0", O_RDWR);
  while (1)
    {
      ret = read(fd, &sample, sizeof(sample));
      if (ret != sizeof(sample))
      {
        break;
      }

      printf("U=%12" PRIu32 " uV I=%12" PRId32 " uA\n",
             sample.voltage, sample.current);
      
      usleep(POWER_SLEEP*1000);
    }

  close(fd);
  return 0;
}
