from instagram.client import InstagramAPI

# access_token = "YOUR_ACCESS_TOKEN"
# client_secret = "YOUR_CLIENT_SECRET"
# api = InstagramAPI(access_token=access_token, client_secret=client_secret)
# recent_media, next_ = api.user_recent_media(user_id="userid", count=10)
# for media in recent_media:
#    print (media.caption.text)
import instaloader
import json
import requests
import time

from datetime import datetime
now_time_str = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
# # Login or load session
# USER = 'THIS IS YOUR ACCOUNT NAME'
# # PASSWORD = 'THIS IS YOUR PASSWORD'
# # L.login(USER, PASSWORD)        # (login)
# L.interactive_login(USER)      # (ask password on terminal)
# # L.load_session_from_file(USER) # (load session created w/
# # #                                #  `instaloader -l USERNAME`)
# # #
# # # Obtain profile metadata

def get_user_info(user_name):
    url = "https://www.instagram.com/" + user_name + "/?__a=1"
    try:
        r = requests.get(url)
    except requests.exceptions.ConnectionError:
        print ('Seems like dns lookup failed..')
        time.sleep(60)
        return None
    if r.status_code != 200:
        print ('User: ' + user_name + ' status code: ' + str(r.status_code))
        print (r)
        return None
    print(r.text)
    info = json.loads(r.text)
    return info


# Get instance
myInsLoader = instaloader.Instaloader()

# Login or load session
USER = 'boyuan0511'
PASSWORD = '.........' # ENTER PASSWORD HERE
myInsLoader.login(USER, PASSWORD)
# myInsLoader.interactive_login(USER)      # (ask password on terminal)
# myInsLoader.load_session_from_file(USER) # (load session created w/
# #                                #  `instaloader -l USERNAME`)
# #
# # Obtain profile metadata
myProfile = instaloader.Profile.from_username(myInsLoader.context, USER)

print("FOR INS ACCOUNT: ",USER)

f_followee = open(now_time_str + '_followees_list.txt','w')
# # Print list of followees
total_followees = []
for followee in myProfile.get_followees():
    # print(followee.username)
    f_followee.write(followee.username + "\n")
    total_followees.append(followee.username)
print("TOTAL FOLLOWEES NUMBER:",len(total_followees))


total_followers = []
f_follower = open(now_time_str + '_followers_list.txt','w')
for follower in myProfile.get_followers():
    # print(follower.username)
    f_follower.write(follower.username + "\n")
    total_followers.append(follower.username)
print("TOTAL FOLLOWERS NUMBER:",len(total_followers))

doubtLists = ['rou2551']

for user in doubtLists:
    try:
        profile = myProfile.from_username(myInsLoader.context, user)
        posts = profile.get_posts()
        # print("USER THAT MAY NOT FOLLOW YOU:", user)
    except Exception as ex:
        print("USER THAT MAY BLOCK YOU:",user)


# (likewise with profile.get_followers())
# /Library/Frameworks/Python.framework/Versions/3.7/bin/python3.7 /Users/wangboyuan/Desktop/2019Autumn/INSTAGRAM/main.py
# FOR INS ACCOUNT:  boyuan0511
# TOTAL FOLLOWEES NUMBER: 192
# TOTAL FOLLOWERS NUMBER: 149
# JSON Query to rou2551/: Could not find "window._sharedData" in html response. [retrying; skip with ^C]
# JSON Query to rou2551/: Could not find "window._sharedData" in html response. [retrying; skip with ^C]
# USER THAT MAY BLOCK YOU: rou2551
#
# Process finished with exit code 0