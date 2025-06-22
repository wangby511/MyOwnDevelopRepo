import matplotlib.pyplot as plt
import datetime

INDEX_STRING = "<div class=\"flex flex-col items-start\">"
DATE_FORMAT = "<span class=\"text-xs text-label-2 dark:text-dark-label-2\" data-state=\"closed\">"
END_STRING = "<div class=\"flex flex-shrink-0 items-center\" style=\"width: 92px;\">"
ACCEPTED = "Accepted"
LOG_FILE = 'log.txt'
NEVER_SOLVED = -1001
NEVER_TOUCHED = -2000
DATABASE_PROBLEMS = [175, 176, 180, 181, 182, 183, 196, 197, 511, 512,
                     570, 580, 584, 595, 596, 603, 607, 608, 610, 613, 619, 620, 627]
SHELL_PROBLEMS = [192, 193, 194, 195]
CONCURRENCY_PROBLEMS = [1114, 1115, 1116, 1117, 1188, 1195, 1226, 1242, 1279]
total_submissions = 0


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
    month_to_number_map = {'Jan': 1, 'Feb': 2, 'Mar': 3, 'Apr': 4, 'May': 5, 'Jun': 6,
                           'Jul': 7, 'Aug': 8, 'Sep': 9, 'Oct': 10, 'Nov': 11, 'Dec': 12}
    month_in_english = date_string[0: 2 + 1]
    month = month_to_number_map[month_in_english]
    day = int(date_string[4: 5 + 1])
    year = int(date_string[8: 11 + 1])
    formatted_time = datetime.datetime(year, month, day, 0, 0, 0, 0)
    return formatted_time


class LeetcodeProblemResult:
    def __init__(self, number_id, accepted_date_list, errors):
        self.number_id = number_id
        self.accepted_date_list = accepted_date_list
        self.total_error_times = errors
        self.total_submissions = len(accepted_date_list) + errors

    def __lt__(self, other):
        if len(self.accepted_date_list) == 0 or len(other.accepted_date_list) == 0:
            return True

        if self.accepted_date_list[-1] < other.accepted_date_list[-1]:
            return True
        elif self.accepted_date_list[-1] == other.accepted_date_list[-1]:
            return self.number_id < other.number_id
        return False


def query_single_page(page_id):
    html_file_path = "my_leetcode_data/" + str(page_id) + ".html"
    try:
        f = open(html_file_path, "r")
    except FileNotFoundError:
        print("File #", page_id, "does not exist. The Leetcode #", str(page_id), "was never touched. Continue...")
        return LeetcodeProblemResult(page_id, [], 0)

    whole_content = f.read()

    split_strings = whole_content.split(INDEX_STRING)
    accepted_date_list = []
    other_status = []
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
            other_status.append(status)
            continue
        date = contents[6]

        """
        E.g. Accepted Aug 15, 2023
        """
        formatted_time = parse_date(date)
        accepted_date_list.append(formatted_time)
    return LeetcodeProblemResult(page_id, accepted_date_list, len(other_status))


def is_algorithm_problem(index):
    if index in DATABASE_PROBLEMS:
        return False
    if index in SHELL_PROBLEMS:
        return False
    if index in CONCURRENCY_PROBLEMS:
        return False
    return True


DATES_IN_SEATTLE = [[parse_date('Jan 01, 2020'), parse_date('Jun 15, 2022')]]

# if parse_date('Nov 26, 2020') <= date <= parse_date('Nov 30, 2021'):  # 2020 BayArea - 2
#     return False
# # if parse_date('May 22, 2021') <= date <= parse_date('May 30, 2021'):  # 2021 BayArea - 1
# #     return False
# # if parse_date('Oct 16, 2021') <= date <= parse_date('Oct 18, 2021'):  # First 395 Hwy Road Trip
# #     return False
# # if parse_date('Nov 25, 2021') <= date <= parse_date('Nov 28, 2021'):  # San Diego
# #     return False
# # if parse_date('Dec 25, 2021') <= date <= parse_date('Jan 01, 2021'):  # 2021 BayArea - 2
# #     return False
# # if parse_date('May 07, 2022') <= date <= parse_date('May 10, 2022'):  # 2022 BayArea - 1
# #     return False
# return True


def main():
    start = 1
    end = 2500
    leetcode_never_touched = []
    leetcode_attempted = []
    leetcode_first_solved_time = []
    leetcode_result_struct_list = []
    algorithm_only = False

    for i in range(start, end + 1):
        if algorithm_only:
            if not is_algorithm_problem(i):
                continue
        leetcode_result_struct = query_single_page(i)
        if leetcode_result_struct.total_submissions == 0:
            leetcode_never_touched.append(i)
            continue
        if len(leetcode_result_struct.accepted_date_list) == 0:
            print("The Leetcode #" + str(i) + " was attempted/never solved.")
            leetcode_attempted.append(i)
            continue
        first_accepted_date = leetcode_result_struct.accepted_date_list[-1]
        print("The Leetcode #" + str(i) + " was firstly solved at time " + str(first_accepted_date) +
              ". Total submission times: " + str(leetcode_result_struct.total_submissions) + ".")
        leetcode_first_solved_time.append(first_accepted_date)
        leetcode_result_struct_list.append(leetcode_result_struct)

    # Pre-generate the plot list
    leetcode_first_solved_time.sort()
    leetcode_cumulative = []
    for i in range(len(leetcode_first_solved_time)):
        leetcode_cumulative.append(i + 1)
    print("Total solved count: " + str(len(leetcode_first_solved_time)) + "\n")

    leetcode_result_struct_list.sort()
    print("Cumulative Date: ")
    count = 1
    total_solved_in_certain_period = dict()
    for leetcode_result_struct in leetcode_result_struct_list:
        print(str(leetcode_result_struct.accepted_date_list[-1]) + ", id=" + str(leetcode_result_struct.number_id) +
              ", cumulative count: " + str(count))
        count = count + 1
        for accepted_date in leetcode_result_struct.accepted_date_list:
            if accepted_date not in total_solved_in_certain_period:
                total_solved_in_certain_period[accepted_date] = set()
            total_solved_in_certain_period[accepted_date].add(leetcode_result_struct.number_id)

    total_solved_in_certain_period = sorted(total_solved_in_certain_period.items(), key=lambda item: item[0])
    max_problems_per_day = 0
    max_problems_day = None
    for date, ids in total_solved_in_certain_period:
        print("Solved " + str(len(ids)) + " problems during day " + str(date) + ": " + str(ids))
        if len(ids) > max_problems_per_day:
            max_problems_per_day = len(ids)
            max_problems_day = date

    print("Maximum: Solving " + str(max_problems_per_day) + " problems during day " + str(max_problems_day) + ".")

    plot = True
    if not plot:
        return
    plt.figure(figsize=(18, 9))
    date_range_list = leetcode_first_solved_time
    y_curve_list = leetcode_cumulative
    plt.plot(date_range_list, y_curve_list, color='blue')

    for segment in DATES_IN_SEATTLE:
        # --- Filter data for the fill_between region using list comprehension ---
        x_fill_list = []
        y_fill_list = []

        for i in range(len(date_range_list)):
            current_date = date_range_list[i]
            current_y = y_curve_list[i]

            if segment[0] <= current_date <= segment[1]:
                x_fill_list.append(current_date)
                y_fill_list.append(current_y)

        # --- Fill the area between x1 and x2, from y=0 to y_curve ---
        plt.fill_between(x_fill_list, y_fill_list, 0, color='lightblue', alpha=0.5)

    plt.ylim((0, count * 1.2))
    plt.xlabel('Calendar Time')
    plt.ylabel('Total Leetcode Problems Solved')
    plt.grid()
    plt.show()


main()
