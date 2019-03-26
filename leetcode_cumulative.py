import requests
import json

import datetime
import matplotlib.pyplot as plt
N = 162
# import datetime
# from datetime import datetime,timedelta
# import sys
# import os
# from urllib.request import Request
# from urllib.request import urlopen
# from urllib.error import URLError
# url = "https://jsonmock.hackerrank.com/api/movies/search?Title=spiderman&page="
# list = []
IndexString = "All My Submissions"
startString = "Language"
endString = "</tbody>"
id = 0


def deleteShadding(input):
    n = len(input)
    i = 0
    j = n - 1
    while (i < n and input[i] == ' '):
        i = i + 1
    while (j >= 0 and input[j] == ' '):
        j = j - 1
    return input[i:j + 1]


def dealwithTime(input):
    num = 0
    input = input[:-4]  # delete " ago"
    # print("dealwithTime:input = ", input)
    arr = input.split(' ')
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
        # print("item = ",item)
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
            num = float(item)

    now_time = datetime.datetime.now()
    now_time = datetime.datetime(2019, 3, 25, 18, 00, 0, 00000)
    # print("now_time =",now_time)
    _day = _day + 30 * _month
    _day = _day + 365 * _year
    prev_time = now_time - datetime.timedelta(days=_day, minutes=_minute, hours=_hour, weeks=_week)
    # print(prev_time)
    return prev_time

    # for i in range(hours):
    #     now_time -= datetime.timedelta(hours=1)
    # next_timestamp = now_time.strftime('%Y-%m-%d %H:%M:%S')
    # print
    # 'next_timestamp: ', next_timestamp
    # return next_timestamp
# global str
totalList = []
for pageId in range(1, N + 1):
    # print("pageId =", str(pageId))
    htmlName = "my_leetcode_data/Submissions - LeetCode" + str(pageId) + ".htm"
    # print("htmlName =",htmlName)
    f = open(htmlName, "r")
    wholeContent = f.read()
    startIndex = wholeContent.find(IndexString)
    startIndex = wholeContent.find(startString, startIndex)
    endIndex = wholeContent.find(endString, startIndex)
    # print("endIndex =",endIndex)
    singlePage = wholeContent[startIndex + len(startString): endIndex]

    prevIndex = 0
    circularindex = 0
    singleRecord = {}
    mylist = []
    for i in range(len(singlePage)):
        if singlePage[i] == '>':
            prevIndex = i + 1
        elif singlePage[i] == '<':
            if i > 0 and singlePage[i - 1] != '>':
                t = singlePage[prevIndex:i]
                if circularindex == 0:
                    singleRecord["time"] = dealwithTime(t)
                elif circularindex == 1:
                    singleRecord["question"] = deleteShadding(t)
                elif circularindex == 2:
                    singleRecord["status"] = t
                elif circularindex == 3:
                    singleRecord["runtime"] = t
                else:
                    singleRecord["language"] = t
                circularindex = circularindex + 1
                if circularindex == 5:
                    circularindex = 0
                    # mylist.append(singleRecord)
                    id = id + 1
                    singleRecord["id"] = id
                    # print(singleRecord, '\n')
                    totalList.append(singleRecord)
                    singleRecord = {}
totalList.reverse()
leetcode_q_cnt = 0
leetcode_q_done = []
leetcode_q_time = []
leetcode_q_culmulative = []

accepted_no = 0
for item in totalList:
    if item["status"] == "Accepted":
        accepted_no = accepted_no + 1

print("total submissions =",id)
print("accepted submissions =",accepted_no)
DataBaseQ = ["Big Countries","Shortest Distance in a Line","Swap Salary","Find Customer Referee","Not Boring Movies",\
             "Triangle Judgement","Consecutive Available Seats","Sales Person","Duplicate Emails",\
             "Combine Two Tables","Employees Earning More Than Their Managers","Customers Who Never Order",\
             "Biggest Single Number","Classes More Than 5 Students","Rising Temperature","Delete Duplicate Emails",\
             "Second Highest Salary","Tree Node","Count Student Number in Departments","Consecutive Numbers"]
ShellQ = ["Valid Phone Numbers","Tenth Line"]

for item in totalList:
    if item["question"] not in leetcode_q_done and item["status"] == "Accepted"\
            and item["question"] not in DataBaseQ and item["question"] not in ShellQ:
        leetcode_q_done.append(item["question"])
        leetcode_q_cnt = leetcode_q_cnt + 1
        # time_dict = {}
        # time_dict["time"] = item["time"]
        # time_dict["num"] = leetcode_q_cnt
        leetcode_q_time.append(item["time"])
        if leetcode_q_cnt % 100 == 0:
            print("leetcode_q_cnt =",leetcode_q_cnt," , Time =",item["time"])
        leetcode_q_culmulative.append(leetcode_q_cnt)

# for item in leetcode_q_time:
#     print(item)
# for item in leetcode_q_done:
    # print(item)
print("Total Done in Algorithms :",len(leetcode_q_done))
print("leetcode_q_cnt =",leetcode_q_cnt)

plt.plot(leetcode_q_time,leetcode_q_culmulative,'r')
plt.xlabel('TIME')
plt.ylabel('LEETCODE_ALGORITHMS_WORKED_OUT')
plt.grid()
plt.show()
# results["data"] = totalList
# with open('results.json', 'w') as result_file:
#     json.dump(results, result_file)

# print(f.read())
# for i in range(10):
#     URL = url + t(i + 1)
#     response = requests.get(URL,params = {},headers = [])
#     json_response = response.json()
#     data = json_response['data']
#     for j in range(len(data)):
#         list.append(data[j]['Title'])
#     if(len(data) < 10):
#         break
# list.sort()
# for title in list:
#     print (title)
# response = requests.get(URL,params = {},headers = [])
# json_response = response.json()
# print(response.content)
