import requests
import sys

url = "https://discord.com/api/webhooks/888820998428835850/313DEhurBm7xENgYNvEeED5hvA3a81tVerod-TZ5BFFVtm-WO-08JTVSQjt2tkU4lwpx"

data = {
    "username" : 'Beam Official API'
}

data["embeds"] = [
    {
        "description" : "Username: " + sys.argv[1] + "\n Host: " + sys.argv[2] + "\n Port: " + sys.argv[3] + "\n Time: " + sys.argv[4] + "\n Method: " + sys.argv[5],
        "title" : "API Attack Sent!"
    }
]

result = requests.post(url, json = data)

try:
    result.raise_for_status()
except requests.exceptions.HTTPError as err:
    print(err)
else:
    print("Webhook Sent!, Code {}".format(result.status_code))