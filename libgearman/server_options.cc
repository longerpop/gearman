/*  vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
 * 
 *  Gearmand client and server library.
 *
 *  Copyright (C) 2013 Data Differential, http://datadifferential.com/
 *  Copyright (C) 2013 Keyur Govande
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *      * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *      * Redistributions in binary form must reproduce the above
 *  copyright notice, this list of conditions and the following disclaimer
 *  in the documentation and/or other materials provided with the
 *  distribution.
 *
 *      * The names of its contributors may not be used to endorse or
 *  promote products derived from this software without specific prior
 *  written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * @file
 * @brief Server options
 */

#include "gear_config.h"
#include <libgearman/common.h>

#include "libgearman/server_options.hpp"

gearman_server_options_st::gearman_server_options_st(gearman_universal_st &universal_arg,
                                                     const char* option_arg, const size_t option_arg_size) : 
  next(NULL),
  prev(NULL),
  option(option_arg), 
  option_length(option_arg_size),
  universal(universal_arg)
{
  if (universal.server_options_list)
  {
    universal.server_options_list->prev= this;
  }
  next= universal.server_options_list;
  universal.server_options_list= this;
}

gearman_server_options_st::~gearman_server_options_st()
{
  if (option)
  {
    free((void*)option);
  }

  { // Remove from universal list
    if (universal.server_options_list == this)
    {
      universal.server_options_list= next;
    }

    if (prev)
    {
      prev->next= next;
    }

    if (next)
    {
      next->prev= prev;
    }
  }
}
