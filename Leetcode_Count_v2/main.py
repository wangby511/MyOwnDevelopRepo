import matplotlib.pyplot as plt
from util import *

indexString = "All My Submissions"
startString = "Language"
endString = "</tbody>"
ACCEPTED = "Accepted"
LOG_FILE = 'log.txt'
TIME = 'time'
TITLE = 'title'
STATUS = 'status'
RUNTIME = 'runtime'
LANGUAGE = 'language'
ID = 'id'
log = open(LOG_FILE, "w")
id = 0
totalList = []

def querySinglePage(pageId):
    global id, totalList

    HTML_FILE_PATH = "my_leetcode_data/Submissions - LeetCode - " + str(pageId) + ".html"
    try:
        f = open(HTML_FILE_PATH, "r")
    except:
        print("File #.", pageId, "does not exist. Continue..." )
        return

    wholeContent = f.read()

    startIndex = wholeContent.find(indexString)
    startIndex = wholeContent.find(startString, startIndex)
    endIndex = wholeContent.find(endString, startIndex)
    singlePage = wholeContent[startIndex + len(startString): endIndex]

    prevIndex = 0
    circularIndex = 0
    singleRecord = {}
    for i in range(len(singlePage)):
        if singlePage[i] == '>':
            prevIndex = i + 1
        elif singlePage[i] == '<':
            if i > 0 and singlePage[i - 1] != '>':
                word = singlePage[prevIndex:i]
                if circularIndex == 0:
                    singleRecord[TIME] = retrieveRoughlySubmittedTime(word)
                elif circularIndex == 1:
                    singleRecord[TITLE] = word.strip()
                elif circularIndex == 2:
                    singleRecord[STATUS] = word
                elif circularIndex == 3:
                    singleRecord[RUNTIME] = word
                else:
                    singleRecord[LANGUAGE] = word
                circularIndex = circularIndex + 1
                if circularIndex == 5:
                    circularIndex = 0
                    id = id + 1
                    singleRecord[ID] = id
                    # print(singleRecord)
                    totalList.append(singleRecord)
                    singleRecord = {}

def makeGraph():
    global totalList
    totalList.reverse()

    leetcode_culmulative_accepted = 0
    leetcode_already_done = []
    leetcode_submitted_time = []
    leetcode_q_culmulative = []

    accepted_no = 0
    for item in totalList:
        if item[STATUS] == ACCEPTED:
            accepted_no = accepted_no + 1

    for item in totalList:
        if item[TITLE] not in leetcode_already_done and item[STATUS] == ACCEPTED:
            leetcode_already_done.append(item[TITLE])
            leetcode_culmulative_accepted = leetcode_culmulative_accepted + 1

            leetcode_submitted_time.append(item[TIME])
            if leetcode_culmulative_accepted % 100 == 0:
                print("leetcode_culmulative_accepted =", leetcode_culmulative_accepted, ", time =", item[TIME])

            leetcode_q_culmulative.append(leetcode_culmulative_accepted)
            log.write(str(item[TIME]) + " , " + item[TITLE] + '\n')

    print("Total Algorithms Solved:", len(leetcode_already_done))
    print("Total Accepted: ", accepted_no)
    print("Total Submissions:", len(totalList))

    plt.plot(leetcode_submitted_time, leetcode_q_culmulative, color='blue')
    plt.ylim((0, 1600))
    plt.xlabel('Calendar Time')
    plt.ylabel('Leetcode Problems Solved')
    plt.grid()
    plt.show()

def main():
    TOTAL_PAGE_NUMBER = 406
    for i in range(1, TOTAL_PAGE_NUMBER + 1):
        print("Processing page #.", i, "...")
        querySinglePage(i)

    print('\n')
    makeGraph()

main()
