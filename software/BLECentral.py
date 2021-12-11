import requests
import json
import time
import bluepy.btle as btle

p = btle.Peripheral("13:99:9d:63:64:6a")
services=p.getServices()
s = p.getServiceByUUID(list(services)[2].uuid)
c = s.getCharacteristics()[0]
preFeedTime = time.time()
pretime = time.time()
interval = 10
feedFre = 12
amount = 1
cmdURL = "http://172.91.84.234:5000/getcmd"
sendURL = "http://172.91.84.234:5000/data"
resetURL = "http://172.91.84.234:5000/reset"
freURL = "http://172.91.84.234:5000/getFre"
amountURL = "http://172.91.84.234:5000/getAmount"
while True:
    #print("get cmd")
    curtime = time.time()
    if curtime - pretime > interval:
        data_byte = c.read()
        datas = data_byte.decode()
        headers = {'Content-Tpye':'application/json'}
        requests.post(url = sendURL, headers = headers, data = json.dumps(datas))
        pretime = time.time()
        print("sent data")
        print(datas)
    amount = requests.get(amountURL).json()
    feedFre = requests.get(freURL).json()
    
    if curtime - preFeedTime > feedFre*60*60:
        c.write(str(amount).encode(), True)
        print("Auto Feed", amount) 
        prefeedTime = time.time()
    
    cmd= requests.get(cmdURL).json()
    if not cmd == 0:
        c.write(str(cmd).encode(), True)
        print("Manually Feed ", cmd)
        requests.get(resetURL)
    time.sleep(1)
p.disconnect()
