#!/usr/bin/python
# -*- coding=utf-8 -*-
# this is what 
from datetime import datetime  as dt
from datetime import timedelta
from pytz import timezone
import pytz
import time
import datetime
import sys
# 根据时间戳与时区值 返回此时间戳在此时区下的时间
def get_time( ts, time_zone ):
    print("current ts:", ts)
    str_tz = 'Etc/GMT' + time_zone
    dd = dt.fromtimestamp(ts, pytz.timezone('Etc/GMT-8'))
    str_time = dd.strftime("%Y-%m-%d %H:%M:%S")
    print("current time:%s",str_time )
    print("change timezone:%s", str_tz)
    dd = dt.fromtimestamp(ts, pytz.timezone(str_tz))
    str_time = dd.strftime("%Y-%m-%d %H:%M:%S")
    print("target time::%s", str_time)

if __name__ == '__main__':
    get_time(1487185259, sys.argv[1])
    pass
