import datetime

def retrieveRoughlySubmittedTime(inputTime):
    num = 0
    copyString = inputTime
    inputTime = inputTime.replace('ago', '')
    inputTime.strip()

    arr = inputTime.split(',')
    arr_copy = []
    for item in arr:
        temp = item.split("&nbsp;")
        for it in temp:
            arr_copy.append(it)

    _year = 0
    _month = 0
    _week = 0
    _minute = 0
    _day = 0
    _hour = 0

    for item in arr_copy:
        if item.find("year") != -1:
            _year = num
        elif item.find("month") != -1:
            _month = num
        elif item.find("week") != -1:
            _week = num
        elif item.find("day") != -1:
            _day = num
        elif item.find("hour") != -1:
            _hour = num
        elif item.find("minute") != -1:
            _minute = num
        else:
            num = int(item)

    # current_time = datetime.datetime.now()
    current_time = datetime.datetime(2023, 9, 17, 0, 00, 0, 00000)

    # _day = _day + 7 * _week # Not needed since timedelta has already contained this parameter below
    _day = _day + 30 * _month
    _day = _day + 365 * _year
    submitted_time = current_time - datetime.timedelta(days=_day, minutes=_minute, hours=_hour, weeks=_week)
    # print(submitted_time)
    return submitted_time

# print(retrieveRoughlySubmittedTime("11&nbsp;months, 2&nbsp;weeks ago"))