import matplotlib.pyplot as plt
import datetime

INDEX_STRING = "<div class=\"flex flex-col items-start\">"
DATE_FORMAT = "<span class=\"text-xs text-label-2 dark:text-dark-label-2\" data-state=\"closed\">"
END_STRING = "<div class=\"flex flex-shrink-0 items-center\" style=\"width: 92px;\">"
ACCEPTED = "Accepted"
LOG_FILE = 'log.txt'


def split_string_with_angle_bracket(original_string):
    result = []
    split_strings = original_string.split('<')
    for split_string in split_strings:
        further_split_strings = split_string.split('>')
        for further_split_string in further_split_strings:
            if len(further_split_string) != 0:
                result.append(further_split_string)
    return result


def parse_date(date_string):
    month_to_number_map = {'Jan': 1, 'Feb': 2, 'Mar': 3, 'Apr': 4, 'May': 5, 'Jun': 6, 'Jul': 7, 'Aug': 8, 'Sep': 9,
                           'Oct': 10, 'Nov': 11, 'Dec': 12}
    month_in_english = date_string[0: 2 + 1]
    month = month_to_number_map[month_in_english]
    day = int(date_string[4: 5 + 1])
    year = int(date_string[8: 11 + 1])
    formatted_time = datetime.datetime(year, month, day, 0, 0, 0, 0)
    return formatted_time


def query_single_page(page_id):

    html_file_path = "my_leetcode_data/" + str(page_id) + ".html"
    try:
        f = open(html_file_path, "r")
    except FileNotFoundError:
        print("File #", page_id, "does not exist. Continue...")
        return []

    whole_content = f.read()

    split_strings = whole_content.split(INDEX_STRING)
    accepted_times = []
    for split_string in split_strings:
        if split_string.find(DATE_FORMAT) == -1:
            continue
        end_index = split_string.find(END_STRING)
        fixed_content = split_string[0: end_index]

        contents = split_string_with_angle_bracket(fixed_content)
        """
        contents:
        ['div class="truncate text-green-s dark:text-dark-green-s"',
         'span class="text-green-s dark:text-dark-green-s text-sm font-medium opacity-40"', 'Accepted', '/span', '/div',
         'span class="text-xs text-label-2 dark:text-dark-label-2" data-state="closed"', 'Aug 15, 2023', '/span',
         '/div', '/div']
        """
        status = contents[2]
        if status != ACCEPTED:
            continue
        date = contents[6]

        """
        Accepted Aug 15, 2023
        """
        formatted_time = parse_date(date)
        accepted_times.append(formatted_time)
    return accepted_times


def main():
    start = 1
    end = 100
    leetcode_submitted_time = []
    for i in range(start, end + 1):
        accepted_dates = query_single_page(i)
        if len(accepted_dates) == 0:
            continue
        first_accepted_date = accepted_dates[-1]
        print("The Leetcode #", i, "was first resolved at the time", first_accepted_date)
        leetcode_submitted_time.append(first_accepted_date)

    leetcode_submitted_time.sort()
    leetcode_cumulative = []
    for i in range(len(leetcode_submitted_time)):
        leetcode_cumulative.append(i + 1)

    plt.plot(leetcode_submitted_time, leetcode_cumulative, color='blue')
    # plt.ylim((0, 1600))
    plt.xlabel('Calendar Time')
    plt.ylabel('Leetcode Problems Solved')
    plt.grid()
    plt.show()


main()
